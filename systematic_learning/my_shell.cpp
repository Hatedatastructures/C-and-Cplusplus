#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#define COMMAND_LENGTH 1024
#define OPTIONS_LENGTH 64
char options[COMMAND_LENGTH];
void input_cmd()
{
    std::cout << "["<< getenv("USER") << "@ simple shell]# ";
    fflush(stdout);
    memset(options,0,COMMAND_LENGTH);
    std::cin >> options;
}
// void process_replacement()
// {

// }
int main()
{
    std::cout << "进入命令行 " << std::endl;
    while(true)
    {
        input_cmd();
    }
    return 0;
}