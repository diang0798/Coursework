// 6522104  zy22104  Ang Ding

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Zone{
	int x;
	int y;
	int r;
	struct Zone *next;
};

struct Plan{
	int x;
	int y;
	struct Plan *next;
};

typedef struct Zone Zone;
typedef Zone *ZonePtr;
typedef struct Plan Plan;
typedef Plan *PlanPtr;

// prototypes
void load_zone(ZonePtr **start, int zone_x, int zone_y, int zone_r); // modified by stack program in textbook
void load_plan(PlanPtr **start, int plan_x, int plan_y);  // modified by list_append function from lecture
void nofly(ZonePtr *start, char **file);
void flightplan(PlanPtr *start, char **file);
void result(ZonePtr zone_curPtr, PlanPtr plan_curPtr);
void zone_free(ZonePtr *start);  // modified by list_free function from lab
void plan_free(PlanPtr *start);  // modified by list_free function from lab

int main(int argc,char *argv[])
{
	// check if number of command line parameters are correct
	if(argc != 3)
	{
		printf("Invalid command line arguments. Usage: <noflyzones> <flightplan>\n");
		exit(6);
	}
	
	ZonePtr zone_start = NULL; // points to struct Zone top;
	PlanPtr plan_start = NULL; // points to struct Plan top;
	nofly(&zone_start,argv);   // load and check data in nofly.txt
	flightplan(&plan_start,argv); // load and check data in flightplan.txt
	result(zone_start, plan_start); // check whether the flight plan of a drone enter any no-fly zones
	zone_free(&zone_start);
	plan_free(&plan_start);
}    

// load data from nofly.txt and store it into struct Zone
void load_zone(ZonePtr **start, int zone_x, int zone_y, int zone_r)
{
	ZonePtr dataPtr = malloc(sizeof(Zone));
    
	if (dataPtr != NULL)
	{   
    	dataPtr->x = zone_x;
    	dataPtr->y = zone_y;
    	dataPtr->r = zone_r;
    	dataPtr->next = **start;
    	**start = dataPtr;
	}
	else   //no space available
	{
    	printf( "Unable to allocate memory." );
    	exit(5);
	}
}

// load data from flightplan.txt and store it into struct Plan
void load_plan(PlanPtr **start, int plan_x,int plan_y)
{
     PlanPtr dataPtr = malloc(sizeof(Plan));
    
    if (dataPtr != NULL)
    {
        if(**start == NULL)
        {
        	**start = dataPtr;
        	dataPtr->x = plan_x;
        	dataPtr->y = plan_y;
        	dataPtr->next = NULL;
        }
        else
        {
        	PlanPtr cur = **start;
        	while(cur->next != NULL)
       		{
	   			cur = cur->next;
       		}
       		dataPtr->x = plan_x;
        	dataPtr->y = plan_y;
        	dataPtr->next = NULL;
        	cur->next = dataPtr;
        }
    }
    else    // no space available
    {
        printf( "Unable to allocate memory." );
        exit(5);
    }
}


