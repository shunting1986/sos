void
kern_init(void) {
	char *raw_s = "Welcome to SOS!";
	char *s = (char *) ((int) raw_s & 0x0FFFFFFF);
	char *cp = (char *) 0xB8000;
	int i;
	for (i = 0; s[i]; i++) {
		cp[i * 2] =  s[i];
		cp[i * 2 + 1] = 3;
	}
}
