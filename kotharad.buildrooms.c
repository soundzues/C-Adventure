//Name: Aditya Kothari
//Clas: CS344
//Assignment: Program 2 - adventure, Rooms program


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>

struct room //struct stores name, id, coonections
{
	int type;
	char *name;
	int num_connections;
	struct room *connections[6];
};

char *room_names[10] = {"Downward", "Lupes", "Peacock", "Impulse", "Johnson", "Gleeson", "Dearborn", "Kelly", "Batchler", "Owen"}; //10 hardcoded room names 
char *room_types[3] = {"START_ROOM", "MID_ROOM", "END_ROOM"}; //3 types of rooms

int connection_matrix[7][7]; //keep track of connections

//function to intializes struct 
void InitalizeStruct(struct room *input)
{
	int i = 0;
	int j = 0;
	for(i=0; i<7; i++)
	{
		input[i].type = 0;
		input[i].name = NULL;
		input[i].num_connections = 0;
		for(j=0; j < 6; j++)	
		{
			input[i].connections[j] = NULL; 
		}
	}
		
}

//returns a room does not validate connection
struct room* GetRandomRoom(struct room *input, int *room)
{
	int random;
	random = rand()%7; //genrate random number between 0 and 6
	*room = random; //return room number from matrix 
	return &input[random]; //return random room address
}

//returns true(1) if room can be added otherwise fales(0)
int CanAddConnectionFrom(struct room roomx, int x)
{
	if(roomx.num_connections<6)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// Returns true if Rooms x and y are the same Room, false otherwise
int IsSameRoom(int x, int y)
{
	if(x == y)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}	

//Returns true if a connection from Room x to Room y already exists, false otherwise
int ConnectionAlreadyExists(int x, int y)
{
	if(connection_matrix[x][y] == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//makes connection 
void ConnectRoom(struct room *roomx, struct room *roomy, int x, int y)
{
	connection_matrix[x][y] = 1; //connetion made on the matrix 
	
	roomx->connections[roomx->num_connections] = roomy;//connection made via room pointer 

	roomx->num_connections++;//increment number of connections 

}

void AddRandomConnection(struct room *input)
{
	struct room *a;
	struct room *b;
	int roomNum_a = -5; //random room generated number
	int roomNum_b = -5; 
	int test;

	while(1)
	{
		a = GetRandomRoom(input, &roomNum_a); //get a random room

		if (CanAddConnectionFrom(*a, roomNum_a) == 1); //check if a new room can be added 
		{
			break;
		}
	}

	do
	{	//0 = false, 1 = true
		b = GetRandomRoom(input, &roomNum_b); //get second random room
		
	}while(CanAddConnectionFrom(*b, roomNum_b) == 0 || IsSameRoom(roomNum_a, roomNum_b) == 1 || ConnectionAlreadyExists(roomNum_a, roomNum_b) == 1);
	
	//Make 2 wat conenction 	
	ConnectRoom(a, b, roomNum_a, roomNum_b);

	ConnectRoom(b, a, roomNum_b, roomNum_a);
	
}

//checks if graph is full or not 
int IsGraphFull()
{
		int i, j;
		int count=0;		
		
		for(i=0; i<7; i++) //itrate through the whole matrix 
		{
			for(j=0; j<7; j++)
			{ 
				if(connection_matrix[i][j] == 1) //count number of connection made 
				{
					count++;
				}
			}
	
		
			if(count<3) //if count is less than 3 graph not full
			{
				return 0; //retrurn 0 = false 
			}
			else //move to the next room to count number of connections 
			{
				count = 0; //re-set counter
			}
		}
		return 1; //graph full return 1 = true

}

int main()
{
	char *dirname = "kotharad.rooms.";
	int pid = getpid(); //getting process id and storing it in pid
	char *folder_name;

	char *newdir;
	time_t t;
	int i;
	int random;
	char *room_used[7];
	struct room *room_struct;
	room_struct = malloc(7*sizeof(struct room)); //allocate memory for 7 structs

	InitalizeStruct(room_struct);
	
	//create directory: 
	folder_name = malloc(30 * sizeof(char)); //dynamicly alocating memory to the string
	assert(folder_name);

	memset(folder_name, '\0', 30); //fill the sting with null chars 

	sprintf(folder_name, "%s%d", dirname, pid); // get the folder name in right format 

	mkdir(folder_name, 0755); //create directory with the right permissions

	//move to the newly created directory
	newdir = malloc(35 * sizeof(char));
	assert(newdir);

	sprintf(newdir, "./%s", folder_name);
	//printf("%s", newdir);	

	chdir(newdir); //move in to the new directory

	//randomly chose 7 out of 10 rooms
	srand(time(&t)); // intialize random number generator
	int test[10];
	int x, p, j;
	
	//genrating 7  non repeating random numbers 
	while(i < 7)
	{
		random = rand()%10;
		
		for(x = 0; x < i; x++)
		{
			if(test[x] == random)
			{
				break;
			}
		}
		if(x == i)
		{
			test[i++] = random;
		}
	}
	
	//chose 7 names at random 
	for(p = 0; p < 7; p++)
	{
		room_used[p] = room_names[test[p]];
	}

	//assign names 
	for(j=0; j<7; j++)
	{
		room_struct[j].name = room_used[j]; //assigning room names to struct
		
	}

	//assigning room types
	for(i=0; i<7; i++)
	{
//		printf("%d\n", i);
	
		if(i == 0)
		{
		//	printf("start\n");
			room_struct[i].type = 0; //start room	
		}
		else if(i == 6)
		{
		//	printf("end\n");	
			room_struct[i].type = 2; //mid room
		}
		else
		{
		//	printf("mid\n");	
			room_struct[i].type = 1; //end room	
		}
	}

	//initializing adjacent matrix
	for(i=0; i<7; i++)
	{
		for(j=0; j<7; j++)
		{
			connection_matrix[i][j]=0; //filling matrix with 0s 
		}
	}
	
	//make connections	
	while (IsGraphFull() == 0) //if graph not full add connections 
	{
		AddRandomConnection(room_struct); //add random connection
	}
	
/*	//TEST PRINT MATRIX 
	for(i=0; i<7; i++)
	{
		for(j=0; j<7; j++)
		{
			printf("%d ",connection_matrix[i][j]);
		}
			printf("\n");
	}
*/

	//write to FILE
	FILE *fp; //file pointer intialization
	int count = 1;// keep track of number of conenctions 
	for(i=0; i<7; i++) 
	{
		fp = fopen(room_struct[i].name, "w"); //create files named after room names 
		fprintf( fp,"ROOM NAME: %s\n", room_struct[i].name); //print to the file room names 
		for(j=0; j<room_struct[i].num_connections; j++)
		{
			fprintf( fp,"CONNECTION %d: %s\n", count,room_struct[i].connections[j]->name); //print out to file name and number of conenctions 
			count++;
		}
			fprintf( fp,"ROOM TYPE: %s\n", room_types[room_struct[i].type]); //print out type of room 
			count=1; //reset counter 
	}

	//free memory 
	free(newdir);
	free(folder_name);

	return 0;
}
