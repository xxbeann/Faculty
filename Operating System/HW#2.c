#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LENGTH 100

int is_builtin_command(char *command) {
    return strcmp(command, "cd") == 0;
    /*여기서 다른 builtin명령어 form들을 추가할 수 있음*/
}

void execute_command(char *command) {

    char *arguments[MAX_LENGTH] = {NULL};
    int i = 0;
    char *token = strtok(command, " ");
    while (token != NULL && i < MAX_LENGTH - 1) {
        arguments[i++] = token;
        token = strtok(NULL, " ");
    }
    /*명령어 실행 과정에서 발생하는 오류처리 stderr*/
    arguments[i] = NULL;
    if (execvp(arguments[0], arguments) == -1) {
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    /*outfile이 지정되지 않거나 command가 3개이상일 경우 오류 메시지*/
    if (argc != 6) {
        fprintf(stderr, "Usage: %s 'command_1' '|' 'command_2' '<' 'outfile'\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    char *command1 = argv[1];
    char *command2 = argv[3];
    char *outfile = argv[5];

    int pipefd1[2];
    int pipefd2[2];
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    /*buitin command일경우 예외처리*/
    if (is_builtin_command(command1)) {
    printf("%s: builtin command\n", argv[1]);
    exit(EXIT_SUCCESS);
    }
    if (is_builtin_command(command2)) {
    printf("%s: builtin command\n", argv[3]);
    exit(EXIT_SUCCESS);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        close(pipefd1[0]);
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[1]);

        execute_command(command1);
    }

    close(pipefd1[1]);
    int outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (outfile_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        dup2(pipefd1[0], STDIN_FILENO);
        close(pipefd1[0]);
        dup2(pipefd2[1], STDOUT_FILENO);
        close(pipefd2[0]);
        close(pipefd2[1]);
        execlp("tee", "tee", outfile, (char *)NULL);
    }

    close(pipefd1[0]);
    close(pipefd2[1]);

    pid_t pid3 = fork();
    if (pid3 < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid3 == 0) {
        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[0]);

        execute_command(command2);
    }

    close(pipefd2[0]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    waitpid(pid3, NULL, 0);

    return 0;
}
