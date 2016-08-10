/*pager.c
 * 简单的分页程序：将指定文件的内容分页显示到标准输出上
 * 2016.07.12
 * Leon-Thomas
 * 备注：利用dup2和exec函数从定向子进程的标准输出
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "apue.h"

#define DEF_PAGER   "/bin/more"     //默认分页程序
#define MAXLINE     256             //每行最大字节数

int main(int argc, char *argv[])
{
    FILE *fp;
    int fd[2];
    pid_t pid;

    if(argc != 2)
        err_quit("Usage:<filename>");

    fp = fopen(argv[1],"r");
    if(fp == NULL)
        err_sys("fopen");

    if(pipe(fd) == -1)
        err_sys("pipe");

    if( (pid = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }else if(pid > 0)
    {   //父进程
        close(fd[0]);
        size_t n;
        char line[MAXLINE];

        while(fgets(line,MAXLINE,fp) != NULL)
        {
            n = strlen(line);
            if(write(fd[1],line,n) != n)
                err_sys("write");
        }
        if(ferror(fp))
            err_sys("fgets");

        fclose(fp);
        close(fd[1]); //及时关闭写入端，否则子进程分页程序会一直读阻塞
        if( wait(NULL) < 0)
            err_sys("wait");

        printf("已结束\n");

        exit(0);
    }else 
    {       //子进程
        close(fd[1]);
        if(fd[0] != STDIN_FILENO)
        {
            if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
                err_sys("dup2");
            close(fd[0]);
        }
        char *pager,*argv0;

        if( (pager = getenv("PAGER")) == NULL)
            pager = DEF_PAGER;
        if( (argv0 = strrchr(pager,'/')) == NULL)
            argv0 = pager;
        else 
            ++argv0;
        if(execl(pager,argv0,"-fu",(char *)0) == -1)
            err_sys("execl");
    }

    return 0;
}

