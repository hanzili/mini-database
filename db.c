#include <stdio.h>
#include <string.h>

int main() {
    char input[100];
    while (1) {
        printf("Enter command: ");
        fgets(input, 100, stdin);

        if (strcmp(input, "exit") == 0) {
            break;
        }

        printf("You entered: %s\n", input);
    }

    return 0;
}