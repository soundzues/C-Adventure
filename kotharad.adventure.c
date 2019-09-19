//Name: Aditya Kothari
//Class: CS344
//Assignment: Program2 - adventure, The Game & Time Keeping

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<assert.h>
#include<pthread.h>
#include<time.h>

char *name_list[7]; //store 7 room names
char *connection_list[7];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int StartEndFinder(char *room_type,int room_count)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmpr;
	char compare[256];	
	int flag = 0;
	int startroom_loc;
	int i;
	FILE *fptr; 
	
	for(i = 0; i < room_count; i++)
	{
		fptr = fopen(name_list[i], "r");
		while((read = getline(&line, &len, fptr)) != -1)//read each line 
		{
			if(strstr(line, room_type) != NULL) //if found break
			{
		//		printf("lol");
				flag = 1;
				break;
			}
		}
		if(flag == 1)
		{
			break;
		}
	}
	return i;
}

//STORES CONNECTIONS FROM START_ROOM 
int connectionStore(int room_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmpr;
	char compare[256];	
	int flag = 0;
	int startroom_loc;
	FILE *fptr; 

			
		int x = 0;
		fptr = fopen(name_list[room_name], "r");
		while((read = getline(&line, &len, fptr)) != -1)//read each line 
		{//someting go wrong debug this
			if(strstr(line, "Batchler") != NULL) //if found break
			{
		//		printf("Batchler \n");
				connection_list[x] = "Batchler";
				x++;
			}

			if(strstr(line, "Impulse") != NULL) //if found break
			{
		//		printf("Impulse \n");
				connection_list[x] = "Impulse";
				x++;
			}
			
			if(strstr(line, "Downward") != NULL) //if found break
			{
		//		printf("Downward \n");
				connection_list[x] = "Downward";
				x++;
			}
	
			if(strstr(line, "Owen") != NULL) //if found break
			{
	//			printf("Owen \n");
				connection_list[x] = "Owen";
				x++;
			}
			
			if(strstr(line, "Kelly") != NULL) //if found break
			{
	//			printf("Kelly \n");
				connection_list[x] = "Kelly";
				x++;
			}
			
			if(strstr(line, "Gleeson") != NULL) //if found break
			{
	//			printf("Gleeson \n");
				connection_list[x] = "Gleeson";
				x++;
			}
			
			if(strstr(line, "Johnson") != NULL) //if found break
			{
	//			printf("Johnson \n");
				connection_list[x] = "Johnson";
				x++;
			}
			
			if(strstr(line, "Lupes") != NULL) //if found break
			{
	//			printf("Lupes \n");
				connection_list[x] = "Lupes";
				x++;
			}
		
			if(strstr(line, "Peacock") != NULL) //if found break
			{
	//			printf("Peacock \n");
				connection_list[x] = "Peacock";
				x++;
			}
				
			if(strstr(line, "Dearborn") != NULL) //if found break
			{
	//			printf("Dearborn \n");
				connection_list[x] = "Dearborn";
				x++;
			}

		}
		fclose(fptr);
		return x;
}

//thread function to write to a file based on name
int connectionStore_2(char *room_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmpr;
	char compare[256];	
	int flag = 0;
	int startroom_loc;
	FILE *fptr; 

			
		int x = 0;
		fptr = fopen(room_name, "r");
		while((read = getline(&line, &len, fptr)) != -1)//read each line 
		{//someting go wrong debug this
			if(strstr(line, "Batchler") != NULL) //if found break
			{
		//		printf("Batchler \n");
				connection_list[x] = "Batchler";
				x++;
			}

			if(strstr(line, "Impulse") != NULL) //if found break
			{
		//		printf("Impulse \n");
				connection_list[x] = "Impulse";
				x++;
			}
			
			if(strstr(line, "Downward") != NULL) //if found break
			{
		//		printf("Downward \n");
				connection_list[x] = "Downward";
				x++;
			}
	
			if(strstr(line, "Owen") != NULL) //if found break
			{
	//			printf("Owen \n");
				connection_list[x] = "Owen";
				x++;
			}
			
			if(strstr(line, "Kelly") != NULL) //if found break
			{
	//			printf("Kelly \n");
				connection_list[x] = "Kelly";
				x++;
			}
			
			if(strstr(line, "Gleeson") != NULL) //if found break
			{
	//			printf("Gleeson \n");
				connection_list[x] = "Gleeson";
				x++;
			}
			
			if(strstr(line, "Johnson") != NULL) //if found break
			{
	//			printf("Johnson \n");
				connection_list[x] = "Johnson";
				x++;
			}
			
			if(strstr(line, "Lupes") != NULL) //if found break
			{
	//			printf("Lupes \n");
				connection_list[x] = "Lupes";
				x++;
			}
		
			if(strstr(line, "Peacock") != NULL) //if found break
			{
	//			printf("Peacock \n");
				connection_list[x] = "Peacock";
				x++;
			}
				
			if(strstr(line, "Dearborn") != NULL) //if found break
			{
	//			printf("Dearborn \n");
				connection_list[x] = "Dearborn";
				x++;
			}

		}
		fclose(fptr);
		return x;
}
//displays connections
void Display(int total_connections)
{

		int count;
		printf("CURRENT LOCATION: %s \n", connection_list[0]); //First element has to be current location
		printf("POSSIBLE CONNECTIONS:");
		for(count = 1; count < total_connections; count++) // rest of them possible connections
		{
			printf(" %s, ",connection_list[count]);
		}
		printf("\n");
}

