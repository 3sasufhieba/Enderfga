#ifndef _SHAPEFILE_H_   //��ֹͷ�ļ����ظ������ͱ���
#define _SHAPEFILE_H_
#include<iostream>
#include"Edge.h"
#include"Shape.h"
#include<fstream>//���ڶ�ȡ�ļ�
#include<string>//�����ַ�������
#include<vector>
#include<memory>
using namespace std;
class ShapeFile
{
public:
    ShapeFile() //�ù��캯������shapes.txt��д���������ձ���
    {
        string cd1 = "#Prepresents Point, format: (x, y)";
        string cd2 = "#circle format: center, radius (int)";
        string cd3 = "#polygon format: sequence of vertices";
        //����ע�Ϳ���������Ϊ�ж�����
        ifstream in("shapes.txt");//��ȡͬһ��Ŀ¼�µ�shapes.txt
        string line;
        vector<Point> ps;//�����ȡ�ĵ㼯
        int j, k;
        j = k = 0;
        if (in) // �и��ļ�
        {
            while (getline(in, line)) // line�в�����ÿ�еĻ��з�
            {
                if (line == cd1)
                    continue;//�����ȡ����һ��ע�ͣ��������һ��ѭ��
                if (line == cd2)
                    break;//�����ȡ���ڶ���ע�ͣ��������һ��ѭ��
                Point temp((line[5] - (double)'0'), ((double)line[7] - '0'));
                //����ȡ���ַ���ȥ'0'���ҽ���ǿ������ת������������ת��Ϊ��������֣��÷���������ASCII�룬utf-8��
                ps.push_back(temp);
            }
            while (getline(in, line)) // line�в�����ÿ�еĻ��з�
            {
                if (line == cd2)
                    continue;//�����ȡ���ڶ���ע�ͣ��������һ��ѭ��
                if (line == cd3)
                    break;//�����ȡ��������ע�ͣ��������һ��ѭ��
                Circle temp(ps[((int)line[9] - '0')], ((double)line[11] - '0'));
                c.push_back(temp);
                shared_ptr<Shape> p1;
                shared_ptr<Circle> Ptr1 = make_shared<Circle>(temp);//���ƶ�ȡ��ķ�������shape��������ָ�����shapes
                p1 = dynamic_pointer_cast<Shape>(Ptr1);
                shapes.push_back(p1);
            }
            int flag = 0;//ֻ������һ�������Σ�����Ϊ�ı��Σ���������flag��������
            while (getline(in, line)) // line�в�����ÿ�еĻ��з�
            {
                if (line == cd3)
                    continue;//�����ȡ��������ע�ͣ��������һ��ѭ��
                vector<shared_ptr<Edge>> e;
                vector<Point> v;
                if (flag == 0)
                {
                    flag = 1;
                    v.push_back(ps[(int)line[10] - '0']);
                    v.push_back(ps[(int)line[14] - '0']);
                    v.push_back(ps[(int)line[18] - '0']);
                }
                else
                {
                    v.push_back(ps[(int)line[10] - '0']);
                    v.push_back(ps[(int)line[14] - '0']);
                    v.push_back(ps[(int)line[18] - '0']);
                    v.push_back(ps[(int)line[22] - '0']);
                }
                for (unsigned i = 0; i < v.size() - 1; i++)
                {
                    Edge tmp(v[i], v[i + 1]);
                    shared_ptr<Edge> ptr = make_shared<Edge>(tmp);
                    e.push_back(ptr);
                }//�Ե㼯����߼����ٹ���shape
                Edge tmp(v.back(), v[0]);
                shared_ptr<Edge> ptr = make_shared<Edge>(tmp);
                e.push_back(ptr);//���Ҫ��ͼ��պϣ���ѭ�����һ�����յ��������
                Polygon temp(e);
                p.push_back(temp);
                shared_ptr<Shape> p2;
                shared_ptr<Polygon> Ptr2 = make_shared<Polygon>(temp);
                p2 = dynamic_pointer_cast<Shape>(Ptr2);
                shapes.push_back(p2);//���ƶ�ȡ��ķ�������shape��������ָ�����shapes
            }
        }
        else // û�и��ļ�
        {
            cout << "no such file" << endl;
        }
        this->Generate();//��ȡ������txt�ļ�֮��ִ��Generate������compositeShapes
    }
    ~ShapeFile() {}
    void Generate()
    {
        //������������в��ͽ����ж��Ƿ�Ϸ������Ϸ��Ķ���push��compositeShapes��
        Circle temp;
        if ((c[0] | c[1]).IsValid())
            temp = (c[0] | c[1]);
        if ((c[0] & c[1]).IsValid())
            temp = (c[0] & c[1]);
        shared_ptr<Shape> p1;
        shared_ptr<Circle> Ptr1 = make_shared<Circle>(temp);
        p1 = dynamic_pointer_cast<Shape>(Ptr1);
        compositeShapes.push_back(p1);
        for (unsigned i = 0; i < p.size(); i++)
            for (unsigned j = i + 1; j < p.size(); j++)
            {
                Polygon temp;
                if ((p[i] | p[j]).IsValid())
                {
                    temp = (p[i] | p[j]);
                    shared_ptr<Shape> p2;
                    shared_ptr<Polygon> Ptr2 = make_shared<Polygon>(temp);
                    p2 = dynamic_pointer_cast<Shape>(Ptr2);
                    compositeShapes.push_back(p2);
                }

                if ((p[i] & p[j]).IsValid())
                {
                    temp = (p[i] & p[j]);
                    shared_ptr<Shape> p2;
                    shared_ptr<Polygon> Ptr2 = make_shared<Polygon>(temp);
                    p2 = dynamic_pointer_cast<Shape>(Ptr2);
                    compositeShapes.push_back(p2);
                }
            }
        //˫��ѭ����������shapes��Ա�����ཻ��
    }
    void Print()
    {
        for (unsigned i = 0; i < shapes.size(); i++)
            shapes.at(i)->Print();
        for (unsigned i = 0; i < compositeShapes.size(); i++)
            compositeShapes.at(i)->Print();
        //��shapes��compositeShapes����ָ���Ա���ö�Ӧ��print������ӡ
    }
private:
    vector<shared_ptr<Shape>> shapes;
    vector<shared_ptr<Shape>> compositeShapes;
    vector<Circle> c;//���Ƚ�Circle/Polygon��vector�洢������Generate
    vector<Polygon> p;
};
#endif