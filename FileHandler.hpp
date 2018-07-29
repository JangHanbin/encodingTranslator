//
//  FileHandler.hpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#ifndef FileHandler_hpp
#define FileHandler_hpp

#include <fstream>


class FileHandler{
    uint8_t readbuf[BUFSIZ]; //BUFSIZ is 1024 and define in stdio
    std::ifstream ifFile;
    
public:
    FileHandler();
    ~FileHandler();
    void initName(const uint8_t* name);
    uint8_t* getReadBuf();
    std::ifstream getIfFile();
    bool readLines();
    
};

#endif /* FileHandler_hpp */
