#ifndef connect
#define iconnect
#include "connect.hpp"
#endif
//#include "reply.hpp"
#define SPORT "5000"

class client : public connection
{
	char command[MAXSIZE];
	char buffer[MAXSIZE];
	char *dataport;
	int client_sock;
	bool connection_active;
	
	bool send_cmd(const char *s, int len);
public:
	client();
	//client(int blog);
	//client(char *port, int blog);		I don't think dese 2 ctors will b used by client
	void set_client_sock(int sockfd);
	void send_put();
	void send_get();
	void send_ls();
	void send_cd();
	void send_pwd();
	void send_quit();
	void send_port();
	
	void talk();
	void recv_data();
	void recv_reply();
};