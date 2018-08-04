//
//  encodeParser.cpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//


#include <cstring>
#include <locale>
#include <codecvt>
#include "encodeParser.hpp"
#include "printdata.hpp"
bool isASCII(u_int8_t c)
{
    if(c > 0x80)
        return false;
    
    return true;
}

uint16_t ltob16(uint16_t num)
{
    return ((num>>8) + (num<<8));
}
uint16_t btol16(uint16_t num)
{
    return ((num>>8) + (num<<8));
}
uint32_t ltob32(uint32_t num)
{
    return ((num<<24)&(0xff000000)) + ((num<<16)&(0xff0000)) + ((num>>16)&(0x0000ff00)) + ((num>>24)&(0x000000ff));
}
uint32_t btol32(uint32_t num)
{
    return ((num<<24)&(0xff000000)) + ((num<<16)&(0xff0000)) + ((num>>16)&(0x0000ff00)) + ((num>>24)&(0x000000ff));
}

std::string UTF8FromUTF16(uint16_t num)
{
    std::wstring_convert<codecvt_utf8_utf16<char16_t>,char16_t> convert;
    return convert.to_bytes(num);
}

//std::string UTF8FromECUKR(uint16_t num)
//{
//    std::wstring_convert<codecvt_u convert;
//    return convert.to_bytes(num);
//}
int isUTF(uint8_t* c, int preEncode)
{
    //need to swap endian
    
    // if I use else if there is occured an error.
    // cuz can't not check other situaion
    uint16_t str = *((uint16_t*)c);

    if((c[0]==0)&&isASCII(c[1]))
    {
        return UTF_16ASCII;
    }
    else if((((c[0]&UTF_24MASK)==UTF_24BIT)&&((c[1]&UTF_SUBMASK)==UTF_SUB)&&((c[2]&UTF_SUBMASK)==UTF_SUB)) && (0xAC00<=str && str<=0xD7AF))
    {
        //if ture at both of them. return preEncode System.
        //if thre is preEncode set
        if(preEncode==UTF_24BIT||preEncode==UNICODE_KOREAN)
            return preEncode;
    }
    
    if(((c[0]&UTF_24MASK)==UTF_24BIT)&&((c[1]&UTF_SUBMASK)==UTF_SUB)&&((c[2]&UTF_SUBMASK)==UTF_SUB)) //if UTF8 and use 24 bit
    {
        return UTF_24BIT;
    }
    if(((c[0]&UTF_16MASK)==UTF_16BIT)&&((c[1]&UTF_SUBMASK)==UTF_SUB)&&!(0xAC00<=str && str<=0xD7AF)) //if UTF8 and use 16 bit
    {
        return UTF_16BIT;
    }
    else if((0xAC00<=str && str<=0xD7AF)) // if Korean lange
    {
        return UNICODE_KOREAN;
    }
    
    return false;
    
}
