#ifndef _sos_inc_stdarg_h
#define _sos_inc_stdarg_h

#ifndef SOS32
#error need revise for 64 bit
#endif

typedef void *va_list;

// XXX assume shift a size of long is good enough
#define va_start(va, last) (va = (void *) &last + sizeof(long))

#define va_end(va) /* do nothing */

#define va_arg(va, type) (va += sizeof(long), *(type *) (va - sizeof(long)))

#endif
