#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <cassert>



int getHeader(FILE* parsedFile, char* header);
int parseLine(FILE* parsedFile, FILE* numfile);
void putHeader(FILE* numfile, char* header);

int main(){
    
    char filename[200] = "";
    char* header = (char*) calloc(50, sizeof(char));
    char path[70] = "/home/zakhar/diy_isalpha/ucd/";
    char* fullpath = (char*) calloc(70, sizeof(char));;
    FILE* numfile = NULL;
    FILE* parsedFile = NULL;     


    scanf("%s", filename);

    printf("\nfile name: %s\n", filename);
    parsedFile = fopen(filename, "r");


    if( parsedFile == NULL ) {
        printf("\nfile open error: [%d]\n", errno);
        exit(1);
    }
    

    while( getHeader(parsedFile, header) != 1 ){
        
        int i = 0;
        for(; path[i] != '\0'; i++ ) fullpath[i] = path[i];
        fullpath[i] = '\0';

        fullpath = strcat(fullpath, header);
        printf("newfile: %s\n", fullpath);

        numfile = fopen(fullpath, "w");
        assert( numfile != NULL );

        while( parseLine(parsedFile, numfile) != 1 );

        fclose(numfile);
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
    
    readch = fgetc(parsedFile);

    int i = 0;
    
    while( (readch != EOF) && (readch != '\n') && (readch != ' ') ){
        header[i] = readch;
        i++;
        readch = fgetc(parsedFile);
    }

    header[i] = '\0';

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










