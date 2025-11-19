# 1. 基础配置（兼容旧政策，解决 CMP0167 警告）
cmake_minimum_required(VERSION 3.26)
project(httpserver)  # 项目名建议与可执行文件一致，避免混淆

# 关键：兼容旧的 FindBoost 模块（解决 Policy CMP0167 警告）
cmake_policy(SET CMP0167 OLD)

# 2. C++ 标准与编译选项
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 编译选项（保留你的 -Wall -O2 等）
set(COMMON_COMPILE_FLAGS
        -Wall
        -Wextra
        -g3
        -O2
        -march=native
)
add_compile_options(${COMMON_COMPILE_FLAGS})  # 全局编译选项


# 3. 手动指定 Boost 路径和版本（关键：解决 Boost 库找不到的问题）
# 替换为你的 Boost 实际安装路径（例如 MSYS2 的 ucrt64 目录）
set(BOOST_ROOT "C:/msys64/ucrt64")
set(Boost_INCLUDE_DIR "${BOOST_ROOT}/include")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib")
set(Boost_VERSION "1.89.0")  # 对应你使用的 boost_1_89

# 查找 Boost 组件（必须与你链接的库名匹配）
find_package(Boost ${Boost_VERSION} REQUIRED
        COMPONENTS
        log_setup log regex filesystem thread
        date_time chrono timer atomic program_options
        json url process random container coroutine
        fiber context contract type_erasure serialization
        wserialization unit_test_framework
)


# 4. 定义可执行目标（确保源文件存在！）
# 替换为你的实际源文件（如 server.cpp，不要写头文件）
add_executable(${PROJECT_NAME}
        server.cpp
        # 其他源文件：xxx.cpp yyy.cpp
)


# 5. 链接选项（严格按你的静态/动态切换顺序）
target_link_options(${PROJECT_NAME} PRIVATE
        -Wl,-Bstatic                # 静态链接开始
        -Wl,--start-group           # 解决库循环依赖
)

# 6. 链接静态库（--start-group 和 --end-group 之间）
target_link_libraries(${PROJECT_NAME} PRIVATE
        # 第三方库（jsoncpp、crypto 等）
        jsoncpp
        ssl
        crypto
        cryptopp

        # Boost 库（使用 find_package 找到的目标，自动匹配版本）
        Boost::log_setup
        Boost::log
        Boost::regex
        Boost::filesystem
        Boost::thread
        Boost::date_time
        Boost::chrono
        Boost::timer
        Boost::atomic
        Boost::program_options
        Boost::json
        Boost::url
        Boost::process
        Boost::random
        Boost::container
        Boost::coroutine
        Boost::fiber
        Boost::context
        Boost::contract
        Boost::type_erasure
        Boost::serialization
        Boost::wserialization
        Boost::unit_test_framework
)

# 7. 切换到动态链接并链接系统库
target_link_options(${PROJECT_NAME} PRIVATE
        -Wl,--end-group             # 结束库分组
        -Wl,-Bdynamic               # 动态链接开始
)

# 8. 链接动态库（系统库）
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


# 9. 确保编译器能找到头文件（Boost 等）
target_include_directories(${PROJECT_NAME} PRIVATE
        ${Boost_INCLUDE_DIR}  # Boost 头文件目录
        # 其他头文件目录（如果需要）：${CMAKE_CURRENT_SOURCE_DIR}/include
)