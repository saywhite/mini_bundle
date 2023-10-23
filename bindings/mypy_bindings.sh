#!/usr/bin/env bash
 mypy mini_bundle \
    |grep -v no-redef \
    | grep -v " Too many arguments for \"ImVec" \
    | grep -v "(default has type \"int\", argument has type \"ImColor" \
    | grep -v "argument has type \"int\"" \
    | grep -v "variable has type \"int\"" \
    | grep -v " Too many arguments for \"ImColor\""
