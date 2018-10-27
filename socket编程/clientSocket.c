/*
sockaddr_in（在netinet/in.h中定义）：
struct sockaddr_in {
short int sin_family;                       Address family 
unsigned short int sin_port;        Port number 
struct in_addr sin_addr;               Internet address 
unsigned char sin_zero[8];          Same size as struct sockaddr 
};
struct in_addr {
unsigned long s_addr;
};
typedef struct in_addr {
union {
            struct{
                        unsigned char s_b1,
                        s_b2,
                        s_b3,
                        s_b4;
                        } S_un_b;
           struct {
                        unsigned short s_w1,
                        s_w2;
                        } S_un_w;
            unsigned long S_addr;
          } S_un;
} IN_ADDR;

sin_family指代协议族，在socket编程中只能是AF_INET
sin_port存储端口号（使用网络字节顺序）
sin_addr存储IP地址，使用in_addr这个数据结构
sin_zero是为了让sockaddr与sockaddr_in两个数据结构保持大小相同而保留的空字节。
s_addr按照网络字节顺序存储IP地址

sockaddr_in和sockaddr是并列的结构，指向sockaddr_in的结构体的指针也可以指向
sockadd的结构体，并代替它。也就是说，你可以使用sockaddr_in建立你所需要的信息,
在最后用进行类型转换就可以了bzero((char*)&mysock,sizeof(mysock));//初始化
mysock结构体名
mysock.sa_family=AF_INET;
mysock.sin_addr.s_addr=inet_addr("192.168.0.1");
……
等到要做转换的时候用：
（struct sockaddr*）mysock
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

int main(int argc,char* argv[]){
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	if(argc != 3){
		printf("Usage : %s <IP> <Port>\n",argv[0]);
		exit(1);
	}

	sock=socket(PF_INET,SOCK_STREAM,0);
	if(sock == -1)
		error_handling("socket()  error");

	//memset：作用是在一段内存块中填充某个给定的值，
	//对较大的结构体或数组进行清零操作的一种最快方法
	memset(&serv_addr, 0 ,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
		error_handling("connect() error");

	str_len=read(sock,message,sizeof(message)-1);
	if(str_len==-1)
		error_handling("read()  error!");

	printf("Message from server:%s \n",message);
	close(sock);
	return 0;
	}
}

void error_handling(char *message){
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