// check the validity of nofly.txt 
void nofly(ZonePtr *start, char **file)
{
	FILE *fp1;	// nofly.txt file potiner
	
	// fp2pen opens file. Exit program if file cannot be opend
    if((fp1 = fopen(file[1], "r")) == NULL)
    {
        perror("Cannot open nofly.txt file.\n");
        exit(1);
    }   
    
    int zone_x;
    int zone_y;
    int zone_r;
    char content;
    int count_char;  // count the number of character in one line
    
    fscanf(fp1, "%c", &content);
    fseek(fp1,-(sizeof(char)), SEEK_CUR);
    // read all records from file (until eof)
    while((!feof(fp1)))
    {   
        fscanf(fp1, "%c", &content);  //check the first character in a line.
        if(content == '#')
        {
        	// ignore contents until the end of the line if a line starts with '#'  
            while(content != '\n') 
            {
            	fscanf(fp1, "%c", &content);
            }
        }
        else if(content == '\n')
        {
            continue;  // ignore blank lines
        }
        else
        {
            if(content == ' ')
            {
            	printf("No-fly zone file invalid.\n"); // invalid if the first character in a line is a whitespace
            	exit(3);
            }
            else
            {
            	count_char=1;
            	do
            	{
            		// invalid if a character is not a digit or whitespace in the line
            		if((content< ' '|| content > ' ')&& (content < '0'|| content > '9'))
            		{
            			printf("No-fly zone file invalid.\n");
            			exit(3);
            		}
            		
            		fscanf(fp1, "%c", &content);
            		count_char++;
            	}while(content != '\n'); // check every characters until the end of the line
            }
            	
            // file pointer back to the first character of the line.	
            fseek(fp1,-(count_char * sizeof(char)), SEEK_CUR);
            
            // set record zone_x
            fscanf(fp1,"%d",&zone_x);
            do
            {
            	fscanf(fp1, "%c", &content);
            	// invalid if there is only one record in the line
            	if(content == '\n')
            	{
            		printf("No-fly zone file invalid.\n");
            		exit(3);
            	}
            }while(!(content >= '0' && content <= '9'));
            fseek(fp1,-(sizeof(char)), SEEK_CUR);
            
            // set record zone_y
            fscanf(fp1,"%d",&zone_y);
            do
            {
            	fscanf(fp1, "%c", &content);
            	// invalid if there are only two records in the line
            	if(content == '\n')
            	{
            		printf("No-fly zone file invalid.\n");
            		exit(3);
            	}
            }while(!(content >= '0' && content <= '9'));
            fseek(fp1,-(sizeof(char)), SEEK_CUR);
            
            // set record zone_r 
            fscanf(fp1,"%d",&zone_r);
            
            // check the character after the third record
            fscanf(fp1, "%c", &content);
            // invalid if the charcater is not '\n'
            if(content != '\n')
            {
            	printf("No-fly zone file invalid.\n");
            	exit(3);
            }
            
            // check if x, y and radius in the range
            if(zone_x < 0 || zone_x >= 10000 || zone_y < 0 || zone_y >= 10000 || zone_r <=0 || zone_r >= 10000)
            {
            	printf("No-fly zone file invalid.\n");
            	exit(3);
            }
            
            // store records into struct Zone
            load_zone(&start, zone_x, zone_y, zone_r);
        }
    }
    fclose(fp1);
}

// check the validity of flightplan.txt 
void flightplan(PlanPtr *start, char **file)
{
    FILE *fp2; // flightplan.txt file potiner
	
	// fp2pen opens file. Exit program if file cannot be opend
    if((fp2 = fopen(file[2], "r")) == NULL)
    {
        perror("Cannot open flightplan.txt file.\n");
        exit(1);
    }
    
    int plan_x;
    int plan_y;
    char content;
    int count_point=0;	//count the number of way-point
    int count_char;		// count the number of character in one line
    int previous_x = 0;
    int previous_y = 0;
    
    // read all records from file (until eof)
    while((!feof(fp2)))
    {   
        fscanf(fp2, "%c", &content); //check the first character in a line.
        
        // ignore contents until the end of the line if a line starts with '#'
        if(content == '#')
        {
            while(content != '\n')
            {
            	fscanf(fp2, "%c", &content);
            }
        }
        else if(content == '\n')
        {
            continue; // ignore blank lines
        }
        else
        {
            while(content != '\n')
            {
            	if(content == ' ')
            	{
            		printf("Flight plan file invalid.\n"); // invalid if the first character in a line is a whitespace
            		exit(3);
            	}
            	else
            	{
            		count_char=1;
            		do
            		{
            			// invalid if a character is not a digit or whitespace in the line
            			if((content< ' '|| content > ' ')&& (content < '0'|| content > '9'))
            			{
            				printf("Flight plan file invalid.\n");
            				exit(3);
            			}
            			
            			fscanf(fp2, "%c", &content);
            			count_char++;
            		}while(content != '\n'); // check every characters until the end of the line
            	}
            }
            
            // file pointer back to the first character of the line. 
            fseek(fp2,-(count_char * sizeof(char)), SEEK_CUR);
            
            // set record plan_x
            fscanf(fp2,"%d",&plan_x);
            do
            {
            	fscanf(fp2, "%c", &content);
            	// invalid if there is only one record in the line
            	if(content == '\n')
            	{
            		printf("Flight plan file invalid.\n");
            		exit(3);
            	}
            }while(!(content >= '0' && content <= '9'));
            fseek(fp2,-(sizeof(char)), SEEK_CUR);
            
            // set record plan_y
            fscanf(fp2,"%d",&plan_y);
            
            // check the character after the third record
            fscanf(fp2, "%c", &content);
            // invalid if the charcater is not '\n'
            if(content != '\n')
            {
            	printf("Flight plan file invalid.\n");
            	exit(3);
            }
            
            // check if x, y and radius in the range
            if(plan_x < 0 || plan_x >= 10000 || plan_y < 0 || plan_y >= 10000)
            {
            	printf("Flight plan file invalid.\n");
            	exit(3);
            }
            
            // store records into struct Plan
            load_plan(&start, plan_x, plan_y);
            count_point++;
            
            // check if two consecutive way-points have the same coordinates.
            if(previous_x == plan_x && previous_y == plan_y)
            {
            	printf("Flight plan file invalid.\n");
            	exit(3);
            }
            
            previous_x = plan_x;
            previous_y = plan_y;
        }
    }
    
    // invalid if there are less then 2 way-points 
    if(count_point < 2)
    {
        printf("Flight plan file invalid.\n");
        exit(3);
    }
    fclose(fp2);
}

