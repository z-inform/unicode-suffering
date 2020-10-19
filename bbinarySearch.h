#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int binarySearch(unsigned int* arr, int len, unsigned int svalue);
int getLen(FILE* numfile);

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



int binarySearch(unsigned int* arr, int len, unsigned int svalue){
    
    int low = 0;
    int high = len;
    int middle = 0;
    unsigned int mvalue = 0;

    if( arr[0] == svalue ) return 1;

    if( arr[len] == svalue ) return 1;


    while( (high - low) > 1 ){
        middle = (low + high) / 2;
        mvalue = arr[middle];

        if( svalue == mvalue ) return 1;
        else if( svalue < mvalue ) high = middle;
        else low = middle;

        assert( low >= 0 );
        assert( high <= len );

    }
        
    return 0;

}
