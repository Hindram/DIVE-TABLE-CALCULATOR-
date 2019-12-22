#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<conio.h>
#define ROWS 27
#define COLS 12
#define ROWS2 52
#define COLS2 27


void menu();
void Backup_Dive_Info(); 	
void print_2d_array(int a[ ][COLS], int rows, int cols);
void print_2d_array2(int a[ ][COLS2], int rows, int cols);


//printing the dive info table with 2D array
void print_2d_array(int a[ ][COLS], int rows, int cols)
{ int i, j;
    for(i=0; i<rows; i++)
      {
        for (j=0; j<cols; j++)
             printf("%5d ", a[i][j]);
         printf("\n");
    }
}

//printing the surface time table with 2D array
void print_2d_array2(int a[ ][COLS2], int rows, int cols)
{ int i, j;
  
    for(i=1; i<rows; i++)
      {
        for (j=0; j<cols; j++)
             printf("%5d ", a[i][j]);
         printf("\n");
    }
}

int main (void){

int choice;
char c1;

int x,y,z,a;
char n,m;

FILE *in, *in2, *outptr, *outptr2, *out;
FILE *inptr,*inptr2;
in=fopen("Dive_Table.txt","r");
in2=fopen("Surface_Interval_time.txt","r");
if(in==NULL)
{
        printf("File Not found\n");
        getch();
        return 0;
}
if(in2==NULL)
{
        printf("File Not found\n");
        getch();
        return 0;
}
int first_dive =48,c=-1,r=-1,cr=0, cr2=0, c2=-1,r2=-1;
int time=76;
int surface,second_dive,rnt,amdt, surface_hr,surface_min;
int counter=0, counter2=1;

//2D array for Dive table (table 1)
int value[ROWS][COLS];

//2D array for surface time table (table 2)
int value_t2[ROWS2][COLS2];

//reading tables from txt file and store them in 2D array
while(fscanf(in, "%d", &value[cr][counter])!= EOF)
{
        counter++;
        if(counter==COLS)
        {   cr++;
            counter=0;
        }
}

//padding the first col with zeros in table 2 array
  int k;
        for (k=0; k<ROWS2 ; k++){
		
             value_t2[k][0] = 0;
         }
             
    
while(fscanf(in2, "%d", &value_t2[cr2][counter2])!= EOF)
{
        counter2++;
        if(counter2==COLS2)
        {   cr2++;
            counter2=1;
        }
}

	 
//menus loop options
do{
	 //CALL OF MENU FUNCTION, to print the starting list
	 menu();
	scanf("%s", &c1);
	
	//check if the entered value is digit or not and convert the char to int
	if (isdigit(c1)){
		choice = c1 - '0';
	
	}
	else 
	{
		choice = 5;
	}
	
	 
	//Calls of functions based on choice		
	switch(choice){
	       case 1:
				   /*case 1: read one Dive information 
					 (Depth of first dive, the total time for first dive, and length of surface interval and Depth of second dive) 
					 from user and calculate PGFD, PGSI, RNT*/ 
					printf("\t\tEnter Depth of first dive > ");
					scanf("%d",&first_dive);
					printf("\t\tEnter Total time of first dive > ");
					scanf("%d",&time);
					printf("\t\tLength of surface interval: (hours & min) > ");
					scanf("%d %d", &surface_hr,&surface_min);
				     printf("\t\tEnter Depth of second dive> ");
					 scanf("%d", &second_dive);
					 
					 // Make sure surface interval in  minutes
					     surface = surface_hr * 60 + surface_min; 
					  
					  //storing result into txt file , to use it in backup option later  
					  outptr2 = fopen("outputuser.txt", "w");
					 
					 //making sure that the user entered values in the acceptable range    
					 if (first_dive <= 0 || first_dive > 140)
					    {
					        printf("\n\t\tYour first dive must be between 1 and 140 ft.");
					        break;
					    }
					
					    if (time <= 0)
					    {
					        printf("\n\t\tYou must enter the total time of your first dive.");
					    break;
					    }
					
					    if (surface < 10 || surface > 1440)
					    {
					        printf("\n\t\tYour surface interval must at least 10 minutes and no greater than 24 hours.");
					        break;
					    }
					
					    if (second_dive <= 0 || second_dive > 130)
					    {
					       printf("\n\t\tYour second dive must be between 1 and 130 ft.");
					      break;
					    }
					  
					int i, j;
					//Table 1: determine the Pressure group after the first dive
					//selecting the related col for the first_dive
					for(i=0; i<COLS; i++)
					      if(first_dive<=value[0][i] )
					      {c=i; break;}
					
					//looking for the time slot that related to the selected col for first_dive above
					for(i=1; i<ROWS; i++)
					      if(time<=value[i][c] )
					          {
					           r=i;
					           break;
					          }
					          
					       
					//Table 2: determine Pressure group after the surface interval
						//selecting the related col for the first_dive
						r2=r*2;
						for(i=0; i<COLS2; i++)
					      if ( surface >= value_t2[r2-2][i] && surface <= value_t2[r2-1][i] && value_t2[r2-1][i]!=0 )
					      {
						  //printing to check values
						 // printf("\nsur %d %d ",value_t2[r2-2][i], value_t2[r2-1][i] );
						  c2=i; break;}
					
					
				
					          
					 //RNT After the second dive (Residual nitrogen time after the second dive)
					 	for(i=0; i<COLS; i++)
					      if(second_dive<=value[0][i] )
					      {amdt=i; break;}
					      
					      rnt= value[c2][amdt];
					
					
					
					 //if no pressure group avaliable for this range, showing error msg       
					   if (r==-1) {
					   	printf("\n\tThe time/depth of your first dive is beyond. The no-decompression table limits. Please enter a shallower depth and/or shorter dive time");
					   	break;
					   }
					   else {
					            
						//printf("%d %d %c %c %d %d",c,r,64+r, 64+c2, c2, rnt);
						printf("\n\n\tPressure group after the first dive is %c" , 64+r);
						printf("\n\tPressure group after the surface interval is %c" , 64+c2);
						printf("\n\tResidual Nitrogen Time is %d minutes" , rnt); 
							
						fprintf(outptr2, "%c\t%c\t%d\n", 64+r, 64+c2, rnt);
					}
 	                	fclose(outptr2);   
				
		      
			   break; 
           case 2: 
           			/*case 2: read multi Dive information 
					 (Depth of first dive, the total time for first dive, and length of surface interval and Depth of second dive) 
					 from data.txt file and calculate PGFD, PGSI, RNT*/ 
            	if((inptr = fopen("data.txt", "r")) == NULL){
					printf("\n\nError: Cannot open data.txt\n");
					
						}
						
				//show the result with error msg		
           		outptr = fopen("output.txt", "w");
           		
           		//show the ruselt without error msg -- will be used in back up option
           		out = fopen("output1.txt", "w");
           		
				while(fscanf(inptr, "%d%d%d%d", &first_dive,&time,&surface,&second_dive) != EOF){ 
				  
				 // Error checks 
				    if (first_dive <= 0 || first_dive > 140)
				    {
				        printf("\n\t\tYour first dive must be between 1 and 140 ft.");
				         break;
				    }
				
				    if (time <= 0)
				    {
				        printf("\n\t\tYou must enter the total time of your first dive.");
				         break;
				    
				    }
				
				    if (surface < 10 || surface > 1440)
				    {
				        printf("\n\t\tYour surface interval must at least 10 minutes and no greater than 24 hours.");
				         break;
				        
				    }
				
				    if (second_dive <= 0 || second_dive > 130)
				    {
				       printf("\n\t\tYour second dive must be between 1 and 130 ft.");
				        break;
				      
				    }
				    int i, j;
					//Table 1
					//selecting the related col for the first_dive
					for(i=0; i<COLS; i++)
					      if(first_dive<=value[0][i] )
					      {c=i; break;}
					
					//looking for the time slot that related to the selected col for first_dive above
					for(i=1; i<ROWS; i++)
					      if(time<=value[i][c] )
					          {
					           r=i;
					           break;
					          }
					          
					        
					//Table 2
						//selecting the related col for the first_dive
						r2=r*2;
						
					
					      
					for(i=0; i<COLS2; i++)
					      if ( surface >= value_t2[r2-2][i] && surface <= value_t2[r2-1][i] && surface <= value_t2[r2-1][i]!= 0)
					      {//printf("\nsur %d %d",value_t2[r2-2][i], value_t2[r2-1][i] );
						  
						  c2=i; break;}
					      
					  
					
					
					          
					 //RNT After the second dive
					 	for(i=0; i<COLS; i++)
					      if(second_dive<=value[0][i] )
					      {amdt=i; break;}
					      
					      rnt= value[c2][amdt];
					
					
					          
				//	printf("%d %d %c %c %d %d",c,r,64+r, 64+c2, c2, rnt);
				  if (r==-1) {
					   	printf("\n\n\t\tThe time/depth of your first dive is beyond. The no-decompression table limits. Please enter a shallower depth and/or shorter dive time");
					   	fprintf(outptr, "%s\n", "Please enter a shallower depth and/or shorter dive time");
					   }
					 else {
					   
					printf("\n\n\tPressure group after the first dive is %c" , 64+r);
					printf("\n\tPressure group after the surface interval is %c" , c2+64);
					printf("\n\tResidual Nitrogen Time is %d minutes" , rnt); 
				    fprintf(outptr, "%c\t%c\t%d\n", 64+r, 64+c2, rnt);
				    fprintf(out, "%c\t%c\t%d\n", 64+r, 64+c2, rnt);
				}
 				//returning variables to it's default state
    			first_dive =48,c=-1,r=-1,cr=0, cr2=0, c2=-1,r2=-1;
				
				}
					
					fclose(outptr);
					fclose(out);
				printf("\nResults written to output.txt\n");
			   
		    break;      
           case 3: 
		   //printing all dive info with result txt also 
		   		/*	if((inptr = fopen("data.txt", "r")) == NULL){
					printf("\n\nError: Cannot open data.txt\n");
					
					}
					if((inptr2 = fopen("output.txt", "r")) == NULL){
					printf("\n\nError: Cannot open data.txt\n");
					
					}*/
					printf("\t*******Dive Table*******\n");
					print_2d_array(value,ROWS,COLS);
					
					printf("\n\n\t*******Surface Intravel Time *******\n");
				    print_2d_array2(value_t2,ROWS2,COLS2);
				    
				  /*  printf("\n\n\t*******Data Table********\n");
				    while(fscanf(inptr, "%d %d %d %d", &x, &y, &z, &a) != EOF){   
					printf("%d\t %d\t %d\t %d\t\n", x, y, z, a);
					}*/
					
				/*	printf("\n\n\t*******Result Table********\n");
				    while(fscanf(inptr2, "%s %s %d", &n, &m, &q) != EOF){   
					printf("%c\t %c\t %d\t \n", n, m, q);
					} 	*/
		   
		    break; 
           case 4:  Backup_Dive_Info(); break;     
          
           case 0: //exit(1); 
		         break; 
				   
           default: printf("\t\tPlease, enter an integer number from 0 to 4.");  break; 
	 }

//returning variables to it's default state
    first_dive =48,c=-1,r=-1,cr=0, cr2=0, c2=-1,r2=-1;
    
	}while(choice != 0); 

				//	fclose(inptr);
				//	fclose(inptr2);
					fclose(in);
					fclose(in2);
					getch(); 

	return 0;
}


