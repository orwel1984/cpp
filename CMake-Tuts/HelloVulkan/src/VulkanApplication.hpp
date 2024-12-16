#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


const int MAX_FRAMES_IN_FLIGHT = 2;
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> g_validationLayers = 
{
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> g_deviceExtensions = 
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,            // "VK_KHR_swapchain"
    "VK_KHR_portability_subset"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

/*
---------------
SWAP-CHAINS
---------------
Vulkan does not have the concept of a "default framebuffer", 
hence it requires an infrastructure that will own the buffers we will render to before we visualize them on the screen. 
This infrastructure is known as the swap chain and must be created explicitly in Vulkan. 
The swap chain is essentially a queue of images that are waiting to be presented to the screen. 
Our application will acquire such an image to draw to it, and then return it to the queue.

Not all graphics cards are capable of presenting images directly to a screen for various reasons, 
for example because they are designed for servers and don't have any display outputs. 
Secondly, since image presentation is heavily tied into the window system and the surfaces associated with windows, 
it is not actually part of the Vulkan core. 
You have to enable the VK_KHR_swapchain device extension after querying for its support.

Just checking if a swap chain is available is not sufficient, because it may not actually be compatible with our window surface.
Creating a swap chain also involves a lot more settings than instance and device creation, 
so we need to query for some more details before we're able to proceed.

---------------

*/

class HelloTriangleApplication 
{
    // class members
    GLFWwindow* m_window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device;
    VkSurfaceKHR m_surface;
    
    VkQueue m_presentQueue;
    VkQueue m_graphicsQueue;

    VkSwapchainKHR m_swapChain;
    std::vector<VkImageView> m_swapChainImageViews;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    VkRenderPass m_renderPass;
    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;

    std::vector<VkFramebuffer> m_swapChainFramebuffers;

    VkCommandPool m_commandPool;

    std::vector<VkCommandBuffer> m_commandBuffers;    
    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;    

    uint32_t g_currentFrame = 0;

public:
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    void drawFrame();

    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice(); 
    void createSurface();
    void createSwapChain();
    void createImageViews();

    void createRenderPass();
    void createGraphicsPipeline();
    void createFramebuffers();
    void createCommandPool();  
    void createCommandBuffer();
    void createSyncObjects();

private:

    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    VkShaderModule  createShaderModule(const std::vector<char>& code);

    bool  checkValidationLayerSupport();

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

    std::vector<VkExtensionProperties> getAllExtensionsAvailable();
    const std::vector<const char*> getExtensionsRequiredByGLFW();
    bool checkAllRequiredExtensionsAreAvailable(const std::vector<const char*>& extRequiredByGLFW, const std::vector<VkExtensionProperties>& extAvailableOnSystem);
    
    void handleErrors(VkResult result);

    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void setupDebugMessenger();
    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) ;

};
