// Part of ImGui Bundle - MIT License - Copyright (c) 2022-2023 Pascal Thomet - https://github.com/pthom/mini_bundle
#include <pybind11/pybind11.h>


#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;


void py_init_module_mini_bundle(py::module& m);


// This builds the native python module `_mini_bundle`
// it will be wrapped in a standard python module `mini_bundle`
PYBIND11_MODULE(_mini_bundle, m)
{
    #ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
    #else
    m.attr("__version__") = "dev";
    #endif

    py_init_module_mini_bundle(m);
}