void result(ZonePtr zone_curPtr, PlanPtr plan_curPtr)
{
	// if the number of no-fly zone is zero
	if(zone_curPtr == NULL)
	{
		printf("Flight plan valid.\n");
        exit(0);
    }
    
    ZonePtr topPtr = zone_curPtr;
    long int shortone;
    int i = 0;  // detcet whether drone enters restricted area
    int result_x, result_y; // the coordinates of the center of the first no-fly zone entered
    int Ax,Ay,Bx,By;
    // check the first segment
    Ax = plan_curPtr->x;
    Ay = plan_curPtr->y;
    plan_curPtr = plan_curPtr->next;
    Bx = plan_curPtr->x;
    By = plan_curPtr->y;
    
    // check all the segments
    while(plan_curPtr != NULL)
    {
        long int X,Y,Z;
        int Cx = zone_curPtr->x;
        int Cy = zone_curPtr->y;
        int r = zone_curPtr->r;
        X = Ax * Ax - (2 * Ax * Bx) + Bx * Bx + Ay * Ay - (2 * Ay * By) + By * By; 
        Y = (2 * Cx * Bx) - (2 * Cx * Ax) - (2 * Cy * Ay) + (2 * Cy * By) + (2 * Ax * Bx) + (2 * Ay * By) - (2 * Bx * Bx) - (2 * By * By);
        Z = Cx * Cx - (2 * Cx * Bx) + Cy * Cy - (2 * Cy * By) - r * r + Bx * Bx + By * By;
        long int Discrim = Y * Y - (4 * X * Z);
        float t1 = (-Y + sqrt(Discrim)) / (2 * X);
        float t2 = (-Y - sqrt(Discrim)) / (2 * X);
        if((t1>=0 && t1<=1) || (t2>=0 && t2<=1))   // in this case, drone enters restricted area
        {	
        	// because no no-fly zones overlap, so the first no-fly zone drone enters has the smallest value of (the distance between the start point of segement and zone center minus radius of the zone)
        	long int distance = sqrt((Ax - Cx) * (Ax - Cx) + (Ay - Cy) * (Ay - Cy)) - r;
        	if(i == 0)
        	{
        		shortone = distance;
        		result_x = Cx;
        		result_y = Cy;
        	}
        	else if(distance < shortone)  // if a segment enters more than one no-fly zone, compare their distance.
        	{
        		shortone = distance;
        		result_x = Cx;
        		result_y = Cy;
        	}
        	i++;
        }
        zone_curPtr = zone_curPtr->next; // check the next no-fly zone
        
        // if a segment has been checked with all the no-fly zones
        if(zone_curPtr == NULL)
        {
        	if(i>0)
        	{
        		printf("Invalid flight plan.\n");
        		printf("Enters restricted area around %d,%d.\n", result_x, result_y);
        		exit(4);
        	}
        	else    // check next segment
        	{
            	Ax = plan_curPtr->x;
        		Ay = plan_curPtr->y;
        		plan_curPtr = plan_curPtr->next;
        		if(plan_curPtr == NULL)    // break if all the segments has been checked
        		{
        			break;
        		}
         		Bx = plan_curPtr->x;
         		By = plan_curPtr->y;
            	zone_curPtr = topPtr;
            }
        }
    }
        printf("Flight plan valid.\n");
        exit(0);
}

// free all the elements of Zone and set the start to NULL
void zone_free(ZonePtr *start)
{
   ZonePtr cur = *start;
   while(cur != NULL)
   {
      ZonePtr temp = cur->next;
      free(cur);
      cur = temp;
   }
   *start = NULL;
}

// free all the elements of Plan and set the start to NULL
void plan_free(PlanPtr *start)
{
   PlanPtr cur = *start;
   while(cur != NULL)
   {
      PlanPtr temp = cur->next;
      free(cur);
      cur = temp;
   }
   *start = NULL;
}
