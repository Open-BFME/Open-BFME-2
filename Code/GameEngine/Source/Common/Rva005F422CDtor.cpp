// cl: /O1 /DNDEBUG /MD /arch:SSE /G7
// ?rva005F422C@Rva005F422C@@QAEXXZ, RVA 0x005F422C, 40 bytes.
// Packet pin supplies the address-derived name; retail installs vtable data 0x00879468 and releases the pointer at this-8.
extern const void *const g_00C79468[];
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class Rva005F422C
{
public:
	void rva005F422C();
};

void Rva005F422C::rva005F422C()
{
	unsigned int subobject = *(unsigned int *)((char *)this - 0x14);
	unsigned int table = *(unsigned int *)(subobject + 4);
	*(unsigned int *)(table + (unsigned int)this - 0x14) = (unsigned int)g_00C79468;
	subobject = *(unsigned int *)((char *)this - 0x14);
	table = *(unsigned int *)(subobject + 4);
	*(unsigned int *)(table + (unsigned int)this - 0x18) = table - 0x14;
	TargetRef00217D4C *p = *(TargetRef00217D4C **)((char *)this - 8);
	if (p)
		ReleaseTreeHintRef00217D4C(p);
}
