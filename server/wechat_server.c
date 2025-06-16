/*===============================================
*   文件名称：wechat_server.c
*   创 建 者：
*   创建日期：2024年12月21日
*   描    述：
================================================*/
#include <stdio.h>
#include"tcp.h"
#include"sqlite3.h"
#include<pthread.h>
#include<string.h>
#include <errno.h>
#include <unistd.h>
#include<stdlib.h>

//about free port
// 手动实现将主机字节序转换为网络字节序
unsigned short htons_custom(unsigned short host_short) {
	unsigned char *host_bytes = (unsigned char *)&host_short;
	unsigned short network_short;
	unsigned char *network_bytes = (unsigned char *)&network_short;

	network_bytes[0] = host_bytes[1];
	network_bytes[1] = host_bytes[0];

	return network_short;
}

// 检查指定端口是否空闲，返回1表示空闲，0表示已被占用
int is_port_free(int port) {
	int sockfd;
	struct sockaddr_storage server_addr;
	// 手动初始化地址结构体
	memset(&server_addr, 0, sizeof(server_addr));
	((struct sockaddr *) &server_addr)->sa_family = AF_INET;

	// 手动设置端口号，先转换为网络字节序
	unsigned short port_network = htons_custom(port);
	// 对于 sockaddr_storage 中存储 sockaddr_in 结构的情况（对应IPv4地址），
	// 需要通过合适的偏移量来访问和设置端口号，偏移量为2字节处开始存端口号
	memcpy(((char *)&server_addr) + sizeof(((struct sockaddr *) &server_addr)->sa_family),
	       &port_network, sizeof(port_network));

	// 创建套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("socket creation failed");
		return 0;
	}

	// 尝试绑定端口，若绑定成功，说明端口空闲，绑定失败则说明端口已被占用
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == 0) {
		close(sockfd);
		return 1;
	} else {
		close(sockfd);
		return 0;
	}
}

// 返回指定范围内的一个空闲端口，如果没有找到空闲端口则返回 -1
int find_free_port(int start_port, int end_port) {
	for (int port = start_port; port <= end_port; port++) {
		if (is_port_free(port)) {
			return port;
		}
	}
	return -1;
}
void test1() {
	int st = 8000, ed = 8020;
	for (int i = st; i <= ed; i++) {
		printf("free port:%d\n", find_free_port(st, ed));
		st++;
	}
}


//about serving client
//start check free port
int alloc_port = 8000;
int alloc_s_fd, alloc_c_fd;
char send_buf[128], rec_buf[128];
int stot, rtot;
void pre_sdrc() {
	stot = 0, rtot = 0;
	memset(send_buf, 0, sizeof send_buf);
	memset(rec_buf, 0, sizeof rec_buf);
}
void set_int_send_buf(int x) {
	if (x < 0) {
		set_int_send_buf(-x);
		return;
	}
	if (x > 9)set_int_send_buf(x / 10);
	send_buf[stot++] = x % 10 + '0';
	return;
}
//send int to the send buffer
void sittsb(int x) {
	pre_sdrc();
	set_int_send_buf(x);
	send_buf[stot] = '\0';
}
void test_write_in_the_send_buf() {
	while (1) {
		int x;
		scanf("%d", &x);
		sittsb(x);
		printf("%s\n", send_buf);
	}
}

