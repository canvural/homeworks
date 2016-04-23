#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void mostOften(int *);
int main(int argc, char *argv[])
{
    int allChars[256];
    char text[256];
    int i=0;
    for(i; i<sizeof(allChars); i++)
    {
        allChars[i]=0;
    }
    
    while(fgets(text, sizeof(text), stdin))
    {
        
    
    if(argc<2)
    {
        printf("o");
        
    }
    else
    {
         switch(argv[1][1])
         {
         case 'M':
            mostOften(allChars);
            break;
         /*case 'L':
            leastOften(allChars);
            break;*/
         }
    }
    return 0;
}
void mostOften(int *allChars)
{
    int max=0;
    int i=0, a;
    while(i<sizeof(allChars)/sizeof(int))
    {
    while(allChars[i]>max)
    {
        max=allChars[i];
        a=i;
    }
    i++;
    }
    printf("najczesciej wystepuje litera %c, %d razy", a, max);

}
