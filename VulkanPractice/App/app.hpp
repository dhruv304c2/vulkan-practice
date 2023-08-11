#ifndef app_hpp
#define app_hpp

#include <stdio.h>
#include "Process/process.hpp"
#include "RenderPipeline/render_pipeline.hpp"
#include "generic_singleton.hpp"
#include "vulkan_helper.hpp"

namespace app{
    class App : public common::GenericSingleton<App>{
        public:
            static constexpr int width = 800;
            static constexpr int height = 600;
            const std::string app_name = "Vulkan App";
            bool is_running();
            void run();
            void clean_up();
        private:
            process::Process main_process{width,height,app_name};
            renderPipeline::RenderPipeline render_Pipeline{"shaders/simple_shader.frag.spv", "shaders/simple_shader.vert.spv"};
    };
} 

#endif