//port manage
struct node {
	int port_num;
	char user_name[30];
	char pass_word[30];
};
int s_fd[50], c_fd[50], tot;
struct node mnuser[50];
void port_init() {
	memset(s_fd, 0, sizeof s_fd);
	memset(c_fd, 0, sizeof c_fd);
	tot = 0;
	memset(mnuser, 0, sizeof mnuser);
}
void add(int s_fl, int c_fl, struct node us) {
	s_fd[++tot] = s_fl;
	c_fd[tot] = c_fl;
	mnuser[tot] = us;
}
void erase(int s_fl) {
	for (int i = 1; i <= tot; i++) {
		if (s_fd[i] == s_fl) {
			Tcp_Close(s_fd[i]);
			Tcp_Close(c_fd[i]);
			s_fd[i] = s_fd[tot];
			c_fd[i] = c_fd[tot];
			s_fd[tot] = 0;
			c_fd[tot] = 0;
			mnuser[i] = mnuser[tot];
			tot--;
			return;
		}
	}
	for (int i = 1; i <= tot; i++) {
		printf("leave:%d %s %s\n", mnuser[i].port_num, mnuser[i].user_name, mnuser[i].pass_word);
	}
}
//send the free port to the client
int stop_free_port_service = 0;
int st = 8001, ed = 8100;
void* sd_free_port(void* arg) {
	while (1) {
		printf("waiting for new client...\n");
		if (stop_free_port_service == 1)return NULL;
		alloc_s_fd = Tcp_ServerInit(alloc_port);
		alloc_c_fd = Tcp_WaitNewConnection(alloc_s_fd);
		int pt = find_free_port(st, ed);
		printf("the port distribution=%d\n", pt);
		sittsb(pt);
		Tcp_Send(alloc_c_fd, send_buf, strlen(send_buf));
		int tmp_s_fd = Tcp_ServerInit(pt);
		int tmp_c_fd = Tcp_WaitNewConnection(tmp_s_fd);
		struct node us;
		us.port_num = pt;
		strcpy(us.user_name, "");
		strcpy(us.pass_word, "");
		add(tmp_s_fd, tmp_c_fd, us);
		Tcp_Close(alloc_s_fd);
	}
	return NULL;
}

//about database
//create table users(name char,password char);
sqlite3* db;
char name[32], password[32];
char sql[128];
char *errmsg;
int has_got;
int user_callback(void *arg, int num, char **val, char **colname) {
	strcpy(name, val[0]);
	strcpy(password, val[1]);
	has_got += 1;
	return 0;
}
int db_show_all(void *arg, int num, char **val, char **colname) {
	printf("%s|%s\n", val[0], val[1]);
	return 0;
}
void sc_init() {
	memset(name, 0, sizeof name);
	memset(password, 0, sizeof password);
	memset(sql, 0, sizeof sql);
	has_got = 0;
	errmsg = NULL;
}
void ex_sql() {
	sqlite3_exec(db, sql, user_callback, NULL, &errmsg);
}
void sql_sd(char* cont) {
	sc_init();
	strcpy(sql, cont);
	ex_sql();
}
void db_show() {
	sc_init();
	strcpy(sql, "select * from users");
	sqlite3_exec(db, sql, db_show_all, NULL, &errmsg);
}
int reg(char* uname, char *upass) {
	if (uname == NULL) {
		printf("none name!\n");
		return -1;
	}
	if (upass == NULL) {
		printf("none password!\n");
		return -1;
	}
	if (strlen(uname) > 10) {
		printf("username length has exceeded\n");
		return -1;
	}
	if (strlen(upass) > 10) {
		printf("password length has exceeded\n");
		return -1;
	}
	char pack[128];
	sprintf(pack, "select * from users where name='%s'", uname);
	sql_sd(pack);
	if (has_got > 0) {
		//send to client

		//send to client
		if (errmsg != NULL)
			printf("error:%s\n", errmsg);
		printf("has ex\n");
		return -2;
	}
	sprintf(pack, "insert into users values('%s','%s')", uname, upass);
	sql_sd(pack);
	if (errmsg != NULL) {
		printf("error:%s\n", errmsg);
		return -3;
	} else {
		printf("successfully!\n");
		db_show();
		return 0;
	}
}
int log_in(char *uname, char *upass) {
	if (uname == NULL) {
		printf("none name!\n");
		return -1;
	}
	if (upass == NULL) {
		printf("none password!\n");
		return -1;
	}
	if (strlen(uname) > 10) {
		printf("username length has exceeded\n");
		return -1;
	}
	if (strlen(upass) > 10) {
		printf("password length has exceeded\n");
		return -1;
	}
	char pack[128];
	sprintf(pack, "select * from users where name='%s'", uname);
	sql_sd(pack);
	if (has_got == 0) {
		//send to client
		//send to client
		printf("this user has not in the database\n");
		return -2;
	}
	if (strcmp(upass, password)) {
		printf("wrong password!\n");
		return -3;
	}
	printf("user:%s log in successfully!\n", uname);
	//link to client
	//send to client
	return 0;
}



