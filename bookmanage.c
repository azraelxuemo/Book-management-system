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

void login();
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

void jieshu();
int suretob(char *book_name);

void huanshu();
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
		printf("��ӭ��ʹ������ͼ���ϵͳ����: 1.��¼, 2.ע�� 3.ע��,4.�˳�\n");
		int choice;
		printf("����������ѡ��:");
		scanf("%d",&choice);
		switch(choice)
		{
		case 1:login();break;
		case 2 :zhuce();break;
		case 3:zhuxiao();break;
		case 4 :printf("��л����ʹ�ã������˳�ͼ���ϵͳ����\n");exit(1);
		default:printf("������Ч������������\n");break;
		}
	}			
}

void login()
{
	printf("�������û���:");
	scanf("%s",username);
	char passwd[20];
	printf("����������:");
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
	printf("�˺Ż����������������\n\n");
	num=num+1;
	if(num>3)
	 {
	 	printf("����������࣬�˳�����\n");
	 	exit(1);
	 }
}
   else 	
	{
		printf("��¼�ɹ�����������ʹ�ý���\n");
	    int choice;
	    printf("��ǰ��¼�û���Ϣ:\n");
	    showuserinfo();
		while(1)
{
	printf("��ӭ��ʹ������ͼ���ϵͳ����:1.��ѯ����,2.ͼ�����ݹ������(ֻ֧�ֹ���Ա),3.�������,4.�������,5.�û���Ϣ�޸ķ���,6.�˳�����\n");
	printf("����������ʹ�õķ���:"); 
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:chaxun();break;
		case 2 :bookadmin();break;
		case 3:jieshu();break;
		case 4:huanshu();break;
		case 5:useradmin();break;
		case 6 :printf("��л����ʹ�ã������˳�ͼ���ϵͳ����\n");return 0;break;
		default:printf("������Ч������������\n");break;
	}
}
	}
}

void zhuce()
{
	printf("�������û���:");
	scanf("%s",username);
	char passwd[20];
	printf("����������:");
	scanf("%s",passwd);
	char sex[8];
	printf("�����������Ա��л�Ů:");
	scanf("%s",sex);
	printf("���������Ĺ�����λ:");
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
    printf("ʧ��!���û����Ѿ�����,������ע��\n");  
    else 
{ 
    printf("���û������ã�����Ϊ��ע��\n");
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
     	printf("�û�ע��ʧ��\n");
		 exit(1); 
	 }
     else ;
	 printf("��ϲ��ע��ɹ�\n");
     printf("���������û���Ϣ������:\n\n");
     showuserinfo();
}
}

void zhuxiao()
{
	printf("�������û���:");
	scanf("%s",username);
	char passwd[20];
	printf("����������:");
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
    	printf("ִ��ɾ���û������쳣: %s",mysql_error(mysql));
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
    	printf("ִ��ɾ���û������쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE users SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("ִ����������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else printf("ע���ɹ�\n") ;
	}
	else 
	{
		printf("������������޷�ע���������³���\n");
	}
    }
    else 
{
    printf("���û������ڣ�������ע��\n");
}
}



