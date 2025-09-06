
cmake_minimum_required(VERSION 3.10) 
project(ADT_forC C) 
# 设置C标准 
set(CMAKE_C_STANDARD 99) 
set(CMAKE_C_STANDARD_REQUIRED ON) 
# 设置输出目录 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 
# 包含目录 
include_directories(${CMAKE_SOURCE_DIR}) 
# 查找所有子目录 
set(ADT_MODULES linked_list ) 
# 为每个模块构建静态库 
foreach(module ${ADT_MODULES}) 
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${module}) 
        file(GLOB_RECURSE ${module}_SOURCES "${CMAKE_SOURCE_DIR}/${module}/*.c") 
        if(${module}_SOURCES) 
            add_library(${module} STATIC ${${module}_SOURCES}) 
            target_include_directories(${module} PUBLIC ${CMAKE_SOURCE_DIR}) 
            message(STATUS "Added library: ${module} with sources: ${${module}_SOURCES}") 
        endif() 
    endif() 
endforeach() 
# 添加tests子目录 
add_subdirectory(tests)