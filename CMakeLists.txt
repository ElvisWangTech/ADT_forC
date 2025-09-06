cmake_minimum_required(VERSION 3.10)
project(ADT_forC C)

# 设置C标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置统一的头文件输出目录
set(CMAKE_HEADER_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/include)

# 包含目录
include_directories(${CMAKE_SOURCE_DIR})

# 查找所有子目录
set(ADT_MODULES linked_list)

# 收集所有头文件
set(ALL_HEADER_FILES "")

# 为每个模块构建静态库
foreach(module ${ADT_MODULES})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/${module})
        # 收集源文件
        file(GLOB_RECURSE ${module}_SOURCES "${CMAKE_SOURCE_DIR}/${module}/*.c")
        
        # 收集头文件
        file(GLOB_RECURSE ${module}_HEADERS "${CMAKE_SOURCE_DIR}/${module}/*.h")
        list(APPEND ALL_HEADER_FILES ${${module}_HEADERS})
        
        if(${module}_SOURCES)
            add_library(${module} STATIC ${${module}_SOURCES})
            target_include_directories(${module} PUBLIC ${CMAKE_SOURCE_DIR})
            message(STATUS "Added library: ${module} with sources: ${${module}_SOURCES}")
            message(STATUS "Collected headers for ${module}: ${${module}_HEADERS}")
        endif()
    endif()
endforeach()

# 创建头文件安装规则
foreach(header_file ${ALL_HEADER_FILES})
    # 获取相对路径
    file(RELATIVE_PATH relative_path ${CMAKE_SOURCE_DIR} ${header_file})
    
    # 获取目录名
    get_filename_component(dir_name ${relative_path} DIRECTORY)
    
    # 安装头文件到统一目录
    install(FILES ${header_file}
            DESTINATION ${CMAKE_HEADER_OUTPUT_DIRECTORY}/${dir_name})
endforeach()

# 创建构建时头文件复制规则
add_custom_target(copy_headers ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_HEADER_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${ALL_HEADER_FILES} ${CMAKE_HEADER_OUTPUT_DIRECTORY}
    COMMENT "Copying header files to unified include directory"
    VERBATIM
)

# 为每个模块添加头文件复制依赖
foreach(module ${ADT_MODULES})
    if(TARGET ${module})
        add_dependencies(${module} copy_headers)
    endif()
endforeach()

# 添加tests子目录
add_subdirectory(tests)