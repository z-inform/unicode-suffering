#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>



int getHeader(FILE* parsedFile, char* header);
int parseLine(FILE* parsedFile, FILE* numfile);
void putHeader(FILE* numfile, char* header);

int main(){
    
    char filename[200] = "";
    char header[50] = "";
    FILE* numfile = fopen("numline", "w");
    FILE* parsedFile = NULL;     


    printf("Enter filename or \"exit\" to exit:\t");
    scanf("%s", filename);

    //fgets(filename, 200, stdin);

    while( strcmp(filename, "exit") != 0 ){
        printf("%s", filename);
        parsedFile = fopen(filename, "r");


        if( (parsedFile == NULL) || (numfile == NULL) ) {
            printf("\nfile open error: [%d]\n", errno);
            exit(1);
        }
        
/*      while( parseLine(parsedFile, numfile) != 1 );

        fprintf(parsedFile, "\n");

        fprintf(parsedFile, "text"); */

        while( getHeader(parsedFile, header) != 1 ){

            putHeader(numfile, header);
           
            while( parseLine(parsedFile, numfile) != 1 );

            fprintf(numfile, "\n");
        }
    
        printf("\nEnter filename or \"exit\" to exit:\t");
        scanf("%s", filename); 

    } 

    return 0;
}

void putHeader(FILE* numfile, char* header){
    
    fputc('[', numfile);
    for( int i = 0; header[i] != '\n'; i++){
        fputc(header[i], numfile);
    }
    fputc(']', numfile);
    fputc(' ', numfile);

}


int getHeader(FILE* parsedFile, char* header){
    int readch = fgetc(parsedFile);
    bool brflag = true;

    while( (readch != EOF) && (brflag == true) ){
        if( readch == '#' ){
            fseek(parsedFile, 1, SEEK_CUR);
            if( fgetc(parsedFile) == '=' ) brflag = false;
        }
        readch = fgetc(parsedFile);
    }

    if( brflag == true ) return 1;

    while( fgetc(parsedFile) != '\n' ){};
    fgetc(parsedFile);

    while( fgetc(parsedFile) != ':' );
    while( fgetc(parsedFile) == ' ' );
    fseek(parsedFile, -1, SEEK_CUR);
    

    fgets(header, 50 + 1, parsedFile);
    
    bool comEnd = false;

    while( comEnd == false ){
        while( fgetc(parsedFile) != '\n' );
        if( fgetc(parsedFile) != '#' ) comEnd=true;
    }


    return 0;
}

int parseLine(FILE* parsedFile, FILE* numfile){

    unsigned int codePoint = 0;
    unsigned int rCodePoint = 0; // second codepoint if defined as range
    bool rangeFlag = false;

    if( fscanf(parsedFile, "%x", &codePoint) == 0 ) return 1;
    else{
        if( fgetc(parsedFile) == '.' ){
            fseek(parsedFile, 1, SEEK_CUR);
            fscanf(parsedFile, "%x", &rCodePoint);
            rangeFlag = true;
        }
            
        if( !rangeFlag ){
            fprintf(numfile, "%x ", codePoint);
        }
        else{
            for( unsigned int i = codePoint; i <= rCodePoint; i++){
                fprintf(numfile, "%x ", i);
            }
        }

        while( fgetc(parsedFile) != '\n' );
    }



    return 0;
}










