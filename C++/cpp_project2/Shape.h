#ifndef _SHAPE_H_   //��ֹͷ�ļ����ظ������ͱ���
#define _SHAPE_H_
#include<iostream>
#include<cmath>//��������ܳ���Ҫʹ��
#include"Edge.h"
#include<vector>
#include<memory>
constexpr double pi = 3.1415926;//�޶��ڱ����ڵĳ�����
using namespace std;
class Shape
{
public:
    Shape() {}
    ~Shape() {}
    virtual double Circumference() const = 0;
    virtual double Area() const = 0;
    virtual void Print() const = 0;
    virtual bool IsValid()const
    {
        return UnknownValue;
    }
protected:
    static const int UnknownValue = -1;
};//ֻ�д��麯�����麯���ĳ�����shape
class Circle : public Shape
{
public:
    Circle()
    {
        Point center;
        this->radius = 0.0;
    }
    Circle(Point p, double r)
    {
        this->center = p;
        this->radius = r;
        if (!this->IsValid())
            cout << "Warning,your shape is invalid. " << endl;//����֮����кϷ����ж�
    }
    Circle(const Circle& c)
    {
        this->center = c.center;
        this->radius = c.radius;
    }
    ~Circle() {} //����Ϊ���޲����Ĺ��캯�������ƹ��캯�������������������������ݹ�Ϊ��
    double Circumference() const  override
    {
        if (!this->IsValid())
            return UnknownValue; //�����Ϸ�������-1
        return 2 * pi * radius;
    }//���������ʽ����
    double Area() const  override
    {
        return pi * pow(radius, 2);    //�����ܳ���ʽ����
    }
    void set(Point p, double r)
    {
        this->center = p;
        this->radius = r;
    }
    void Print() const  override
    {
        if (this->IsValid())
        {
            printf("This is a circle with a radius of %f at the center of ", radius);
            center.Print();
            cout << " The circumference is: " << Circumference() << ",the area is: " << Area() << endl;
        }//���Ϸ�����ӡ������ͼ����Ϣ��Բ�ģ��뾶���ܳ������
    }
    virtual bool IsValid()const override
    {
        if (radius > 0)
            return true;
        else return false;
    }//Բ���԰뾶�Ƿ����0Ϊ�жϺϷ�����׼
    Circle operator&(const Circle& c)
    {
        if (typeid(*this) == typeid(c)) //�ж��Ƿ�Ϊͬһ��
        {
            Point center_(0.5 * (this->center.getx() + c.center.getx()), 0.5 * (this->center.gety() + c.center.gety()));
            Edge diam(this->center, c.center);
            if (diam.getlen() < (this->radius + c.radius))
            {
                Circle result;
                return result;
            }
            Circle result(center_, 0.5 * diam.getlen());
            return result;
        }
        Circle result;
        return result;
    }
    Circle operator|(const Circle& c)
    {
        if (typeid(*this) == typeid(c)) //�ж��Ƿ�Ϊͬһ��
        {
            Point center_(0.5 * (this->center.getx() + c.center.getx()), 0.5 * (this->center.gety() + c.center.gety()));
            Edge diam(this->center, c.center);
            if (diam.getlen() >= (this->radius + c.radius))
            {
                Circle result;
                return result;
            }
            Circle result(center_, 0.5 * diam.getlen());
            return result;
        }
        Circle result;
        return result;
    }//Բ�εĲ��ͽ�������������Բ��Ϊ�˵��ֱ��d��Բ���������ڲ�����d>r1+r2 ������d<r1+r2
private:
    Point center;
    double radius;
};
double LinearIntegration(const Point& p1, const Point& p2)
{
    return 0.5 * (p2.getx() - p1.getx()) * (p2.gety() + p1.gety());
}//�ú��������ڳ�Ա���������ڸ�������n�������
class Polygon : public Shape
{
public:
    Polygon()
    {
        vector<shared_ptr<Edge>> edges;
        sides = edges.size();
    }
    Polygon(vector<shared_ptr<Edge>> es)
    {
        this->edges = es;
        this->sides = edges.size();
        if (!this->IsValid())
            cout << "Warning,your shape is invalid. " << endl;//����֮����кϷ����ж�
    }
    Polygon(const Polygon& p)
    {
        this->edges = p.edges;
        this->sides = edges.size();
    }
    ~Polygon() {} //����Ϊ���޲����Ĺ��캯�������ƹ��캯�������������������������ݹ�Ϊ��
    vector<Point> getpoints(vector<shared_ptr<Edge>> edges, int length) const
    {
        vector<Point> points;
        for (int i = 0; i < length; ++i)
        {
            points.push_back((*edges[i]).getp1());
        }
        return points;
    }//�ú������ڻ�ö���ε����е㣬������β��ӣ���ֻ��ȫ��ȡ��һ���㼴��
    double Circumference() const  override
    {
        double sum = 0;
        for (int i = 0; i < sides; ++i)
        {
            sum += (*edges[i]).getlen();
        }
        return sum;
    } //�ܳ������бߵ���getlen�����ۼӵ���
    double Area() const  override
    {
        if (!this->IsValid())
            return UnknownValue;
        double area = 0.0;
        int length = sides;
        vector<Point> points;
        points = getpoints(edges, length);
        for (int i = 0; i < length - 1; ++i)
        {
            area += LinearIntegration(points[i], points[i + 1]);
        }
        area += LinearIntegration(points[length - 1], points[0]);
        return area >= 0.0 ? area : -area;
    } //�ò��ֺ����ο�������һ��n���ε�����󷨣�ͨ����������������������ۼ�
    void set(vector<shared_ptr<Edge>> es)
    {
        this->edges = es;
        this->sides = edges.size();
    }
    void Print() const  override
    {
        printf("This is a polygon with %d sides\n", sides);
        for (int i = 0; i < sides; ++i)
        {
            cout << i + 1 << ":";
            (*edges[i]).Print();
        }
        cout << "The circumference is: " << Circumference() << ",the area is: " << Area() << endl;
    }//���Ϸ�����ӡ������ͼ����Ϣ�����������бߵ������յ㣬�ܳ������
    virtual bool IsValid()const override
    {
        if (sides < 3)
            return false;
        if ((*edges[sides - 1]).getp2() != (*edges[0]).getp1())
            return false;
        for (int i = 0; i < sides - 1; ++i)
        {
            if ((*edges[i]).getp2() != (*edges[i + 1]).getp1())
                return false;
        }
        return true;
    } //����ΰ��ձ����������2����ÿһ���ߵ��յ����һ�ߵ����������жϺϷ����
    Polygon operator|(const Polygon& p) //�ж��Ƿ�Ϊͬһ��
    {
        if (typeid(*this) == typeid(p))
        {
            vector<Point> v;
            vector<Point> t1;
            t1 = getpoints(this->edges, this->sides);
            vector<Point> t2;
            t2 = getpoints(p.edges, p.sides);
            for (unsigned i = 0; i < t1.size(); i++)
            {
                v.push_back(t1[i]);
            }
            for (unsigned i = 0; i < t2.size(); i++)
            {
                v.push_back(t2[i]);
            }
            vector<Point> r;
            for (int i = 0; i < 4; i++)
            {
                r.push_back(v[(rand() % (v.size() + 1))]);
            }
            vector<shared_ptr<Edge>> e;
            for (unsigned i = 0; i < r.size() - 1; i++)
            {
                Edge temp(r[i], r[i + 1]);
                shared_ptr<Edge> ptr = make_shared<Edge>(temp);
                e.push_back(ptr);
            }
            Edge temp(r.back(), r[0]);
            shared_ptr<Edge> ptr = make_shared<Edge>(temp);
            e.push_back(ptr);
            Polygon result(e);
            return result;
        }
        Polygon result;
        return result;
    }
    Polygon operator&(const Polygon& p) //�ж��Ƿ�Ϊͬһ��
    {
        if (typeid(*this) == typeid(p))
        {
            vector<Point> v;
            vector<Point> t1;
            t1 = getpoints(this->edges, this->sides);
            vector<Point> t2;
            t2 = getpoints(p.edges, p.sides);
            for (unsigned i = 0; i < t1.size(); i++)
            {
                v.push_back(t1[i]);
            }
            for (unsigned i = 0; i < t2.size(); i++)
            {
                v.push_back(t2[i]);
            }
            vector<shared_ptr<Edge>> e;
            for (unsigned i = 0; i < v.size() - 1; i++)
            {
                Edge temp(v[i], v[i + 1]);
                shared_ptr<Edge> ptr = make_shared<Edge>(temp);
                e.push_back(ptr);
            }
            Edge temp(v.back(), v[0]);
            shared_ptr<Edge> ptr = make_shared<Edge>(temp);
            e.push_back(ptr);
            Polygon result(e);
            return result;
        }
        Polygon result;
        return result;
    }//���ڱ�����ҵ���ǿ���͹���㷨�����ݣ��ʶ���εĽ��Ƿ���һ�����е��е����4���Σ����Ƿ������е���ϵ�n����
private:
    vector<shared_ptr<Edge>> edges;
    int sides;
};


#endif