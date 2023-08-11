//
//  render_pipeline.hpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 09/08/23.
//

#ifndef render_pipeline_hpp
#define render_pipeline_hpp

#include <stdio.h>
#include <string>
#include <vector>

namespace renderPipeline{
    class RenderPipeline{
        public:
            RenderPipeline(const std::string& fragmentShaderPath, const std::string& vertexShaderPath);
        private:
            std::vector<char> readFile(const std::string& filepath);
            void createGraphicsPipeline(const std::string& fragmentShaderPath,const std::string& vertexShaderPath);
    };
}

#endif /* render_pipeline_hpp */
