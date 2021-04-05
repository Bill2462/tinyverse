#ifndef BARNES_HUT_HPP_INCLUDED
#define BARNES_HUT_HPP_INCLUDED

#include "physics/gravity/gravity_solver.hpp"
#include <array>
#include <memory>
#include <vector>

struct TreeNode
{
    void reset()
    {
        center_of_mass = {0, 0, 0};
        weighted_sum_of_mass = {0, 0, 0};
        body_index = -1;
        mass = 0;
        is_internal = false;
    }

    Vector3D<Real> bottom_left_corner;
    Real cube_size;
    Vector3D<Real> center_of_mass = {0, 0, 0};
    Vector3D<Real> weighted_sum_of_mass = {0, 0, 0};

    long long body_index = -1;
    bool is_internal = false;
        
    // Mass of all bodies inside this node.
    Real mass = 0;

    // First 4 nodes are lower 4 cubes in clockwise order starting from the bottom left cube.
    // Last 4 nodes are uppper r 4 cubes in clockwise order starting from the bottom left cube.
    std::array<TreeNode*, 8> children;
};

class BarnesHutGravitySolver : public GravitySolver
{
public:
    BarnesHutGravitySolver(const Vectors3D& position, const Vector& mass,
    Real G, bool use_softening, Real softening_epsilon = 2,
    Real max_universe_size = 10000, Real theta=0.5);

    // Rebuilds tree from scratch.
    void rebuild_tree();

    Vector3D<Real> compute_net_grawitational_force(std::size_t body_index) const override;
    GravitySolver::Type get_type() const override;
    
private:
    TreeNode* tree_root;

    std::vector<std::shared_ptr<TreeNode>> node_pool;
    std::size_t nodes_in_use_counter = 0;

    // Obtains new node from the node pool.
    // If all nodes from the pool are assigned then
    // we append new node to the counter.
    TreeNode* get_empty_node();

    // Create 8 children nodes and add them to the
    void add_children(TreeNode* node);
    
    void construct_tree();
    void destroy_tree(); // Destroys tree by reseting all nodes.

    // Checks if position is inside the node.
    bool is_inside_node(const TreeNode* node, const Vector3D<Real>& pos) const;

    // If node is empty, then body is inserted into the node.
    // If there is already a body in the node then we ensure that children of the node exist
    // by creating them if they don't exist.
    // Then we take both bodies (the body that we are trying to add the body that was already in the node)
    // and we add them to the children that they fit into.
    // If they fit into the same children then we add them to the same node one by one.
    // That splits the node recursively if them until they end up in the separate children.
    void insert_body(TreeNode* node, const Vector3D<Real>& pos, Real mass, std::size_t body_index);
    void add_force(const TreeNode* node, const Vector3D<Real>& pos, std::size_t body_index, Vector3D<Real>& force) const;

    const Vectors3D* position;
    const Vector* mass;
    const Real G;
    const bool use_softening;
    const Real softening_epsilon;
    const std::size_t nbody;
    const Real max_universe_size;
    const Real theta;
    const Vector3D<Real> universe_bottom_left_corner;
};

#endif
