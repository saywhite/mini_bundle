include(../cmake/find_pybind11.cmake)
include(../cmake/add_simple_library.cmake)
include(../cmake/add_imgui.cmake)
include(../cmake/add_glfw.cmake)

# Build imgui
add_compile_options(-fPIC)
set(BUILD_SHARED_LIBS OFF)
set(imgui_dir ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui)
set(imgui_backends_dir ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui/backends)
add_imgui(${imgui_dir})
target_compile_definitions(imgui PUBLIC MINI_BUNDLE_BUILD_PYTHON)
target_link_libraries(mini_bundle PUBLIC imgui)

# Build imgui_pywrappers
find_pybind11()
add_simple_external_library(imgui_pywrappers imgui/imgui_pywrappers)
target_sources(imgui_pywrappers PRIVATE
    imgui/imgui_pywrappers/imgui_pywrappers.cpp imgui/imgui_pywrappers/imgui_pywrappers.h
    imgui/imgui_pywrappers/imgui_internal_pywrappers.cpp imgui/imgui_pywrappers/imgui_internal_pywrappers.h
    )
target_link_libraries(imgui_pywrappers PUBLIC pybind11::pybind11)

# Build glfw
set(glfw_dir ${CMAKE_CURRENT_LIST_DIR}/glfw/glfw)
add_glfw()
target_link_libraries(mini_bundle PUBLIC glfw)

# Build implot
set(implot_dir ${CMAKE_CURRENT_LIST_DIR}/implot/implot)
add_simple_external_library_with_sources(implot implot)
target_compile_definitions(implot PRIVATE "IMPLOT_CUSTOM_NUMERIC_TYPES=(signed char)(unsigned char)(signed short)(unsigned short)(signed int)(unsigned int)(signed long)(unsigned long)(signed long long)(unsigned long long)(float)(double)(long double)")
target_compile_options(implot PRIVATE -include ${CMAKE_CURRENT_LIST_DIR}/../cmake/mini_bundle_config.h)
target_compile_options(implot PRIVATE -Wno-terminate)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(mini_bundle PUBLIC OpenGL::GL)
 
target_include_directories(mini_bundle
                           PUBLIC ${imgui_dir} 
                           PUBLIC ${imgui_backends_dir} 
                           PUBLIC ${glfw_dir}
                           PUBLIC ${implot_dir} ) 

target_sources(mini_bundle PRIVATE
                      ${imgui_backends_dir}/imgui_impl_opengl3.h
                      ${imgui_backends_dir}/imgui_impl_opengl3.cpp
                      ${imgui_backends_dir}/imgui_impl_glfw.h
                      ${imgui_backends_dir}/imgui_impl_glfw.cpp
                      )

####################################################
# Main
####################################################
add_executable(imgui_demo src/demo.cpp)

target_include_directories(imgui_demo
                           PUBLIC ${imgui_dir} 
                           PUBLIC ${imgui_backends_dir} 
                           PUBLIC ${glfw_dir}
                           PUBLIC ${implot_dir} ) 

target_link_libraries(imgui_demo
                      PUBLIC OpenGL::GL
                      PUBLIC imgui 
                      PUBLIC glfw 
                      PUBLIC implot)

target_sources(imgui_demo PRIVATE
                      ${imgui_backends_dir}/imgui_impl_opengl3.h
                      ${imgui_backends_dir}/imgui_impl_opengl3.cpp
                      ${imgui_backends_dir}/imgui_impl_glfw.h
                      ${imgui_backends_dir}/imgui_impl_glfw.cpp
                      )
