// ?rva00468657@Rva00468657@@QAEXPAVObject@@E@Z
// partial score=0.9 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// Target: 0x00468657..0x00468748 (242 bytes). The receiver is the
// secondary contain interface: its owner Object is at -0x18, its int-key
// string map at +0x1C, and slot 0xB0 returns four status words by value.
// The transport-family placement is a boundary/neighbour lead; neither the
// exact method name nor the status flag's semantic name is established.
// The mapped four-byte value uses the existing verified AsciiString view.

#include <map>
#include "ascii_string.h"

class Drawable
{
public:
	void rva0027656F(int ownerID, AsciiString bone);
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object;

class Rva0055A88BDwordField
{
public:
	int get() const;
};

class Rva002716Holder
{
public:
	void Rva0027167FBroadcast(int id);
	void Rva002716D3Broadcast(int id);
	void rva00271601(unsigned char value);
};

class Rva004650A0
{
public:
	AsciiString &rva004650A0(const int &key);
};

struct ContainStatus468657
{
	unsigned int words[4];
};

class Rva00468657
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n() = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22) CONTAIN_SLOT(23)
	CONTAIN_SLOT(24) CONTAIN_SLOT(25) CONTAIN_SLOT(26) CONTAIN_SLOT(27)
	CONTAIN_SLOT(28) CONTAIN_SLOT(29) CONTAIN_SLOT(30) CONTAIN_SLOT(31)
	CONTAIN_SLOT(32) CONTAIN_SLOT(33) CONTAIN_SLOT(34) CONTAIN_SLOT(35)
	CONTAIN_SLOT(36) CONTAIN_SLOT(37) CONTAIN_SLOT(38) CONTAIN_SLOT(39)
	CONTAIN_SLOT(40) CONTAIN_SLOT(41) CONTAIN_SLOT(42) CONTAIN_SLOT(43)
#undef CONTAIN_SLOT
	virtual ContainStatus468657 status(int mode) = 0;
	void rva00468657(Object *object, unsigned char value);
private:
	char pad04[0x18];
	_STL::map<int, AsciiString> bones;
};

void Rva00468657::rva00468657(Object *object, unsigned char value)
{
	if (!object)
		return;
	Drawable *passenger = reinterpret_cast<Thing *>(object)->getDrawable();
	if (!passenger)
		return;
	Thing *owner = *reinterpret_cast<Thing **>(reinterpret_cast<char *>(this) - 0x18);
	Drawable *drawable = owner->getDrawable();
	if (!drawable)
		return;
	if (!static_cast<bool>((status(0).words[1] >> 29) & 1))
	{
		int id = reinterpret_cast<Rva0055A88BDwordField *>(passenger)->get();
		if (value)
			reinterpret_cast<Rva002716Holder *>(drawable)->Rva002716D3Broadcast(id);
		else
			reinterpret_cast<Rva002716Holder *>(drawable)->Rva0027167FBroadcast(id);
		if (bones.find(static_cast<int>(*reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 0x74))) != bones.end())
			passenger->rva0027656F(
				reinterpret_cast<Rva0055A88BDwordField *>(drawable)->get(),
				reinterpret_cast<Rva004650A0 *>(&bones)->rva004650A0(
					static_cast<int>(*reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 0x74))));
		else
			passenger->rva0027656F(
				reinterpret_cast<Rva0055A88BDwordField *>(drawable)->get(),
				AsciiString("FIREPOINT01"));
	}
	reinterpret_cast<Rva002716Holder *>(passenger)->rva00271601(value);
}
