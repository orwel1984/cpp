# Vulkan

Vulkan is a new API by the Khronos Group which provides a much better abstraction of modern graphics cards.

- It better describe what your application intends to do, which leads to better performance and less surprising driver behavior compared to existing APIs like OpenGL and Direct3D. 

- The ideas behind Vulkan are similar to those of Direct3D 12 and Metal, but Vulkan has the advantage of being fully cross-platform (Windows, Linux, Android, MacOS, iOS ).


## Origin of Vulkan

 Problem with older APIs is that the era in which they were designed featured GPUs  that were mostly limited to configurable fixed functionality.

As GPU architectures evolved, they started offering more and more programmable functionality

Then mobile GPUs have different architectures based on their energy & space requirements. One such example is "tiled rendering", which would benefit from improved performance by offering the programmer more control over this functionality.