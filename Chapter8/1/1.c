#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHIMSIZE 256
#define KEYFILE_PATH "./hello.txt"
#define PROJ_CHAR 'S'

int main()
{
    int shmsize;
    int shmid;
    key_t keyval;
    char *ptr;
    char *head;

    // generate key for shmget using id of file and last 8 bits of PROJ_CHAR
    keyval = ftok(KEYFILE_PATH, (int)PROJ_CHAR);
    shmsize = SHIMSIZE;

    //Get the shared memory ID, 0660 = -rw-rw---- = allow user and group to read and write but not execute
    if ((shmid = shmget(keyval, shmsize, IPC_CREAT | 0660)) == -1)
    {
        perror("shmget");
        exit(1);
    }

    printf("shmid: %d\n", shmid);

    //Attach the shared memory
    head = ptr = (char *)shmat(shmid, 0, 0);
    if (head == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    printf("Address of shared memory: %p\n", ptr);

    //Output information of the shared memory
    while (1)
    {
        if (*ptr == 'q')
            break;
        if (*ptr != 0)
            putchar(*ptr++);
    }

    return 0;
}
