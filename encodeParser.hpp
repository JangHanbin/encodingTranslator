//
//  encodeParser.hpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#ifndef encodeParser_hpp
#define encodeParser_hpp

/* There is some rules in UTF-8 and Here's a Magic Number list */
#define UTF_ASCII 0x7F
#define UTF_16ASCII 0x7F0
#define UTF_16BIT 0x80
#define UTF_24BIT 0x800
#define UTF_SUB 0x7F



#include <iostream>

uint16_t ltob16(uint16_t num);  //little endian to big endian 16bit
uint16_t btol16(uint16_t num);  //big endian to little endian 16bit
uint32_t ltob32(uint32_t num);  //little endian to big endian 32bit
uint32_t btol32(uint32_t num);  //big endian to little endian 32bit
bool isASCII(u_int8_t c);
int isUTF(u_int8_t* c); //Return  Magic  number of UTF 


#endif /* encodeParser_hpp */
