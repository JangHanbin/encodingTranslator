//
//  encodeParser.hpp
//  EncodingTranslator
//
//  Created by 장한빈 on 2018. 7. 30..
//  Copyright © 2018년 장한빈. All rights reserved.
//

#ifndef encodeParser_hpp
#define encodeParser_hpp

#include <iostream>

uint16_t ltob16(uint16_t num);  //little endian to big endian 16bit
uint16_t btol16(uint16_t num);  //big endian to little endian 16bit
uint32_t ltob32(uint32_t num);  //little endian to big endian 16bit
uint32_t btol32(uint32_t num);  //big endian to little endian 16bit
bool isASCII(u_int8_t c);

#endif /* encodeParser_hpp */
