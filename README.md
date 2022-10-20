# RAIIEngine


Co-authored-by: James Sumihiro <8211447+JHorace@users.noreply.github.com>

Co-authored-by: Bryan Johnson <61810643+BryanJohnson626a@users.noreply.github.com>

Engine ownership structure:

    IEngine
        Context
        Instance
    ??? Renderer ???
        Device Manager (Physical Device)
            LogicalDevice(s)
                Swapchain(s)
                    DepthBuffer
                Queue(s)
                DeviceMemoryManager
                CommandDispatch
                    CommandPool(s)
                    CommandBuffer(s)
            Surface(s)
            QueueManager
                QueueFamilies
                QueuePool

    Scene
        Vertices


Semaphores

    _imageAvailableSemaphore
        Stored: LogicalDevice (eventually Renderer)
        Signal: Swapchain::Update (acquireNextImage)
        Wait: LogicalDevice::Draw (submit)

    _presentReadySemaphore
        Stored: LogicalDevice (eventually Renderer)
        Signal: LogicalDevice::Draw (submit)
        Wait: Swapchain::PresentCurrentImage (present)

Fences

    _drawReadyFence
        Stored: LogicalDevice (eventually Renderer)
        Sent: LogicalDevice::Draw (submit)
        Wait: LogicalDevice::Update (before draw)

