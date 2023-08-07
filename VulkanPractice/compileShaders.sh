echo "compiling shaders..."
SHADER_SRC_PATH="${PROJECT_DIR}/VulkanPractice/shaders"
SHADER_BUILD_PATH="${CONFIGURATION_BUILD_DIR}/shaders"


/usr/local/bin/glslc ${SHADER_SRC_PATH}/simple_shader.vert -o ${SHADER_SRC_PATH}/simple_shader.vert.spv
/usr/local/bin/glslc ${SHADER_SRC_PATH}/simple_shader.frag -o ${SHADER_SRC_PATH}/simple_shader.frag.spv

echo "compilation complete..."

if [ -d ${SHADER_BUILD_PATH} ]; then
    echo "removing old shaders..."
    rm "${SHADER_BUILD_PATH}"
fi

mkdir "${SHADER_BUILD_PATH}"
echo "new shader build directory creted..."


cp "${SHADER_SRC_PATH}/simple_shader.vert.spv" "${SHADER_BUILD_PATH}"
cp "${SHADER_SRC_PATH}/simple_shader.frag.spv" "${SHADER_BUILD_PATH}"

echo "done!"
