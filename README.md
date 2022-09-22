# RAIIEngine


Co-authored-by: James Sumihiro <8211447+JHorace@users.noreply.github.com>

Co-authored-by: Bryan Johnson <61810643+BryanJohnson626a@users.noreply.github.com>

Engine ownership structure:

    IEngine
        Context
        Instance
        Renderer
        Device Manager (Physical Device)
            LogicalDevice(s)
                Swapchain(s)
                    DepthBuffer
                Queue(s)
                VertexBuffer
                UniformBuffer
                CommandDispatch
                    CommandPool(s)
                    CommandBuffer(s)
            Surface(s)
            QueueManager
                QueueFamilies
                QueuePool

    Scene
        Vertices