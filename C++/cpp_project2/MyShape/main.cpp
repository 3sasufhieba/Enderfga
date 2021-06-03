#include<iostream>
#include"Edge.h"
#include"Shape.h"
#include"ShapeFile.h"
#include<memory>
using namespace std;
int main()
{
    Edge e1;
    e1.Print();//�޲���Ĭ�Ϲ���ı�
    Point p1(5.32, 3.23);
    Point p2(3.12, 6.33);
    Point p3(-1, -1);
    Edge e2(p1, p2);
    e2.Print();
    e2.Length();
    Circle c1;
    c1.set(p3, 1);
    if (c1.IsValid())
        c1.Print();//��Բc1�Ϸ������ӡ�����Ϣ
    Point p4(0, 3);
    Point p5(4, 0);
    vector<shared_ptr<Edge>> f;
    Edge e3(p3, p4);
    Edge e4(p4, p5);
    Edge e5(p5, p3);
    shared_ptr<Edge> ptr1 = make_shared<Edge>(e3);
    f.push_back(ptr1);
    shared_ptr<Edge> ptr2 = make_shared<Edge>(e4);
    f.push_back(ptr2);
    shared_ptr<Edge> ptr3 = make_shared<Edge>(e5);
    f.push_back(ptr3);
    Polygon P(f);
    if (P.IsValid())
        P.Print();//��������P�Ϸ������ӡ�����Ϣ
    Circle c2(p5, 1);
    (c1 & c2).Print();
    (c1 | c2).Print();
    (c1 & c2 | c2).Print();//������Բ���򽻣�����֮��
    Point t1(4, 0);
    Point t2(5, 0);
    Point t3(5, 1);
    Point t4(4, 1);
    vector<shared_ptr<Edge>> g;
    Edge e6(t1, t2);
    Edge e7(t2, t3);
    Edge e8(t3, t4);
    Edge e9(t4, t1);
    shared_ptr<Edge> ptr4 = make_shared<Edge>(e6);
    g.push_back(ptr4);
    shared_ptr<Edge> ptr5 = make_shared<Edge>(e7);
    g.push_back(ptr5);
    shared_ptr<Edge> ptr6 = make_shared<Edge>(e8);
    g.push_back(ptr6);
    shared_ptr<Edge> ptr7 = make_shared<Edge>(e9);
    g.push_back(ptr7);
    Polygon T(g);
    if (T.IsValid())
        T.Print();//���ı���T�Ϸ������ӡ�����Ϣ
    (P & T).Print();
    (P | T).Print();//����������β���
    ShapeFile sfile;//����ShapeFile�Ķ�������ļ���ȡ�ͳ�Ա���ɶ����ڹ��캯�������
    sfile.Print();//����Print��������ӡ���ж���
}