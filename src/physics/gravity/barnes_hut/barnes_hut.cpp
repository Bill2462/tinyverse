#include "barnes_hut.hpp"

BarnesHutGravitySolver::BarnesHutGravitySolver(const Vectors3D& position, const Vector& mass,
Real G, bool use_softening, Real softening_epsilon, Real max_universe_size, Real theta):
    position(&position),
    mass(&mass),
    G(G),
    use_softening(use_softening),
    softening_epsilon(softening_epsilon),
    nbody(position.rows()),
    max_universe_size(max_universe_size),
    theta(theta),
    universe_bottom_left_corner({-max_universe_size/2, -max_universe_size/2, -max_universe_size/2})
{
    construct_tree();
}

void BarnesHutGravitySolver::rebuild_tree()
{
    destroy_tree();
    construct_tree();
}

TreeNode* BarnesHutGravitySolver::get_empty_node()
{
    if(nodes_in_use_counter == node_pool.size())
    {
        node_pool.push_back(std::make_shared<TreeNode>());
        nodes_in_use_counter++;
        return node_pool.back().get();
    }
    return node_pool[nodes_in_use_counter++].get();
}

void BarnesHutGravitySolver::destroy_tree()
{
    nodes_in_use_counter = 0;
    
    for(auto it=node_pool.begin(); it!=node_pool.end(); it++)
        (*it).get()->reset();
}

void BarnesHutGravitySolver::construct_tree()
{
    // Initialize tree root.
    tree_root = get_empty_node();

    tree_root->bottom_left_corner = universe_bottom_left_corner;
    tree_root->cube_size = max_universe_size;
    add_children(tree_root);

    // Insert all bodies into the tree as long as they fit in the body.
    for(std::size_t i=0; i<nbody; i++)
    {
        const Vector3D<Real> body_pos = {
            (*position)(i, 0),
            (*position)(i, 1),
            (*position)(i, 2)
        };

        if(!is_inside_node(tree_root, body_pos))
            continue;
    
        const Real body_mass = (*mass)(i);

        // Insert body into the root to start the recursive algorithm.
        insert_body(tree_root, body_pos, body_mass, i);
    }
}

void BarnesHutGravitySolver::add_children(TreeNode* node)
{
    const Real children_cube_size = node->cube_size/2;

    // Creates nodes.
    for(int i=0; i<8; i++)
    {
        node->children[i] = get_empty_node();
        node->children[i]->cube_size = children_cube_size;
    }

    // Generate corner positions.
    node->children[0]->bottom_left_corner = node->bottom_left_corner;

    node->children[1]->bottom_left_corner = {
        node->bottom_left_corner.x,
        node->bottom_left_corner.y + children_cube_size,
        node->bottom_left_corner.z
    };

    node->children[2]->bottom_left_corner = {
        node->bottom_left_corner.x + children_cube_size,
        node->bottom_left_corner.y + children_cube_size,
        node->bottom_left_corner.z
    };

    node->children[3]->bottom_left_corner = {
        node->bottom_left_corner.x + children_cube_size,
        node->bottom_left_corner.y,
        node->bottom_left_corner.z
    };

    node->children[4]->bottom_left_corner = {
        node->bottom_left_corner.x,
        node->bottom_left_corner.y,
        node->bottom_left_corner.z + children_cube_size
    };

    node->children[5]->bottom_left_corner = {
        node->bottom_left_corner.x,
        node->bottom_left_corner.y + children_cube_size,
        node->bottom_left_corner.z + children_cube_size
    };

    node->children[6]->bottom_left_corner = {
        node->bottom_left_corner.x + children_cube_size,
        node->bottom_left_corner.y + children_cube_size,
        node->bottom_left_corner.z + children_cube_size
    };

    node->children[7]->bottom_left_corner = {
        node->bottom_left_corner.x + children_cube_size,
        node->bottom_left_corner.y,
        node->bottom_left_corner.z + children_cube_size
    };

    node->is_internal = true;
}

bool BarnesHutGravitySolver::is_inside_node(const TreeNode* node, const Vector3D<Real>& pos) const
{
    return (pos.x >= node->bottom_left_corner.x && pos.x <= (node->bottom_left_corner.x + node->cube_size)) &&
           (pos.y >= node->bottom_left_corner.y && pos.y <= (node->bottom_left_corner.y + node->cube_size)) &&
           (pos.z >= node->bottom_left_corner.z && pos.z <= (node->bottom_left_corner.z + node->cube_size));
}

