#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#include "StringView.h"

int main()
{

    StringView cmd_frame = sv("ls -a");
    StringView *tokens = sv_Tokenizer(&cmd_frame);

    size_t token_count = 0;
    while (tokens[token_count].start != NULL)
    {
        token_count++;
    }

    char **args = malloc((token_count + 1) * sizeof(char *));
    for (size_t i = 0; i < token_count; i++)
    {

        args[i] = malloc(tokens[i].count + 1);
        strncpy(args[i], tokens[i].start, tokens[i].count);
        args[i][tokens[i].count] = '\0';
    }

    args[token_count] = NULL;

    free(tokens);

    // created a child process
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("failed to create a process");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
        printf("%d", getpid());

        printf("\nthe child now will preform the %s command :\n", args[0]);
        execvp(args[0], args);

        // if the program reached this place that means the execvp failed
        perror("the child could not preform the command");
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;

        waitpid(pid, &status, 0);

        // decoding the status value (report generated)
        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            printf("Parent: Child exited normally with code: %d\n", exit_code);
        }
        else if (WIFSIGNALED(status))
        {
            int signal_num = WTERMSIG(status);
            printf("Parent: Child was killed by signal: %d\n", signal_num);
        }
    }

    return 0;
}
