//
//  encodeParser.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#include "encodeParser.hpp"


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
