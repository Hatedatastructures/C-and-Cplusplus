#include <iostream>
class Time
{
    private:
    int hour;
    int minute;
    int second;
    public:
    Time(int h, int m, int s)
    {
        hour = h;
        minute = m;
        second = s;
    }
    Time()
    {
        hour = 0;
        minute = 0;
        second = 0;     
    }
    void Time_p()
    {
        std::cout << hour << " " << minute << " " << second << std::endl;
        Time_print();
    }
    static void Time_print()
    {
        std::cout << "hello,word!" << std::endl;
    }
};
int main()
{
    Time t1 ;
    Time t2 (2025, 3 ,24);
    t1.Time_p();
    t2.Time_p();
    return 0;
}
