#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define CTRL_KEYPRESS(k) ((k)  & 0x1f)

FILE *fp1, *fp2, *fp3, *fp;

void Create(){
    char c, fn[100];

    fp1 = fopen("temp.txt","w");
    printf("\n\tEnter the text and press 'CTRL + S' to save\n\n\t");
    while(1){
        c = getchar();
        fputc(c, fp1);
        if(c == 19) {
            fclose(fp1);
            printf("\n\tEnter then new filename: ");
            scanf("%s",fn);
            fp1 = fopen("temp.txt","r");
            fp2 = fopen(fn,"w");

            while(!feof(fp1)) {
                c=getc(fp1);
                putc(c, fp2);
            }

            fclose(fp2);
            break;
        }
    }

}

void Rename(){

    int ret;
    char newname[100], oldname[100];

    printf("\n\tEnter the file name : ");
    scanf("%s", &oldname);

    printf("\n\tEnter the new name : ");
    scanf("%s", &newname);

    ret = rename(oldname, newname);

    if(ret == 0) {
        printf("\n\tFile renamed successfully");
    } else {
        printf("\n\tError: unable to rename the file(Please close the file if it's open.)!");
    }

}

void Display(){

    char ch, fn[100];
    printf("\n\tEnter the file name: ");
    scanf("%s",fn);

    fp = fopen(fn, "r");

    if(fp == NULL){
        printf("\n\tError: File not found!\n");
        exit(1);
        fclose(fp);
    }
    else{
        while(!feof(fp)){
            ch = getc(fp);
            printf("%c", ch);
        }
        fclose(fp);
        printf("\n\n\tPress any key to continue...\n");
        getch();
    }
}


void Delete(){

    char fn[100];
    printf("\n\tEnter the file name: ");
    scanf("%s",fn);
    fp = fopen(fn,"r");
    if(fp == NULL) {
        printf("\n\tError: File not found!");
        exit(1);
        fclose(fp);
    }
    
    if(remove(fn) == 0) {
        printf("\n\n\tFile has been deleted successfully!\n");
        printf("\n\n\tPress any key to continue...\n");
        fclose(fp);
    }
    else{
        printf("\n\tError!\n");
        printf("\n\n\tPress any key to continue...\n");
        getch();
    }

}

void Append(){
    char c, fn[100];

    printf("\n\tEnter the file name: ");
    scanf("%s", fn);
    fp1 = fopen(fn, "r");
    if(fp1 == NULL)  {
        printf("\n\tError: File not found!");
        exit(1);
        fclose(fp1);
    }
    while(!feof(fp1)){
        c = getc(fp1);
        printf("%c", c);
    }
    fclose(fp1);

    printf("\n\tType the text and press 'Ctrl+S' to append.\n");

    fp1 = fopen(fn, "a");
    while(1){
        c = getch();
        if(c==19) //ASCII Code 19 == DC3(which basically means CTRL+S)
            goto end;
        if(c==13)   { //cartige return
            c='\n';
            printf("\n\t");
            fputc(c,fp1);
        }
        else{
            printf("%c",c);
            fputc(c,fp1);
        }

    }
    end: fclose(fp1);
    getch();
}

int main() {

    char c[5];

    printf("\t\t WLC to CLI-Text-Editor\t\t\t\n\n");
    do{

        printf("\n--> (Type ':h' for help) ");
        scanf("%s",&c);

        if(strcmp(":h", c) == 0){
            printf("\n\t':c' - CREATE\n\t':r' - RENAME\n\t':d' - DISPLAY\n\t':a' - APPEND\n\t':del' - DELETE\n\t':ex' - EXIT\n");
        }
        else if(strcmp(":c", c) == 0){
            Create();
        }
        else if(strcmp(":d", c) == 0){
            Display();
        }
        else if(strcmp(":a", c) == 0){
            Append();
        }
        else if(strcmp(":r", c) == 0){
            Rename();
        }
        else if(strcmp(":del", c) == 0){
            Delete();
        }
        else if(strcmp(":ex", c) == 0){
            exit(0);
        }
        else{
            printf("\n\tError: Invalid Command!!\n");
        }

    } while(1);

    return 0;
}
