#include <inc/elf.h>
#include <inc/string.h>

#define TOPHY(a) ((void *) ((uint32_t) (a) & 0x0FFFFFFF))

void bootmain(void) {
	Elf32_Ehdr *ehdr = (Elf32_Ehdr *) 0x10000;
	uint8_t *file_sa = (uint8_t *) 0x10000;
	#if 0 // verify the magic number
	if (*(uint32_t *) ehdr != 0x464C457F) {
		while (1) {
		}
	}
	#endif

	// load segments
	Elf32_Phdr *phdr = (Elf32_Phdr *) (file_sa + ehdr->e_phoff);
	Elf32_Phdr *phend = phdr + ehdr->e_phnum;
	while (phdr != phend) {
		// load loadable segments
		// Let kernel itself to clear BSS
		if (phdr->p_type == PT_LOAD) {
			memcpy(TOPHY(phdr->p_vaddr), file_sa + phdr->p_offset,
				phdr->p_filesz);
		}
		++phdr;
	}

	/* // dump the first 26 bytes of kernel
	char *cp = (char *) 0xB8000;
	char *src = (char *) 0x10000;
	int i;
	for (i = 0; i < 26; i++) {
		cp[i * 2] = src[i];
		cp[i * 2 + 1] = 3;
	}
	while (1) { }
	 */
	((void(*)(void))TOPHY(ehdr->e_entry))();
}
