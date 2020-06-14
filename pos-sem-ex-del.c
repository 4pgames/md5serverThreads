/*
 *
 *   posix-semaphore-example.c: Program to demonstrate POSIX semaphores 
 *                        in C under Linux (Producer - Consumer problem)
 */
 
 // https://www.softprayog.in/programming/posix-semaphores
 // gcc posix-semaphore-example.c -o posix-semaphore-example -lpthread
 // gcc posix-semaphore-example.c -o posix-semaphore-example -lpthread -lcrypto -lssl

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define SEM_MUTEX_NAME "/sem-mutex"
#define SEM_BUFFER_COUNT_NAME "/sem-buffer-count"
#define SEM_SPOOL_SIGNAL_NAME "/sem-spool-signal"

// Buffer data structures
#define MAX_BUFFERS 500
char buf [MAX_BUFFERS] [100];
int buffer_index;
int buffer_print_index;

sem_t *mutex_sem, *buffer_count_sem, *spool_signal_sem;

void *producer (void *arg);
void *spooler (void *arg);

// https://stackoverflow.com/questions/7627723/how-to-create-a-md5-hash-of-a-string-in-c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(__APPLE__)
#  define COMMON_DIGEST_FOR_OPENSSL
#  include <CommonCrypto/CommonDigest.h>
#  define SHA1 CC_SHA1
#else
#  include <openssl/md5.h>
#endif

//gcc MD5.c -lcrypto -lssl
//sudo dnf install openssl-devel
// libssl-dev on ubuntu?

// verify-1-HelloWorld
// 3DD27BEB687E2C901480DE72728858A4



void setupSEMs(){
    //  mutual exclusion semaphore, mutex_sem with an initial value 1.
    if ((mutex_sem = sem_open (SEM_MUTEX_NAME, O_CREAT, 0660, 1)) == SEM_FAILED) {
        perror ("sem_open"); exit (1);
    }
    
    // counting semaphore, indicating the number of available buffers. Initial value = MAX_BUFFERS
    if ((buffer_count_sem = sem_open (SEM_BUFFER_COUNT_NAME, O_CREAT, 0660, MAX_BUFFERS)) == SEM_FAILED) {
        perror ("sem_open"); exit (1);
    }

    // counting semaphore, indicating the number of strings to be printed. Initial value = 0
    if ((spool_signal_sem = sem_open (SEM_SPOOL_SIGNAL_NAME, O_CREAT, 0660, 0)) == SEM_FAILED) {
        perror ("sem_open"); exit (1);
    }

}


void cleanupSEMs() {
    if (sem_unlink (SEM_MUTEX_NAME) == -1) {
        perror ("sem_unlink"); exit (1);
    }

    if (sem_unlink (SEM_BUFFER_COUNT_NAME) == -1) {
        perror ("sem_unlink"); exit (1);
    }

    if (sem_unlink (SEM_SPOOL_SIGNAL_NAME) == -1) {
        perror ("sem_unlink"); exit (1);
    }
}


int main (int argc, char **argv)
{
    pthread_t tid_producer [10], tid_spooler;
    int i, r;

    // initialization
    buffer_index = buffer_print_index = 0;
    
     for (int i =1; i<253; i++){
     // printf("%s", synthBlock(i));
     sprintf (buf [i], "verify-1-HelloWorld %d\n", i);
     printf("%s", "\n");
     }

    setupSEMs();

    cleanupSEMs();


    exit (0);
}

