//
//  FileHandler.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include "FileHandler.hpp"
#include "printdata.hpp"
#include <iostream>

FileHandler::FileHandler()
{
    memset(readbuf, 0, sizeof(readbuf)); // init read buf by zero
}

FileHandler::~FileHandler()
{
    if(ifFile.is_open())
        ifFile.close();
}

bool FileHandler::initName(const uint8_t * name)
{
    ifFile.open((char*)name,std::ifstream::binary | std::ios::ate); //init file handler & open file as a binary & ate for get file size
    file_size=ifFile.tellg();
    ifFile.seekg(ifFile.beg);    //pointer move to begin
    cout<<"File size : "<<file_size<<endl;
    
    return ifFile.is_open();
}

uint8_t* FileHandler::getReadBuf()
{
    return readbuf;
}

uint64_t FileHandler::getFileSize()
{
    return file_size;
}
bool FileHandler::readFromFile()
{
    if(ifFile)
        ifFile.read((char*)readbuf, BUFSIZ); //read one line from file
    else
        return false;
    
    return true;
  
}
