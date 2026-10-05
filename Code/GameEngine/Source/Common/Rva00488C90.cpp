// cl: /O1 /MD /arch:SSE
//
// ?rva00488C90@Rva00488C90@@QAEHXZ, retail 0x00488C90 (52 bytes).
// Address-derived helper: calls this vtable's slot 28 twice when non-null,
// reads the returned float at +0x324, and converts it to int. The inline fld
// keeps MSVC's x87 __ftol2 path used by retail after its SSE conditional load.

class Rva00488C90
{
public:
#define RVA00488C90_SLOT(n) virtual void vslot##n() = 0;
RVA00488C90_SLOT(00) RVA00488C90_SLOT(01) RVA00488C90_SLOT(02) RVA00488C90_SLOT(03)
RVA00488C90_SLOT(04) RVA00488C90_SLOT(05) RVA00488C90_SLOT(06) RVA00488C90_SLOT(07)
RVA00488C90_SLOT(08) RVA00488C90_SLOT(09) RVA00488C90_SLOT(10) RVA00488C90_SLOT(11)
RVA00488C90_SLOT(12) RVA00488C90_SLOT(13) RVA00488C90_SLOT(14) RVA00488C90_SLOT(15)
RVA00488C90_SLOT(16) RVA00488C90_SLOT(17) RVA00488C90_SLOT(18) RVA00488C90_SLOT(19)
RVA00488C90_SLOT(20) RVA00488C90_SLOT(21) RVA00488C90_SLOT(22) RVA00488C90_SLOT(23)
RVA00488C90_SLOT(24) RVA00488C90_SLOT(25) RVA00488C90_SLOT(26) RVA00488C90_SLOT(27)
#undef RVA00488C90_SLOT
	virtual void *vslot28() = 0;
	int rva00488C90();
};

extern "C" int __cdecl _ftol2(void);

// ?<Rva00488C90::rva00488C90> present-unmatched
int Rva00488C90::rva00488C90()
{
	float value;
	if (vslot28())
		value = *(float *)((char *)vslot28() + 0x324);
	else
		value = 0.0f;
	__asm { fld dword ptr [value] }
	return _ftol2();
}
