# Tinyverse

Tinyverse is a result of a challenge of writing a physics
engine in 2 weeks.

# Compiling

Compiling works only on linux and possibly on macOS.

The following dependencies are required:

 - spdlog (https://github.com/gabime/spdlog)
 - json (https://github.com/nlohmann/json)
 - Eigen3 (https://eigen.tuxfamily.org/index.php?title=Main_Page)
 - Magnum (https://github.com/mosra/magnum)

To configure project cmake is required.

# Running tinyverse

Tinyverse takes one console argument which is a path to the
config file.

```
./tinyverse -f ../examples/collapsing_cube.json
```

Enjoy!
