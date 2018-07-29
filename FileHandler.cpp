//
//  FileHandler.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include "FileHandler.hpp"
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

void FileHandler::initName(const uint8_t * name)
{
    ifFile.open((char*)name,std::ios::binary); //init file handler & open file as a binary
}

uint8_t* FileHandler::getReadBuf()
{
    return readbuf;
}

bool FileHandler::readLines()
{

    ifFile.getline((char*)readbuf, BUFSIZ); //read one line from file


    return !ifFile.eof(); // return true if not eof 
        
}
