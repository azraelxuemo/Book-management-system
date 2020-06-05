#include  <winsock.h>
#include <windows.h>
#include  <mysql.h>
#include  <stdio.h>
#include  <stdlib.h>
#include<string.h>

#define mysqlip "127.0.0.1"
#define port 3306
#define loginusername "username"
#define loginpassword "password"
#define mysqlname "library"

MYSQL *mysql;
MYSQL_RES *result;
MYSQL_ROW row; 
MYSQL_FIELD *field;

int num_fields;
int i;
char username[20];
static num=0;

int newatoi(char *s);
int isnum(char s[]);

int login();
void zhuce();
void zhuxiao(); 

int chaxun();
void selbyallbookname();
void selbywritername();
void selbytype();
void selbyunclearname();
void selbyyear();
int showallbook();
void showbyidup();
void showbyiddown();
void showbynameup();
void showbynamedown();
void showbywriterup();
void showbywriterdown();

void showuserinfo();
void showborrow();

int bookadmin();
void addbook();
int delbook();
void delbyid();
void delbybookname();
void delbywritername();
int modifybook();
void modifybookname();
void modifywritername();
void modifyremain();
void modifyfans();
void modifyyear();
void modifytype();


int useradmin();
void modifyname();
void modifypass();
void modifysex();
void modifywork();


void showalluser();

int jieshu();
int suretob(char *book_name);

int huanshu();
int suretoh(char *book_name);
void showuserborrow();
char *DeletS2(char *s1,const char *s2);

int main()
{
	mysql=mysql_init(NULL);   
	mysql_real_connect(mysql,mysqlip,loginusername,loginpassword,mysqlname,port,NULL,0);
    const char * code = "SET NAMES GB2312";  
    mysql_real_query(mysql,code,(unsigned int)strlen(code));
	while(1)
	{
		printf("欢迎您使用我们图书馆系统服务: 1.登录, 2.注册 3.注销,4.退出\n");
		int choice;
		printf("请输入您的选择:");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:login();break;
		case 2 :zhuce();break;
		case 3:zhuxiao();break;
		case 4 :printf("感谢您的使用，即将退出图书馆系统服务\n");exit(1);
		default:printf("输入无效，请重新输入\n");break;
		}
	}			
}

int login()
{
	printf("请输入用户名:");
	scanf("%s",username);
	char passwd[20];
	printf("请输入密码:");
	scanf("%s",passwd);
    char s[100]=" select id from users where username=";
    strcat(s,"'");
    strcat(s,username);
    strcat(s,"'");
    strcat(s,"and password = '");
    strcat(s,passwd);
    strcat(s,"'");
    char id[8];
	mysql_real_query(mysql,s,(unsigned int)strlen(s)) ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
    int id1;
    id1=newatoi(id);
    if(id1==0)
{
	printf("账号或者密码错误，请重试\n\n");
	num=num+1;
	if(num>3)
	 {
	 	printf("错误次数过多，退出服务\n");
	 	exit(1);
	 }
}
   else 	
	{
		printf("登录成功，即将进入使用界面\n");
	    int choice;
	    printf("当前登录用户信息:\n");
	    showuserinfo();
		while(1)
{
	printf("欢迎您使用我们图书馆系统服务:1.查询服务,2.图书数据管理服务(只支持管理员),3.借书服务,4.还书服务,5.用户信息修改服务,6.退出服务\n");
	printf("请输入您想使用的服务:"); 
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:chaxun();break;
		case 2 :bookadmin();break;
		case 3:jieshu();break;
		case 4:huanshu();break;
		case 5:useradmin();break;
		case 6 :printf("感谢您的使用，即将退出图书馆系统服务\n");return 0;break;
		default:printf("输入无效，请重新输入\n");break;
	}
}
	}
}

