#include <stdio.h>
#include <stdlib.h>



int getHeader(FILE* parsedFile, char* header);
int parseLine(FILE* parsedFile, FILE* numfile);
void putHeader(FILE* numfile, char* header);

int main(){
    
    FILE* numfile = fopen("numline", "w");
    FILE* parsedFile = fopen("/home/zakhar/Programs/www.unicode.org/Public/UCD/latest/ucd/DerivedCoreProperties.txt", "r");
    if( (parsedFile == NULL) || (numfile == NULL) ) {
        printf("file open error\n");
        exit(1);
    }

    char header[30] = "";
    
    getHeader(parsedFile, header); 
    putHeader(numfile, header);
    
    while( parseLine(parsedFile, numfile) != 1 );

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
    fseek(parsedFile, 20, SEEK_CUR);
    fgets(header, 30 + 1, parsedFile);
    
    while( fgetc(parsedFile) != '\n' ){}
    fgetc(parsedFile);

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










