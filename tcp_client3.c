/*************************************************************************
  > File Name:    tcp_client.c
  > Author:       hczbha
  > Description:
  > Created Time: 2023年12月05日 星期二 19时46分41秒
 ************************************************************************/

#include "head.h"

// 注册用户
void register_user(int cfd)
{
    char name[32], pwd[32];
    bzero(name, sizeof(name));
    bzero(pwd, sizeof(pwd));

    printf("Input username:");
    scanf("%s", name);
    printf("Input password:");
    scanf("%s", pwd);

    char buf[64];
    while (1)
    {
        bzero(buf, sizeof(buf));
        sprintf(buf, "register:%s:%s", name, pwd);

        send(cfd, buf, sizeof(buf), 0);

        char result[32];
        bzero(result, sizeof(result));

        sleep(0.5);

        int n = recv(cfd, result, sizeof(result), 0);
        printf("%d\n", n);
        if (n < 10)
        {
            printf("register_user success\n");
            break;
        }
        else
        {
            printf("register_user fail\n");
        }
    }
}

// 用户登录
void login_user(int cfd)
{
    char name[32], pwd[32];
    bzero(name, sizeof(name));
    bzero(pwd, sizeof(pwd));

    printf("Input username:");
    scanf("%s", name);
    printf("Input password:");
    scanf("%s", pwd);

    char buf[64];
    while (1)
    {
        bzero(buf, sizeof(buf));
        sprintf(buf, "login:%s:%s", name, pwd);

        send(cfd, buf, sizeof(buf), 0);

        char result[32];
        bzero(result, sizeof(result));

        sleep(0.5);

        int n = recv(cfd, result, sizeof(result), 0);
        printf("%d\n", n);
        if (n < 10)
        {
            printf("login_user success\n");
            break;
        }
        else
        {
            printf("user or mima error\n");
        }
    }

    // 文件操作函数

    int choice;
    do
    {
        printf("\n1. 查找文件\n");
        printf("2. 下载文件\n");
        printf("3. 上传文件\n");
        printf("4. 退出\n");
        printf("请选择操作： ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            file_sel(cfd);
            break;
        case 2:
            file_dow(cfd);
            break;
        case 3:
            file_up(cfd);
            break;
        case 4:
            printf("程序退出\n");
            break;

        default:
            printf("无效选择，请重新输入\n");
        }
    } while (choice != 4);
}

// 修改密码
void change_password(int cfd)
{
    char name[32], pwd[32];
    bzero(name, sizeof(name));
    bzero(pwd, sizeof(pwd));

    printf("Input username:");
    scanf("%s", name);
    printf("Input new password:");
    scanf("%s", pwd);

    char buf[64];
    while (1)
    {
        bzero(buf, sizeof(buf));
        sprintf(buf, "change:%s:%s", name, pwd);

        send(cfd, buf, sizeof(buf), 0);

        char result[32];
        bzero(result, sizeof(result));

        sleep(0.5);

        int n = recv(cfd, result, sizeof(result), 0);
        printf("%d\n", n);
        if (n < 10)
        {
            printf("change_Password success\n");
            break;
        }
        else
        {
            printf("change_Password fail\n");
        }
    }
}

// 用户注销
void log_out(int cfd)
{
    char name[32];
    bzero(name, sizeof(name));

    printf("Input username:");
    scanf("%s", name);

    char buf[64];
    while (1)
    {
        bzero(buf, sizeof(buf));
        sprintf(buf, "logout:%s", name);

        send(cfd, buf, sizeof(buf), 0);

        char result[32];
        bzero(result, sizeof(result));

        sleep(0.5);

        int n = recv(cfd, result, sizeof(result), 0);
        printf("%d\n", n);
        if (n < 10)
        {
            printf("log_out success\n");
            break;
        }
        else
        {
            printf("log_out failed\n");
        }
    }
}