void zhuce()
{
	printf("请输入用户名:");
	scanf("%s",username);
	char passwd[20];
	printf("请输入密码:");
	scanf("%s",passwd);
	char sex[8];
	printf("请输入您的性别，男或女:");
	scanf("%s",sex);
	printf("请输入您的工作单位:");
	char workplace[20];
	scanf("%s",workplace);
    char s[200]=" select id from users where username=";
    strcat(s,"'");
    strcat(s,username);
    strcat(s,"'");
    char id[8];
	mysql_real_query(mysql,s,(unsigned int)strlen(s)) ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
    int id1;
    id1=newatoi(id);
    char id2[8];
    itoa(id1,id2,10);
    if(strcmp(id2,id)==0)
    printf("失败!该用户名已经存在,请重新注册\n");  
    else 
{ 
    printf("该用户名可用，马上为您注册\n");
    char m[200]="insert into users  (username,password,sex,workplace) values('";
    strcat(m,username);
    strcat(m,"','");
    strcat(m,passwd);
    strcat(m,"','");
    strcat(m,sex);
    strcat(m,"','");
    strcat(m,workplace);
    strcat(m,"'");
    strcat(m,")");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
     {
     	printf("用户注册失败\n");
		 exit(1); 
	 }
     else ;
	 printf("恭喜您注册成功\n");
     printf("这是您的用户信息请收下:\n\n");
     showuserinfo();
}
}

