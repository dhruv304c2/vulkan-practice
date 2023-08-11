//
//  render_pipeline.cpp
//  VulkanPractice
//
//  Created by Tech Alchemy on 09/08/23.
//

#include "render_pipeline.hpp"
#include <fstream>
#include <iostream>

namespace renderPipeline{

    RenderPipeline::RenderPipeline(const std::string& fragmentShaderPath, const std::string& vertexShaderPath){
        createGraphicsPipeline(fragmentShaderPath,vertexShaderPath);
    }

    std::vector<char> RenderPipeline::readFile(const std::string &filepath){
        std::fstream file(filepath, std::ios::ate | std::ios::binary);
        
        if(!file.is_open()){
            std::runtime_error("failed to open file");
        }
        
        size_t fileSize = static_cast<int>(file.tellg());
        
        file.seekg(0);
        std::vector<char> buffer(fileSize);
        file.read(buffer.data(), fileSize);
        file.close();
        
        return buffer;
    }

    void RenderPipeline::createGraphicsPipeline(const std::string& fragmentShaderPath, const std::string& vertexShaderPath){
        std::cout << "compiled fragment shader file size " << sizeof(readFile(fragmentShaderPath)) << std::endl;
        std::cout << "compiled vertex shader file size " << sizeof(readFile(vertexShaderPath)) << std::endl;
    }
}

