// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?Rva000FDCD7Get@@YAHXZ @0x000FDCD7 26B; chain of Rva000F630CGet.
// Retail: call 0x000F630C / test al,al / jne / xor eax,eax / ret / xor eax,eax / mov [0x00DE1F50],0x00DB5BD4 / inc eax / ret.
// Target facts: calls rowed ?Rva000F630CGet@@YAHXZ; tests low byte so false path needs xor; sets data 0x009E1F50 to data 0x009B5BD4 then returns 1 else 0.
// Callers: none; callees: 0x000F630C only.
// Not established: owning TU/class and global identities; names are address-derived.
extern unsigned int g_Va00DE1F50;
// g_Va00DE1F50: matched references place it at VA 0xde1f50 (zero-filled .bss).
unsigned int g_Va00DE1F50;
int Rva000F630CGet(void);

int Rva000FDCD7Get(void)
{
	if ((unsigned char)Rva000F630CGet() == 0)
		return 0;
	g_Va00DE1F50 = 0x00DB5BD4;
	return 1;
}
