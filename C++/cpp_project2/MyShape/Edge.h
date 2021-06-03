#ifndef _EDGE_H_   //��ֹͷ�ļ����ظ������ͱ���
#define _EDGE_H_
#include<iostream>
#include<cmath>   //�������㳤�Ȼ��õ�
#include<memory>
using namespace std;
class Point
{
public:
    Point()
    {
        this->x = 0;
        this->y = 0;
    }
    Point(double x_, double y_)
    {
        this->x = x_;
        this->y = y_;
    }
    Point(const Point& p)
    {
        this->x = p.x;
        this->y = p.y;
    }
    ~Point() {} //����Ϊ���޲����Ĺ��캯�������ƹ��캯�������������������������ݹ�Ϊ��
    virtual void Print() const
    {
        cout << "(" << x << "," << y << ")";
    }//���գ�x��y������ʽ��ӡ����
    Point operator=(const Point& p)
    {
        this->x = p.x;
        this->y = p.y;
        return*this;
    }
    void set(double x_, double y_)
    {
        this->x = x_;
        this->y = y_;
    }
    double getx() const
    {
        return this->x;
    }
    double gety() const
    {
        return this->y;
    }//����get�������������ȡx��y����
    bool operator!=(const Point& p) const
    {
        if (this->x != p.x)
            return true;
        else if (this->y != p.y)
            return true;
        return false;
    }
    bool operator==(const Point& p) const
    {
        if (this->x == p.x)
            if (this->y == p.y)
                return true;
        return false;
    }//������������ر��ں���ͼ���Ƿ�Ϸ��ж�
protected:
    double x;
    double y;
};
class Edge : public Point
{
public:
    Edge()
    {
        Point p1;
        Point p2;
    }
    Edge(Point p1_, Point p2_)
    {
        this->p1 = p1_;
        this->p2 = p2_;
    }
    Edge(const Edge& e)
    {
        this->p1 = e.p1;
        this->p2 = e.p2;
    }
    ~Edge() {} //����Ϊ���޲����Ĺ��캯�������ƹ��캯�������������������������ݹ�Ϊ��
    Edge operator=(const Edge& e)
    {
        this->p1 = e.p1;
        this->p2 = e.p2;
        return *this;
    }
    void set(Point p1_, Point p2_)
    {
        this->p1 = p1_;
        this->p2 = p2_;
    }
    void Print() const  override
    {
        cout << "The edge is from ";
        p1.Print();
        cout << " to ";
        p2.Print();
        cout << endl;
    }//���ա�The edge is from ��x��y��to��x��y����ӡ
    double getlen() const
    {
        return sqrt(pow((p1.getx() - p2.getx()), 2) + pow((p1.gety() - p2.gety()), 2));
    }//����ñߵĳ���
    void Length() const
    {
        cout << "The length of this edge is " << this->getlen() << endl;
    }//չʾ�ñߵĳ���
    Point getp1() const
    {
        return this->p1;
    }
    Point getp2() const
    {
        return this->p2;
    }//����get���������ȡ���꣬Ϊ�������������׼��
private:
    Point p1;
    Point p2;
};
#endif