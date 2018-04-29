#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "tree.h"

// only take one argument
int parse_command(char *s, char **command, char **arg)
{
        char *p = s;
        *command = Malloc(sizeof(char) * 64);
        *arg = Malloc(sizeof(char) * 64);

        // pass lead space
        while (*p == ' ') {
                p++;
        }

        // parse command
        int i = 0;
        while (*p != ' ' && *p != '\0' && *p != '\n') {
                (*command)[i++] = *p;
                p++;
        }
        (*command)[i] = '\0';  // this is command

        while (*p == ' ') {
                p++;
        }
        
        // parse argument
        int j = 0;
        while (*p != '\0' && *p != '\n') {
                (*arg)[j++] = *p;
                p++;
        }
        (*arg)[j] = '\0';
        
        if ((*arg)[0] == '\0') {
                return 0;
        }

        return 1;
}

int main()
{
        TreePtr root_dir = file_system_init();
        TreePtr current_dir = root_dir;
        print_prompt(root_dir->file_name);

        //char command_buffer[128];
        char *command_buffer;
        command_buffer = Malloc(sizeof(char) * 128);
        size_t num = 128;
        //while (scanf("%s", command_buffer) != EOF) {
        while (getline(&command_buffer, &num, stdin) != -1) {
                //printf("%s\n", command_buffer);
                char *command, *arg;
                int num_arg = parse_command(command_buffer, &command, &arg);
                if (num_arg == 1) {  // one argument
                        if (strcmp(command, "cd") == 0) {
                                current_dir = command_cd(current_dir, arg);
                        } else if (strcmp(command, "mkdir") == 0) {
                                current_dir = command_mkdir(current_dir, arg);
                        } else if (strcmp(command, "touch") == 0) {
                                current_dir = command_touch(current_dir, arg);
                        } else if (strcmp(command, "rm") == 0) {
                                current_dir = command_rm(current_dir, arg);
                        } else {
                                printf("command not found\n");
                                print_prompt(current_dir->file_name);
                        }
                        free(command);
                        free(arg);
                } else {  // no argument
                        if (strcmp(command, "ls") == 0) {
                                current_dir = command_ls(current_dir);
                        } else if (strcmp(command, "pwd") == 0) {
                                current_dir = command_pwd(current_dir);
                        } else if (strcmp(command, "lsfs") == 0) {
                                current_dir = command_lsfs(current_dir);
                        } else {
                                printf("command not found\n");
                                print_prompt(current_dir->file_name);
                        }
                }
                memset(command_buffer, '\0', sizeof(char) * 128);
        }
        return 0;
}
