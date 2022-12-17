#include <stdio.h> 
int main () 
{  
int test_case = 0; 
char note[1000];  
while (gets( note ) != NULL) 
{  
test_case ++;  
if (note[0] == 'A' && note[1] == ' ') 
else if (note[0] == 'A' && note[1] == '#') 
{  
note[0] = 'B'; 
note[1] = 'b';  
printf("%s\n",note);break; 
else if (note[0] == 'B' && note[1] == 'b') 
{  
note[0] = 'A'; 
note[1] = '#';  
printf("%s\n",note);break;  
}  
else if (note[0] == 'B' && note[1] == ' ') 
{printf( "UNIQUE\n");break;} 
else if (note[0] == 'C' && note[1] == ' ') 
{printf( "UNIQUE\n");break;} 
else if (note[0] == 'C' && note[1] == '#') 
{  
note[0] = 'D'; 
note[1] = 'b';  
printf("%s\n",note);break; 
}  
else if (note[0] == 'D' && note[1] == 'b') 
{  
note[0] = 'C'; 
note[1] = '#';  
printf("%s\n",note);break; 
}  
else if (note[0] == 'D' && note[1] == ' ') 
{printf("UNIQUE\n");break;}  
else if (note[0] == 'D' && note[1] == '#') 
{  
note[0] = 'E'; 
note[1] = 'b';  
printf("%s\n",note);break; 
}  
else if (note[0] == 'E' && note[1] =='b') 
{  
note[0] = 'D'; 
note[1] = '#';  
printf("%s\n",note);break; 
}  
else if (note[0] == 'E' && note[1] == ' ') 
{printf("UNIQUE\n");break;} 
else if (note[0] == 'F' && note[1] == ' ') 
{printf("UNIQUE\n");break;}  
else if (note[0] == 'F' && note[1] == '#') 
{  
note[0] = 'G'; 
note[1] = 'b';  
printf("%s\n",note);break; 
}  
else if (note[0] == 'G' && note[1] == 'b') 
{  
note[0] = 'F';  
note[1] = '#';  
printf("%s\n",note);break; 
else if (note[0] == 'G' && note[1] == ' ') 
{printf("UNIQUE\n");break;}  
else if (note[0] == 'G' && note[1] == '#') 
{  
note[0] = 'A'; 
printf("%s\n",note);break; 
}  
else if (note[0] == 'A' && note[1] == 'b') 
{  
note[0] = 'G'; 
note[1] = '#';  
printf("%s\n",note);break; 
}  
else {printf("false");break;} 
}  
return 0; 

}
