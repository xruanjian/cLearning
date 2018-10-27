/*
以下为服务端程序：四个套接字创建的步骤
serv_sock=socket(PF_INET,SOCK_STREAM,0);
	该行调用socket函数创建套接字

if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)	
	该行调用bind函数分配IP和端口号

if(listen(serv_sock,5)==-1)	
	该行调用listen函数将套接字转换为可以连接状态

clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);	
	该行调用accept函数受理连接请求，如果没有连接请求的情况下调用该函数，则不会有返回，
	直到有连接请求为止。

*/

//C语言中，char*pc=(char *)&a 是什么意思？
//char占一个字节，pc指向a中第一个字节的地址
//（char *）a[4]的意思是将指针型数组a中的元素a[4]强行转化为char类型


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//声明自定义的错误处理函数，以方便main函数使用
void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock;
    int clnt_sock;
    
    struct sockaddr_in  serv_addr;
    struct sockaddr_in  clnt_addr;
    socklen_t clnt_addr_size;

    char message[]="Hello world!";

					//这个argc!=2,表示如果输入的参数不是两个的话(其实是输入一个参数，第一个参数操作系统提供)
    if(argc!=2){
    	printf("Usage : %s<port>\n",argv[0]);
    	/*exit用于在程序运行的过程中随时结束程序，函数原型void exit(int status)，
    	exit的参数是返回给操作系统的。这个参数识了应用程序的一些运行信息。
    	操作系统有关一般是0为正常退出，非0为非正常退出。非0的数字可以是自己拟定的可以是任意一个整型数字。
 		通过这个参数用来标识程序是在那一部分退出的。*/
    	exit(1);
    }

    /*相关头文件中的定义：
    				AF = Address Family
                    PF = Protocol Family
                    AF_INET = PF_INET

		在windows中的Winsock2.h中，

                    #define AF_INET 0
                    #define PF_INET AF_INET

		所以在windows中AF_INET与PF_INET完全一样. 

    	而在Unix/Linux系统中，在不同的版本中这两者有微小差别.对于BSD,是AF,对于POSIX是PF.
*/
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    //创建socket错误，返回-1错误码时候
    if(serv_sock == -1)
    	error_handling("socket() error");

	    memset(&serv_addr, 0 ,sizeof(serv_addr));
	    serv_addr.sin_family=AF_INET;
	    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	    serv_addr.sin_port=htons(atoi(argv[1]));
	//使用了强制类型转换
    if(bind(serv_sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
    	error_handling("bind() error");

    if(listen(serv_sock,5)==-1)
    	error_handling("listen()  error");
    	clnt_addr_size=sizeof(clnt_addr);
    	
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

    	if(clnt_sock==-1)
    		error_handling("accept()  error");
    	write(clnt_sock, message, sizeof(message));
    	close(clnt_sock);
    	close(serv_sock);
    	return 0;
    }
    
//定义错误处理信息
void  error_handling(char *message){
	//C语言库函数，把字符串写入到指定的流( stream) 中，但不包括空字符。不包括字符串结尾\n
	//函数原型：int fputs(const char *str, FILE *stream);
	fputs(message,stderr);
	//将字符c写到文件指针fp所指向的文件的当前写指针的位置。
	//函数格式：int fputc (char c, FILE *fp)。
	//配合fputs，给他加一个字符串结尾符号
	fputc('\n',stderr);
	exit(1);
}
	