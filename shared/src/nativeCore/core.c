#include "core.h"

typedef enum {
	MDER_POSITIVE_INFINITY = 0x007FFFFE,
	MDER_NaN = 0x007FFFFF,
	MDER_NRes = 0x00800000,
	MDER_RESERVED_VALUE = 0x00800001,
	MDER_NEGATIVE_INFINITY = 0x00800002
} ReservedFloatValues;
static const int32_t FIRST_RESERVED_VALUE = MDER_POSITIVE_INFINITY;

// (2 ** 23 - 3)
#define MDER_FLOAT_MANTISSA_MAX 0x007FFFFD
// 2 ** 7 - 1
#define MDER_FLOAT_EXPONENT_MAX 127
#define MDER_FLOAT_EXPONENT_MIN -128
// (2 ** 23 - 3) * 10 ** 127
#define MDER_FLOAT_MAX 8.388604999999999e+133
// -(2 ** 23 - 3) * 10 ** 127
#define MDER_FLOAT_MIN (-MDER_FLOAT_MAX)
// 10 ** -128
#define MDER_FLOAT_EPSILON 1e-128
// 10 ** upper(23 * log(2) / log(10))
// precision for a number 1.0000xxx
#define MDER_FLOAT_PRECISION 10000000

typedef enum {
    MDER_S_POSITIVE_INFINITY = 0x07FE,
    MDER_S_NaN = 0x07FF,
    MDER_S_NRes = 0x0800,
    MDER_S_RESERVED_VALUE = 0x0801,
    MDER_S_NEGATIVE_INFINITY = 0x0802
} ReservedSFloatValues;

static const uint32_t FIRST_S_RESERVED_VALUE = MDER_S_POSITIVE_INFINITY;

// (2 ** 11 - 3)
#define MDER_SFLOAT_MANTISSA_MAX 0x07FD
// 2 ** 3 - 1
#define MDER_SFLOAT_EXPONENT_MAX 7
#define MDER_SFLOAT_EXPONENT_MIN -8
// (2 ** 11 - 3) * 10 ** 7
#define MDER_SFLOAT_MAX 20450000000.0
// -(2 ** 11 - 3) * 10 ** 7
#define MDER_SFLOAT_MIN (-MDER_SFLOAT_MAX)
// 10 ** -8
#define MDER_SFLOAT_EPSILON 1e-8
// 10 ** upper(11 * log(2) / log(10))
#define MDER_SFLOAT_PRECISION 10000

static const double reserved_float_values[5] = {INFINITY, NAN, NAN, NAN, -INFINITY};

float read_sfloat(uint16_t intData) {
    uint16_t mantissa = intData & 0x0FFF;
    int8_t expoent = intData >> 12;

    if (expoent >= 0x0008) {
        expoent = -((0x000F + 1) - expoent);
    }

    float output = 0;

    if (mantissa >= FIRST_S_RESERVED_VALUE && mantissa
        <= MDER_S_NEGATIVE_INFINITY) {
        output = reserved_float_values[mantissa
                           - FIRST_S_RESERVED_VALUE];
    } else {
        if (mantissa >= 0x0800) {
            mantissa = -((0x0FFF + 1) - mantissa);
        }
        double magnitude = pow(10.0f, expoent);
        output = (mantissa * magnitude);
    }

    return output;
}

uint16_t getUint16(uint8_t b [], int32_t offset, uint8_t isLittleEndian) {

    uint16_t value = 0;
    if(!isLittleEndian) {
        value = (b[offset] << 8) | (b[offset + 1]);
    } else {
        value = (b[offset+1] << 8) | (b[offset]);
    }
    return value;
}

uint32_t write_sfloat(float data)
{
	uint16_t result = MDER_S_NaN;

	if (isnan(data)) {
		//goto finally;
		return result;
	} else if (data > MDER_SFLOAT_MAX) {
		result = MDER_S_POSITIVE_INFINITY;
		//goto finally;
		return result;
	} else if (data < MDER_FLOAT_MIN) {
		result = MDER_S_NEGATIVE_INFINITY;
		//goto finally;
		return result;
	} else if (data >= -MDER_SFLOAT_EPSILON &&
		data <= MDER_SFLOAT_EPSILON) {
		result = 0;
		//goto finally;
		return result;
	}

	double sgn = data > 0 ? +1 : -1;
	double mantissa = fabs(data);
	int exponent = 0; // Note: 10**x exponent, not 2**x

	// scale up if number is too big
	while (mantissa > MDER_SFLOAT_MANTISSA_MAX) {
		mantissa /= 10.0;
		++exponent;
		if (exponent > MDER_SFLOAT_EXPONENT_MAX) {
			// argh, should not happen
			if (sgn > 0) {
				result = MDER_S_POSITIVE_INFINITY;
			} else {
				result = MDER_S_NEGATIVE_INFINITY;
			}
			//goto finally;
			return result;
		}
	}

	// scale down if number is too small
	while (mantissa < 1) {
		mantissa *= 10;
		--exponent;
		if (exponent < MDER_SFLOAT_EXPONENT_MIN) {
			// argh, should not happen
			result = 0;
			//goto finally;
			return result;
		}
	}

	// scale down if number needs more precision
	double smantissa = round(mantissa * MDER_SFLOAT_PRECISION);
	double rmantissa = round(mantissa) * MDER_SFLOAT_PRECISION;
	double mdiff = fabs(smantissa - rmantissa);
	while (mdiff > 0.5 && exponent > MDER_SFLOAT_EXPONENT_MIN &&
			(mantissa * 10) <= MDER_SFLOAT_MANTISSA_MAX) {
		mantissa *= 10;
		--exponent;
		smantissa = round(mantissa * MDER_SFLOAT_PRECISION);
		rmantissa = round(mantissa) * MDER_SFLOAT_PRECISION;
		mdiff = fabs(smantissa - rmantissa);
	}

	uint16_t int_mantissa = (uint16_t) round(sgn * mantissa);
	result = ((exponent & 0xF) << 12) | (int_mantissa & 0xFFF);

//finally:
	return result;
}