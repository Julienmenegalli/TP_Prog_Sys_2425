#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define Welcome "$ ./enseash \nBienvenue dans le Shell enseash. \nTapez 'exit' pour quitter.\n"
#define BUFFER_SIZE 128
#define enseash "enseash"
#define pourcentage " % "
#define end "Au revoir !\n"
#define MSG_EXIT "[exit:%d "
#define MSG_SIGN "[sign:%d "
#define MSG_TIME " | %d ms] "

int main() {
    int status;

    char input[BUFFER_SIZE];

    // first message
    write(STDOUT_FILENO,Welcome , strlen (Welcome));

    while (1) {
        // print prompt
        write(STDOUT_FILENO, enseash, strlen(enseash));
        write(STDOUT_FILENO,pourcentage,strlen(pourcentage));

        // read user entry
        ssize_t bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);

        //  add a terminator null, to make a valid chain
        input[bytes_read - 1] = '\0'; // Remplace '\n' par '\0'

        // user type "exit" quit if
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO,end , strlen (end));
            exit(EXIT_SUCCESS);
        }
        if (fork() == 0) {
            execlp(input,input, NULL);
            exit(EXIT_FAILURE);
        }
        else {wait(&status);}

        if (WIFEXITED(status)){
            char message_to_sent[BUFFER_SIZE] = {'\0'};
            snprintf(message_to_sent, 128, MSG_EXIT, WEXITSTATUS(status));
            write(STDOUT_FILENO, message_to_sent, strlen(message_to_sent));
        }
        else if (WIFSIGNALED(status)) {
            char message_to_sent[BUFFER_SIZE] = {'\0'};
            snprintf(message_to_sent, 128, MSG_SIGN, WTERMSIG(status));
            write(STDOUT_FILENO, message_to_sent, strlen(message_to_sent));
        }
    }

    return 0;
}


