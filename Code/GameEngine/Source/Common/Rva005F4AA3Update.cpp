// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva005F4AA3@Rva005F4AA3@@QAEXXZ, RVA 0x005F4AA3, 22 bytes.
// Address-derived thiscall helper; retail reads [this-4] and installs two vtable pointers.
extern "C" char s_slot3E4first;
extern const void *const g_00C77C70[];

class Rva005F4AA3
{
public:
	void rva005F4AA3();
};

void Rva005F4AA3::rva005F4AA3()
{
	unsigned int table = *(unsigned int *)((char *)this - 4);
	*(unsigned int *)((char *)this - 8) = (unsigned int)&s_slot3E4first;
	table = *(unsigned int *)(table + 4);
	*(unsigned int *)(table + (unsigned int)this - 4) = (unsigned int)g_00C77C70;
}
