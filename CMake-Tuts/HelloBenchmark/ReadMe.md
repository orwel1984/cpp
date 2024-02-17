# Hello Benchmark 

Download the Google's benchmark library from 
https://github.com/google/benchmark 

And add the library to **external/*** folder


(You might also need to download GoogleTest if the build instructions below don't work )
### Project Structure

The directory structure should look like:

    HelloBenchmark
    |
    |- external/
    |  |
    |  |-benchmark/
    |    |
    |    |-googletest/
    |
    |- src/
    |
    |- CMakeLists.txt


You always add your sources in the ***src*** folder and add all external libraries like boost inside the ***external*** folder.

## Build & Run

To build and run the HelloBoost example, use the following commands:

#### Generate Make Project ####
```
cmake -S . -B build -DBENCHMARK_ENABLE_GTEST_TESTS=OFF -DCMAKE_BUILD_TYPE=Release 
```
#### Build ####
```
cmake --build build
```
#### Run ####
```
./build/HelloBenchmark
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