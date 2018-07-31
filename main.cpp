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
#include "encodeParser.hpp"


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
    
    //location for travel buf
    uint64_t location=0;
    //swapBIt for check endian
    uint16_t swpBit;
    wchar_t tmp;
    
    while(fHandler.readFromFile())
    {
        while (location < BUFSIZ)
        {
            switch (isUTF(fHandler.getReadBuf()+location)) {
                case UTF_16BIT:
                    cout<<"UTF 16BIT"<<endl;
                    location+=2;
                    break;
                case UTF_24BIT:
                    cout<<"UTF 24BIT"<<endl;
                    location+=3;
                    break;
                case UTF_16ASCII:
                    cout<<(char *)(fHandler.getReadBuf()+location);
                    location +=2;
                    break;
                default:
                    //Do Swap endian parsing
                    swpBit=ltob16(*((uint16_t*)(fHandler.getReadBuf()+location)));
//                    printByHexData((uint8_t*)&swpBit, sizeof(swpBit));
                    switch (isUTF((uint8_t*)&swpBit)) {
                        case UTF_16BIT:
                            cout<<"UTF 16BIT-BE"<<endl;
                            location+=2;
                            break;
                        case UTF_24BIT:
                            cout<<"UTF 24BIT-BE"<<endl;
                            location+=3;
                            break;
                        case UTF_16ASCII:
                            cout<<(char)btol16(swpBit);
                            location +=2;
                            break;
                        default:
                            if(isASCII(fHandler.getReadBuf()[location]))
                            {
                                //if ASCII, ASCII must be check later because UTF8, 16 contain ASCII Range
                                cout<<fHandler.getReadBuf()[location]<<" ";
                                location++;
                            }
                            else{
                                //There is no ASCII code
                                cout<<" ";
                                location++;
                                
                            }
                            break;
                            
                            
                    }
                    
            }
            
            //                }
        }
        location=0; //clear location
        break;
    }
    
    return 0;
}
