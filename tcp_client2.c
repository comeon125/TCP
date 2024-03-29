#include "head.h"

int main(int argc, char const *argv[])
{
    //创建套结字
    int cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd < 0)
    {
        perror("socket create fail");
        return -1;
    }
    else
    {
        printf("socket create success\n");
    }
        
    //连接服务端
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = 11125;
    int ret = inet_pton(AF_INET, argv[1], (struct in_addr*)&addr.sin_addr);
    if (ret == 0)
    {
        printf("inet_pton no same\n");
        return -1;
    }
    else if (ret == -1)
    {
        perror("inet_pton fail");
        return -1;
    }

    ret = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0)
    {
        perror("connect fail");
        return -1;
    }
    else
    {
        printf("connect success\n");
    }

    int choice;
    do
    {
        printf("\n1. 用户注册\n");
        printf("2. 用户登录\n");
        printf("3. 修改密码\n");
        printf("4. 用户注销\n");
        printf("5. 退出\n");
        printf("请选择操作： ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            register_user(cfd);
            break;
        case 2:
            login_user(cfd);
            break;
        case 3:
            change_password(cfd);
            break;
        case 4:
            log_out(cfd);
            break;
        case 5:
            printf("程序退出\n");
            break;
        
        default:
            printf("无效选择，请重新输入\n");
        }
    } while (choice != 5);

    //关闭套结字
    close(cfd);
        
    return 0;
}