void zhuxiao()
{
	printf("请输入用户名:");
	scanf("%s",username);
	char passwd[20];
	printf("请输入密码:");
	scanf("%s",passwd);
    char s[200]=" select id from users where username=";
    strcat(s,"'");
    strcat(s,username);
    strcat(s,"'");
    char id[8];
	mysql_real_query(mysql,s,(unsigned int)strlen(s)) ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
    int id1;
    id1=newatoi(id);
    char id2[8];
    itoa(id1,id2,10);
    if(strcmp(id2,id)==0)
	{
	char s[200]=" select password from users where username=";
    strcat(s,"'");
    strcat(s,username);
    strcat(s,"'");
    char realpassword[20];
	mysql_real_query(mysql,s,(unsigned int)strlen(s)) ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(realpassword,row[0]);
    if(strcmp(realpassword,passwd)==0)
    {
	char w[100]=" select id from users where username=";
	strcat(w,"'"); 
	strcat(w,username);
	strcat(w,"'");
	char id[8];
	if(mysql_real_query(mysql,w,(unsigned int)strlen(w)))
    {
    	printf("执行删除用户出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
  mysql_free_result(result);
  char o[100]=" delete from users where id=";
	strcat(o,id);
	if(mysql_real_query(mysql,o,(unsigned int)strlen(o)))
    {
    	printf("执行删除用户出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE users SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行重新排序时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else printf("注销成功\n") ;
	}
	else 
	{
		printf("密码输入错误，无法注销，请重新尝试\n");
	}
    }
    else 
{
    printf("该用户不存在，请重新注销\n");
}
}


int bookadmin()
{
	if(strcmp(username,"root")!=0)
	{
		printf("你没有权限进入该系统\n");
		return 0; 
	}
    else
	{	
	while(1)
{
    int choice;
	printf("支持的图书数据管理方式如下:   1.添加书籍,   2.删除书籍,  3.修改书籍数据,   4.显示当前所有书籍,    5.显示当前所有用户信息,6.退出图书数据管理服务\n");
	printf("请输入您的图书数据管理方式:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:addbook();break;
		case 2:delbook();break;
		case 3:modifybook();break;
		case 4:showallbook();break;
		case 5:showalluser();break;
		case 6:printf("感谢您使用图书数据管理服务，即将退出图书数据管理服务\n");return 0;
		default:printf("\n\n输入无效，请重新输入\n\n");break;
	}
}
}
}
void addbook()
{
	char p[100]="select max(id) from  book";
	char maxid[8];
	 if(mysql_real_query(mysql,p,(unsigned int)strlen(p)))
    {
    	printf("查询图书管理数据库当前最大id时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    strcat(maxid,row[0]);
    mysql_free_result(result);//查询当前数据库最大id，用于解决自增的问题 
    
	int maxid1;
    char w[100]="alter table book auto_increment="; 
    char maxid2[10];
    itoa(newatoi(maxid),maxid2,10);
    strcat(w,maxid2);
    if(mysql_real_query(mysql,w,(unsigned int)strlen(w)))
    {
    	printf("修改当前自增id出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char s[200]="insert into book values(NULL,";
	char book_name[20];
	char writer_name[20];
	char remain[3];
	char year[10];
	char  type[20];
	printf("请输入图书全称:");
	scanf("%s",book_name);
	strcat(s,"'");
	strcat(s,book_name);
	strcat(s,"'");
	strcat(s,",");
	printf("请输入作者全名:");
	scanf("%s",writer_name);
	strcat(s,"'");
	strcat(s,writer_name);
	strcat(s,"'");
	strcat(s,",");
	printf("请输入书的类型:");
	scanf("%s",type);
	strcat(s,"'");
	strcat(s,type);
	strcat(s,"'");
	strcat(s,",");
	printf("请输入目前图书馆该图书的余量:");
	scanf("%s",remain);
	strcat(s,remain);
	strcat(s,",");
	strcat(s,"0");
	strcat(s,",");
	printf("请输入该书出版的时间:");
	scanf("%s",year);
	strcat(s,year);
	strcat(s,",");
	strcat(s,"1");
	strcat(s,")");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行添加图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书添加成功，添加结果如下\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,book_name);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询添加图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
int delbook()
{
	while(1)
	{
	printf("请输入您想要通过哪种方式删除书籍：1.id,2.书的全程,3.作者名称,4.退出删除\n");
	int choice;
	printf("请输入您的选择:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:delbyid();break;
		case 2:delbybookname();break;
		case 3:delbywritername();break;
		case 4:printf("感谢您的使用，即将退出图书删除服务\n");return 0;
		default:printf("\n\n输入无效，请重新输入");break; 
	}
}
}
void delbyid()
{
	char s[100]=" delete from book where id=";
	char id[8];
	printf("请输入您要删除的图书id:");
	scanf("%s",id);
	strcat(s,id);
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行删除图书出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行重新排序时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("图书删除成功，当前剩余所有图书数据结果如下\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void delbybookname()
{
		printf("\n\n");
	char s[100]=" select id from book where name=";
	char name[20];
	printf("请输入您要删除的图书全称:");
	scanf("%s",name);
	strcat(s,"'"); 
	strcat(s,name);
	strcat(s,"'");
	char id[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行删除图书出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
  mysql_free_result(result);
  char o[100]=" delete from book where id=";
	strcat(o,id);
	if(mysql_real_query(mysql,o,(unsigned int)strlen(o)))
    {
    	printf("执行删除图书出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行重新排序时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("图书删除成功，当前剩余所有图书数据结果如下\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void delbywritername()
{
	char s[100]=" select id from book where writer=";
		printf("\n\n");
	char name[20];
	printf("请输入您要删除的图书的作者名称:");
	scanf("%s",name);
	strcat(s,"'"); 
	strcat(s,name);
	strcat(s,"'");
	char id[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行删除图书出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(id,row[0]);
  mysql_free_result(result);
  char o[100]=" delete from book where id=";
	strcat(o,id);
	if(mysql_real_query(mysql,o,(unsigned int)strlen(o)))
    {
    	printf("执行删除图书出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行重新排序时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("图书删除成功，当前剩余所有图书数据结果如下\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
int modifybook()
{
	while(1)
{
	int choice;
	printf("请选择您要修改的内容：1.书名,  2.作者姓名,  3.余量,  4.热度   5.出版时间, 6.类型,7.退出修改服务\n");
	printf("请输入您的选择：");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:modifybookname();break;
		case 2:modifywritername();break;
		case 3:modifyremain();break;
		case 4:modifyfans();break;
		case 5:modifyyear();break;
		case 6:modifytype();break;
		case 7:printf("感谢您的使用，即将退出修改服务\n");return 0;
		default:printf("\n\n输入格式不正确，请重新输入\n\n");break;
	 } 
}
}
void modifybookname()
{
	char oldbookname[20];
		printf("\n\n");
	printf("请输入你要修改的图书原名:");
	scanf("%s",oldbookname);
	printf("请输入修改后的图书名称:");
	char newbookname[20];
	scanf("%s",newbookname);
	char s[100]="update book set name = ";
	strcat(s,"'");
	strcat(s,newbookname);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,oldbookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书名称时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书名称修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,newbookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifywritername()
{
		printf("\n\n");
	char bookname[20];
	printf("请输入你要修改的图书全程:");
	scanf("%s",bookname);
	printf("请输入修改后的作者名称:");
	char writername[20];
	scanf("%s",writername);
	char s[100]="update book set writer = ";
	strcat(s,"'");
	strcat(s,writername);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书作者姓名时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书作者姓名修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后图书成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifyremain()
{
		printf("\n\n");
	char bookname[20];
	printf("请输入你要修改的图书全称:");
	scanf("%s",bookname);
	printf("请输入修改后的图书余量:");
	char newremain[8];
	scanf("%s",newremain);
	char s[100]="update book set remain = ";
	strcat(s,"'");
	strcat(s,newremain);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书余量修改成功，修改结果如下\n");
		printf("\n\n");
	int remain;
	remain=newatoi(newremain);
	if(remain==0)
	{
	char s[100]="update book set stillalive = ";
	strcat(s,"'");
	strcat(s,"0");
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	}
	else 
	{
	char s[100]="update book set stillalive = ";
	strcat(s,"'");
	strcat(s,"1");
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后图书成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifyyear()
{
		printf("\n\n");
    char bookname[20];
	printf("请输入你要修改的图书全程:");
	scanf("%s",bookname);
	printf("请输入修改后的图书出版日期:");
	char year[10];
	scanf("%s",year);
	char s[100]="update book set year = ";
	strcat(s,"'");
	strcat(s,year);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书出版日期时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书出版日期修改成功，修改结果如下\n");	printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后图书成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifyfans()
{
	char bookname[20];
		printf("\n\n");
	printf("请输入你要修改的图书全称:");
	scanf("%s",bookname);
	printf("请输入修改后的图书热度:");
	char fans[8];
	scanf("%s",fans);
	char s[100]="update book set fans = ";
	strcat(s,"'");
	strcat(s,fans);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书热度时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书热度 修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后图书成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void modifytype()
{
	char bookname[20];
		printf("\n\n");
	printf("请输入你要修改的图书全称:");
	scanf("%s",bookname);
	printf("请输入修改后的图书类型:");
	char type[20];
	scanf("%s",type);
	char s[100]="update book set type = ";
	strcat(s,"'");
	strcat(s,type);
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,bookname);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行图书类型 时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("图书类型 修改成功，修改结果如下\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void showalluser()
{
	char s[200]="select * from users order by convert(username using gbk) asc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
		printf("查询");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    int n=1;
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) 
		  {
		  	while(field = mysql_fetch_field(result)) 
			 {
                printf("%-10s", field->name);
             }
            printf("\n");
          }
          printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");	
}


int chaxun()
{
	while(1)
	{
	int choice;
	printf("查询方式:  1.书名查找,  2.作者查找, 3.类别查找 ,4.模糊查找,  5.出版年份查找, 6.显示当前所有书籍, 7.查询当前用户信息, 8.查询图书借阅记录, 9.退出查询服务\n");
	printf("请输入您的查询方式:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:selbyallbookname();break;
		case 2:selbywritername();break;
		case 3:selbytype();break;
		case 4:selbyunclearname();break;
		case 5:selbyyear();break;
		case 6:showallbook();break;
		case 7:showuserinfo();break;
		case 8:showborrow();break;
		case 9:printf("感谢您使用查询服务，即将退出查询服务\n");return 0;break;
		default:printf("\n\n输入无效，请重新输入\n\n");break;
	}
}
}
void selbyallbookname()
{
	char book_name[50];
    printf("请输入您要查找的书的全称:");
    scanf("%s",book_name);
    char s[100]="select * from book where name=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");
}
void selbywritername()
{
    char writer_name[50];
    printf("请输入您要查找的作者的全称:");
    scanf("%s",writer_name);
    char s[100]="select * from book  where writer=";
    strcat(s,"'");
    strcat(s,writer_name);
    strcat(s,"'");
    strcat(s," order by convert(name using gbk) asc");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void selbytype()
{
	char s[100]="select  distinct type from book ";
     if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
         printf("%-10s", row[0] ? row[0] : "NULL");
  }
  printf("\n");
  mysql_free_result(result);
  char type[20];
  printf("请输入您想要查询的类别:");
  scanf("%s",type);
  char m[100]="select * from book where type='";
  strcat(m,type);
  strcat(m,"'");
  if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");
}
void selbyunclearname()
{
    char book_name[50];
    printf("请输入您要查找的书的关键词:");
    scanf("%s",book_name);
    char s[100]="select * from book  where name like ";
    strcat(s,"'");
    strcat(s,"%");
    strcat(s,book_name);
    strcat(s,"%");
    strcat(s,"'");
    strcat(s," order by convert(name using gbk) asc");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");
}
void selbyyear()
{
    char year[10];
    printf("请输入您要查找的书的出版时间:");
    scanf("%s",year);
    char s[100]="select * from book  where year= ";
    strcat(s,year);
    strcat(s," order by convert(name using gbk) asc"); 
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");
}
int showallbook()
{
	int choice;
	while (1)
	{
	printf("请选择展现方式:  1书号升序 2书号降序 3书名升序 4书名降序 5作者名升序 6 作者名降序 7 退出\n");
	printf("请输入您的选择:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:showbyidup();break;
		case 2:showbyiddown();break;
		case 3:showbynameup();break;
		case 4:showbynamedown();break;
		case 5:showbywriterup();break;
		case 6:showbywriterdown();break;
		case 7:return 0;break;
		default:printf("输入无效请重新输入\n");break;
	}
}
}
void showbyidup()
{
    char s[100]="select * from book order by id asc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void showbyiddown()
{
	char s[100]="select * from book order by id desc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void showbynameup()
{
  char s[100]="select * from book  order by convert(name using gbk) asc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);	
}
void showbynamedown()
{
 char s[100]="select * from book  order by convert(name using gbk) desc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);	
}
void showbywriterup()
{
  char s[100]="select * from book  order by convert(writer using gbk) asc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void showbywriterdown()
{
	char s[100]="select * from book  order by convert(writer using gbk) desc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
}
void showuserinfo()
{
	printf("用户基本信息\n");
	char o[100]="select * from users where username=";
    strcat(o,"'");
    strcat(o,username);
    strcat(o,"'");
    if(mysql_real_query(mysql,o,(unsigned int)strlen(o)))
    {
    	printf("执行查询用户信息时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n"); 
  	printf("用户借阅信息\n");
  char m[100]="select * from borrow where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询用户信息时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-20s", field->name);
             }
          printf("\n");
          }
         printf("%-20s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");
} 
void showborrow()
{
    char book_name[50];
    printf("请输入您要查找的书的全称:");
    scanf("%s",book_name);
    char s[100]="select * from borrow_list where bookname=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-20s", field->name);
             }
          printf("\n");
          }
         printf("%-20s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");	
}


int jieshu()
{
	char book_name[50];
    printf("请输入您要借阅的书的全称:");
    scanf("%s",book_name);
    char qqi[200]="select min(id) from book where name='";
	strcat(qqi,book_name);
	strcat(qqi,"'");
	mysql_real_query(mysql,qqi,(unsigned int)strlen(qqi));
	 result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
   		if(row[0]==NULL)
   	{
   		printf("Sorry,our library do not have this book,please try again \n");
   		return 0;
	   }else break;
   }
    char s[100]="select * from book where name=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
    mysql_free_result(result);
	int choice;
	printf("\n您确定是借阅这本书吗?1.是,2.不是\n");
	printf("请输入您的选择:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:suretob(book_name);break;
		case 2:printf("感谢您的使用，即将退出书籍借阅服务\n");break; 
	}
}
int suretob(char *book_name)
{
	char s[100]="select remain from book where name='";
	strcat(s,book_name)	;
	strcat(s,"'");
	char remain[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(remain,row[0]);
    mysql_free_result(result);
      int remain1;
     remain1=atoi(remain);
     char m[100]="select remaintime from users where username='";
	strcat(m,username);
	strcat(m,"'");
	char remain2[8];
	if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询可借阅次数出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(remain2,row[0]);
    mysql_free_result(result);
    int remain3;
     remain3=newatoi(remain2);
    printf("当前可借阅图书数量为%d\n",remain3);
	 if(remain1==0)
{
	 	printf("这本书不在书架上，无法被借走，即将退出服务\n");
	 	return 0;
}
	  else if(remain3==0)
{
	  	printf("您的借阅次数不足，无法借阅，即将退出服务\n");
	  	return 0;
}
	  else
{
	printf("这本书可以借阅，正在为您办理图书借阅手续，请稍等\n");
	char ti[200]="insert into borrow_list (username,bookname,borrowtime) values('";
	char pi[200]="insert into borrow values('";
	strcat(ti,username);
	strcat(pi,username);
	strcat(ti,"','");
	strcat(pi,"','");
	strcat(ti,book_name);
	strcat(pi,book_name);
	strcat(ti,"',"); 
	strcat(pi,"',");
	strcat(ti,"NOW()");
	strcat(pi,"NOW()");
	strcat(ti,")");
    strcat(pi,",");
    strcat(pi,"DATE_ADD(NOW(),INTERVAL 1 MONTH)");
	strcat(pi,")");	
	mysql_real_query(mysql,ti,(unsigned int)strlen(ti));
	mysql_real_query(mysql,pi,(unsigned int)strlen(pi));
	remain1=remain1-1;
	remain3=remain3-1;
	char newremain2[8];
	itoa(remain3,newremain2,10);
	char s[100]="update users set remaintime = ";
	strcat(s,"'");
	strcat(s,newremain2);
	strcat(s,"'");
	strcat(s,"where username = '");
	strcat(s,username);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改剩余图书借阅次数时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("图书已经借阅，您可以借阅1个月,当前用户信息为\n");
	showuserinfo();
	char newremain1[8];
	itoa(remain1,newremain1,10);
	char w[100]="update book set remain = ";
	strcat(w,"'");
	strcat(w,newremain1);
	strcat(w,"'");
	strcat(w,"where name = '");
	strcat(w,book_name);
	strcat(w,"'");
	if(mysql_real_query(mysql,w,(unsigned int)strlen(w)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	 char b[100]="select fans from book where name='";
	strcat(b,book_name);
	strcat(b,"'");
	char remain4[8];
	if(mysql_real_query(mysql,b,(unsigned int)strlen(b)))
    {
    	printf("执行查询当前图书热度出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(remain4,row[0]);
    mysql_free_result(result);
    int remain5;
     remain5=newatoi(remain4);
    remain5=remain5+1;
    itoa(remain5,remain4,10);
    char v[100]="update book set fans = '";
	strcat(v,remain4);
	strcat(v,"'");
	strcat(v,"where name = '");
	strcat(v,book_name);
	strcat(v,"'");
	if(mysql_real_query(mysql,v,(unsigned int)strlen(v)))
    {
    	printf("执行修改图书热度时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}else ;
	if(remain1==0)
	{
	char s[100]="update book set stillalive = '";
	strcat(s,"0");
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,book_name);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	}
	else 
	{
	char n[100]="update book set stillalive = '";
	strcat(n,"1");
	strcat(n,"'");
	strcat(n," where name = '");
	strcat(n,book_name);
	strcat(n,"'");
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
}
}


int huanshu()
{
	char book_name[50];
	showuserborrow();
    printf("请输入您要归还的书的全称:");
    scanf("%s",book_name);
    char qqi[200]="select min(borrowtime) from borrow where username='";
	strcat(qqi,username);
	strcat(qqi,"' and bookname = '");
	strcat(qqi,book_name);
	strcat(qqi,"'");
	char maxid23[32];
	mysql_real_query(mysql,qqi,(unsigned int)strlen(qqi));
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
	{
		if(row[0]==NULL)
		{printf("you do not have this Book borrowing records,please try again\n");
		return 0;
		}		
		 strcpy(maxid23,row[0]);
	}
	char pi[200]=" select *   from borrow where borrowtime='";
	strcat(pi,maxid23);
	strcat(pi,"' and username ='");
	strcat(pi,username);
	strcat(pi,"' and bookname = '");
	strcat(pi,book_name);
	strcat(pi,"'");
	mysql_real_query(mysql,pi,(unsigned int)strlen(pi));
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0)
		   {
             while(field = mysql_fetch_field(result)) {
                printf("%-20s", field->name);
             }
          printf("\n");
          }
         printf("%-20s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
	int choice;
	printf("您确定是归还这本书吗?1.是,2.不是\n");
	printf("请输入您的选择:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:suretoh(book_name);break;
		case 2:printf("感谢您的使用，即将退出书籍归还服务\n");break; 
	}
} 
int suretoh(char *book_name)
{
	char haha[200]="select * from borrow where username= '";
	strcat(haha,username);
	strcat(haha,"' and bookname = '");
	strcat(haha,book_name);
	strcat(haha,"'");
	strcat(haha," and unix_timestamp(duetime)>unix_timestamp(NOW())");
    mysql_real_query(mysql,haha,(unsigned int)strlen(haha));
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    if(row = mysql_fetch_row(result)==0)
		 printf("超时归还，请向xxx账号转账100元违约金\n");
	else 
		printf("恭喜你未超时归还\n");
		char s[100]="select remain from book where name='";
	strcat(s,book_name)	;
	strcat(s,"'");
	char remain[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行查询图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(remain,row[0]);
    mysql_free_result(result);
      int remain1;
     remain1=atoi(remain);
     char m[100]="select remaintime from users where username= '";
	strcat(m,username);
	strcat(m,"'");
	char remain2[8];
	if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询可借阅次数出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else;
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
         strcpy(remain2,row[0]);
    mysql_free_result(result);
    int remain3;
     remain3=newatoi(remain2);	
	printf("正在为您办理图书归还手续，请稍等\n");
	remain1=remain1+1;
	remain3=remain3+1;
	char newremain2[8];
	itoa(remain3,newremain2,10);
	char k[100]="update users set remaintime = ";
	strcat(k,"'");
	strcat(k,newremain2);
	strcat(k,"'");
	strcat(k,"where username = '");
	strcat(k,username);
	strcat(k,"'");
	if(mysql_real_query(mysql,k,(unsigned int)strlen(k)))
    {
    	printf("执行修改剩余图书借阅次数时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char newremain1[8];
	itoa(remain1,newremain1,10);
	char w[100]="update book set remain = ";
	strcat(w,"'");
	strcat(w,newremain1);
	strcat(w,"'");
	strcat(w,"where name = '");
	strcat(w,book_name);
	strcat(w,"'");
	if(mysql_real_query(mysql,w,(unsigned int)strlen(w)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	if(remain1==0)
	{
	char s[100]="update book set stillalive = '";
	strcat(s,"0");
	strcat(s,"'");
	strcat(s,"where name = '");
	strcat(s,book_name);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	}
	else 
	{
	char n[100]="update book set stillalive = '";
	strcat(n,"1");
	strcat(n,"'");
	strcat(n," where name = '");
	strcat(n,book_name);
	strcat(n,"'");
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("执行修改图书余量时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
	char ai[200]="select min(id) from borrow_list where username='";
	strcat(ai,username);
	strcat(ai,"' and bookname = '");
	strcat(ai,book_name);
	strcat(ai,"' and backtime = 0");
	char maxid[32];
	mysql_real_query(mysql,ai,(unsigned int)strlen(ai));
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   strcpy(maxid,row[0]);
	char ti[100]="update borrow_list set backtime = NOW() where id =";
	strcat(ti,maxid);
	mysql_real_query(mysql,ti,(unsigned int)strlen(ti));
	char qqi[200]="select min(borrowtime) from borrow where username='";
	strcat(qqi,username);
	strcat(qqi,"' and bookname = '");
	strcat(qqi,book_name);
	strcat(qqi,"'");
	char maxid23[32];
	mysql_real_query(mysql,qqi,(unsigned int)strlen(qqi));
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   strcpy(maxid23,row[0]);
	char pi[200]=" delete from borrow where borrowtime='";
	strcat(pi,maxid23);
	strcat(pi,"' and username ='");
	strcat(pi,username);
	strcat(pi,"' and bookname = '");
	strcat(pi,book_name);
	strcat(pi,"'");
	mysql_real_query(mysql,pi,(unsigned int)strlen(pi));
	printf("图书已经归还，当前用户信息为\n");
    showuserinfo();      
}

void showuserborrow()
{
	printf("用户借阅信息\n");
  char m[100]="select * from borrow where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询用户信息时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-20s", field->name);
             }
          printf("\n");
          }
         printf("%-20s", row[i] ? row[i] : "NULL");
      }
  }
  mysql_free_result(result);
  printf("\n");	
}
char *DeletS2(char *s1,const char *s2)
{
    char *p=s1,*q,*c,d[80];
    unsigned long n=strlen(s2);
    
    while (1) {
        q=strstr(p,s2);
        if(q==NULL)
            break;
        c=q+n;
        *q='\0';
        strcpy(d,c);
        p=strcat(p,d);
    }
    return p;
}
int  useradmin()
{
	while(1)
{
    int choice;
	printf("支持的用户信息修改如下:   1.用户名修改,   2.密码修改,  3.性别修改,   4.单位修改,    5.退出图用户信息修改服务\n");
	printf("请输入您的图书数据管理方式:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:modifyname();break;
		case 2:modifypass();break;
		case 3:modifysex();break;
		case 4:modifywork();break;
		case 5:printf("感谢您使用用户信息修改服务，即将退出用户信息修改服务\n");return 0;
		default:printf("\n\n输入无效，请重新输入\n\n");break;
	}
}
}
void modifyname()
{
	printf("请输入修改后的用户名称:");
	char newusername[20];
	scanf("%s",newusername);
	char s[100]="update users set username = ";
	strcat(s,"'");
	strcat(s,newusername);
	strcat(s,"'");
	strcat(s,"where username = '");
	strcat(s,username);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改用户名时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("用户名修改成功，修改结果如下\n");
		printf("\n\n");
		strcpy(username,newusername);
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,newusername);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后用户信息成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifypass()
{
	printf("请输入修改后的用户密码:");
	char newpassword[20];
	scanf("%s",newpassword);
	char s[100]="update users set password = ";
	strcat(s,"'");
	strcat(s,newpassword);
	strcat(s,"'");
	strcat(s,"where username = '");
	strcat(s,username);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改用户名时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("用户密码修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后用户信息成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifysex()
{
	printf("请输入修改后的用户性别:");
	char newsex[20];
	scanf("%s",newsex);
	char s[100]="update users set sex = ";
	strcat(s,"'");
	strcat(s,newsex);
	strcat(s,"'");
	strcat(s,"where username = '");
	strcat(s,username);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改用户名时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("用户密码修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后用户信息成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
void modifywork()
{
	printf("请输入修改后的用户密码:");
	char workplace[20];
	scanf("%s", workplace);
	char s[100]="update users set workplace = ";
	strcat(s,"'");
	strcat(s,workplace);
	strcat(s,"'");
	strcat(s,"where username = '");
	strcat(s,username);
	strcat(s,"'");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("执行修改用户名时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("用户密码修改成功，修改结果如下\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("执行查询修改后图书时出现异常: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("查询修改后用户信息成功，查询结果如下\n");
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   {
      for(i = 0; i < num_fields; i++)
      {
          if (i == 0) {
             while(field = mysql_fetch_field(result)) {
                printf("%-10s", field->name);
             }
          printf("\n");
          }
         printf("%-10s", row[i] ? row[i] : "NULL");
      }
  }
  printf("\n");
  mysql_free_result(result);
  	printf("\n\n");
}
int isnum(char s[])
{
    int i;
    for(i=0;i<strlen(s);i++)
	{
        if(s[i]<'0'||s[i]>'9')
		{
		return 0;
		}
	}
    return 1;
}
int newatoi(char *s)
{
	int i;  
    int n = 0;
    for (i = 0; s[i]!='\0'; i++)  
    {  
       if(s[i]>='0'&&s[i]<='9')
        n = 10 * n + (s[i] - '0');  
    }  
    return n;  
}
