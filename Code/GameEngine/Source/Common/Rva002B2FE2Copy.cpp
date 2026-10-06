// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva002B2FE2Copy@@YAXPAVRva004F6093Holder@@ABV1@@Z @0x002B2FE2 18B.
// Null-checked placement copy through the rowed Rva004F6093Holder copy ctor.
// Evidence: retail mov ecx,[esp+4]; test ecx,ecx; je ret; push [esp+8];
// call 0x004F6093; ret. Callers at 0x003F74DD 0x003F7508 0x003F79F3 0x003F7B34.
// throw() on the callee removes EH (frameless 18B); placement new needs <new>.
#include <new>
struct Rva004F6093Ref
{
	char m_pad[0xB0];
	int m_refCount;
};
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other) throw();
private:
	Rva004F6093Ref *m_ptr;
};

void __cdecl Rva002B2FE2Copy(Rva004F6093Holder *dst, const Rva004F6093Holder &src)
{
	if (dst == 0)
		return;
	new(dst) Rva004F6093Holder(src);
}
