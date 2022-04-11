#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

#include "voter_registration.c"
#include <stdbool.h>
#include <string.h>

// Detect OS and define clearing command
#if defined(_WIN32)
	#define CLEAR_COMMAND "cls"		// Windows
#else
	#define CLEAR_COMMAND "clear"	// Other OS
# endif

int tally_votes(int sockfd)
{
	char buff[MAX];
	printf("\n\t\t\tTALLYING\n\t\tThis will take a second");

	strcpy(buff, "READY");
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));
	printf("%s",buff);

	while (strncmp("exit", buff, sizeof(buff)) != 0) {
			strcpy(buff, "READY");
			write(sockfd, buff, sizeof(buff));
			bzero(buff, sizeof(buff));
			read(sockfd, buff, sizeof(buff));

			printf("%s",buff);
		}

}

int register_candidate(int sockfd)
{
	char fname[50];
	char lname[50];
	char reg[20];
	char buff[MAX];

	printf("\n<<Welcome to SONU Elections Candidates Registration>>\n\n");

	// Define titles
	char position_titles[10][50] = { "Chairperson",
		"Vice Chair",
		"Secretary General",
		"Secretary Finance",
		"Organizing Secretary",
		"Secretary Academic Affairs",
		"Secretary Catering and Accommodation",
		"Secretary Health and Environment",
		"Secretary Sports and Entertainment",
		"Secretary Legal Affairs" };
	int positions = 10;
	char file_path[50] = "candidates/";

	int i = 0;
	for (i = 0; i < positions; i++)
	{
		printf("\t%d. %s \n", i + 1, position_titles[i]);
	}

	int choice;
	printf("\n\nPlease enter your choice on the position you wish to vie for :: ");
	scanf("%d", &choice);

	snprintf(buff, sizeof(buff), "%d", choice);
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));

	printf("Enter your First name \t:  ");
	scanf("%s", fname);

	strcpy(buff, fname);
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));

	printf("Enter your Last name \t:  ");
	scanf("%s", lname);

	strcpy(buff, lname);
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));

	printf("Enter your Reg no \t:  ");
	scanf("%s", reg);

	strcpy(buff, reg);
	write(sockfd, buff, sizeof(buff));
	bzero(buff, sizeof(buff));
	read(sockfd, buff, sizeof(buff));

	printf("\nSuccesfully Registered :: %s %s %s", fname, lname, reg);

	return 0;
}

void func(int sockfd)
{
	char buff[MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		char entryOptions[5][100] = { "1. Register as a candidate",
			"2. Register as a voter",
			"3. Vote",
			"4. Announce results",
		};

		int entryChoice = 0;

		printf("Welcome to the UNSA Elections Voting System. \n\nWhat would you like to do? \n");

		while (entryChoice == 0)
		{
			int i = 0;
			for (i = 0; i < 4; i++)
			{
				printf("%s", entryOptions[i]);
				printf("\n");
			}

			printf(">> ");
			scanf("%d", &entryChoice);

			if (entryChoice < 1 || entryChoice > 4)
			{
				entryChoice = 0;
				printf("Please enter a valid choice\n");
			}
		}	

		n = 0;
		//while ((buff[n++] = getchar()) != '\n')
		//	;
		snprintf(buff, sizeof(buff), "%d", entryChoice);
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		printf("From Server : %s", buff);

		if (atoi(buff) == 1)
        {
            register_candidate(sockfd);
        }

        else if (atoi(buff) == 2)
        {
            tally_votes(sockfd);
        }

        else if (atoi(buff) == 3)
        {
            printf("%s\n", "vote");
        }

        else if (atoi(buff) == 4)
        {
            printf("%s\n", "tally");
        }

		if ((strncmp(buff, "exit", 4)) == 0) {
			printf("Client Exit...\n");
			break;
		}
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}