//time keeping thread -- UTILIZING MUTEX
void* time_finder()
{

	pthread_mutex_lock(&mutex);	//lock mutex
	
	
	chdir("..");	//go to the directory game is present 
	
	time_t t;
	struct tm *tmp;
	char timeString[200];
	time(&t);
	tmp = localtime(&t);

	//open and write time to the file
	FILE *fp = fopen ("currentTime.txt", "w");

	strftime(timeString, sizeof(timeString), "%I:%M%p, %A, %b %d, %G", tmp );//formating time
		

	fprintf(fp,"%s", timeString);//write to file

	pthread_mutex_unlock(&mutex); //unlock mutex

	fclose(fp);

	pthread_exit(NULL);
}

void buildRoomDir()
{
	char *newdir;
	int newestDirTime = -1; // Modified timestamp of newest subdir examined
  	char targetDirPrefix[32] = "kotharad.rooms."; // Prefix we're looking for
  	char newestDirName[256]; // Holds the name of the newest dir that contains prefix
  	memset(newestDirName, '\0', sizeof(newestDirName));

  	DIR* dirToCheck; // Holds the directory we're starting in
  	struct dirent *fileInDir; // Holds the current subdir of the starting dir
  	struct stat dirAttributes; // Holds information we've gained about subdir

 	dirToCheck = opendir("."); // Open up the directory this program was run in

 	if (dirToCheck > 0) // Make sure the current directory could be opened
  	{
    		while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
    		{
      			if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
      			{
        			stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry

        			if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
        			{
          				newestDirTime = (int)dirAttributes.st_mtime;
         				memset(newestDirName, '\0', sizeof(newestDirName));
          				strcpy(newestDirName, fileInDir->d_name);
        			}
      			}
    		}
  	}	
	closedir(dirToCheck); // Close the directory we opened

	//move to the most recent dierectory 
	newdir = malloc(35*sizeof(char));
	assert(newdir);	
	
	sprintf(newdir, "./%s", newestDirName);	
	
	chdir(newdir);//open the most recent direcetory

}

