cmake_minimum_required(VERSION 3.26)
project(MyProject)

# 1. 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 2. 查找 Boost 库（必须添加，否则无法链接 Boost.Asio）
find_package(Boost REQUIRED COMPONENTS system thread)

# 3. 定义可执行目标
add_executable(${PROJECT_NAME}
        server.cpp  # 你的主源文件
)

# 4. 编译选项（保持不变）
target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall
        -Wextra
        -g3
        -O2
        -march=native
)

# 5. 链接选项（保持顺序，注意 Boost 库需在分组内）
target_link_options(${PROJECT_NAME} PRIVATE
        -Wl,-Bstatic
        -Wl,--start-group
)

# 6. 链接库（添加 Boost 库，确保顺序正确）
target_link_libraries(${PROJECT_NAME} PRIVATE
        jsoncpp
        ssl
        crypto
        cryptopp
        Boost::system  # 链接 Boost.system
        Boost::thread  # 链接 Boost.thread
)

# 7. 关闭分组并切换动态链接
target_link_options(${PROJECT_NAME} PRIVATE
        -Wl,--end-group
        -Wl,-Bdynamic
)

# 8. 链接系统动态库（保持不变）
target_link_libraries(${PROJECT_NAME} PRIVATE
        pdh
        ws2_32
        mswsock
        crypt32
        advapi32
        bcrypt
        gdi32
        user32
        dbghelp
        ole32
        shell32
)