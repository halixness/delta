#include <stdio.h>
#include <string.h>
#include <time.h>

#define CHARS 35
#define KEY_LENGHT 30
#define MAX_INPUT 100000

char key[KEY_LENGHT];
char chars[CHARS] = {"abcdefghijklmnopqrstuwxyz1234567890"};


void generateKey();
void injectContent(char* filename);
void readContent(char* filename);
int checkFile(char* filename);


int main(){

    char filename[MAX_INPUT];
    int option;

    while(1){
        do{

            /* Title text */
            printf(" ______   ______   __     _________  ________   \n");
            printf("/_____/\\ /_____/\\ /_/\\   /________/\\/_______/\\   \n");
            printf("\\:::_ \\ \\\\::::_\\/_\\:\\ \\  \\__.::.__\\/\\::: _  \\ \\   \n");
            printf(" \\:\\ \\ \\ \\\\:\\/___/\\\\:\\ \\    \\::\\ \\   \\::(_)  \\ \\   \n");
            printf("  \\:\\/.:| |\\:\\____/\\\\:\\/___/\\\\::\\ \\   \\:.\\ \\  \\ \\   \n");
            printf("   \\____/_/ \\_____\\/ \\_____\\/ \\__\\/    \\__\\/\\__\\/    \n");


            /* Selecting filename */
            while(1){
                printf("\n Insert filename (with extention) selected for operations : ");
                gets(filename);

                if(checkFile(filename))
                    break;
                else
                    printf("The file doesn't exists.");
            }


            /* Menu */
            printf("\t 0. Inject content \n");
            printf("\t 1. Read injected content \n");
            printf("\t 2. Exit program \n");

            printf("\n Choose an option : ");
            scanf("%d", &option);

            getchar();


            switch(option){
                case 0:
                    injectContent(filename);
                    break;

                case 1:
                    readContent(filename);
                    break;

                case 2:
                    return 0;

                default:
                    break;
            }

            putchar(10);
            system("pause");
            system("cls");

        }while(option < 0 || option > 2);
    }

    return 0;
}


void generateKey(){
    int i;
    srand((unsigned)time(NULL));

    for(i = 0; i < KEY_LENGHT; i++){
        key[i] = chars[rand()%CHARS];
    }

}

void injectContent(char* filename){

    char content[MAX_INPUT];
    char command[MAX_INPUT] = {};

    printf("Insert content : ");
    gets(content);

    generateKey();


    strcat(command, "echo ");
    strcat(command, content);
    strcat(command, " >> ");
    strcat(command, filename);
    strcat(command,":");
    strcat(command, key);
    strcat(command, ".txt");

    system(command);

    printf("Content successully hidden.\n Key generated : %s", key);

}

void readContent(char* filename){

    char command[MAX_INPUT] = {};
    char keyValue[MAX_INPUT];
    char hiddenfile[MAX_INPUT] = {};

    printf("Insert DataStream key : ");
    gets(keyValue);

    strcat(command, "notepad.exe ");

    /* Composing reading command */
    strcat(command, filename);
    strcat(command, ":");
    strcat(command, keyValue);
    strcat(command, ".txt");

    /* Composing string to check file extistance */
    strcat(hiddenfile, filename);
    strcat(hiddenfile, ":");
    strcat(hiddenfile, keyValue);
    strcat(hiddenfile, ".txt");

    if(checkFile(hiddenfile))
        system(command);
    else
        printf("\n There's no datastream available for this key.");

}

int checkFile(char* filename){

    FILE *fp;

    fp = fopen(filename,"r");

    if(fp)
        return 1;
    else
        return 0;
}
