void
kern_init(void) {
	char *s = "Welcome to SOS!";
	char *cp = (char *) 0xB8000;
	int i;
	for (i = 0; s[i]; i++) {
		cp[i * 2] =  s[i];
		cp[i * 2 + 1] = 3;
	}
}