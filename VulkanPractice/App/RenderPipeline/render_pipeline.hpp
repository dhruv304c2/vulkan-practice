#ifndef render_pipeline_hpp
#define render_pipeline_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <vulkan/vulkan.h>

namespace renderPipeline{

    struct RenderPipelineCreateInfo{
        VkDevice device;
        std::string fragment_shader_path;
        std::string vertex_shader_path;
        VkExtent2D swapchain_extent;
    };

    class RenderPipeline{
        private:
            VkPipelineLayout pipeline_layout;
            std::vector<char> read_file(const std::string& filepath);
            VkShaderModule create_shader_module(VkDevice device,const std::vector<char> &code);
            RenderPipelineCreateInfo create_info;
        public:
            void create_graphics_pipeline(RenderPipelineCreateInfo create_info);
            VkPipelineLayout get_pipeline_layout(){return pipeline_layout;};
            void clean_up();
    };
}

#endif