void BarnesHutGravitySolver::insert_body(TreeNode* node, const Vector3D<Real>& pos, Real mass, std::size_t body_index)
{
    // If body is internal then update it's ceneter of mass and recursively go into the
    // appropriate quadrant.
    if(node->is_internal)
    {
        // Update center of mass.
        node->weighted_sum_of_mass = {
            node->weighted_sum_of_mass.x + pos.x*mass,
            node->weighted_sum_of_mass.y + pos.y*mass,
            node->weighted_sum_of_mass.z + pos.z*mass
        };
        node->mass += mass;
        node->center_of_mass = {
            node->weighted_sum_of_mass.x / node->mass,
            node->weighted_sum_of_mass.y / node->mass,
            node->weighted_sum_of_mass.z / node->mass
        };

        // Go into the appropriate quadrant.
        for(int i=0; i<8; i++)
        {
            if(is_inside_node(node->children[i], pos))
            {
                insert_body(node->children[i], pos, mass, body_index);
                return;
            }
        }
    }

    // If there is no body then insert it into the current node.
    if(node->body_index == -1)
    {
        node->mass = mass;
        node->body_index = body_index;
        
        // Initialize center of mass.
        node->weighted_sum_of_mass = {
            pos.x*mass,
            pos.y*mass,
            pos.z*mass
        };
        node->center_of_mass = pos;
        return;
    }

    // If there already is a body in the current node then construct children.
    // From now on this node becomes internal.
    add_children(node);

    // Now place body that is currently in the node and body that we want to add into
    // appropriate quadrants.

    // First place the currently existing body.
    // It's position is current center of mass of the body
    // It's mass is the current mass of the node.
    for(int i=0; i<8; i++)
    {
        if(is_inside_node(node->children[i], node->center_of_mass))
        {
            insert_body(node->children[i], node->center_of_mass, node->mass, node->body_index);
            break;
        }
    }

    // Update center of mass.
    node->weighted_sum_of_mass = {
            node->weighted_sum_of_mass.x + pos.x*mass,
            node->weighted_sum_of_mass.y + pos.y*mass,
            node->weighted_sum_of_mass.z + pos.z*mass
    };
    node->mass += mass;
    node->center_of_mass = {
            node->weighted_sum_of_mass.x / node->mass,
            node->weighted_sum_of_mass.y / node->mass,
            node->weighted_sum_of_mass.z / node->mass
    };

    // Now place the body that we are trying to add.
    // If the body that was previusly in this node was placed in the same children then
    // the children will be split further and procedure will continue recursively
    // until two bodies will be placed in the separate quadrants.
    for(int i=0; i<8; i++)
    {
        if(is_inside_node(node->children[i], pos))
        {
            insert_body(node->children[i], pos, mass, body_index);
            break;
        }
    }
}

Vector3D<Real> BarnesHutGravitySolver::compute_net_grawitational_force(std::size_t body_index) const
{
    // If body is not in the universe then just return zero force.
    const Vector3D<Real> body_pos = {
        (*position)(body_index, 0),
        (*position)(body_index, 1),
        (*position)(body_index, 2)
    };

    if(!is_inside_node(tree_root, body_pos))
       return {0, 0, 0};
    
    Vector3D<Real> force = {0,0,0};

    add_force(tree_root, body_pos, body_index, force);

    const Real body_mass = (*mass)(body_index);
    
    force.x *= static_cast<Real>(-1)*body_mass*G;
    force.y *= static_cast<Real>(-1)*body_mass*G;
    force.z *= static_cast<Real>(-1)*body_mass*G;
    
    return force;
}

void BarnesHutGravitySolver::add_force(const TreeNode* node, const Vector3D<Real>& pos,
std::size_t body_index, Vector3D<Real>& force) const
{
    // Compute distance and distance vector to the current nodes center of mass.
    const Vector3D<Real> distace_vec = {
        pos.x - node->center_of_mass.x,
        pos.y - node->center_of_mass.y,
        pos.z - node->center_of_mass.z,
     };
        
    const Real distance = distace_vec.norm2();

    // If node is internal then check if we should recursively got further down the tree.
    if(node->is_internal)
    {
        // If the value of s/d is larger than threshold then add explore gravity from the children.
        if(node->cube_size/distance > theta)
        {
            for(int i=0; i<8; i++)
                add_force(node->children[i], pos, body_index, force);

            return;
        }
    }
    else
    {
        if(node->body_index == static_cast<long long>(body_index))
            return;
        
        if(node->body_index == -1)
            return;
    }

    // Otherwise use nodes center of mass to compute gravity.
    Real a;
    if(use_softening)
    {
        Real div = softening_epsilon*softening_epsilon + distance*distance;
        div = sqrt(div*div*div);
        a = node->mass/div;
    }
    else
        a = node->mass/(distance*distance*distance);
    
    force.x += distace_vec.x*a;
    force.y += distace_vec.y*a;
    force.z += distace_vec.z*a;
}

GravitySolver::Type BarnesHutGravitySolver::get_type() const
{
    return GravitySolver::Type::BARNES_HUT;
}
