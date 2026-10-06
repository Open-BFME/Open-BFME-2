// cl: /MD
//
// ?Rva003EFE82Get@@YAHPAURva003EFE82Obj@@PAX@Z, retail 0x003EFE82, 24 bytes.
// Free function forwarding to virtual slot 0x94 (37) on its first arg:
// obj->Get("LivingWorldRegionID", out, 4) with this in ecx. Frameless
// push-mem shape needs /O1 (defaults /O2 emits mov edx plus push edx).
// Leaf (indirect call only). Callers include 0x0020EFFE 0x0020F083 0x002B9C1F
// 0x003F3082 0x003F708E. Prev 0x003EFDD7 lea getter / next 0x003EFE9A const
// getter. Honest address name; owner class and virtual identity unproven.
struct Rva003EFE82Obj
{
	virtual void _pad00() = 0;
	virtual void _pad01() = 0;
	virtual void _pad02() = 0;
	virtual void _pad03() = 0;
	virtual void _pad04() = 0;
	virtual void _pad05() = 0;
	virtual void _pad06() = 0;
	virtual void _pad07() = 0;
	virtual void _pad08() = 0;
	virtual void _pad09() = 0;
	virtual void _pad10() = 0;
	virtual void _pad11() = 0;
	virtual void _pad12() = 0;
	virtual void _pad13() = 0;
	virtual void _pad14() = 0;
	virtual void _pad15() = 0;
	virtual void _pad16() = 0;
	virtual void _pad17() = 0;
	virtual void _pad18() = 0;
	virtual void _pad19() = 0;
	virtual void _pad20() = 0;
	virtual void _pad21() = 0;
	virtual void _pad22() = 0;
	virtual void _pad23() = 0;
	virtual void _pad24() = 0;
	virtual void _pad25() = 0;
	virtual void _pad26() = 0;
	virtual void _pad27() = 0;
	virtual void _pad28() = 0;
	virtual void _pad29() = 0;
	virtual void _pad30() = 0;
	virtual void _pad31() = 0;
	virtual void _pad32() = 0;
	virtual void _pad33() = 0;
	virtual void _pad34() = 0;
	virtual void _pad35() = 0;
	virtual void _pad36() = 0;
	virtual int Get(const char *name, void *out, int size);
};

int __cdecl Rva003EFE82Get(struct Rva003EFE82Obj *obj, void *out)
{
	return obj->Get("LivingWorldRegionID", out, 4);
}
