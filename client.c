#include "header.h"

int main()
{
	int fd;
    socklen_t len;
   	char send_buf[SIZE];
    char recv_buf[SIZE];
    struct sockaddr_un sock,svaddr;

    //create socket
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (fd == -1) {
    	printf("Error create\n");
		exit(1);
    }
	
	printf("\nSocket created successfully...\n");

    //clear struct
    memset(&sock, 0, sizeof(struct sockaddr_un));

    //inital struct
    sock.sun_family = AF_UNIX;
    strncpy(sock.sun_path, SOCK_NAME, sizeof(sock.sun_path) - 1);

    //len = sizeof(sock);
    while (1) {
		len = sizeof(struct sockaddr_un);
    	printf("Enter the msg\n");
        fgets(send_buf, SIZE, stdin);
        if ( (sendto(fd, send_buf, SIZE, 0, (struct sockaddr *) &sock, len) )== -1) {
			printf("\nsend failed...\n");
			exit(1);
		}
        if ( (recvfrom(fd, recv_buf, SIZE, 0, NULL, NULL)) == -1 ) {
			printf("\nRecieve failed...\n");
			exit(1);
		}
        printf("Server msg: %s", recv_buf);
	}
    close(fd);
    return 0;
}
