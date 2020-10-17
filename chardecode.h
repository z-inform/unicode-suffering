#include <stdio.h>
#include <ctype.h>
#include <locale.h>


int rchar(FILE* fp, int byte);

int rchar(FILE* fp, int byte){
    
    int chcode = 0;
    char count = 0;

if( (byte & 0x80) == 0 ){
        count = 0;
        chcode = byte & 0x7F;
    }
    else if( (byte & 0xF8) == 0xF0 ){
        count = 3; 
        chcode = byte & 0x7;
    }
    else if( (byte & 0xF0) == 0xE0){
        count = 2;
        chcode = byte & 0xF;
    }
    else if( (byte & 0xE0) == 0xC0 ){
        count = 1;
        chcode = byte & 0x1F;
    }
    else{
        return 0x00; //Возращается в случае ошибки при декодировании        
    }

    for(int i = 0; i < count; i++){
        chcode = chcode << 6;
        fscanf(fp, "%c", (char*) &byte);
        chcode = chcode | (byte & 0x3F);
    }


    return chcode;
}



