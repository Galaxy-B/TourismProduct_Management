#ifndef __backend_h__
#define __backend_h__

#include <stdio.h>

typedef int ID;
#define client 1     // 顾客
#define enterprise 2 // 企业

typedef struct DATE // 日期结构体
{
    int year;
    int month;
    int day;
} DATE;

/*
---ACCOUNT结构体对应存储文件:Account.txt
*/
typedef struct ACCOUNT // 存放账号信息的结构体
{
    ID identity;         // 用户的身份(企业/顾客)
    char account_id[10]; // 账号
    char password[10];   // 密码
    int info_ptr;        // 指向对应存储文件中该账户信息的序号
} ACCOUNT, *ACCOUNT_Ptr;

/*
---USER结构体对应存储文件:User.txt
*/
typedef struct USER // 存放用户信息的结构体
{
    int number;            // 编号
    char name[20];         // 昵称
    char phone_number[12]; // 电话号码
    int collect_amount;    // 收藏产品的数量
    int collect[12];       // 存放收藏产品编号的结构体

} USER, *USER_Ptr;

/*
---FIRM结构体对应存储文件:Firm.txt
*/
typedef struct FIRM
{
    int number;            // 编号
    char name[20];         // 昵称
    char phone_number[15]; // 联系方式
    int product_amount;    // 产品数量
    int product[12];       // 存放旗下产品编号的数组
} FIRM, *FIRM_Ptr;

/*
---ORDER结构体对应存储文件:******.txt
---******为用户的账号
---所有文件存储于文件夹Order中
*/
typedef struct ORDER // 存放单个订单的结构体
{
    int number;            // 编号
    int product_ptr;       // 指向对应存储文件中对应产品的编号
    int amount;            // 购买数量
    char name[10];         // 预订人姓名
    char phone_number[12]; // 预订人电话号码
    DATE book_time;        // 下单日期
} ORDER, *ORDER_Ptr;

/*
---PRODUCT结构体对应存储文件:Product.txt
*/
typedef struct PRODUCT // 存放旅游信息的结构体
{
    int number;      // 编号
    char name[30];   // 产品名
    char place[30];  // 地点
    int price;       // 价格
    DATE start_date; // 开始日期
    DATE end_date;   // 结束日期
    int amount;      // 销售数量
    int firm_ptr;    // 指向对应存储文件中企业信息的编号
} PRODUCT, *PRODUCT_Ptr;

// 函数功能：初始化用户名单
//@return 指向用户信息数组的指针
ACCOUNT_Ptr Init_Account(void);

// 函数功能：读取日期
// 注意调用位置的正确性,一般在其他函数中使用
// @param fp 待读取文件
// @return 存储了日期的DATE结构体
DATE get_date(FILE *fp);

// 函数功能：判断是登录成功，成功返回值为1，否则为0
//@param id 待查询用户账号
//@param password 待查询用户密码
//@param account_list 用户列表
//@param list_len 列表长度
//@return 1为登录成功 0为登录失败
int login_success(char *id, char *password, ACCOUNT *account_list, int list_len);

// 函数功能：初始化账号清单
// @return 指向账号信息数组的指针
ACCOUNT_Ptr Init_Account(void);

// 函数功能：初始化用户清单
// 读取顺序为：总人数，编号，昵称 ，电话，收藏产品数量，收藏产品编号
// @return 指向用户信息数组的指针
USER_Ptr Init_User(void);

// 函数功能：初始化公司清单
// @return 指向公司数组的指针
FIRM_Ptr Init_Firm(void);

// 函数功能：初始化某一用户的订单清单
// @param account_id 该用户的账号
// @return 指向该用户订单清单的指针
ORDER_Ptr Init_Order(char *account_id);

// 函数功能：初始化旅游产品清单
// @return 指向旅游产品信息数组的指针
PRODUCT_Ptr Init_Product(void);
#endif