int main()
{
	char *newdir;
	int i,j,x,y; //for loop counters 

	//alocate memory for 7 room names 
	for(i = 0; i < 7; i++)
	{
		name_list[i] = malloc(20*sizeof(char));
	}
	
	for(x = 0; x < 7; x++)
	{
		connection_list[x] = malloc(20*sizeof(char));
	}

	//Finding most recent diectroy - taken from provied sample program
	int newestDirTime = -1; // Modified timestamp of newest subdir examined
  	char targetDirPrefix[32] = "kotharad.rooms."; // Prefix we're looking for
  	char newestDirName[256]; // Holds the name of the newest dir that contains prefix
  	memset(newestDirName, '\0', sizeof(newestDirName));

  	DIR* dirToCheck; // Holds the directory we're starting in
  	struct dirent *fileInDir; // Holds the current subdir of the starting dir
  	struct stat dirAttributes; // Holds information we've gained about subdir

 	dirToCheck = opendir("."); // Open up the directory this program was run in

 	if (dirToCheck > 0) // Make sure the current directory could be opened
  	{
    		while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
    		{
      			if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
      			{
        			stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry

        			if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
        			{
          				newestDirTime = (int)dirAttributes.st_mtime;
         				memset(newestDirName, '\0', sizeof(newestDirName));
          				strcpy(newestDirName, fileInDir->d_name);
        			}
      			}
    		}
  	}	
	closedir(dirToCheck); // Close the directory we opened

	//move to the most recent dierectory 
	newdir = malloc(35*sizeof(char));
	assert(newdir);	
	
	sprintf(newdir, "./%s", newestDirName);	
	
	chdir(newdir);//open the most recent direcetory

	//open directory and read all the files, store it in array 
	dirToCheck = opendir("."); //open new dierctory 
	int room_count = 0;	
	while(fileInDir = readdir(dirToCheck))
	{
		
		//dont want parrent or current directory so continue
		if(!strcmp(fileInDir->d_name,"."))
		{
			continue;
		}

		if(!strcmp(fileInDir->d_name,".."))
		{
			continue;
		}
		
		strcpy(name_list[room_count], fileInDir->d_name);
		room_count++;
	}
	
	//Identify start and end room from file
	//Start room location:
	char room_start[]= "START_ROOM";
	int location_start = StartEndFinder(room_start, room_count);

	//End room location:
	char room_end[]= "END_ROOM";
	int location_end = StartEndFinder(room_end, room_count);

	//Initial game start
	//Count total connections and store them in START_ROOM
	int total_connections = connectionStore(location_start);
	
	//Print out connections
	Display(total_connections);
	
	//game start:
	char whereto[10];
	memset(whereto, '\0', sizeof(whereto));
	FILE *f;
	int steps = 0;	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *cmpr;
	char compare[256];	
	int flag = 0;
	int startroom_loc;
	x = 0;
	char path[150][10];
	pthread_t id;


	for(j = 0; j < 150; j++)
	{
		memset(path[j], '\0', sizeof(path[j][10]));
	}

	//loop game:
	while(1)
	{
		printf("WHERE TO? >");
		scanf("%s", whereto);
		strtok(whereto, "\n");	
		printf("\n");	

		//if user enter time show time - do thread stuff
		if(strcmp(whereto, "time") == 0)
		{
			struct timespec ts = {0, 100000000L}; //sleep time = 0.1 sec
			FILE *fptr; // to read
			char time[200]; 

			//creating secod thread to write time to current 
			pthread_create(&id, NULL, time_finder, NULL);
			
			//sleep for 0.1 sec, wait for second thread to complete writng to file
			nanosleep(&ts, NULL);
		
			//read and print file
			fptr = fopen("currentTime.txt", "r");

			fgets(time, sizeof(time), fptr); //read in time from file
	
			printf("%s \n", time);

			printf("\n");
			
			fclose(fptr);
			
			//go back to the most recent directory to continue playing game	
 			dirToCheck = opendir("."); // Open up the directory this program was run in

 			if (dirToCheck > 0) // Make sure the current directory could be opened
  			{
    				while ((fileInDir = readdir(dirToCheck)) != NULL) // Check each entry in dir
    				{
      					if (strstr(fileInDir->d_name, targetDirPrefix) != NULL) // If entry has prefix
      					{
        					stat(fileInDir->d_name, &dirAttributes); // Get attributes of the entry

        					if ((int)dirAttributes.st_mtime > newestDirTime) // If this time is bigger
        					{
          						newestDirTime = (int)dirAttributes.st_mtime;
         						memset(newestDirName, '\0', sizeof(newestDirName));
          						strcpy(newestDirName, fileInDir->d_name);
        					}
      					}
    				}
  			}	


			sprintf(newdir, "./%s", newestDirName);	
	
			chdir(newdir);//open the most recent direcetory

		} 		
		else //play game
		{
			f = fopen(whereto, "r");
	
			if(!f) //file cannot be open throw error
			{		
				printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN. \n");
				printf("\n");
			} //print connections and check for end room
			else
			{
				strcpy(path[steps], whereto);
				steps++; //increment steps				

				//find end room
				x = 0;	//keeps track of number of fconnections				
				while((read = getline(&line, &len, f)) != -1)//read each line 
				{//someting go wrong debug this
	//				printf("%s", line);
					if(strstr(line, "END_ROOM") != NULL) //if found break
					{
						printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
						flag = 1;
						break;
					}
				}
				if(flag == 1) //end room found break game loop
				{
					break;
				}
				//if end room not found get total connections and sotore them of that room
				x = connectionStore_2(whereto);
				
				//display those connections
				Display(x); 
			}
	
		}
	}
	

	//at the end of game print out all the connections
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS: \n", steps);
	int k = 0;
	for(k = 0; k < steps; k++)
	{
		printf("%s \n", path[k]);
	}

	exit(0);	
}
