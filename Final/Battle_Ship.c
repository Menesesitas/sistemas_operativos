#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <string.h> 


#define NO_ITEMS 10
#define NUM_SHIPS 5

int buffer = 0;
int boardp1[10][10];
int boardp2[10][10];
int countp1 = NUM_SHIPS;
int countp2 = NUM_SHIPS;

pthread_mutex_t mutex;
pthread_cond_t cond_consumer, cond_producer;

//board of player 1
void p1board()
{
    printf("\nPLAYER 1\n");
    printf("    ");
    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", i+1);
        
    }
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", i+1);
        for (int j = 0; j < 10; j++)
        {
            if (boardp1[i][j] == 1) //ship
            printf("%3c ", 'S');
            else if (boardp1[i][j] == 5) //attack
            printf("%3c ", 'A');
            else if (boardp1[i][j] == 0) //sunken ship
            printf("%3c ", 'X');
            else //agua
            printf("%3c ", 'W');
        }
        printf("\n");
        
    }
}

//board of player 2
void p2board()
{
    printf("\nPLAYER 2\n");
    printf("    ");
    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", i+1);
        
    }
    printf("\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%3d ", i+1);
        for (int j = 0; j < 10; j++)
        {
            if (boardp2[i][j] == 1) //ship
            printf("%3c ", 'S');
            else if (boardp2[i][j] == 5) //attack
            printf("%3c ", 'A');
            else if (boardp2[i][j] == 0) //sunken ship
            printf("%3c ", 'X');
            else //agua
            printf("%3c ", 'W');
        }
        printf("\n");
    }
}

//ships from player 1
void ships_p1()
{
  int x, y;
  printf("\nPLAYER 1\n");
  for (int i = 0; i <5; i++) 
  {
    printf("\nEnter the position of the ship #%d: \n", i+1);
    scanf("%d %d", &x, &y);
    boardp1[x-1][y-1] = 1;
  }
}

//ships from player 2
void ships_p2()
{
  int x, y;
  printf("\nPLAYER 2\n");
  for (int i = 0; i <5; i++) 
  {
    printf("\nEnter the position of the ship #%d: \n", i+1);
    scanf("%d %d", &x, &y);
    boardp2[x-1][y-1] = 1;
  }
}

//check the attack from player1
void check_p1()
{
  int x, y;
  printf("\nPLAYER 1\n");
  printf("\nEnter the position to attack PLAYER 2: \n");
  scanf("%d %d", &x, &y);
  if (boardp2[x-1][y-1] == 1)
  {
    boardp2[x-1][y-1] = 0;
    boardp1[x-1][y-1] = 5;
    printf("\nYOU HIT A SHIP :0\n");
    countp2--;
  }
  else
  {
    boardp1[x-1][y-1] = 10;
    printf("\nNOTHINGS THERE, JUST WATER\n");
  }
  if(countp2 == 0 )
  {
    pthread_kill( pthread_self(), SIGUSR1 );
  }
}

//check the attack from player_2
void check_p2()
{
  int x, y;
  printf("\nPLAYER 2\n");
  printf("\nEnter the position to attack PLAYER 1: \n");
  scanf("%d %d", &x, &y);
  if (boardp1[x-1][y-1] == 1)
  {
    boardp1[x-1][y-1] = 0;
    boardp2[x-1][y-1] = 5;
    printf("\nYOU HIT A SHIP :0\n");
    countp1--;
  }
  else
  {
    boardp2[x-1][y-1] = 10;
    printf("\nNOTHINGS THERE, JUST WATER\n");
  }
  if(countp1 == 0 )
  {
    pthread_kill( pthread_self(), SIGUSR2 );
  }
}

