#ifndef _FILEQUERY_H_
#define _FILEQUERY_H_
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
using namespace std;
//ͷ�ļ��н����������������ʵ����cppԴ�ļ���
typedef pair<string, int> PAIR;
bool cmp_by_value(const PAIR& lhs, const PAIR& rhs);
//����������Ϊmap����value������׼��
class FileQuery
{
    typedef map<string, int>::iterator mit;//������������
public:
    FileQuery(ifstream& file);
    void PrintSentences();
    void PrintSentencesAscend();
    void PrintWordCount();
    void PrintTopWordContext(int n);
private:
    map<string, int> ma;//�洢�ʻ㼰����ִ���
    mit it;//������
    vector<string> sentences;//���зָ�ľ���
    vector<string> words;//��˳�����Ĵʻ�
};

#endif
