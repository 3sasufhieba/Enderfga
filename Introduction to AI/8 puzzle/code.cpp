#include <queue>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <time.h>
using namespace std;

struct borad {
    int status[9];//status[0]��status[8]��ʾ3X3�ľ���0��ʾ�ո�
    int depth;//���
    int Fn;//��������ֵ��Fn = depth + hn����ȼ������پ���
    borad* pre;//��ָ�룬ָ���ƶ�ǰ������״̬
    borad() : pre(0), status(), depth(0), Fn(INT_MAX - 1) {
        for (int j = 0; j < 9; j++) {
            status[j] = j;
        }
    }
    borad(borad* x, int i[9], int y, int z) : pre(x), depth(y), Fn(z) {
        for (int j = 0; j < 9; j++) {
            status[j] = i[j];
        }
    }
};

//���ȶ����Զ��������������
struct cmp {
    bool operator() (const borad* a, const borad* b) {
        return a->Fn > b->Fn;
    }
};

bool swapnum(int a, int b, int* status);//����Ԫ��
int getindex(int* status, int num);//���Ԫ���������ϵ�һά����
void print(int* status);//��ӡ����
int hn(int* status, int* target);//��ǰ״̬��Ŀ��״̬�������پ���
void printans(borad* cur);//��ӡ�ⷨ������
int status2int(int* status);//����״̬תΪint��ʽ
int reversesum(int* status);//����������֮��
int* randstatus(int* target);//��������ʼ״̬

int main() {
    clock_t start_t, end_t;
    double total_t;
    int go[4] = { -1,1,-3,3 };//�ĸ��ƶ�����
    int start[9] = { 1,8,7,3,0,5,4,6,2 };//��ʼ״̬
    int target[9] = { 1,2,3,4,5,6,7,8,0 };//Ŀ��״̬
    //int* start;//�����ʼ״̬
    //���������ʼ״̬
    //start = randstatus(target);
    stack<borad*> D_open;//DFS��open��ʹ��ջ����ȴ���ڱ�ͷ
    queue<borad*> B_open;//BFS��open��ʹ�ö��У����С���ڱ�ͷ
    priority_queue<borad*, vector<borad*>, cmp> A_open;//A*��open��ʹ�����ȶ��У���������ֵС��Ԫ���ڱ�ͷ
    unordered_set<int> close;//close������ѷ��ʹ���״̬��Ԫ��Ϊ״̬��int��ʽ
    //����{ 1,2,3,8,0,4,7,6,5 }==��123804765(int)
    //{ 0,1,3,8,2,4,7,6,5 }==��13824765(int)


    A_open.push(new borad(NULL, start, 0, INT_MAX - 1));
    borad* temp = A_open.top();
    printf("��ʼ״̬��");
    print(temp->status);
    printf("Ŀ��״̬��");
    print(target);

    start_t = clock();
    //--------------------------------------------start-A*-------- Fn=Gn+Hn -----------------------------//
    //��ʼ״̬ѹ�����
    printf("A* Fn=Gn+Hn��\n");
    while (!A_open.empty()) {
        //����һ��״̬
        borad* cur = A_open.top();
        A_open.pop();
        //hn=Fn-depthΪ��Ŀ��״̬�������پ��룬Ϊ0������Ŀ��״̬
        if (cur->Fn - cur->depth == 0) {
            printf("����Ŀ��״̬\nclose���СΪ%d\nĿ��״̬���Ϊ%d\n", close.size(), cur->depth);
            //printans(cur);
            break;
        }
        //���int��ʽ��״̬
        int intstatus = status2int(cur->status);
        //�����ظ�״̬
        if (close.count(intstatus)) {
            continue;
        }
        //����close����ʾ�ѷ��ʹ�
        close.insert(intstatus);
        //���0������
        int zeroindex = getindex(cur->status, 0);
        for (int i = 0; i < 4; i++) {
            //�½��ڵ㣬���Ƶ�ǰ����״̬�����+1
            borad* temp = new borad(cur, cur->status, cur->depth + 1, 0);
            //0���ĸ������ƶ�
            if (swapnum(zeroindex, zeroindex + go[i], temp->status)) {
                //�ƶ��ɹ�
                //������������ֵ�������½ڵ�
                temp->Fn = temp->depth + hn(temp->status, target);
                //����A_open��
                A_open.push(temp);
            }
            else {
                //�ƶ�ʧ��
                delete(temp);
            }
        }
    }
    //���close��
    close.clear();
    //--------------------------------------------end-A*--------- Fn=Gn+Hn -------------------------//
    end_t = clock();
    //���A_open
    while (!A_open.empty()) {
        A_open.pop();
    }
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("��ʱ�䣺%f\n\n\n", total_t);
    start_t = clock();
    //--------------------------------------------start-BFS------------------------------------------//
    //��ʼ״̬ѹ�����
    B_open.push(new borad(NULL, start, 0, INT_MAX - 1));
    printf("BFS��\n");
    while (!B_open.empty()) {
        //����һ��״̬
        borad* cur = B_open.front();
        B_open.pop();
        //��Ŀ��״̬�ľ��룬Ϊ0������Ŀ��״̬
        if (hn(cur->status, target) == 0) {
            printf("����Ŀ��״̬\nclose���СΪ%d\nĿ��״̬���Ϊ%d\n", close.size(), cur->depth);
            //printans(cur);
            break;
        }
        //���int��ʽ��״̬
        int intstatus = status2int(cur->status);
        //�����ظ�״̬
        if (close.count(intstatus)) {
            continue;
        }
        //����close����ʾ�ѷ��ʹ�
        close.insert(intstatus);

        //���0������
        int zeroindex = getindex(cur->status, 0);
        for (int i = 0; i < 4; i++) {
            //�½��ڵ㣬���Ƶ�ǰ����״̬�����+1
            borad* temp = new borad(cur, cur->status, cur->depth + 1, INT_MAX - 1);
            //0���ĸ������ƶ�
            if (swapnum(zeroindex, zeroindex + go[i], temp->status)) {
                //�ƶ��ɹ�
                B_open.push(temp);
            }
            else {
                //�ƶ�ʧ��
                delete(temp);
            }
        }
    }
    //���close��
    close.clear();
    //--------------------------------------------end-BFS------------------------------------------//
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("��ʱ�䣺%f\n\n\n", total_t);
    start_t = clock();
    //--------------------------------------------start-DFS------------------------------------------//
    //��ʼ״̬ѹ�����
    D_open.push(new borad(NULL, start, 0, INT_MAX - 1));
    printf("DFS��\n");
    while (!D_open.empty()) {
        //����һ��״̬
        borad* cur = D_open.top();
        D_open.pop();
        //if (cur->depth == 5) {
        //    break;
        //}
        //��Ŀ��״̬�ľ��룬Ϊ0������Ŀ��״̬
        if (hn(cur->status, target) == 0) {
            printf("����Ŀ��״̬\nclose���СΪ%d\nĿ��״̬���Ϊ%d\n", close.size(), cur->depth);
            //printans(cur);
            break;
        }
        //���int��ʽ��״̬
        int intstatus = status2int(cur->status);
        //�����ظ�״̬
        if (close.count(intstatus)) {
            continue;
        }
        //����close����ʾ�ѷ��ʹ�
        close.insert(intstatus);

        //���0������
        int zeroindex = getindex(cur->status, 0);
        for (int i = 0; i < 4; i++) {
            //�½��ڵ㣬���Ƶ�ǰ����״̬�����+1
            borad* temp = new borad(cur, cur->status, cur->depth + 1, INT_MAX - 1);
            //0���ĸ������ƶ�
            if (swapnum(zeroindex, zeroindex + go[i], temp->status)) {
                //�ƶ��ɹ�
                D_open.push(temp);
            }
            else {
                //�ƶ�ʧ��
                delete(temp);
            }
        }
    }
    //--------------------------------------------end-DFS------------------------------------------//
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("��ʱ�䣺%f\n", total_t);
    //delete(start);
    return 1;
}

