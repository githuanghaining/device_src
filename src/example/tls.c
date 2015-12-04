#include <stdio.h>
#include <pthread.h>

int test_tls(int t)
{
    static __thread int err = -1;
    err = t;
    return err;
}

static void* thread_test(void* p)
{
		while(1){
    int i = (int)p;
    int t = test_tls(i);
    printf("thread %d: %d\n", i, t);
  	}
    return NULL;
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    int i;
    const int N = 3;
    pthread_t tid[N];

    for (i=0; i<N; i++) {
        pthread_create(&tid[i], NULL, thread_test, (void*)i); 
    }

    for (i=0; i<N; i++) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}
