// cl: /O1 /Ob2 /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// ??0Rva0074104C@@QAE@XZ, retail 0x00740FD9..0x00741044 (107 bytes, EH,
// ret 0). Constructor of the 0x80-byte object the factory 0x0074109B builds
// (class named by its rowed destructor 0x0074104C and deleting destructor
// 0x007410D0; layout from that destructor file, OpaqueScalarDeletingDtorsB19.cpp):
// the primary base (vptr 0x00CF1630, then 0x00CF1648 as the final vptr)
// keeps -1 at +4, the Apt window half (0x002D2C34) sits at +8 under vptr
// 0x00CF1644, and the tail +0x60..+0x7C is cleared (floats at +0x68/+0x6C).
// The tail's types are not known beyond their sizes.
#include "ascii_string.h"

class Rva002D2C34
{
public:
	void rva002D2C34();
};

class Rva0074104CBase
{
public:
	Rva0074104CBase() : unknown04(-1) {}
	virtual ~Rva0074104CBase();
private:
	unsigned int unknown04;
};

class __declspec(novtable) Rva005248D0
{
public:
	__forceinline Rva005248D0() { ((Rva002D2C34 *)this)->rva002D2C34(); }
	virtual ~Rva005248D0();
private:
	unsigned char opaque[0x54];
};

struct Float2
{
	float x, y;
	__forceinline Float2() : x(0.0f), y(0.0f) {}
};

class Rva0074104C : public Rva0074104CBase, public Rva005248D0
{
public:
	Rva0074104C();
	virtual ~Rva0074104C();
private:
	unsigned int unknown60;
	AsciiString str64;
	Float2 pair68;
	unsigned int unknown70;
	bool flag74;
	bool flag75;
	unsigned int unknown78;
	unsigned int unknown7C;
};

Rva0074104C::Rva0074104C()
	: unknown60(0), unknown70(0), flag74(false), flag75(false), unknown78(0), unknown7C(0)
{
}
