#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
    time_t t = time(NULL);
    struct tm *systime = localtime(&t);

    // 拼接操作时间
    char timestr[64];
    strftime(timestr, sizeof(timestr) - 1, "%Y-%m-%d %H:%M:%S", systime);
    printf("%s\n", timestr);

    char path[] = "../20231211/1.txt";
    char res[32];
    char *p = strrchr(path, '/');
    if (p)
    {
        snprintf(res, sizeof(res), "./%s", p + 1);
    }

    printf("%s\n", res); // ./1.txt

    // char sql[256];
    // snprintf(sql, sizeof(sql)-1, "INSERT INTO log(type, param, time) VALUES(%d, '%s', '%s')",1, "param", timestr);
    // return 0;
}
