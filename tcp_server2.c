/*************************************************************************
  > File Name:    tcp_server.c
  > Author:       hczbha
  > Description:  
  > Created Time: 2023年12月01日 星期五 19时19分05秒
 ************************************************************************/

#include "head.h"

int main(int argc,char *argv[])
{
    //创建套接字
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0)
    {
        perror("create socket fail");
        return -1;
    }
    else
    {
        printf("create socket success\n");
    }

    //绑定套接字
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 11125;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret = bind(sfd,(struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0)
    {
        perror("bind socket fail");
        return -1;
    }
    else
    {
        printf("bind socket success\n");
    }

    //监听
    ret = listen(sfd, 6);
    if (ret < 0)
    {
        perror("listen fail");
        return -1;
    }
    else
    {
        printf("listen success\n");
    }

    //接受客户端连接请求
    int len = sizeof(addr);
    int cfd = accept(sfd, (struct sockaddr*)&addr, &len);
    if (cfd < 0)
    {
        perror("accept fail");
        return -1;
    }
    else
    {
        printf("accept success\n");
    }

    //接受客户端的数据
    char buf[64];
    while(1)
    {
        bzero(buf, sizeof(buf));

        recv(cfd, buf, sizeof(buf), 0);
        char* decide = NULL;
        char* name = NULL;
        char* pwd = NULL;
        decide = strtok(buf, ":");

        //注册用户
        if (strcmp(decide, "register") == 0)
        {
            name = strtok(NULL, ":");
            pwd = strtok(NULL, ":");

            ret = insert_mysql(name, pwd);
            if (ret == 1)
            {
                printf("qqqqqqqqqq\n");
                int ret2 = send(cfd, "success", 8, 0);
                printf("%d\n", ret2);
            }
            else
            {
                printf("fafffaaf\n");
                int ret1 = send(cfd, "user or pwd error", 18, 0);
                printf("%d\n", ret1);

            }
        }

        //用户登录
        if (strcmp(decide, "login") == 0)
        {
            name = strtok(NULL, ":");
            pwd = strtok(NULL, ":");

            ret = query_mysql(name, pwd);
            if (ret == 1)
            {
                printf("qqqqqqqqqq\n");

                int ret2 = send(cfd, "success", 8, 0);
                printf("%d\n", ret2);
                break;

            }
            else
            {
                printf("fafffaaf\n");
                int ret1 = send(cfd, "user or pwd error", 18, 0);
                printf("%d\n", ret1);

            }

        }
        

        //修改密码
        if (strcmp(decide, "change") == 0)
        {
            name = strtok(NULL, ":");
            pwd = strtok(NULL, ":");

            ret = update_mysql(name, pwd);
            if (ret == 1)
            {
                printf("qqqqqqqqqq\n");
                int ret2 = send(cfd, "success", 8, 0);
                printf("%d\n", ret2);
            }
            else
            {
                printf("fafffaaf\n");
                int ret1 = send(cfd, "user or pwd error", 18, 0);
                printf("%d\n", ret1);

            }
        }

        //用户注销
        if (strcmp(decide, "logout") == 0)
        {
            name = strtok(NULL, ":");
            
            ret = delete_mysql(name);
            if (ret == 1)
            {
                printf("qqqqqqqqqq\n");
                int ret2 = send(cfd, "success", 8, 0);
                printf("%d\n", ret2);
            }
            else
            {
                printf("fafffaaf\n");
                int ret1 = send(cfd, "user or pwd error", 18, 0);
                printf("%d\n", ret1);

            }
        }
        
    }

    sleep(1);

    char r_buf[64];
    char f_buf[1024];

    while(1)
    {
        bzero(r_buf, sizeof(r_buf));
        bzero(f_buf, sizeof(f_buf));

        printf("aaaaaaaaaa\n");
        recv(cfd, r_buf, sizeof(r_buf), 0);
        
        printf("bbbbbbbbb\n");
        printf("%s\n", r_buf);
        char* decide = NULL;
        char* path = NULL;
        decide = strtok(r_buf, ":");

        printf("%s\n", decide); 

        if(strcmp(decide, "sfile") == 0)
        {
            path = strtok(NULL, ":");

            FILE* fp = popen(path, "r");
            int out = fread(f_buf, 1, sizeof(f_buf), fp);
            send(cfd, f_buf, out, 0);
            pclose(fp);
        }

        if(strcmp(decide, "download") == 0)
        {
            char h_buf[32];
            char l_buf[32];
            char s_buf[256];
            bzero(h_buf, sizeof(h_buf));
            bzero(l_buf, sizeof(l_buf));
            bzero(s_buf, sizeof(s_buf));


            path = strtok(NULL, ":");

            sprintf(h_buf, "find ./ -name %s", path);

            FILE* fp = popen(h_buf, "r");

            fread(l_buf, 1, sizeof(l_buf), fp);
            pclose(fp);
            

            F f1;
            if(strlen(l_buf) != 0)
            {
                memset(f1.name, 0, sizeof(f1.name));
                strncpy(f1.name, l_buf, strlen(l_buf)-1);

                printf("f1.name = %s\n", f1.name);

                FILE* fp = fopen(f1.name, "r+");
                if(fp == NULL)
                {
                    perror("fopen fail");
                    return -1;
                }

                fseek(fp, 0, SEEK_SET);
                memset(f1.cont, 0, sizeof(f1.cont));
                fread(f1.cont, 1, sizeof(f1.cont), fp);
                fclose(fp);

                printf("cont = %s\n", f1.cont);

                memcpy(s_buf, &f1, sizeof(f1));

                send(cfd, s_buf, sizeof(s_buf), 0);
            }
            else
            {
                send(cfd, "file fail", 10, 0);
            }

        }

        if(strcmp(decide, "upload") == 0)
        {
            char re[256];
            bzero(re, sizeof(re));
            path = strtok(NULL, ":");
            
            recv(cfd, re, sizeof(re), 0);
            F f2;
            memset(&f2, 0, sizeof(f2));
            memcpy(&f2, re, sizeof(f2));
            printf("%s\n", f2.name);
            char* p = strstr(f2.name, "./");
            printf("ccccccccccc\n");
            printf("%s\n", p);
            if(p)
            {
                printf("p = %s\n", p);
                FILE* fp1 = fopen(p, "w+");
                printf("%s\n", f2.cont);

                fwrite(f2.cont, 1, strlen(f2.cont), fp1);
                fseek(fp1, 0, SEEK_SET);
                char www[64] = "success";
                send(cfd, www, strlen(www), 0);

                fclose(fp1);
                
            }
            else
            {
                printf("receive data\n");
                send(cfd, "fail", 5, 0);
            }


        }

    }

    //关闭套结字
    close(cfd);
    close(sfd);

    return 0;
}
