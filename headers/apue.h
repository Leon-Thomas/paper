#ifndef APUE_H
#define APUE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <stdarg>

//自定义printf输入函数
int my_printf(const char *format,...);

//提示系统错误信息并退出
#define  err_sys(msg)   \
    do{perror(msg);exit(EXIT_FAILURE);}while(0)

//提示用户错误并退出
#define err_quit(msg) \
    do{fprintf(stderr,msg);exit(EXIT_FAILURE);}while(0)



#endif //APUE_H