int bookadmin()
{
	if(strcmp(username,"root")!=0)
	{
		printf("��û��Ȩ�޽����ϵͳ\n");
		return 0; 
	}
    else
	{	
	while(1)
{
    int choice;
	printf("֧�ֵ�ͼ�����ݹ���ʽ����:   1.����鼮,   2.ɾ���鼮,  3.�޸��鼮����,   4.��ʾ��ǰ�����鼮,    5.��ʾ��ǰ�����û���Ϣ,6.�˳�ͼ�����ݹ������\n");
	printf("����������ͼ�����ݹ���ʽ:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:addbook();break;
		case 2:delbook();break;
		case 3:modifybook();break;
		case 4:showallbook();break;
		case 5:showalluser();break;
		case 6:printf("��л��ʹ��ͼ�����ݹ�����񣬼����˳�ͼ�����ݹ������\n");return 0;
		default:printf("\n\n������Ч������������\n\n");break;
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
    	printf("��ѯͼ��������ݿ⵱ǰ���idʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
    result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
    strcat(maxid,row[0]);
    mysql_free_result(result);//��ѯ��ǰ���ݿ����id�����ڽ������������ 
    
	int maxid1;
    char w[100]="alter table book auto_increment="; 
    char maxid2[10];
    itoa(newatoi(maxid),maxid2,10);
    strcat(w,maxid2);
    if(mysql_real_query(mysql,w,(unsigned int)strlen(w)))
    {
    	printf("�޸ĵ�ǰ����id�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char s[200]="insert into book values(NULL,";
	char book_name[20];
	char writer_name[20];
	char remain[3];
	char year[10];
	char  type[20];
	printf("������ͼ��ȫ��:");
	scanf("%s",book_name);
	strcat(s,"'");
	strcat(s,book_name);
	strcat(s,"'");
	strcat(s,",");
	printf("����������ȫ��:");
	scanf("%s",writer_name);
	strcat(s,"'");
	strcat(s,writer_name);
	strcat(s,"'");
	strcat(s,",");
	printf("�������������:");
	scanf("%s",type);
	strcat(s,"'");
	strcat(s,type);
	strcat(s,"'");
	strcat(s,",");
	printf("������Ŀǰͼ��ݸ�ͼ�������:");
	scanf("%s",remain);
	strcat(s,remain);
	strcat(s,",");
	strcat(s,"0");
	strcat(s,",");
	printf("�������������ʱ��:");
	scanf("%s",year);
	strcat(s,year);
	strcat(s,",");
	strcat(s,"1");
	strcat(s,")");
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�����ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ����ӳɹ�����ӽ������\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,book_name);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ���ͼ��ʱ�����쳣: %s",mysql_error(mysql));
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
	printf("����������Ҫͨ�����ַ�ʽɾ���鼮��1.id,2.���ȫ��,3.��������,4.�˳�ɾ��\n");
	int choice;
	printf("����������ѡ��:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:delbyid();break;
		case 2:delbybookname();break;
		case 3:delbywritername();break;
		case 4:printf("��л����ʹ�ã������˳�ͼ��ɾ������\n");return 0;
		default:printf("\n\n������Ч������������");break; 
	}
}
}
void delbyid()
{
	char s[100]=" delete from book where id=";
	char id[8];
	printf("��������Ҫɾ����ͼ��id:");
	scanf("%s",id);
	strcat(s,id);
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ��ɾ��ͼ������쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("ִ����������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("ͼ��ɾ���ɹ�����ǰʣ������ͼ�����ݽ������\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
	printf("��������Ҫɾ����ͼ��ȫ��:");
	scanf("%s",name);
	strcat(s,"'"); 
	strcat(s,name);
	strcat(s,"'");
	char id[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ��ɾ��ͼ������쳣: %s",mysql_error(mysql));
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
    	printf("ִ��ɾ��ͼ������쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("ִ����������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("ͼ��ɾ���ɹ�����ǰʣ������ͼ�����ݽ������\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
	printf("��������Ҫɾ����ͼ�����������:");
	scanf("%s",name);
	strcat(s,"'"); 
	strcat(s,name);
	strcat(s,"'");
	char id[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ��ɾ��ͼ������쳣: %s",mysql_error(mysql));
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
    	printf("ִ��ɾ��ͼ������쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	char n[100]="UPDATE book SET id=id-1 where id>";
	strcat(n,id);
	if(mysql_real_query(mysql,n,(unsigned int)strlen(n)))
    {
    	printf("ִ����������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("ͼ��ɾ���ɹ�����ǰʣ������ͼ�����ݽ������\n");
		printf("\n\n");
	char m[100]="select * from book ";
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
	printf("��ѡ����Ҫ�޸ĵ����ݣ�1.����,  2.��������,  3.����,  4.�ȶ�   5.����ʱ��, 6.����,7.�˳��޸ķ���\n");
	printf("����������ѡ��");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:modifybookname();break;
		case 2:modifywritername();break;
		case 3:modifyremain();break;
		case 4:modifyfans();break;
		case 5:modifyyear();break;
		case 6:modifytype();break;
		case 7:printf("��л����ʹ�ã������˳��޸ķ���\n");return 0;
		default:printf("\n\n�����ʽ����ȷ������������\n\n");break;
	 } 
}
}
void modifybookname()
{
	char oldbookname[20];
		printf("\n\n");
	printf("��������Ҫ�޸ĵ�ͼ��ԭ��:");
	scanf("%s",oldbookname);
	printf("�������޸ĺ��ͼ������:");
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ�������޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,newbookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
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
	printf("��������Ҫ�޸ĵ�ͼ��ȫ��:");
	scanf("%s",bookname);
	printf("�������޸ĺ����������:");
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
    	printf("ִ���޸�ͼ����������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ�����������޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ�ͼ��ɹ�����ѯ�������\n");
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
	printf("��������Ҫ�޸ĵ�ͼ��ȫ��:");
	scanf("%s",bookname);
	printf("�������޸ĺ��ͼ������:");
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ�������޸ĳɹ����޸Ľ������\n");
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ�ͼ��ɹ�����ѯ�������\n");
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
	printf("��������Ҫ�޸ĵ�ͼ��ȫ��:");
	scanf("%s",bookname);
	printf("�������޸ĺ��ͼ���������:");
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
    	printf("ִ���޸�ͼ���������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ����������޸ĳɹ����޸Ľ������\n");	printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ�ͼ��ɹ�����ѯ�������\n");
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
	printf("��������Ҫ�޸ĵ�ͼ��ȫ��:");
	scanf("%s",bookname);
	printf("�������޸ĺ��ͼ���ȶ�:");
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
    	printf("ִ���޸�ͼ���ȶ�ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ���ȶ� �޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ�ͼ��ɹ�����ѯ�������\n");
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
	printf("��������Ҫ�޸ĵ�ͼ��ȫ��:");
	scanf("%s",bookname);
	printf("�������޸ĺ��ͼ������:");
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
    	printf("ִ��ͼ������ ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("ͼ������ �޸ĳɹ����޸Ľ������\n");
	char m[100]="select * from book where name=";
    strcat(m,"'");
    strcat(m,bookname);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
		printf("��ѯ");
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
	printf("��ѯ��ʽ:  1.��������,  2.���߲���, 3.������ ,4.ģ������,  5.������ݲ���, 6.��ʾ��ǰ�����鼮, 7.��ѯ��ǰ�û���Ϣ, 8.��ѯͼ����ļ�¼, 9.�˳���ѯ����\n");
	printf("���������Ĳ�ѯ��ʽ:");
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
		case 9:printf("��л��ʹ�ò�ѯ���񣬼����˳���ѯ����\n");return 0;break;
		default:printf("\n\n������Ч������������\n\n");break;
	}
}
}
void selbyallbookname()
{
	char book_name[50];
    printf("��������Ҫ���ҵ����ȫ��:");
    scanf("%s",book_name);
    char s[100]="select * from book where name=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    printf("��������Ҫ���ҵ����ߵ�ȫ��:");
    scanf("%s",writer_name);
    char s[100]="select * from book  where writer=";
    strcat(s,"'");
    strcat(s,writer_name);
    strcat(s,"'");
    strcat(s," order by convert(name using gbk) asc");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
  printf("����������Ҫ��ѯ�����:");
  scanf("%s",type);
  char m[100]="select * from book where type='";
  strcat(m,type);
  strcat(m,"'");
  if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
    printf("��������Ҫ���ҵ���Ĺؼ���:");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    printf("��������Ҫ���ҵ���ĳ���ʱ��:");
    scanf("%s",year);
    char s[100]="select * from book  where year= ";
    strcat(s,year);
    strcat(s," order by convert(name using gbk) asc"); 
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
	printf("��ѡ��չ�ַ�ʽ:  1������� 2��Ž��� 3�������� 4�������� 5���������� 6 ���������� 7 �˳�\n");
	printf("����������ѡ��:");
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
		default:printf("������Ч����������\n");break;
	}
}
}
void showbyidup()
{
    char s[100]="select * from book order by id asc";
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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
	printf("�û�������Ϣ\n");
	char o[100]="select * from users where username=";
    strcat(o,"'");
    strcat(o,username);
    strcat(o,"'");
    if(mysql_real_query(mysql,o,(unsigned int)strlen(o)))
    {
    	printf("ִ�в�ѯ�û���Ϣʱ�����쳣: %s",mysql_error(mysql));
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
  	printf("�û�������Ϣ\n");
  char m[100]="select * from borrow where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�û���Ϣʱ�����쳣: %s",mysql_error(mysql));
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
    printf("��������Ҫ���ҵ����ȫ��:");
    scanf("%s",book_name);
    char s[100]="select * from borrow_list where bookname=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�ɹ�����ѯ�������\n");
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


void jieshu()
{
	char book_name[50];
    printf("��������Ҫ���ĵ����ȫ��:");
    scanf("%s",book_name);
    char s[100]="select * from book where name=";
    strcat(s,"'");
    strcat(s,book_name);
    strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
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
	printf("\n��ȷ���ǽ����Ȿ����?1.��,2.����\n");
	printf("����������ѡ��:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:suretob(book_name);break;
		case 2:printf("��л����ʹ�ã������˳��鼮���ķ���\n");break; 
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
    	printf("ִ�в�ѯͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ�в�ѯ�ɽ��Ĵ��������쳣: %s",mysql_error(mysql));
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
    printf("��ǰ�ɽ���ͼ������Ϊ%d\n",remain3);
	 if(remain1==0)
{
	 	printf("�Ȿ�鲻������ϣ��޷������ߣ������˳�����\n");
	 	return 0;
}
	  else if(remain3==0)
{
	  	printf("���Ľ��Ĵ������㣬�޷����ģ������˳�����\n");
	  	return 0;
}
	  else
{
	printf("�Ȿ����Խ��ģ�����Ϊ������ͼ��������������Ե�\n");
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
    	printf("ִ���޸�ʣ��ͼ����Ĵ���ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	printf("ͼ���Ѿ����ģ������Խ���1����,��ǰ�û���ϢΪ\n");
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
	 char b[100]="select fans from book where name='";
	strcat(b,book_name);
	strcat(b,"'");
	char remain4[8];
	if(mysql_real_query(mysql,b,(unsigned int)strlen(b)))
    {
    	printf("ִ�в�ѯ��ǰͼ���ȶȳ����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ���ȶ�ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
}
}


void huanshu()
{
	char book_name[50];
	showuserborrow();
    printf("��������Ҫ�黹�����ȫ��:");
    scanf("%s",book_name);
    char s[200]="select * from borrow where username= '";
    strcat(s,username);
	strcat(s,"' and bookname = '");
	strcat(s,book_name);
	strcat(s,"'");
    if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else ;
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
	printf("��ȷ���ǹ黹�Ȿ����?1.��,2.����\n");
	printf("����������ѡ��:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:suretoh(book_name);break;
		case 2:printf("��л����ʹ�ã������˳��鼮�黹����\n");break; 
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
		 printf("��ʱ�黹������xxx�˺�ת��100ԪΥԼ��\n");
	else 
		printf("��ϲ��δ��ʱ�黹\n");
		char s[100]="select remain from book where name='";
	strcat(s,book_name)	;
	strcat(s,"'");
	char remain[8];
	if(mysql_real_query(mysql,s,(unsigned int)strlen(s)))
    {
    	printf("ִ�в�ѯͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ�в�ѯ�ɽ��Ĵ��������쳣: %s",mysql_error(mysql));
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
	printf("����Ϊ������ͼ��黹���������Ե�\n");
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
    	printf("ִ���޸�ʣ��ͼ����Ĵ���ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
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
    	printf("ִ���޸�ͼ������ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}	
	}
	char ai[200]="select max(id) from borrow_list where username='";
	strcat(ai,username);
	strcat(ai,"' and bookname = '");
	strcat(ai,book_name);
	strcat(ai,"'");
	char maxid[32];
	mysql_real_query(mysql,ai,(unsigned int)strlen(ai));
	result = mysql_store_result(mysql);
    num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)))
   strcpy(maxid,row[0]);
	char ti[100]="update borrow_list set backtime = NOW() where id =";
	strcat(ti,maxid);
	mysql_real_query(mysql,ti,(unsigned int)strlen(ti));
	char pi[100]=" delete from borrow where username='";
	strcat(pi,username);
	strcat(pi,"' and bookname = '");
	strcat(pi,book_name);
	strcat(pi,"'");
	mysql_real_query(mysql,pi,(unsigned int)strlen(pi));
	printf("ͼ���Ѿ��黹����ǰ�û���ϢΪ\n");
    showuserinfo();      
}

void showuserborrow()
{
	printf("�û�������Ϣ\n");
  char m[100]="select * from borrow where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�û���Ϣʱ�����쳣: %s",mysql_error(mysql));
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
	printf("֧�ֵ��û���Ϣ�޸�����:   1.�û����޸�,   2.�����޸�,  3.�Ա��޸�,   4.��λ�޸�,    5.�˳�ͼ�û���Ϣ�޸ķ���\n");
	printf("����������ͼ�����ݹ���ʽ:");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:modifyname();break;
		case 2:modifypass();break;
		case 3:modifysex();break;
		case 4:modifywork();break;
		case 5:printf("��л��ʹ���û���Ϣ�޸ķ��񣬼����˳��û���Ϣ�޸ķ���\n");return 0;
		default:printf("\n\n������Ч������������\n\n");break;
	}
}
}
void modifyname()
{
	printf("�������޸ĺ���û�����:");
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
    	printf("ִ���޸��û���ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("�û����޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
		strcpy(username,newusername);
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,newusername);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ��û���Ϣ�ɹ�����ѯ�������\n");
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
	printf("�������޸ĺ���û�����:");
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
    	printf("ִ���޸��û���ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("�û������޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ��û���Ϣ�ɹ�����ѯ�������\n");
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
	printf("�������޸ĺ���û��Ա�:");
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
    	printf("ִ���޸��û���ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("�û������޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ��û���Ϣ�ɹ�����ѯ�������\n");
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
	printf("�������޸ĺ���û�����:");
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
    	printf("ִ���޸��û���ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("�û������޸ĳɹ����޸Ľ������\n");
		printf("\n\n");
	char m[100]="select * from users  where username=";
    strcat(m,"'");
    strcat(m,username);
    strcat(m,"'");
    if(mysql_real_query(mysql,m,(unsigned int)strlen(m)))
    {
    	printf("ִ�в�ѯ�޸ĺ�ͼ��ʱ�����쳣: %s",mysql_error(mysql));
    	exit(1);
	}
	else
	printf("��ѯ�޸ĺ��û���Ϣ�ɹ�����ѯ�������\n");
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

