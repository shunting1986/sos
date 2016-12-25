void bootmain(void) {
	char *cp = (char *) 0xB8000;
	char *src = (char *) 0x10000;
	int i;
	for (i = 0; i < 26; i++) {
		cp[i * 2] = src[i];
		cp[i * 2 + 1] = 3;
	}
}