//producer = player1
void* producer(void* arg)
{
  for ( int i=0; i<NO_ITEMS; i++ ) 
  {
    pthread_mutex_lock( &mutex );
    while( buffer != 0 ) // Wait until the buffer is free
    {
// Release the mutex and wait for the condition to be met (for the signal to arrive)
      pthread_cond_wait( &cond_producer, &mutex );
    }
    buffer = 1;
    printf("\n\n");
    p1board();
    check_p1();
    p1board();
    printf("\n \n");
    
// Notify that there are elements in the buffer
    pthread_cond_signal( &cond_consumer );
    pthread_mutex_unlock( &mutex );
  }

// Send signal to indicate that the producer has finished
  pthread_kill( pthread_self(), SIGUSR1 );

  pthread_exit( NULL );
}

//consumer = player_2
void* consumer(void* arg)
{
  for ( int i=0; i<NO_ITEMS; i++ ) 
  {
    pthread_mutex_lock( &mutex );
// ---------- Critical region
    while (buffer == 0) // Wait until there is data in the buffer
    {
// Release the mutex and wait for the condition to be met (for the signal to arrive)
      pthread_cond_wait( &cond_consumer, &mutex );
    }
    printf("\n\n");
    printf("\n\n");
    p2board();
    check_p2();
    p2board();
  
    buffer = 0;
    
// Warn that the buffer is clean.
    pthread_cond_signal( &cond_producer ); 
    pthread_mutex_unlock( &mutex );
  }

// Send signal to indicate that the consumer has finished
  pthread_kill( pthread_self(), SIGUSR2 );

  pthread_exit(NULL);
}

void signal_handler(int signum)
{
  if (signum == SIGUSR1) 
  {
    printf("VICTORY ROYALE\n");
    printf("GG PLAYER 1\n");
    printf("Please, The file 'match.txt' was created in the same folder of this game, check if all the game data is there :D\n");
    exit(0);
  }
  else if (signum == SIGUSR2)
  {
    printf("VICTORY ROYALE\n");
    printf("GG PLAYER 2\n");
    printf("Please, The file 'match.txt' was created in the same folder of this game, check if all the game data is there :D\n");
    exit(0);
  }
}

void save_game(char* data) {
// Create the file partida.txt with write permissions
  int fd = creat("match.txt", 0644);
  if (fd == -1) {
  printf("Error creating file.\n");
    exit(1);
  }
  
// Write the data to the file
  int bytes_written = write(fd, data, strlen(data));
  if (bytes_written == -1) {
  printf("Error writing to file.\n");
    exit(1);
  }

// Close the file
  int result = close(fd);
  if (result == -1) {
  printf("Error closing file.\n");
    exit(1);
  }
}

int main()
{
	pthread_t thread_1, thread_2;
	
	printf("BATTLESHIP THE FINAL GAME >:D\n");
	printf("Press ENTER to continue to instructions...\n");
	getchar();
	
	printf("INSTRUCTIONS\n");
	printf("\n1. The players will independently select the positions of their ships, which are all of the same size (1).\n");
	printf("2. Each player will have a maximum of 10 chances to take down their opponent's ships.\n");
	printf("3. Consider the next letters and what they mean into the game\n");
	printf("\n NOTE: Be aware of the end of game message\n");
	printf("\nS = Ship			A = Attack\n");
	printf("\nX = Destroyed ship		W = Water\n");
	
	// Pause so the user has time to read the instructions
	printf("\nPress ENTER to continue to the game...");
	getchar();
	
	// Clear the screen and start the game
	system("clear");
	p1board();
	ships_p1();
	p2board();
	ships_p2();
	
	// Save the game data to a file
	char data[1024];
	sprintf(data, "Game data goes here:\n"); // Replace "Game data goes here" with the data you want to save
	save_game(data);
	
	signal(SIGUSR2, signal_handler);
	signal(SIGUSR1, signal_handler);
	
	pthread_mutex_init(&mutex, 0);
	pthread_cond_init(&cond_consumer, 0);
	pthread_cond_init(&cond_producer, 0);
	
	// Create the threads
	pthread_create(&thread_1, NULL, producer, NULL);
	pthread_create(&thread_2, NULL, consumer, NULL);
	
	// Wait for the threads to finish
	pthread_join(thread_1, NULL);
	pthread_join(thread_2, NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond_consumer);
	pthread_cond_destroy(&cond_producer);
	
	return 0;
}
