#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

char *remove_new_line(char *strbuffer)
{
	size_t len = strlen(strbuffer);
	if (strbuffer[len - 1] == '\n')
	{
		strbuffer[len - 1] = '\0';
	}

	return strbuffer;
}


void display_results(char position[30], int *array_ptr, int connfd)
{
    char buff[MAX];
    bzero(buff, MAX);

    // read the message from client and copy it in buffer
    read(connfd, buff, sizeof(buff));
	snprintf(buff,"\n\n\tPosition: %s", position);
    write(connfd, buff, sizeof(buff));

	// Variables for reading file
	char path[20] = "candidates/";

	// Prepare path
	strcat(path, position);

	// Set up file details
	FILE * candfileptr;
	candfileptr = fopen(path, "r");

	char read_name[50];
	char read_id[50];
	int line_number = 1;
	int max = -1;
	char winner[30];
	float total = 0;

	while (fgets(read_name, sizeof(read_name), candfileptr))
	{
        bzero(buff, sizeof(buff));
	    read(connfd, buff, sizeof(buff));
        
		snprintf(buff,"\n\t\t%d. %s \t-\t %d", line_number, remove_new_line(read_name), array_ptr[line_number]);
		write(connfd, buff, sizeof(buff));
        total = total + array_ptr[line_number];

		// Track who has the highest number of votes
		if (max < array_ptr[line_number])
		{
			max = array_ptr[line_number];
			strcpy(winner, read_name);
		}

		// If there is a tie print both
		else if (max == array_ptr[line_number])
		{
			max = array_ptr[line_number];
			strcat(winner, " &");
			strcat(winner, read_name);
		}

		line_number += 1;
	}

	printf("\n\n\tWINNER :: %s with a total of %d votes[%.2f%%]", winner, max, (max / total) *100);
	printf("\n------------------------------------------------------");

	fclose(candfileptr);
}

int tally_votes(int connfd)
{
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

	// Array to hold totals for each position
	int position_tallies[10][30] = { 0 };

	// Iterate positions
	int i;
	for (i = 0; i < positions; i++)
	{
		int *array_ptr = position_tallies[i];
		tally_position(position_titles[i], array_ptr);
		// Display results for this position
		display_results(position_titles[i], array_ptr, connfd);
	}
}

void tally_position(char position[30], int *array_ptr)
{
	strcat(position, ".txt");

	// Variables for reading file
	char path[20] = "votes/";

	// Prepare path
	strcat(path, position);

	// Set up file details
	FILE * candfileptr;
	candfileptr = fopen(path, "r");

	char read_name[30];
	char read_id[30];
	int line_number = 1;
	//int candidate_votes[30] = {0};

	while (fgets(read_id, sizeof(read_id), candfileptr))
	{
		//printf("\n\t\t%d. %s", line_number, read_name);
		line_number += 1;
		array_ptr[atoi(read_id)]++;
	}

	fclose(candfileptr);

}


int register_candidate(int connfd)
{
	char fname[50];
	char lname[50];
	char reg[20];
    char buff[MAX];
	FILE * fptr;

    printf("\n%s\n","called");

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

    bzero(buff, MAX);

    // read the message from client and copy it in buffer
    read(connfd, buff, sizeof(buff));

	int choice = atoi(buff);
	
    switch (choice)
	{
		case 1:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 2:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 3:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 4:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 5:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 6:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 7:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 8:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 9:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		case 10:
			strcat(file_path, position_titles[choice - 1]);
			strcat(file_path, ".txt");
			fptr = fopen(file_path, "a");

			break;

		default:
			printf("\nError: Invalid Choice");
			return;
	}

    strcpy(buff, "ACCEPT");
    write(connfd, buff, sizeof(buff));

	// Error Reading File
	if (fptr == NULL)
	{
		printf("Error!");
		return 0;
	}
	else
	{
        bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
	    strcpy(fname, buff);
        // send
		strcpy(buff, "ACCEPT");
        write(connfd, buff, sizeof(buff));

		bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
	    strcpy(lname, buff);
        // send
		strcpy(buff, "ACCEPT");
        write(connfd, buff, sizeof(buff));

		bzero(buff, MAX);
        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
	    strcpy(reg, buff);
        // send
		strcpy(buff, "ACCEPT");
        write(connfd, buff, sizeof(buff));

		fprintf(fptr, "%s %s %s \n", fname, lname, reg);
		fclose(fptr);

	}

	return 0;
}

// Function designed for chat between client and server.
void func(int connfd)
{
	char buff[MAX];
	int n;
	// infinite loop for chat
	for (;;) {
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));
		// print buffer which contains the client contents
		printf("From client: %s\t To client : ", buff);

        if (atoi(buff) == 1)
        {
            bzero(buff, MAX);
            n = 0;
            // and send that buffer to client
            strcpy(buff, "1");
            write(connfd, buff, sizeof(buff));
            register_candidate(connfd);
        }

        else if (atoi(buff) == 2)
        {
            bzero(buff, MAX);
            n = 0;
            // and send that buffer to client
            strcpy(buff, "2");
            write(connfd, buff, sizeof(buff));
            tally_votes(connfd);
        }

        else if (atoi(buff) == 3)
        {
            printf("%s\n", "vote");
        }

        else if (atoi(buff) == 4)
        {
            printf("%s\n", "tally");
        }

		// if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

// Driver function
int main()
{
	int sockfd, connfd, len;
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}

