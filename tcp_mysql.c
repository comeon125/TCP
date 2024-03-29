/*************************************************************************
  > File Name:    tcp_mysql.c
  > Author:       hczbha
  > Description:  
  > Created Time: 2023年12月02日 星期六 14时42分08秒
 ************************************************************************/

#include "head.h"

MYSQL* msql_init()
{
    //初始化mysql
    MYSQL* p_sql = mysql_init(NULL); 
    if (p_sql == NULL)
    {
        printf("mysql init fail\n");
        return NULL;
    }
    else 
    {
        printf("mysql init success\n");
    }

    //连接数据库
    if ( !mysql_real_connect(p_sql, "localhost", "root", "123456", "tcp_database", 0, NULL, 0) )
    {
        printf("mysql connect fail\n");
        mysql_close(p_sql);
        return NULL;
    }
    else
    {
        printf("mysql connect success\n");
    }

    return p_sql;
}

//用户登陆
int query_mysql(char* user, char* passwd)
{
    MYSQL* p_sql = msql_init();
    if (p_sql == NULL)
    {
        printf("init fail\n"); 
    }
    else
    {
        printf("init success\n");
    }
    char buf[128];
    sprintf(buf, "select * from user_table where username = '%s' and passwd = '%s';", user, passwd);

    int ret = mysql_query(p_sql, buf);

    if ( ret != 0)
    {
        
        mysql_close(p_sql);
        return -1;
    }
    else 
    {
        printf("select ok\n");
    }

    MYSQL_RES* res = mysql_store_result(p_sql);
    if (res == NULL)
    {
        printf("MYSQL_RES fail!\n");
        mysql_close(p_sql);
        return -1;
    }
    
    unsigned int fieldnum = mysql_num_fields(res);
    //printf("field count: %u\n", fieldnum);
    
    MYSQL_FIELD* fieldname = mysql_fetch_fields(res);

    //int i = 0;
    //for (i = 0; i < fieldnum; i++)
    //{
    //    printf("%12s", fieldname[i].name);
    //}
    //printf("\n");

    unsigned long rownum = mysql_num_rows(res);
    printf("row count: %lu\n", rownum);
    if (rownum == 0)
    {
        mysql_free_result(res);
        mysql_close(p_sql);
        printf("cawfagaf\n");
        return -1;
    }
    else
    {
        return 1;
    }

}

//用户注册
int insert_mysql(char* user, char* passwd)
{
    MYSQL* p_sql = msql_init();
    if (p_sql == NULL)
    {
        printf("init fail\n"); 
    }
    else
    {
        printf("init success\n");
    }
    char buf[128];
    sprintf(buf, "insert into user_table values('%s', '%s');", user, passwd);

    int ret = mysql_query(p_sql, buf);
    if (ret != 0)
    {
        printf("%s : fail\n", buf);
        mysql_close(p_sql);
        return -1;
    }
    else 
    {
        printf("select ok\n");
        return 1;
    }
}

//修改密码
int update_mysql(char* user, char* passwd)
{
    MYSQL* p_sql = msql_init();
    if (p_sql == NULL)
    {
        printf("init fail\n"); 
    }
    else
    {
        printf("init success\n");
    }
    char buf[128];
    sprintf(buf, "update user_table set passwd = '%s' where username = '%s';", passwd, user);

    int ret = mysql_query(p_sql, buf);
    if (ret != 0)
    {
        printf("%s : fail\n", buf);
        mysql_close(p_sql);
        return -1;
    }
    else 
    {
        printf("select ok\n");
        return 1;
    }
}

//用户注销
int delete_mysql(char* user)
{
    MYSQL* p_sql = msql_init();
    if (p_sql == NULL)
    {
        printf("init fail\n"); 
    }
    else
    {
        printf("init success\n");
    }
    char buf[128];
    sprintf(buf, "delete from user_table where username = '%s';", user);

    int ret = mysql_query(p_sql, buf);
    if (ret != 0)
    {
        printf("%s : fail\n", buf);
        mysql_close(p_sql);
        return -1;
    }
    else 
    {
        printf("select ok\n");
        return 1;
    }
}