//查看文件
void file_sel(int cfd)
{
    printf("jingleila\n");
    char q_buf[64];
    bzero(q_buf, sizeof(q_buf));

    printf("please path input: ");
    getchar();
    fgets(q_buf, sizeof(q_buf), stdin);
    printf("%lu\n", strlen(q_buf));
    q_buf[strlen(q_buf) - 1] = '\0';

    printf("%lu\n", strlen(q_buf));
    char c_buf[64];
    while (1)
    {

    printf("%lu\n", strlen(q_buf));
        printf("%s\n", q_buf);
        bzero(c_buf, sizeof(c_buf));
        sprintf(c_buf, "sfile:%s", q_buf);
        send(cfd, c_buf, sizeof(c_buf), 0);

        char result1[1024];
        bzero(result1, sizeof(result1));

        sleep(0.5);
        int n1;
        while (1)
        {
            n1 = recv(cfd, result1, sizeof(result1), 0);
            printf("%s\n", result1);
            printf("%d\n", n1);
            break;
        }
        if (n1 < 10)
        {
            printf("login_user success\n");
            break;
        }
        else
        {
            printf("user or mima error\n");
        }
        break;
    }
}

//下载文件
void file_dow(int cfd)
{
    char s_buf[64];
    bzero(s_buf, sizeof(s_buf));

    printf("please path input:");
    getchar();
    fgets(s_buf, sizeof(s_buf), stdin);

    printf("%lu\n", strlen(s_buf));
    s_buf[strlen(s_buf) - 1] = '\0';

    printf("%lu\n", strlen(s_buf));

    char c_buf[64];
    while (1)
    {
        bzero(c_buf, sizeof(c_buf));
        sprintf(c_buf, "download:%s", s_buf);
        send(cfd, c_buf, strlen(c_buf), 0);

        char result1[256];
        bzero(result1, sizeof(result1));

        sleep(0.5);
        int n1;
        while (1)
        {
            n1 = recv(cfd, result1, sizeof(result1), 0);
            printf("%d\n", n1);

            F f2;
            memset(&f2, 0, sizeof(f2));
            memcpy(&f2, result1, sizeof(f2));
            char *pt = strstr(f2.name, "./");
            if (pt)
            {
                printf("pt = %s\n", pt);

                FILE *fp = fopen(pt, "w+");

                fwrite(f2.cont, 1, sizeof(f2.cont), fp);
                fseek(fp, 0, SEEK_SET);
                fclose(fp);
            }
            else
            {
                printf("not found\n");
                printf("%s\n", result1);
            }

            break;
        }

        break;
    }
}

//上传文件
void file_up(int cfd)
{
    char s_buf[64];
    bzero(s_buf, sizeof(s_buf));

    printf("please path input:");
    getchar();
    fgets(s_buf, sizeof(s_buf), stdin);
    
    printf("%lu\n", strlen(s_buf));
    s_buf[strlen(s_buf) - 1] = '\0';
    printf("%lu\n", strlen(s_buf));

    char c_buf[64];
    while(1)
    {
        bzero(c_buf, sizeof(c_buf));

        sprintf(c_buf, "upload:%s", s_buf);
        send(cfd, c_buf, strlen(c_buf), 0);

        char h_buf[64];
        char l_buf[64];
        char r_buf[256];
        bzero(h_buf, sizeof(h_buf));
        bzero(l_buf, sizeof(l_buf));
        bzero(r_buf, sizeof(r_buf));

        sprintf(h_buf, "find ./ -name %s", s_buf);
        FILE* fp = popen(h_buf, "r");

        fread(l_buf, 1, sizeof(l_buf), fp);
        pclose(fp);

        F f1;
        if(strlen(l_buf) != 0)
        {
            memset(f1.name, 0, sizeof(f1.name));

            strncpy(f1.name, l_buf, strlen(l_buf) - 1);
            printf("f1.name = %s\n", f1.name);

            FILE* fp = fopen(f1.name, "r+");
            if(fp == NULL)
            {
                perror("fopen failed");
            }

            fseek(fp, 0, SEEK_SET);
            memset(f1.cont, 0, sizeof(f1.cont));
            fread(f1.cont, 1, sizeof(f1.cont), fp);
            fclose(fp);
            
            printf("cont = %s\n", f1.cont);
            memcpy(r_buf, &f1, sizeof(f1));
            send(cfd, r_buf, sizeof(r_buf), 0);
        }
        else
        {
            char b_buf[64] = "try again upload";
            send(cfd, b_buf, sizeof(b_buf), 0);
        }

        char ret[64];
        while(1)
        {
            bzero(ret, sizeof(ret));
            int n = recv(cfd, ret, sizeof(ret), 0);
            if(n > 6)
            {
                printf("upload success\n");
                break;
            }
            else
            {
                printf("upload failed\n");
                break;
            }
        }
        break;
    }
}
