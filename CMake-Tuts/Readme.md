# CMake Foundational Concepts


## Artifcat 
In software development, a software artifact is an item that is produced during the development process.  It can be an executable, library, test-suite,  etc.  The list of artifacts needed  gives a roadmap for the software to be produced.

## Targets 

A target in CMake, is a high-level logical unit that has a single purpose for CMake. 

Building a target will produce an artifact that will be fed into other targets or delivered as a final product of the build. 

CMake will take care of determining in what order targets have to be built and then execute the necessary steps one by one. 

The main commands used in CMake to build/define targets are:

- add_executable()
- add_library()
- add_custom_target()

Only the last command, for custom targets, does'nt necessarily produce any tangible artifacts.

#### target_link_libraries()
We connect our library targets, created with **add_library()**, to the executable targets  creatred with **add_executable()**, using the **target_link_libraries()**

#### add_dependencies() 
