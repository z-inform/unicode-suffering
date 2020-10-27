#pragma once
#include <stdio.h>
#include <ctype.h>
#include <math.h>


int decodeChar(FILE* fp, int byte);

int encodeChar(unsigned int point);

void putChar(FILE* resFile, unsigned int unicodeChar);

void putChar(FILE* resFile, unsigned int unicodeChar){
    for(int move = 0; (move < 4); move++){
        unsigned int pointChar = (encodeChar(unicodeChar) << move * 8) >> 3*8;
        if( pointChar != 0x0 )  fputc(pointChar, resFile);
    }

}


int encodeChar(unsigned int point){

    int count = (int) (log(point) / log(2) + 1);
    int chcode = 0;
    
    if( count <= 7 ){
        chcode = point;
    }
    else if( count <= 11 ){
        chcode = 0xC080;
        chcode = chcode | (point & 0x3F);
        chcode = chcode | ( (point & 0x7C0) << 2 ); 
    }
    else if( count <= 16 ){ 
        chcode = 0xE08080;
        chcode = chcode | (point & 0x3F);
        chcode = chcode | ( (point & 0x7C0) << 2 );
        chcode = chcode | ( (point & 0xF000) << 4 );
    }
    else if( count <= 21 ){ 
        chcode = 0xF0808080; 
        chcode = chcode | (point & 0x3F);
        chcode = chcode | ( (point & 0x7C0) << 2 );
        chcode = chcode | ( (point & 0x3F000) << 4 );
        chcode = chcode | ( (point & 0x1C0000) << 6 );
    }
    else return -1;


    return chcode;
}


int decodeChar(FILE* fp, int byte){
    
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
        return -1; //Возращается в случае ошибки при декодировании        
    }

    for(int i = 0; i < count; i++){
        chcode = chcode << 6;
        fscanf(fp, "%c", (char*) &byte);
        chcode = chcode | (byte & 0x3F);
    }


    return chcode;
}



