
#include <stdio.h>
#include <ctype.h>


void outcomment(int a,FILE* fp,FILE* ftr);
void incomment(FILE* fp,FILE* ftr);
void string(FILE* fp,FILE* ftr);
int lineCounter = 0;

int main(void) {
    char input[100];
    printf("\nPlease input the file you wish to decoment:\n");
    scanf("%s",input);
    FILE* fp = fopen(input,"rw");


    FILE* ftr = fopen("output.txt","w");

   int a;
   int b;

   while((a=getc(fp)) != EOF){
       outcomment(a,fp,ftr);
       

   }
   fclose(ftr);
   fclose(fp); 
   return 0;
}

   void outcomment(int a, FILE* fp, FILE* ftr){
       int b;

       if(a == '\n'){
           lineCounter++;
           putc(a,ftr);
       }
       else if(a == '/'){
           b = getc(fp);
           if(b == '*'){
               incomment(fp,ftr);
           }
           else if(b == '/'){
               putc(a,ftr);
               outcomment(b,fp,ftr);
           }
           else if( b == '\n'){
            lineCounter++;
            putc(b,ftr);
           }
           else if(b == '"'){
               putc(b,ftr);
               string(fp,ftr);
           }
       }
       else if(a == '"'){
           putc(a,ftr);
           string(fp,ftr);
        }
       
       else{
           putc(a,ftr);
       }

   }
    void incomment(FILE* fp,FILE* ftr){
       int a, b;
       a = getc(fp);
       b = getc(fp);
       int in_com = 1;

       while(in_com == 1){
           if(a == EOF){
               in_com = 0;
               printf("your just wrong at line %d\n",lineCounter);
           }
           else if(b == EOF){
               in_com = 0;
               printf("your just wrong at line %d\n",lineCounter);
           }
            if(a == '*'){
               if(b == '/'){
                 a = getc(fp);
                 outcomment(a,fp,ftr);
                 in_com = 0;
               }
               else{
                   a = b;
                   b = getc(fp);
               }
            }
            else{
              a = b;
              b = getc(fp);
            }
       }
  }

  void string(FILE* fp,FILE* ftr){
       int a,b;
       a = getc(fp);
       int bull = 1;
       while(bull == 1){
           if(a == '\n'){
               lineCounter++;
           }
           else if(b == '\n'){
               lineCounter++;
           }
          if(a == '"'){
             putc(a,ftr);
             b = getc(fp);
             outcomment(b,fp,ftr);
             bull = 0;
          }
          else{
            putc(a,ftr);
            a = getc(fp);
          }
       }
}
