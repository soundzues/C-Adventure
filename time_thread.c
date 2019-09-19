#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<time.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* time_finder()
{

	time_t t;
	struct tm *tmp;
	char timeString[200];
	time(&t);
	tmp = localtime(&t);
	
	pthread_mutex_lock(&mutex);	
		
		strftime(timeString, sizeof(timeString), "%I:%M%p, %A, %b %d, %G", tmp );
		printf("%s \n", timeString);
		//nanosleep(2);

	pthread_mutex_unlock(&mutex);

	pthread_exit(NULL);
}
int main()
{
	char string[20];
	pthread_t id;
	printf("please enter 'time'\n");
	scanf("%s", string);

//	printf("Main Thread before \n");

	if(strcmp(string, "time") == 0)
	{
		pthread_create(&id, NULL, time_finder, NULL);
		
	}

//	pthread_join(id, NULL);
	
	printf("Main Thread after \n");

}
