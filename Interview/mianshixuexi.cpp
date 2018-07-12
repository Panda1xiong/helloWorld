//
// Created by Panda on 2018/6/5.
//
#include <stdio.h>
#include <thread>
#include <iostream>
#include <string.h>

using namespace std;

void show()
{

}

template<typename T, typename ... Types>
void show(const T& tmp, const Types&... args)
{
    cout << tmp << endl;
    show(args...);
}

template <class T>
class student
{
public:
    student();
    student(T t);
    ~student();
private:
public:
    T See(T t);
};

template<class T>
T student<T>::See(T t)
{
    return t;
}

template<class T>
student<T>::student()
{
    cout << "hello" << endl;
}

template<class T>
student<T>::~student()
{

}

template<class T>
student<T>::student(T t)
{
    cout<<"hello T"<<endl;
}


union
{
    int i;
    char x[2];
} a;


template<typename T1, typename T2>
auto Add(T1 x, T2 y) -> decltype(x + y)
{
    return x + y;
};

void t_show()
{
    cout << "hello world" << endl;
}

class A
{
public:
    A();
    virtual  ~A();
    virtual void show();

};

void A::show()
{
    cout << "A show" << endl;
}

A::A()
{
    cout << "A" << endl;
}

A::~A()
{
    cout << "~A" << endl;
}

class B :public A
{
public:
    B();
    ~B();
    void show();
};

B::B()
{
    cout << "B" << endl;
}

B::~B()
{
    cout << "~B" << endl;
}

void B::show()
{
    cout << "B show" << endl;
}

template<typename T>
void showArray(T* array, int len)
{
    for (int i = 0; i < len; ++i)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

//冒泡排序
void maopao(int* nums,int len)
{
    for (int i = 0; i < len - 1 ; ++i)
    {
        for (int j = 0; j < len - 1 - i ; ++j)
        {
            if (nums[j + 1] < nums[j])
            {
                swap(nums[j], nums[j + 1]);
            }
        }

    }
    showArray(nums, len);
}

//选择排序
void xuanze(int* nums, int len)
{
    int pos{0};
    for (int i = 0; i < len - 1 ; ++i)
    {
        pos = i;
        for (int j = i + 1; j < len ; ++j)
        {
            if (nums[pos] > nums[j])
            {
                pos = j;
            }
        }
        swap(nums[i], nums[pos]);
    }
    showArray(nums, len);
}

//插入排序
void charu(int* nums, int len)
{
    for (int i = 1; i < len; ++i)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[j + 1] < nums[j])
            {
                swap(nums[j + 1], nums[j]);
            } else
            {
                break;
            }
        }
    }
    showArray(nums, len);
}


int main(int argc,char** argv)
{
//    show(2, 3, 4);
//    student<int>* student1 = new student<int>;
//    cout << student1->See(33) << endl;
//    int out = 10;
//
//    thread t(t_show);
//    t.join();
//
//    cout << "a+b" << Add(3, 5.4) << endl;

//    A* b = new B;
//    b->show();
//    delete (b);
//
    int na[] = {1,4,64,1,2,4123,54,536,646,7,4,3};
//    maopao(na, sizeof(na) / sizeof(int));
//    xuanze(na, sizeof(na) / sizeof(int));
    charu(na, sizeof(na) / sizeof(int));


//
//    {
//        int N = 20, M = 30;
//        char s1[N],s2[M];
//        int dp[N][M],i,j,max_len=0;
//        gets(s1);
//        gets(s2);
//        for(i=0;i<strlen(s1);i++){
//            for(j=0;j<strlen(s2);j++){
//                if(s1[i]==s2[j]){
//                    if(i>0&&j>0){
//                        dp[i][j]=dp[i-1][j-1]+1;
//                    }else{
//                        dp[i][j]=1;
//                    }
//                    if(max_len<dp[i][j]){
//                        max_len=dp[i][j];
//                    }
//                }
//            }
//        }
//        printf("%d\n",max_len);
//    }

    return 0;
}
