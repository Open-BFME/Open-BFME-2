// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva005CC484@Rva005CC484@@QAEXXZ, RVA 0x005CC484, 22 bytes.
// Same shape as Rva005F4AA3: reads [this-4], installs C74E6C at this-8 and C74E68 at this+off-4.
extern const void *const g_00C74E6C[];
extern const void *const g_00C74E68[];

class Rva005CC484
{
public:
	void rva005CC484();
};

void Rva005CC484::rva005CC484()
{
	unsigned int table = *(unsigned int *)((char *)this - 4);
	*(unsigned int *)((char *)this - 8) = (unsigned int)g_00C74E6C;
	table = *(unsigned int *)(table + 4);
	*(unsigned int *)(table + (unsigned int)this - 4) = (unsigned int)g_00C74E68;
}
