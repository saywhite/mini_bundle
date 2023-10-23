# Part of ImGui Bundle - MIT License - Copyright (c) 2022-2023 Pascal Thomet - https://github.com/pthom/mini_bundle
from mini_bundle._mini_bundle import imgui as imgui
from mini_bundle._mini_bundle import implot as implot

from mini_bundle._mini_bundle import __version__, compilation_time

from mini_bundle._mini_bundle.imgui import ImVec2, ImVec4, ImColor, FLT_MIN, FLT_MAX
from mini_bundle.im_col32 import IM_COL32

# Glfw setup:
# make sure that glfw provided by pip will use our glfw dynamic library.
from mini_bundle._glfw_set_search_path import _glfw_set_search_path
_glfw_set_search_path()

import os

__all__ = [
    # submodules
    "imgui",
    "implot",
    "mini_bundle",
    # Base ImGui types
    "IM_COL32",
    "ImVec2",
    "ImVec4",
    "ImColor",
    "FLT_MIN",
    "FLT_MAX",
    # Base utilities
    "__version__",
]
