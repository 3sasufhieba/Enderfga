#include"FileQuery.h"
#include<iostream>
#include<algorithm>
#include<functional>
#include<fstream>
#include<map>
#include<sstream>
#include<string>
using namespace std;

bool cmp_by_value(const PAIR& lhs, const PAIR& rhs)
{
    return lhs.second > rhs.second;
}
//mapĬ����key���򣬹�ͨ���ú�������value���򣨡�>��Ϊ���򣬷�֮����

FileQuery::FileQuery(ifstream& file)
{
    string str;//�桰�С��ַ���
    string st;//�桰�ʡ��ַ���
    while (getline(file, str))
    {
        sentences.push_back(str);
        istringstream ist(str);
        while (ist >> st)
        {
            string::size_type idx1;
            string::size_type idx2;
            idx1 = st.find(',');
            idx2 = st.find('.');
            if (idx1 != string::npos || idx2 != string::npos)
                st = st.substr(0, st.length() - 1);//�����ȡ���仰���߶�����������
            words.push_back(st);
            it = ma.find(st);
            if (it != ma.end())
                ++(*it).second;//��¼��Ƶ
            else
                ma[st] = 1;
        }
    }
}
void FileQuery::PrintSentences()
{
    for (unsigned i = 0; i < sentences.size(); i++)
        cout << sentences.at(i) << endl;
}
void FileQuery::PrintSentencesAscend()
{
    sort(sentences.begin(), sentences.end(), less<string>());
    //less<string>()��װ��functional�У�����string����������
    for (unsigned i = 0; i < sentences.size(); i++)
        cout << sentences.at(i) << endl;
}
void FileQuery::PrintWordCount()
{
    //���õ�������map�е�key���ʻ㣩��value��Ƶ�ʣ���ӡ����
    for (it = ma.begin(); it != ma.end(); ++it)
        cout << (*it).first << ":" << (*it).second << endl;
}
void FileQuery::PrintTopWordContext(int n)
{
    vector<PAIR> ma(ma.begin(), ma.end());//��map��ת��Ϊvector
    sort(ma.begin(), ma.end(), cmp_by_value);//��������д�õĺ�������
    for (int i = 0; i < n; ++i)  //���ǰn����Ƶ��ߴʻ�
    {
        cout << ma[i].first << ":" << ma[i].second << endl;
        int flag = 1;//ѭ����ʼ��־
        int j = 1;//�ʻ����λ�õ����
        vector<string>::iterator begin = words.begin();
        while (flag)
        {
            auto index = find(begin, words.end(), ma[i].first);
            if (index != words.end())
            {
                cout << j << "  ǰһ�����ʣ�" << *(index - 1) << " ; "  << "��һ�����ʣ�" << *(index + 1) << endl;
                begin = index + 1;//����һ��λ�ÿ�ʼ����Ѱ������ʻ�
                j++;
            }
            else
            {
                flag = 0;//flagΪ0��ѭ������
            }
        }
    }
}

