#include "OS.h"
int open(char *filename);
int close(int fd);
int open_path(char *dirname);
/*--------------全局变量-------------------------*/
extern char* myvhard;//虚拟磁盘起始地址
extern string currentdir;//当前目录
extern string cmd; //读取指令
extern USEROPEN openfilelist[MAXOPENFILE];//文件打开表
extern USEROPEN *ptrcuridr;//当前目录在文件打开表的位置
extern DISK* disk;//将内容结构化
extern char command[50];//文件名标示符

/*----------------------modify current direction---------------------*/
int cd(char *dirname) {
        USEROPEN *temp = ptrcuridr;//temp store the original value of ptrcuridr for later use
        int fd=open_path(dirname);
        if (fd != -1) {
            //close previous old
           int old=temp->pos;
            //get previous old
            if (old != 0)   //root old not match
                close(old);
            //set to work list
            ptrcuridr = openfilelist + fd;
            //assign to current direction
            currentdir= ptrcuridr->dir ;
            currentdir+= '/';
            currentdir+= ptrcuridr->fcb.filename;
            return 0;
        }
        else {
            ptrcuridr = temp;
            printf("No such file or directory\n");
            return 0;
        }
    }
