/* https://tools.ietf.org/html/rfc863 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define SIZE 0x1000

int main()
{
	int sock, sock_client;
	struct sockaddr_in addr, client;
	socklen_t len;
	int ret;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1) {
		fprintf(stderr, "%s:%d: error: socket: %s\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(9);
	addr.sin_addr.s_addr = INADDR_ANY;

	ret = bind(sock, (struct sockaddr*) &addr, sizeof(addr));
	if (ret == -1) {
		fprintf(stderr, "%s:%d: error: bind: %s\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	ret = listen(sock, 128);
	if (ret == -1) {
		fprintf(stderr, "%s:%d: error: listen: %s\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	for (; ; ) {
		len = sizeof(client);
		sock_client = accept(sock, (struct sockaddr*) &client, &len);
		if (sock_client == -1) {
			fprintf(stderr, "%s:%d: error: accept: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(EXIT_FAILURE);
		}
		ret = close(sock_client);
		if (ret == -1) {
			fprintf(stderr, "%s:%d: error: close: %s\n", __FILE__, __LINE__, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	ret = close(sock);
	if (ret == -1) {
		fprintf(stderr, "%s:%d: error: close: %s\n", __FILE__, __LINE__, strerror(errno));
		exit(EXIT_FAILURE);
	}

	return 0;
}
