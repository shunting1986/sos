#ifndef _sos_inc_stdint_h
#define _sos_inc_stdint_h

#ifndef SOS32
#error only support 32 bit yet
#endif

/*
 * Not sure if it's a good location to put definition of NULL
 */
#define NULL ((void *) 0)

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int64_t;
typedef unsigned long long uint64_t;

#endif
