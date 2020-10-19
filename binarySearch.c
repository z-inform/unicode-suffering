#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>

int binarySearch(FILE* numfile, int len, unsigned int svalue);

int main(){

    int count = 0;

    FILE* numfile = fopen("/home/zakhar/diy_isalpha/testbin", "rb");

    //struct stat fstats = {0};
    //stat("/home/zakhar/diy_isalpha/testbin", &fstats);
    
    int readchar = fgetc(numfile);

    while( readchar != EOF ){
        if( readchar == ' ' ) count++;
        readchar = fgetc(numfile);
    }
   
    count++;

    printf("number: %d\n", count);

    printf("started search\n");

    unsigned int hm;
    scanf("%x", &hm);
    printf("result of search: |%d|\n", binarySearch(numfile, count, hm));

    return 0;
}

int binarySearch(FILE* numfile, int len, unsigned int svalue){
    
    int low = 0;
    int high = len;
    int middle = 0;
    unsigned int mvalue = 0;

    while( (high - low) >= 1 ){
        middle = (low + high) / 2;
        printf("mid coord: %d\n", middle);

        int spcount = 0;
        fseek(numfile, 0, SEEK_SET);
        while( spcount < middle ){
            if( fgetc(numfile) == ' ' ) spcount++;
        }

        fscanf(numfile, "%x", &mvalue);
        printf("mid val: %x\n", mvalue);

        if( svalue == mvalue ) return 1;
        else if( svalue < mvalue ) high = middle;
        else low = middle;

        assert( low >= 0 );
        assert( high <= len );

    }
        
    return 0;

}
