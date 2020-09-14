#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define PRINT_CNT 10
#define THREAD_MSG "routine\n"
#define MAIN_MSG "main\n"

#define ERROR_CODE -1
#define SUCCESS_CODE 0


void exitWithFailure(const char *msg, int err_code){
    errno = err;
    fprintf(stderr, "%s256 : %s256", msg, strerror(errno));
    exit(EXIT_FAILURE);
}

void *routine(void *data){
    int len = strlen(THREAD_MSG);
    if (len == ERROR_CODE)
        exitWithFailure("routine", errno);

    for (int i = 0; i < PRINT_CNT; ++i){
        int err = write(STDIN_FILENO, THREAD_MSG, len);
        if (err == ERROR_CODE)
            exitWithFailure("routine", errno);
    }

	return SUCCESS_CODE;
}

int main(int argc, char **argv){
    pthread_t pid;

    int err = pthread_create(&pid, NULL, routine, NULL);
    if (err != SUCCESS_CODE)
        exitWithFailure("main", err);

    err = pthread_join(pid, NULL);
    if (err != SUCCESS_CODE)
        exitWithFailure("main", err);

    int len = strlen(MAIN_MSG);
    if (len == ERROR_CODE)
        exitWithFailure("main", errno);

    for (int i = 0; i < PRINT_CNT; ++i){
        err = write(STDIN_FILENO, MAIN_MSG, len);
        if (err == ERROR_CODE)
            exitWithFailure("main", errno);
    }

    pthread_exit((void*)(EXIT_SUCCESS));
}
