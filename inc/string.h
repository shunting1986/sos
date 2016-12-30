#ifndef _sos_inc_string_h
#define _sos_inc_string_h

inline void memcpy(void *dst, void *src, int32_t len) {
	uint8_t *dd = dst;
	uint8_t *ss = src;
	int i;
	for (i = 0; i < len; i++) {
		dd[i] = ss[i];
	}
}

#endif