//about log reg
char usname[64], uspass[64];
void reset() {
	memset(usname, 0, sizeof usname);
	memset(uspass, 0, sizeof uspass);
}

void kernel_service() {
	printf("start kernel service\n");
	while (1) {
		for (int i = 1; i <= tot; i++) {
			//printf("%d\n",i);
			if (strlen(mnuser[i].user_name) == 0) {
				pre_sdrc();
				Tcp_Recv(c_fd[i], rec_buf, sizeof rec_buf);
				if (strlen(rec_buf) > 0) {
					printf("\n");
					printf("%s:%s\n", mnuser[i].user_name, rec_buf);
					char *tok = strtok(rec_buf, " ");
					while (tok != NULL) {
						printf("%s\n", tok);
						if (strcmp(tok, "log") == 0) {
							printf("%s:\n", tok);
							char* usrname = strtok(NULL, " ");
							char* usrpass = strtok(NULL, " ");
							printf("username:%s\n", usrname);
							printf("user_password:%s\n", usrpass);
							int ret = log_in(usrname, usrpass);
							if (ret == 0) {
								strcpy(mnuser[i].user_name, usrname);
								strcpy(mnuser[i].pass_word, usrpass);
								sittsb(1111);
								Tcp_Send(c_fd[i], send_buf, sizeof send_buf);
							} else {
								sittsb(ret * 111);
								printf("wrong code:%d\n", ret * 1111);
								Tcp_Send(c_fd[i], send_buf, sizeof send_buf);
							}
						} else if (strcmp(tok, "reg") == 0) {
							printf("%s:\n", tok);
							char* usrname = strtok(NULL, " ");
							char* usrpass = strtok(NULL, " ");
							printf("username:%s\n", usrname);
							printf("user_password:%s\n", usrpass);
							int ret = reg(usrname, usrpass);
							if (ret == 0) {
								sittsb(111111);
								Tcp_Send(c_fd[i], send_buf, sizeof send_buf);
							} else {
								sittsb(ret * 11111);
								printf("wrong code:%d\n", ret * 11111);
								Tcp_Send(c_fd[i], send_buf, sizeof send_buf);
							}
						}
						tok = strtok(NULL, " ");
					}
				}
			} else {
				pre_sdrc();
				Tcp_Recv(c_fd[i], rec_buf, sizeof rec_buf);
				if (strlen(rec_buf) > 0) {
					for (int j = 1; j <= tot; j++) {
						if (i == j)continue;
						strcpy(send_buf, rec_buf);
						Tcp_Send(c_fd[j], send_buf, sizeof send_buf);
					}
					for (int j = 0; j < strlen(rec_buf); j++) {
						if (strcmp(rec_buf + j, "leave") == 0) {
							printf("%s\n", rec_buf);
							erase(s_fd[i]);
						}
					}
				}
			}
		}
	}
}


int main(int argc, char *argv[]) {
	db = NULL;
	sqlite3_open("user.db", &db);
	// db_show();
	while (errmsg != NULL) {
		printf("the tabel has not existed yet!\n");
		sql_sd("create table users(name char,password char)");
	}
	pthread_t distribution;
	pthread_create(&distribution, NULL, sd_free_port, NULL);
	kernel_service();
	getchar();
	return 0;
}
