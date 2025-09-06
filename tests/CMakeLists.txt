cmake_minimum_required(VERSION 3.10)

# 设置Unity源码路径
set(UNITITY_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Unity/src)
set(UNITITY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Unity/src)

# 构建Unity静态库
add_library(unity STATIC
    ${UNITITY_SOURCE_DIR}/unity.c
)

# 设置Unity的头文件目录
target_include_directories(unity PUBLIC ${UNITITY_INCLUDE_DIR})

# 扫描tests目录下所有test_前缀的c文件
file(GLOB TEST_SOURCES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    "test_*.c"
)

# 为每个测试文件创建可执行文件
foreach(test_source ${TEST_SOURCES})
    # 获取测试名称（去掉.c后缀）
    get_filename_component(test_name ${test_source} NAME_WE)
    
    # 创建可执行文件
    add_executable(${test_name} ${test_source})
    
    # 链接静态库
    target_link_libraries(${test_name} 
        unity
        linked_list
    )
    
    # 设置头文件目录
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}
        ${UNITITY_INCLUDE_DIR}
    )
    
    message(STATUS "Added test: ${test_name} from ${test_source}")
endforeach()

# 添加测试目标
enable_testing()
foreach(test_source ${TEST_SOURCES})
    get_filename_component(test_name ${test_source} NAME_WE)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()