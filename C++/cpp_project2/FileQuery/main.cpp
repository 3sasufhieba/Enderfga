#include "FileQuery.h"
#include <fstream>
#include <iostream>
using namespace std;
int main()
{
    string filename = "./TwoCities.txt";
    ifstream inputfile(filename);
    FileQuery text(inputfile);
    cout << "�����ǰ��д�ӡ������ԭ��" << endl;
    text.PrintSentences();
    cout << "�������������к��д�ӡ����������" << endl;
    text.PrintSentencesAscend();
    cout << "���������дʻ㼰����ִ���" << endl;
    text.PrintWordCount();
    cout << "�����ǳ��ִ�������ǰn���ʼ�������" << endl;
    text.PrintTopWordContext(3);
}