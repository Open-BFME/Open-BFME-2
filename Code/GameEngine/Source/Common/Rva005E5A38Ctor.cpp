// cl: /DNDEBUG /MD
// ??0Rva005E5A38@@QAE@H@Z @ 0x005E5A38 46B
// Repair: native 0x005E5A46 initializes its by-value stack temporary with
// Rva005E5A24Init; it never copies g_00E0661C. The actual 24-byte copy
// constructor remains declaration-only and resolves to FixedStorageCopyBFME2.
// The default initializer is inline source structure, not a new retail identity.
// Evidence: derived of rowed base 0x005CBA04 via temp built by rowed 0x005E5A24 bits 0 3; outer int at +8; vtable 0x00C77D90; caller 0x005E5B3E passes esi; sibling Rva005756B6 same shape.
typedef int Int;
typedef unsigned int UnsignedInt;

#include "../../Include/Common/BitFlagsTemplate.h"

BitFlags<11> *Rva005E5A24Init(BitFlags<11> *p);

class BfmeFixedStorage002CF0F0
{
	char m_bytes[4];
public:
	BfmeFixedStorage002CF0F0()
	{
		Rva005E5A24Init((BitFlags<11> *)this);
	}
	__declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};

class Rva005CBA04
{
public:
	virtual ~Rva005CBA04();
	Rva005CBA04(BfmeFixedStorage002CF0F0 storage);
private:
	BfmeFixedStorage002CF0F0 m_storage;
};

class Rva005E5A38 : public Rva005CBA04
{
public:
	Rva005E5A38(int arg);
	// Empty: retail's vtable slot 0 (deleting dtor 0x005E5A66) calls 0x00576FCE,
	// one jump to the base dtor 0x005CB9F3.
	virtual ~Rva005E5A38() {}
private:
	int m_08;
};

Rva005E5A38::Rva005E5A38(int arg)
	: Rva005CBA04(BfmeFixedStorage002CF0F0())
	, m_08(arg)
{
}
