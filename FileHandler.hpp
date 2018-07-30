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
    uint8_t readbuf[BUFSIZ];
    uint64_t file_size=0;
    std::ifstream ifFile;
    
    
public:
    FileHandler();
    ~FileHandler();
    bool initName(const uint8_t* name);
    uint8_t* getReadBuf();
    std::ifstream getIfFile();
    bool readFromFile();
    uint64_t getFileSize();
    
};

#endif /* FileHandler_hpp */
