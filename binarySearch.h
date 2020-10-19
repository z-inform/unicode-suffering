int binarySearch(FILE* numfile, int len, unsigned int svalue);
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



int binarySearch(FILE* numfile, int len, unsigned int svalue){
    
    int low = 0;
    int high = len;
    int middle = 0;
    unsigned int mvalue = 0;
    
    fseek(numfile, 0, SEEK_SET);
    fscanf(numfile, "%x", &mvalue);
    if( mvalue == svalue ) return 1;

    fseek(numfile, -4, SEEK_END);
    fscanf(numfile, "%x", &mvalue);
    if( mvalue == svalue ) return 1;

    fseek(numfile, -4, SEEK_END);



    while( (high - low) > 1 ){
        middle = (low + high) / 2;

        int spcount = 0;
        fseek(numfile, 0, SEEK_SET);
        while( spcount < middle ){
            if( fgetc(numfile) == ' ' ) spcount++;
        }

        fscanf(numfile, "%x", &mvalue);

        if( svalue == mvalue ) return 1;
        else if( svalue < mvalue ) high = middle;
        else low = middle;


    }
        
    return 0;

}
