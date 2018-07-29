//
//  main.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 29..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "FileHandler.hpp"
#include "printdata.hpp"

using namespace std;

void usage()
{
    cout<<"Usage : ./EncodingTranslator <FileName>"<<endl;
    exit(1);
    
}

bool chkArgc(int argc)
{
    if(argc != 2)
        return false;
    
    return true;
    
}

int main(int argc, const char * argv[]) {
    
    if(!chkArgc(argc))
        usage();
    
    const uint8_t* file = (uint8_t*)argv[1];
    
    FileHandler fHandler;
    fHandler.initName(file);
    
    while(fHandler.readLines())
    {
        printByHexData(fHandler.getReadBuf(), BUFSIZ);
        memset(fHandler.getReadBuf(), 0xff, BUFSIZ);
        sleep(0.1);
    }
    
    return 0;
}
