//
//  encodeParser.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include "encodeParser.hpp"
#include <cstring>

bool isASCII(u_int8_t c)
{
    if(c > 0x80)
        return false;
    
    return true;
}

uint16_t ltob16(uint16_t num)
{
    return (num>>8) + (num<<8);
}
uint16_t btol16(uint16_t num)
{
    return(num>>8) + (num<<8);
}
uint32_t ltob32(uint32_t num)
{
    return ((num<<24)&(0xff000000)) + ((num<<16)&(0xff0000)) + ((num>>16)&(0x0000ff00)) + ((num>>24)&(0x000000ff));
}
uint32_t btol32(uint32_t num)
{
    return ((num<<24)&(0xff000000)) + ((num<<16)&(0xff0000)) + ((num>>16)&(0x0000ff00)) + ((num>>24)&(0x000000ff));
}

int isUTF(uint8_t* c)
{
    
    if((c[0]==0)&&isASCII(c[1]))
        return UTF_16ASCII;
    else if(((c[0]&UTF_16BIT)==UTF_16BIT)&&((c[1]&UTF_SUB )==UTF_SUB)) //if UTF16 and use 16 bit
        return UTF_16BIT;
    else if(((c[0]&UTF_24BIT)==UTF_24BIT)&&((c[1]&UTF_SUB)==UTF_SUB)&&((c[2]&UTF_SUB)==UTF_SUB)) //if UTF16 and use 24 bit
        return UTF_24BIT;
    
    return false;
    
}
