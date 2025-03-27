#include <iostream>
#include <string>
#include <cstdint>
template <class grades_type>
class Information_management
{
    private:
    class student_list
    {
        public:
        class student
        {
            public:
                class subject 
                {
                    public:
                    grades_type Chinese;                                    /*语文*/
                    grades_type Math;                                       /*数学*/
                    grades_type English;                                    /*英语*/
                    grades_type politics;                                   /*政治*/
                    grades_type history;                                    /*历史*/
                    grades_type geography;                                  /*地理*/
                    grades_type biology;                                    /*生物*/
                    grades_type chemistry;                                  /*化学*/
                    grades_type physics;                                    /*物理*/
                };
                uint32_t num;                                               /*学号*/
                std::string name;                                           /*姓名*/
                uint8_t age;                                                /*年龄*/
                std::string sex;                                            /*性别*/
                uint64_t tel;                                               /*电话*/
                std::string address;                                        /*地址*/
                uint64_t identity_card;                                     /*证号*/
                subject grades;                                             /*成绩*/
                void student_printf() const
                {
                    std::cout << "学号：" << num               << " ";
                    std::cout << "姓名：" << name              << " ";
                    std::cout << "年龄：" << age               << " ";
                    std::cout << "性别：" << sex               << " ";
                    std::cout << "电话：" << tel               << " ";
                    std::cout << "地址：" << address           << " ";
                    std::cout << "证号：" << identity_card     << " ";
                    std::cout << "语文：" << grades.Chinese    << " ";
                    std::cout << "数学：" << grades.Math       << " ";
                    std::cout << "英语：" << grades.English    << " ";
                    std::cout << "政治：" << grades.politics   << " ";
                    std::cout << "历史：" << grades.history    << " ";
                    std::cout << "地理：" << grades.geography  << " ";
                    std::cout << "生物：" << grades.biology    << " ";
                    std::cout << "化学：" << grades.chemistry  << " ";
                    std::cout << "物理：" << grades.physics    << std::endl;
                }
                student()
                {
                    ;
                }
                student(const student& Student_volume)
                {
                    num = Student_volume.num;
                    name= Student_volume.name;
                    age = Student_volume.age;
                    sex = Student_volume.sex;
                    tel = Student_volume.tel;
                    address = Student_volume.address;
                    identity_card = Student_volume.identity_card;
                    grades = Student_volume.grades;
                }
        };
        student* data;
        student_list* prev;
        student_list* next;
        ~student_list()
        {
            delete data;
        }
    };
    public:
    student_list* head;
    Information_management()
    {
        head = nullptr;
    }
    Information_management(const Information_management& Information_management_volume)
    {
        head = nullptr;
        student_list* current = Information_management_volume.head;
        student_list* prevNode = nullptr;
        while (current != nullptr)
        {
            student_list* newNode = new student_list;
            newNode->data = new student(*(current->data));
            newNode->prev = prevNode;
            newNode->next = nullptr;
            if (prevNode != nullptr)
            {
                prevNode->next = newNode;
            }
            else
            {
                head = newNode;
            }
            prevNode = newNode;
            current = current->next;
        }
    }
    ~Information_management()
    {
        student_list* current = head;
        while (current != nullptr)
        {
            student_list* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
    Information_management& operator=(const Information_management& Information_management_volume)
    {
        if (this == &Information_management_volume)
        {
            return *this;
        }
        //拷贝整个链表
        student_list* current = head;
        while (current != nullptr)
        {
            student_list* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        // 复制新链表
        current = Information_management_volume.head;
        student_list* prevNode = nullptr;
        while (current != nullptr)
        {
            student_list* newNode = new student_list;
            newNode->data = new student(*(current->data));
            newNode->prev = prevNode;
            newNode->next = nullptr;
            if (prevNode != nullptr)
            {
                prevNode->next = newNode;
            }
            else
            {
                head = newNode;
            }
            prevNode = newNode;
            current = current->next;
        }
        return *this;
    }
    void Information_management_print_list(const Information_management* cour )
    {
        Information_management* current = cour->head;
        while (current != nullptr)
        {
            cour->Information_management_print(current->head);
            current = current->next;
        }
        std::cout <<"打印完成"<< std::endl;
    }
    void Information_management_print(const student_list* cour )  
    {
        cour->data->Information_management_print();
    }
        
};
    

int main()
{
    Information_management < int > Information_management_volume;
    return 0;
}