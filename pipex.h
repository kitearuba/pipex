//
// Created by christian on 14/10/24.
//

#ifndef PIPEX_PIPEX_H
#define PIPEX_PIPEX_H

#include <unistd.h>  // For pipe(), fork(), dup2(), execve()
#include <fcntl.h>   // For open(), O_RDONLY, O_WRONLY
#include <stdlib.h>  // For malloc(), free(), exit()
#include <stdio.h>   // For perror()
#include <sys/wait.h> // For waitpid()

#endif //PIPEX_PIPEX_H
