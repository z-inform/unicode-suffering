#include <stdio.h>
#include <stdlib.h>

int binarySearch(unsigned int* arr, int len, unsigned int svalue);
int getLen(FILE* numfile);
int disalpha(unsigned int ch);

int getLen(FILE* numfile){
    int count = 0;
    fseek(numfile, 0, SEEK_CUR);
    int readchar = fgetc(numfile);
    while( readchar != EOF ){
        if( readchar == ' ' ) count++;
        readchar = fgetc(numfile);
    }
    fseek(numfile, 0, SEEK_SET);
    return count;
}


int disalpha(unsigned int ch){
    static FILE* datafile;
    static int len;
    static unsigned int* arr;
    if( datafile == NULL ){
        datafile = fopen("Alphabetic", "r");
        len = getLen(datafile);
        arr = (unsigned int*) calloc(len, sizeof(unsigned int));
        for(int i = 0; i < len; i++) fscanf(datafile, "%x", &arr[i]);
    }
    
    return binarySearch(arr, len, ch);


}


int binarySearch(unsigned int* arr, int len, unsigned int svalue){
    
    int low = 0;
    int high = len;
    int middle = 0;
    unsigned int mvalue = 0;

    if( (svalue < arr[0]) || (svalue > arr[len]) ) return 0;

    if( arr[0] == svalue ) return 1;

    if( arr[len] == svalue ) return 1;


    while( (high - low) > 1 ){
        middle = (low + high) / 2;
        mvalue = arr[middle];

        if( svalue == mvalue ) return 1;
        else if( svalue < mvalue ) high = middle;
        else low = middle;

    }
        
    return 0;

}
