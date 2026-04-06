#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "StringView.h"

/**
 * @brief freeing the args from the memory to prevent any potential memory leaks
 */
void free_args(char **args)
{
    if (args == NULL)
        return;
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}

/**
 * @brief allocates an array the contain all the tokens and ends with null terminator
 */
char **allocateStrings(StringView *tokens)
{
    size_t token_count = 0;
    while (tokens[token_count].start != NULL)
    {
        token_count++;
    }

    // As the string view is just a window to the original string, we need to create a new array of strings to pass to execvp
    char **args = malloc((token_count + 1) * sizeof(char *));
    for (size_t i = 0; i < token_count; i++)
    {

        args[i] = malloc(tokens[i].count + 1);
        strncpy(args[i], tokens[i].start, tokens[i].count);
        args[i][tokens[i].count] = '\0';
    }

    args[token_count] = NULL;
    return args;
}

int main()
{

    while (1)
    {
        char *input = NULL;
        size_t len = 0;

        printf("ChillShell> ");

        if (getline(&input, &len, stdin) == -1)
        {
            free(input);
            exit(EXIT_SUCCESS);
        }

        StringView cmd_frame = sv(input);
        StringView *tokens = sv_Tokenizer(&cmd_frame);

        if (tokens[0].start == NULL)
        {
            free(tokens);
            free(input);
            continue;
        }

        char **args = allocateStrings(tokens);
        free(tokens);
        free(input);

        // created a child process
        pid_t pid = fork();

        if (pid < 0)
        {
            printf("failed to create a process");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            execvp(args[0], args);

            // if the program reached this place that means the execvp failed
            perror("Error ");
            exit(EXIT_FAILURE);
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
        }
        free_args(args);
    }
    return 0;
}
