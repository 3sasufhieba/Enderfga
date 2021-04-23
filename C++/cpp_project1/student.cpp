#include <iostream>
#include <string>
using namespace std;
class Student
{
public:
    Student()   //Ĭ�Ϲ��캯���������гɼ���ʼ��Ϊ-1���γ���Ϊ���ַ�
    {
        for (int i = 0; i < maxCourses; i++)
        {
            grades[i] = -1;
            courseNames[i] = "\0";
        }
    }
    Student(const int id, const string name) : id(id), name(name)  //���캯�����ö�Ӧ�Ĳ�����ʼ��
    {
        for (int i = 0; i < maxCourses; i++)
        {
            grades[i] = -1;
            courseNames[i] = "\0";
        }
    }
    Student(const Student& s)   //�������캯����ע����ȸ��ƣ�
    {
        this->id = s.id;
        this->name = s.name;
        for (int i = 0; i < maxCourses; i++)
        {
            courseNames[i].append(s.courseNames[i]);
            grades[i] = s.grades[i];
        }
    }
    Student operator=(const Student& s)  //��=����������أ��ڲ�ʵ�ֲο��������캯��
    {
        if (this == &s)
            return *this;

        this->id = s.id;
        this->name = s.name;
        for (int i = 0; i < maxCourses; i++)
        {
            courseNames[i].append(s.courseNames[i]);
            grades[i] = s.grades[i];
        }

        return *this;
    }
    void SetId(int i)  //����id
    {
        id = i;
    }
    int GetId()const   //��ȡid�����const������
    {
        return id;
    }
    void SetName(string n)    //����name
    {
        name = n;
    }
    string GetName()const    //��ȡname�����const������
    {
        return name;
    }
    bool AddCourse(const string& courseName, double grade)
    {
        for (int i = 0; i < maxCourses; i++)
        {
            if (grades[i] == -1)    //����ɼ�Ϊ-1�����γ�Ϊ�գ���ӿγ���ɼ�
            {
                courseNames[i].append(courseName);
                grades[i] = grade;
                return true;    //��ӳɹ�����������
            }
            else continue;     //����Ϊ-1�����Ѿ����úÿγ���ɼ���������һ��ѭ��
        }
        return false;     //ѭ��������δ��ӣ���γ����������ʧ��
    }
    void SetGrade(const string& courseName, double grade)
    {
        for (int i = 0; i < maxCourses; i++)
        {
            if (courseNames[i] == courseName)   //����Ѱ�Ҷ�Ӧ�γ����óɼ�
            {
                grades[i] = grade;
                break;                          //������ɺ�����ѭ������������
            }
            else continue;
        }
    }
    double GetGrade(const string& courseName)const  //��ȡ�ɼ������const������
    {
        for (int i = 0; i < maxCourses; i++)
        {
            if (courseNames[i] != courseName)
            {
                return grades[i];
            }
            else continue;
        }
        return 0;
    }
    double GetAverageGrade()const     //��ȡƽ���ɼ������const������
    {
        int count = 0;//�����ѧ�����пγ���
        double sum = 0;//�����ѧ�����гɼ��ܺ�
        for (int i = 0; i < maxCourses; i++)
        {
            if (grades[i] != -1)
            {
                sum += grades[i];
                count++;
            }
            else break;
        }
        if (count == 0)   //���γ�Ϊ0������ƽ���ɼ�0
            return 0;
        else
            return sum / (1.0 * count);//����sun��count����ƽ���ɼ�������
    }
    void ShowGrades()const    //չʾѧ���ɼ������const������
    {
        cout << name << " " << id << endl;
        for (int i = 0; i < maxCourses; i++)
        {
            if (grades[i] != -1)//ͨ��-1�ж��Ƿ�ӵ�����ſκͳɼ�
                cout << courseNames[i] << ":" << grades[i] << endl;
            else break;
        }
    }

private:
    static const int maxCourses = 3;  //ͨ����̬�������������γ��� maxCourses Ϊ3
    int id;
    string name;
    string courseNames[maxCourses];
    double grades[maxCourses];
    friend class StudentClass;    //��Ԫ��StudentClass
};
class StudentClass
{
public:
    StudentClass()        //Ĭ�Ϲ��캯�����༶codeΪ���ַ�������studentָ��nullptr
    {
        code = "\0";
        for (int i = 0; i < maxStudents; i++)
        {
            students[i] = nullptr;
        }
    }
    StudentClass(const string code) : code(code)  //���캯�����ò���code��ʼ��������studentָ��nullptr
    {
        for (int i = 0; i < maxStudents; i++)
        {
            students[i] = nullptr;
        }
    }
    StudentClass(const StudentClass& sc)  //���ƹ��캯����ʹ����ȸ���
    {
        code = sc.code;
        for (int i = 0; i < maxStudents; i++)
            students[i] = sc.students[i];
    }
    ~StudentClass()
    {
        for (int i = 0; i < maxStudents; i++)
        {
            if (students[i] != nullptr)//�����ѧ����ָ��nullptr������ʱҪ��ѧ������1
                studentCount--;
            delete students[i];
        }
    }
    void SetCode(string c) //���ð༶code
    {
        code = c;
    }
    string GetCode()const //��ȡcode�����const������
    {
        return code;
    }
    bool AddStudent(const Student* student)
    {
        for (int i = 0; i < maxStudents; i++)
        {
            if (students[i] == nullptr)
            {
                students[i] = new Student(*student);//���ѧ����������һ�οռ�
                studentCount++;  //���ѧ���ɹ���ѧ����Ӧ+1
                return true;//��ӳɹ�����������
            }
        }
        return false;//ѭ�����������ʧ��
    }
    void ShowStudent(int id)const//չʾѧ����Ϣ�����const������
    {
        for (int i = 0; i < maxStudents; i++)
        {
            if (students[i]->id == id)//ͨ��id�������Ҷ�Ӧѧ��������Student���е�ShowGrades����
            {
                students[i]->ShowGrades();
                break;//չʾ����������ѭ������������
            }
        }
    }
    void ShowStudentsByIdOrder(bool(*compare)(int, int))
    {
        int k;
        Student* temp;
        for (int i = 0; i < studentCount - 1; ++i)//ð������
        {
            k = i;
            for (int j = i + 1; j < studentCount; ++j)
            {
                if ((*compare)(students[j]->id, students[k]->id))//�ú����Ĺؼ��������������ǽ���
                {
                    k = j;
                }
            }
            if (k != i)
            {
                temp = students[k];
                students[k] = students[i];
                students[i] = temp;
            }
        }
        cout << "In the order specified��" << endl;//����ָ��˳���ӡѧ�������Ϣ
        for (int i = 0; i < studentCount; ++i)
        {
            cout << students[i]->name << endl;
        }
    }
    static void showStudentCount()   //��̬��������ӡ��ǰѧ������
    {
        cout << "studentCount = " << studentCount << endl;
    }
private:
    static const int maxStudents = 20;
    static int studentCount;
    string code;
    Student* students[maxStudents];
};
int StudentClass::studentCount = 0;
bool ascending(int i1, int i2)//����bool����
{
    return i1 < i2;
}
bool descending(int i1, int i2)//����bool����
{
    return i1 > i2;
}
int main()
{
    Student s1(4001, "Bob");
    s1.AddCourse("Robotics", 95);
    s1.AddCourse("C++", 92);
    s1.AddCourse("Math", 89);
    Student s2(s1);
    s2.SetId(4003);
    s2.SetName("John");
    s2.SetGrade("Robotics", 88);
    s2.SetGrade("C++", 90);
    s2.SetGrade("Math", 91);
    Student s3;
    s3.SetId(4002);
    s3.SetName("Alice");
    s3.AddCourse("Robotics", 99);
    s3.AddCourse("C++", 98);
    s3.AddCourse("Math", 87);
    cout << "----------------" << endl;//�ָ��ߣ��ְ��չʾ��������
    cout << s3.GetName() << " :" << s3.GetId() << " :" << "C++ :" << s3.GetGrade("C++") << endl;
    cout << "----------------" << endl;
    s1.ShowGrades();
    cout << s1.GetName() << " :" << "AverageGrade :" << s1.GetAverageGrade() << endl;
    cout << "----------------" << endl;
    s2.ShowGrades();
    cout << s2.GetName() << " :" << "AverageGrade :" << s2.GetAverageGrade() << endl;
    cout << "----------------" << endl;
    s3.ShowGrades();
    cout << s3.GetName() << " :" << "AverageGrade :" << s3.GetAverageGrade() << endl;
    cout << "--------------------------------" << endl;//�ָ��ߣ����˲�����Student����������
    StudentClass sc1;
    StudentClass sc2("zngc1");
    StudentClass sc3(sc2);
    sc1.SetCode("zngc2");
    sc3.SetCode("znhc3");
    cout << "Class code list��" << sc2.GetCode() << "," << sc1.GetCode() << "," << sc3.GetCode() << "," << endl;
    cout << "----------------" << endl;
    sc2.AddStudent(&s1);
    sc2.AddStudent(&s2);
    sc2.AddStudent(&s3);
    sc2.showStudentCount();
    cout << "----------------" << endl;
    Student s4;
    s4 = s1;
    s4.SetName("Enderfga");
    s4.SetId(4004);
    sc2.AddStudent(&s4);
    sc2.ShowStudent(4004);
    cout << "----------------" << endl;
    sc2.showStudentCount();
    cout << "----------------" << endl;
    sc2.ShowStudentsByIdOrder(ascending);
    cout << "----------------" << endl;
    sc2.ShowStudentsByIdOrder(descending);
    cout << "----------------" << endl;//���˲�����StudentClass�����������
    return 0;
}