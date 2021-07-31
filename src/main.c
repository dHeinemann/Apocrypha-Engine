#include <stdio.h>
#include <string.h>

#define INPUT_LEN 20

int main() {
    char input[INPUT_LEN];
    while (1) {
        printf("> ");
        scanf("%s", input);
        puts(input);

        if      (strcmp(input, "n") == 0) { printf("North\n"); }
        else if (strcmp(input, "s") == 0) { printf("South\n"); }
        else if (strcmp(input, "e") == 0) { printf("East\n");  }
        else if (strcmp(input, "w") == 0) { printf("West\n");  }
        else if (strcmp(input, "q") == 0) { return 0;        }
    }
    return 0;
}