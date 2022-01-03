///
/// https://stackoverflow.com/questions/11564270/how-to-convert-ieee-11073-16-bit-sfloat-to-simple-float-in-java/16474957
/// https://github.com/signove/antidote/blob/master/src/util/bytelib.c
///
#include <stdint.h>
#include <math.h>

float read_sfloat(uint16_t intData);
uint16_t getUint16(uint8_t b [], int32_t offset, uint8_t isLittleEndian);
uint32_t write_sfloat(float data);