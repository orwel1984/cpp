# Hello Boost 

There are two ways to use Boost library in your projects. 

1. You can build the Boost sources alongside your project. 

2. Alternative approach is to build Boost separately and install the binaries somewhere on your system. Then specify the location of Boost binaries on your system.

We will use the method #1 in this project.

## Build Boost alongside your Project

This is the method we will use in this project.

1.  First, go to:  https://www.boost.org/users/download/ 

2. Download e.g. **boost_1_82_0.tar.gz** from Unix.

3. Unzip the contents of this folder into this relative location from this project's root: 
    ${Project_Root}/***external/***

So after unzipping you will have the following directory structure:
    ${Project_Root}*/external/boost_1_82_0/*

### Project Structure

The directory structure should look like:

    HelloBoost
    |
    |- external/
    |  |
    |  |-boost_1_82_0/*
    |
    |- src/
    |
    |- CMakeLists.txt


You always add your sources in the ***src*** folder and add all external libraries like boost inside the ***external*** folder.

### Update CMake

Then you need to update you projects root CMakeLists.txt file with the changes below:

- **BOOST_ROOT** :
Specify the path to your boost sources: *external/boost_1_82_0* folder, like below:

```
set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/boost_1_82_0")
```

- **find_package** :

Now you are ready to make the *find_package* call in your CMake with all the necessary Boost's components that you want to use in your project. 

In this example we want to use  **program_options**, date_time and filesystem components from Boost. Hence we specify it like below:

```
find_package(Boost 1.82 COMPONENTS program_options date_time filesystem  REQUIRED)
```

- **Boost Found** : 

If everything is configured correctly you should see this output during the configure step of cmake:

```
-- Found Boost: ~/Developer/C++/cpp/CMake-Tuts/HelloBoost/external/boost_1_82_0 (found suitable version "1.82.0", minimum required is "1.82") found components: program_options date_time filesystem 
```

See also this documentation page:
https://cmake.org/cmake/help/latest/module/FindBoost.html

It lists all the variables which are now configured when find_package() successfully finds Boost.

These include:

- Boost_INCLUDE_DIRS :   Boost include directories.
- Boost_LIBRARY_DIRS :   Link directories for Boost libraries.


Now add the following lines to link to the main execuatble target:

```
target_include_directories(HelloBoost PUBLIC ${Boost_INCLUDE_DIR}) 
target_link_libraries(HelloBoost ${Boost_LIBRARY_DIR})
target_link_libraries(HelloBoost Boost::program_options Boost::date_time Boost::filesystem)
```



## Run example code

To build and run the HelloBoost example, use the following commands:

```
cmake -S . -B build 
```

```
cmake --build build
```

```
./build/HelloBoost --apples 10 --oranges 10
```

NOTE:

Add the `-DBoost_NO_WARN_NEW_VERSIONS=1` to the first command if you get a warning like below during configure:

```
CMake Warning at /usr/local/Cellar/cmake/3.25.2/share/cmake/Modules/FindBoost.cmake:1384 (message):
  New Boost version may have incorrect or missing dependencies and imported
  targets
Call Stack (most recent call first):
  /usr/local/Cellar/cmake/3.25.2/share/cmake/Modules/FindBoost.cmake:1508 (_Boost_COMPONENT_DEPENDENCIES)
  /usr/local/Cellar/cmake/3.25.2/share/cmake/Modules/FindBoost.cmake:2119 (_Boost_MISSING_DEPENDENCIES)
  CMakeLists.txt:7 (find_package)
```