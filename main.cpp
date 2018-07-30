//
//  main.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 29..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <vector>
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
    if(!fHandler.initName(file))
    {
        cout<<"File Open error! check file path or is exist"<<endl;
    }
    
    
    while(fHandler.readFromFile())
    {
        printByHexData(fHandler.getReadBuf(), BUFSIZ);

    }

    return 0;
}
