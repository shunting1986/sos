typedef unsigned short int uint16_t;

void bootmain(void) {
	char *cp = (char *) 0xB8000;
	int i;
	for (i = 0; i < 26; i++) {
		cp[i * 2] = 'A' + i;
		cp[i * 2 + 1] = 3;
	}
}
