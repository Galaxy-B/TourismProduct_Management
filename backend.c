#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "Backend.h"

// 函数功能：判断是登录成功，成功返回值为1，否则为0
//@param id 待查询用户账号
//@param password 待查询用户密码
//@param account_list 用户列表
//@param list_len 列表长度
//@return 1为登录成功 0为登录失败
int login_success(char *id, char *password, ACCOUNT *account_list, int list_len)
{
    int left = 0, right = list_len - 1, mid;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (!strcmp(account_list[mid].account_id, id) && !strcmp(account_list[mid].password, password))
            return 1;
        else if (strcmp(account_list[mid].account_id, id) > 0)
            right = mid - 1;
        else if (strcmp(account_list[mid].account_id, id) < 0)
            left = mid + 1;
    }
    return 0;
}

// 函数功能：读取日期
// 注意调用位置的正确性,一般在其他函数中使用
// @param fp 待读取文件
// @return 存储了日期的DATE结构体
DATE get_date(FILE *fp)
{
    DATE res;
    fscanf(fp, " %d/%d/%d", &res.year, &res.month, &res.day);
    return res;
}

// 函数功能：初始化账号清单
// @return 指向账号信息数组的指针
ACCOUNT_Ptr Init_Account(void)
{
    FILE *Account;
    if ((Account = fopen("Account.txt", "r")) == NULL)
        exit(0);
    // 如果打开文件失败就shutdown

    int Account_amount;
    // 用户总人数
    fscanf(Account, " %d", &Account_amount);
    // 读取用户总人数
    ACCOUNT_Ptr Account_List = calloc(Account_amount, sizeof(ACCOUNT));
    if (!Account_List) // 如果申请空间失败就shutdown
        exit(0);

    for (int i = 0; i < Account_amount; i++)
    {
        fscanf(Account, " %s", Account_List[i].account_id);
        fscanf(Account, " %s", Account_List[i].password);
        Account_List[i].info_ptr = Account_List[i].account_id[0] - '0';
    }
    fclose(Account);
    return Account_List;
}

// 函数功能：初始化用户清单
// 读取顺序为：总人数，编号，昵称 ，电话，收藏产品数量，收藏产品编号
// @return 指向用户信息数组的指针
USER_Ptr Init_User(void)
{
    FILE *User = fopen("User.txt", "r");
    if (User == NULL)
        exit(0);
    int User_amount;
    fscanf(User, " %d", &User_amount);
    USER_Ptr User_List = (USER_Ptr)calloc(User_amount, sizeof(USER));
    if (User_List == NULL)
        exit(0);

    for (int i = 0; i < User_amount; i++)
    {
        fscanf(User, " %d", &User_List[i].number);
        fscanf(User, " %s", User_List[i].name);
        fscanf(User, " %s", User_List[i].phone_number);
        fscanf(User, " %d", &User_List[i].collect_amount);
        for (int j = 0; j < User_List[i].collect_amount; j++)
            fscanf(User, " %d", &User_List[i].collect[j]);
    }
    return User_List;
}

// 函数功能：初始化公司清单
// @return 指向公司数组的指针
FIRM_Ptr Init_Firm(void)
{
    FILE *Firm = fopen("Firm.txt", "r");
    if (Firm == NULL)
        exit(0);
    int Firm_amount;
    fscanf(Firm, " %d", &Firm_amount);
    FIRM_Ptr Firm_List = (FIRM_Ptr)calloc(Firm_amount, sizeof(FIRM));
    if (Firm_List == NULL)
        exit(0);
    for (int i = 0; i < Firm_amount; i++)
    {
        fscanf(Firm, " %d", &Firm_List[i].number);
        fscanf(Firm, " %s", Firm_List[i].name);
        fscanf(Firm, " %s", Firm_List[i].phone_number);
        fscanf(Firm, " %d", &Firm_List[i].product_amount);
        for (int j = 0; j < Firm_List[i].product_amount; j++)
            fscanf(Firm, " %d", &Firm_List[i].product[j]);
    }
    fclose(Firm);
    return Firm_List;
}

// 函数功能：初始化某一用户的订单清单
// @param account_id 该用户的账号
// @return 指向该用户订单清单的指针
ORDER_Ptr Init_Order(char *account_id)
{
    // 得到每个账号对应的文件名称
    char account_file[20] = {0};
    strcpy(account_file, account_id);
    strcat(account_file, ".txt");
    FILE *Order = fopen(account_file, "r");
    if (Order == NULL)
        exit(0);
    int Order_amount;
    fscanf(Order, " %d", &Order_amount);
    ORDER_Ptr Order_List = (ORDER_Ptr)calloc(Order_amount, sizeof(ORDER));
    if (Order_List == NULL)
        exit(0);
    for (int i = 0; i < Order_amount; i++)
    {
        fscanf(Order, " %d", &Order_List[i].number);
        fscanf(Order, " %d", &Order_List[i].product_ptr);
        fscanf(Order, " %d", &Order_List[i].amount);
        fscanf(Order, " %s", Order_List[i].name);
        fscanf(Order, " %s", Order_List[i].phone_number);
        Order_List[i].book_time = get_date(Order);
    }
    fclose(Order);
    return Order_List;
}

// 函数功能：初始化旅游产品清单
// @return 指向旅游产品信息数组的指针
PRODUCT_Ptr Init_Product(void)
{
    FILE *Product = fopen("Product.txt", "r");
    if (Product == NULL)
        exit(0);
    int Product_amount;
    fscanf(Product, " %d", &Product_amount);
    PRODUCT_Ptr Product_List = (PRODUCT_Ptr)calloc(Product_amount, sizeof(PRODUCT));
    if (Product_List == NULL)
        exit(0);
    for (int i = 0; i < Product_amount; i++)
    {
        fscanf(Product, " %d", &Product_List[i].number);
        fscanf(Product, " %s", Product_List[i].name);
        fscanf(Product, " %s", Product_List[i].place);
        fscanf(Product, " %d", &Product_List[i].price);
        Product_List[i].start_date = get_date(Product);
        Product_List[i].end_date = get_date(Product);
        fscanf(Product, " %d", &Product_List[i].amount);
        fscanf(Product, " %d", &Product_List[i].firm_ptr);
    }
    fclose(Product);
    return Product_List;
}
