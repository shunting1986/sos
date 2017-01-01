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

#ifndef _BOOT_LOADER_ // NOTE: a better solution is move the implementation to c file so boot loader will not include the machine code for these functions because of including the header file
inline void memmove(void *_dst, void *_src, int32_t len) {
	char *dst = _dst;
	char *src = _src;
	if (len <= 0 || dst == src) {
		return;
	}
	if (src > dst) {
		int i;
		for (i = 0; i < len; i++) {
			dst[i] = src[i];
		}
	} else {
		int i;
		for (i = 0; i < len; i++) {
			dst[len - 1 - i] = src[len - 1 - i];
		}
	}
}
#endif

#endif
