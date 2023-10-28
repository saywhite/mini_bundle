set(MINIBUNDLE_WIDGET_PATH ${MINIBUNDLE_PATH}/widget CACHE STRING "" FORCE)

####################################################
# add_simple_widget_library : will add a target
# when its folder structure is simple
####################################################
function(add_simple_widget_library lib_target_name lib_folder)
    add_library(${lib_target_name} STATIC)
    target_link_libraries(${lib_target_name} PUBLIC imgui)

    set(lib_parent_folder ${MINIBUNDLE_WIDGET_PATH}/${lib_folder})
    target_include_directories(${lib_target_name} PUBLIC ${lib_parent_folder})
    target_link_libraries(mini_bundle PUBLIC ${lib_target_name})
endfunction()

function(add_simple_widget_library_with_sources lib_target_name lib_folder)
    add_simple_widget_library(${lib_target_name} ${lib_folder})
    set(lib_parent_folder ${MINIBUNDLE_WIDGET_PATH}/${lib_folder})

    set(lib_inner_folder ${MINIBUNDLE_WIDGET_PATH}/${lib_folder}/${lib_folder})
    file(GLOB lib_sources ${lib_inner_folder}/*.cpp ${lib_inner_folder}/*.h)

    target_sources(${lib_target_name} PRIVATE ${lib_sources})
endfunction()

# Build ImGuiNodes
set(imgui_nodes_dir ${MINIBUNDLE_WIDGET_PATH}/ImGuiNodes/ImGuiNodes)
add_simple_widget_library_with_sources(ImGuiNodes ImGuiNodes)
target_compile_options(ImGuiNodes PRIVATE -Wno-terminate)
target_compile_options(ImGuiNodes PRIVATE -include ${MINIBUNDLE_PATH}/cmake/mini_bundle_config.h)

find_package(OpenGL REQUIRED)

set(imgui_dir ${MINIBUNDLE_EXTERNAL_PATH}/imgui/imgui)
set(imgui_backends_dir ${MINIBUNDLE_EXTERNAL_PATH}/imgui/imgui/backends)
set(glfw_dir ${MINIBUNDLE_EXTERNAL_PATH}/glfw/glfw)
set(implot_dir ${MINIBUNDLE_EXTERNAL_PATH}/implot/implot)

####################################################
# DEMO
####################################################
add_executable(imgui_demo src/demo.cpp)

target_include_directories(imgui_demo
                           PUBLIC ${imgui_dir} 
                           PUBLIC ${imgui_backends_dir} 
                           PUBLIC ${glfw_dir}
                           PUBLIC ${implot_dir}
                           PUBLIC ${imgui_nodes_dir}) 

target_link_libraries(imgui_demo
                      PUBLIC OpenGL::GL
                      PUBLIC imgui 
                      PUBLIC glfw 
                      PUBLIC implot
                      PUBLIC ImGuiNodes)

target_sources(imgui_demo PRIVATE
                      ${imgui_backends_dir}/imgui_impl_opengl3.h
                      ${imgui_backends_dir}/imgui_impl_opengl3.cpp
                      ${imgui_backends_dir}/imgui_impl_glfw.h
                      ${imgui_backends_dir}/imgui_impl_glfw.cpp
                      ${imgui_nodes_dir}/nodes.h
                      ${imgui_nodes_dir}/nodes.cpp
                      )