//��ӡ����
void print(int* status) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0) {
            printf("\n");
        }
        printf("%d ", status[i]);

    }
    printf("\n\n");
}

//���Ԫ���������ϵ�һά����
int getindex(int* status, int num) {
    for (int i = 0; i < 9; i++) {
        if (status[i] == num) {
            return i;
        }
    }
    return -1;
}

//����Ԫ��
bool swapnum(int a, int b, int* status) {
    if (b >= 0 && b <= 8 && (a / 3 == b / 3 || a % 3 == b % 3)) {
        swap(status[a], status[b]);
        return true;
    }
    else {
        return false;
    }
}

//��ǰ״̬��Ŀ��״̬�������پ���
int hn(int* status, int* target) {
    //��õ�ǰ״̬��Ŀ��״̬�Ķ�άx��y����
    int x, y, xt, yt, it, h = 0;
    for (int i = 0; i < 9; i++) {
        x = i % 3;
        y = i / 3;
        it = getindex(target, status[i]);
        xt = it % 3;
        yt = it / 3;
        h += abs(x - xt) + abs(y - yt);
    }
    return h;
}

//��ӡ�ⷨ������
void printans(borad* cur) {
    vector<string> ans;
    while (cur) {
        ans.push_back(to_string(cur->status[0]) + to_string(cur->status[1]) + to_string(cur->status[2]) + "\n"
            + to_string(cur->status[3]) + to_string(cur->status[4]) + to_string(cur->status[5]) + "\n"
            + to_string(cur->status[6]) + to_string(cur->status[7]) + to_string(cur->status[8]));
        cur = cur->pre;
    }
    for (int i = ans.size() - 1; i >= 0; i--) {
        printf("%s\n ��\n", ans[i].c_str());
    }
    printf("END\n\n");
}

//����״̬תΪint��ʽ
int status2int(int* status) {
    int res = 0;
    for (int i = 0, j = 8; i < 9; i++, j--) {
        res += status[i] * pow(10, j);
    }
    return res;
}

//����������֮��
int reversesum(int* status) {
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        if (status[i] != 0) {
            for (int j = 0; j < i; j++) {
                if (status[j] > status[i]) {
                    sum++;
                }
            }
        }
    }
    return sum;
}

//��������ʼ״̬
int* randstatus(int* target) {
    int* start = new int[9]();
    unordered_map<int, int> nums;//��¼����ӵ���
    srand((int)time(0));
    int element, sum1, sum2;
    sum2 = reversesum(target);
    //���ݳ�ʼ״̬��Ŀ��״̬��������֮�ͣ�sum1��sum2���Ƿ���ȣ��жϳ�ʼ״̬�Ƿ��н⣬����ȣ����޽⣩���������ɳ�ʼ״̬
    do {
        for (int i = 0; i < 9; i++) {
            element = rand() % 9;
            while (nums[element]) {
                element = rand() % 9;
            }
            nums[element]++;
            start[i] = element;
        }
        //��ռ�¼
        nums.clear();
        //����������֮��
        sum1 = reversesum(start);
    } while (sum1 % 2 != sum2 % 2);
    return start;
}