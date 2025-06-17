#include <iostream>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

// 函数用于创建新控制台并返回输出流指针
FILE* createNewConsole(const char* title) 
{
    // 创建新的控制台窗口
    AllocConsole();
    SetConsoleTitleA(title);
    
    // 将标准输出重定向到新控制台
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
    _setmode(_fileno(stdout), _O_U16TEXT); // 设置为Unicode模式（可选）
    
    return fp;
}

int main() 
{
    // 主控制台输出
    std::cout << "这是主控制台输出" << std::endl;
    AllocConsole();AllocConsole();AllocConsole();AllocConsole();
    // 创建新控制台
    FILE* newConsole = createNewConsole("子控制台");
    
    // 在新控制台输出
    std::wcout << L"这是新控制台的输出" << std::endl;
    
    // 主控制台继续输出
    std::cout << "主控制台继续执行..." << std::endl;
    
    // 等待用户输入以保持控制台打开
    std::cin.get();
    
    // 释放新控制台
    FreeConsole();
    
    return 0;
}