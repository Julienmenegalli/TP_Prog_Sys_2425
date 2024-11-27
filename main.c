#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define Welcome "$ ./enseash \nBienvenue dans le Shell enseash. \nTapez 'exit' pour quitter.\n"
#define BUFFER_SIZE 128
#define enseash "enseash % "
#define end "Au revoir !\n"
#define ReturnFortune "14 25 39 8 17\n"

int main() {
    char input[BUFFER_SIZE];
    char prompt[] = enseash;

    // Message d'accueil
    write(STDOUT_FILENO,Welcome , strlen (Welcome));

    while (1) {
        // Affichage du prompt
        write(STDOUT_FILENO, prompt, strlen(prompt));

        // Lire l'entrée utilisateur
        ssize_t bytes_read = read(STDIN_FILENO, input, BUFFER_SIZE - 1);

        // Ajouter un terminateur null pour en faire une chaîne valide
        input[bytes_read - 1] = '\0'; // Remplace '\n' par '\0'

        // Si l'utilisateur tape "exit", sortir de la boucle
        if (strcmp(input, "exit") == 0) {
            write(STDOUT_FILENO,end , strlen (end));
            break;
        }
        // Si l'utilisateur tape "fortune", lance la fonction fortune
        if (strcmp(input, "fortune") == 0) {
            write(STDOUT_FILENO,ReturnFortune, strlen(ReturnFortune));
        }
    }
    return 0;
}


