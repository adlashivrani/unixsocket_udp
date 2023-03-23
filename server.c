#include "header.h"

int main()
{
	int fd;
    socklen_t len;
   	char send_buf[SIZE];
   	char recv_buf[SIZE];
    struct sockaddr_un sock, claddr;

    //create socket
    fd = socket(AF_UNIX, SOCK_DGRAM, 0);

    if (fd == -1) {
    	printf("Error create\n");
    }
	
	printf("\nSocket created successfully...\n");
    //clear struct
    memset(&sock, 0, sizeof(struct sockaddr_un));
	//bzero(send_buf, SIZE);
	//bzero(recv_buf, SIZE);
    //inital struct
    sock.sun_family = AF_UNIX;
    strncpy(sock.sun_path, SOCK_NAME, sizeof(sock.sun_path) - 1);
    
    //bind socket
    if (bind(fd, (struct sockaddr *) &sock, sizeof(struct sockaddr_un)) == -1) {
    	printf("Error bind\n");
		exit(1);
    }
	printf("\nSocket bind successful...\n");
   	//len = sizeof(struct sockaddr);
    printf("Wating for clients...\n");
    while (1) {
		len = sizeof(struct sockaddr_un);
    	if ( (recvfrom(fd, recv_buf, SIZE, 0, (struct sockaddr *)&sock, &len)) == -1 ) {
        	printf("\nrecieve failed...\n");
			exit(1);
		}
		
		printf("\nClient msg:\n %s", recv_buf);
		printf("\nEnter the msg: \n");
      	fgets(send_buf, SIZE, stdin);
        if ( (sendto(fd, send_buf, SIZE, 0, (struct sockaddr *)&sock, len)) == -1 ) {
			printf("\nsending failed..\n");
			exit(1);
		}
    }
    close(fd);
    return 0;
}


