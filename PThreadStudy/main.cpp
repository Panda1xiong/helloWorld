//
// Created by xsl on 18-7-12.
//

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstring>


using namespace std;


void* thrCallBack(void* f)
{
//    pthread_testcancel();
//    sleep(1000);
//    pthread_testcancel();
    cout << "this is new thread" << endl;
    int* num = (int*) malloc(sizeof(int));
    *num = 110;
    return (void*)num;

}


int main(int argc, char** argv)
{
    pthread_t pid;
    if (0 != pthread_create(&pid, NULL, thrCallBack, NULL))
    {
        perror("error in pthread_cteate");
        return -1;
    }
//    pthread_cancel(pid);
    void* back;
    pthread_join(pid, &back);
    if (back == PTHREAD_CANCELED)
    {
        cout << "back is: PTHREAD_CANCELED" << back << endl;
    }
    int* out = (int*) back;
    cout << *out << endl;
    free(out);

    return 0;
}