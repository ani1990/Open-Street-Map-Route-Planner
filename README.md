# Open-Street-Map-Route-Planner
A Route Planner designed using Open Street Maps [OSM](https://www.openstreetmap.de/). The project uses IO2D C++ Library for the map graphics rendering.A sample map is added to the project(map.png) for the visualization.

**Brief Description of the Open Steet Map**
The Open Street Map consists of three different kinds of major entities:
**Node** : Most Basic element of an OSM. Each node is identified by an Id, its latitude and its longitude)
**Way** :  Its an ordered List of Nodes that represents a feature in the map. This feature could be a road, or a boundary of a park
           Each way has at least one 'tag' which denotes some information about the way.
**Relation** : A relation is a combination of many different ways and nodes which has a specific importance on the map. 
               Eg. A route relation which lists the ways that form a major highway, cycle route, or bus route.

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it

## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```