//menu functions -- print the options
void menu(){
	
	 printf("\n\t***  Welcome To DIVE TABLE CALCULATOR  ***\n\n");
	 printf("\t\t\t\tMAIN MENU\n");
	 printf("\t\t================================\n");
	 printf("\t\t[1] Enter Dive information from the user\n");
	 printf("\t\t[2] Load Dives information from the file\n");
	 printf("\t\t[3] List ALL the Dive information\n");
	 printf("\t\t[4] Backup Dive information\n");
	 printf("\t\t[0] Exit\n");
	 printf("\t\t======================\n");
	 printf("\t\tEnter your choice: ");
       
}  


 
 
 

//backup the result to txt file. 
 void Backup_Dive_Info(){
 	
 FILE *infile, *infile2, *outfile;
 char F,S;
 int Level1;
 if((infile = fopen("output1.txt", "r")) == NULL){
		printf("\n\nError: output file doesn't exist\n");
	
	}
	
 if((infile2 = fopen("outputuser.txt", "r")) == NULL){
		printf("\n\nError: output file doesn't exist\n");
	
	}

outfile = fopen("Backup.txt", "w");	
fprintf(outfile,"%s  %s  %s\n", "PGFD", "PGSD", "RNT");
//Back up info from multi data -- txt file
while(fscanf(infile, " %c %c %d", &F, &S, &Level1) != EOF){   
		fprintf(outfile, "%c   %c   %d\n", F, S, Level1);
}
fclose(infile);

//Back up info from user single entry 
 while(fscanf(infile2, " %c %c %d", &F, &S, &Level1) != EOF){   
	fprintf(outfile, "%c   %c   %d\n", F, S, Level1);
}

fclose(infile2);	
fclose(outfile);

printf("\n\tThe result have been backedup to Backup.txt file (last row represent the result of user entry).");
 
 }
