// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs
//
// Thiscall forwarder: copies the 8-byte payload behind the second argument
// into a 12-byte stack object (vtable 0x00C74DFC, empty inline virtual dtor
// whose shared body is 0x002BEDA4) and forwards (arg, &obj) to the callee
// 0x002BFDE6 with the incoming this unchanged. The callee's identity and the
// class names are address-derived; layout is read from the retail stores.
// Native 5CBB4A consumes the returned pointer and 2C025A forwards it.
// Both wrappers preserve the canonical 2BFDE6 pointer argument and result.
//
// Both payloads derive from Rva002BED74 (target facts): their shared
// destructor 0x002BEDA4 is mov [ecx],0x00BFE4EC / ret, the table of
// Rva002BED74 ([??_G 0x002BED74, __purecall]), whose ctor 0x002BEDB5 and
// deleting dtor 0x002BED74 store it too; the payload tables 0x00C74DFC and
// 0x00BFE4F4 both start with the deleting dtor 0x005CBAEE, which calls
// 0x002BEDA4. With the empty base destructor expanded, each payload's own
// table store dies and only the base's remains; the funclets 0x007A1395 and
// 0x00776AFF call that body. The view matches InlineDtorDeletingDtorsC01.cpp's
// (inline ctor and dtor, one slot), so both units emit the same COMDATs.
class Rva002BED74
{
public:
	Rva002BED74() {}
	virtual ~Rva002BED74() {}
};

class Rva005CBB0AObj : public Rva002BED74
{
public:
	virtual ~Rva005CBB0AObj() {}
	int m_a;
	int m_b;
	Rva005CBB0AObj(const int *src) : m_a(src[0]), m_b(src[1]) {}
};
#include "../../Include/Common/Rva005CBB0A.h"
void *Rva005CBB0A::rva005CBB0A(void *arg, const int *src)
{
	Rva005CBB0AObj obj(src);
	return rva002BFDE6(arg, &obj);
}

// Twin at 0x002C00E0: byte-identical shape with the 12-byte object's vtable
// 0x00BFE4F4 instead; the callee takes the object as an opaque pointer.
class Rva002C00E0Obj : public Rva002BED74
{
public:
	virtual ~Rva002C00E0Obj() {}
	int m_a;
	int m_b;
	Rva002C00E0Obj(const int *src) : m_a(src[0]), m_b(src[1]) {}
};
void *Rva005CBB0A::rva002C00E0(void *arg, const int *src)
{
	Rva002C00E0Obj obj(src);
	return rva002BFDE6(arg, &obj);
}
