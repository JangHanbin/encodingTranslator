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

void printWord(uint8_t* c, int size)
{
    uint8_t printable[5]={0,};
    memcpy(printable, c, size);
    cout<<printable;
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
    int encode;
    int preEncode=0;
    while(fHandler.readFromFile())
    {
        while (location < BUFSIZ)
        {
            encode =isUTF(fHandler.getReadBuf()+location,preEncode);
            if(encode) //if there is encode set
                preEncode = encode;
            
            //check situaltion
            switch (encode) {
                case UTF_16BIT:
                    swpBit = *((uint16_t*)(fHandler.getReadBuf()+location));
                    cout<<UTF8FromUTF16(swpBit);
                    location+=2;
                    break;
                case UTF_24BIT:
                    printWord(fHandler.getReadBuf()+location, 3);
                    location+=3;
                    break;
                case UTF_16ASCII:
                    printWord(fHandler.getReadBuf()+location, 2);
                    location +=2;
                    break;
                case UNICODE_KOREAN:
                    cout<<UTF8FromUTF16(*((uint16_t*)(fHandler.getReadBuf()+location)));
//                    printWord(fHandler.getReadBuf()+location, 2);
//                    cout<<
                    location+=2;
                    break;
                default:
                    //Do Swap endian parsing
                    swpBit=ltob16(*((uint16_t*)(fHandler.getReadBuf()+location)));
                    encode =isUTF((uint8_t*)&swpBit, preEncode);
                    if(encode) //if there is encode set
                        preEncode = encode;
                    switch (encode) {
                        case UTF_16BIT:
                            cout<<UTF8FromUTF16(swpBit);
                            location+=2;
                            break;
                        case UTF_24BIT:
                            
                            cout<<"UTF 24BIT-BE"<<endl;
                            location+=3;
                            break;
                        case UTF_16ASCII:
                            cout<<UTF8FromUTF16(btol16(swpBit));
                            location +=2;
                            break;
                        case UNICODE_KOREAN:
                            cout<<UTF8FromUTF16(swpBit);
                            location +=2;
                            break;
                        default:
                            if(isASCII(*(fHandler.getReadBuf()+location)))
                            {
                                preEncode = UTF_ASCII;
                                //if ASCII, ASCII must be check later because UTF8, 16 contain ASCII Range
                                printWord(fHandler.getReadBuf()+location, 1);
                                location++;
                            }
                            else{
                                //There is no ASCII code
                                location++;
                            }
                            break;
                    }
            }
        }
        location=0; //clear location
        break;
    }
    
    return 0;
}
