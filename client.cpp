#ifndef client
#define client
#include "client.hpp"
#endif


client::client() : connection()
{
	dataport = NULL;
}

void client::set_client_sock(int sockfd){
	connection_active = true;
	client_sock = sockfd;
}

bool client::send_cmd(char *command, int len){
	int bytesSent;
	if (bytesSent = send(client_sock, command, len, 0) == -1){
		perror("send");
		exit(1);
	}
	return true;
}

void client::recv_reply(){
	int bytesRead = recv(client_sock, (void *)buffer, sizeof(buffer), 0);	
	if(bytesRead == 0)			//other side has closed d connection
		connection_active = false;
	fwrite((const void *)buffer, sizeof(char), bytesRead, stdout);	//if dere was a \n in d message sent, here also
}

void client::send_quit(){
	
	//even if bytesSent == 0 ,i.e. server has already closed d connection, no prob
	connection_active = false;
	close_socket(client_sock);	//assuming d server received d message nd took necessary action
}

void client::send_pwd(){
	recv_reply();
}

void client::send_ls(){
	send_port();
	recv_data();
}

void client::talk(){

	while(connection_active){
		fputs("ftp>", stdout);
		gets(command);			//dis char array(command) contains d command (wout \n) but yes appended by \0
		int cmdlen = strlen(command);		//dis length doesn't include \0
		if (strcmp(command, "quit") == 0){
			send_cmd(command, cmdlen);
			send_quit();
		}
		else if(strncmp(command, "ls", 2) == 0){
			send_cmd(command, cmdlen);
			send_ls();
		}
		else if(strncmp(command, "get", 3) == 0){
			send_cmd(command, cmdlen);
			send_get();
		}
		else if(strncmp(command, "put", 3) == 0){
			send_cmd(command, cmdlen);
			send_put();
		}
		else if(strncmp(command, "pwd", 3) == 0){
			send_cmd(command, cmdlen);
			send_pwd();
		}
		else if(strncmp(command, "cd", 2) == 0){
			send_cmd(command, cmdlen);
			send_pwd();
		}
		else if ((strncmp(command, "!ls", 3) && strncmp(command, "!pwd", 4) && strncmp(command, "!cd", 3)) == 0){
			system(command);
		}
		else puts("An invalid FTP command!\n");
	}
}