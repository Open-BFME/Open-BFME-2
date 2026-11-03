// cl: /DNDEBUG /MD
//
// Apt object next to the 0x00711350 deleting destructor: a non-polymorphic bits
// member at +0x1C and one argument at +0x20 over the Rva006D6360 Apt base, then
// an XML-attributes writer. The base recipe is the rowed Rva006D6500
// construction in Code/Libraries/Source/Apt/Rva006D6360Ctor.cpp; the writer's
// callees are all pinned (isXmlAttributes 0x006DBEC0, rva006DD2A0 0x006DD2A0,
// isString 0x006DC0D0, checkedString 0x006DCE50, EAStringC 0x00620090).
// The enclosing class and writer identities remain address-derived.

// The used vtable prefix is AptValue::AddRef followed by Release.
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
	unsigned int m_flags;
};

#include "../../../Libraries/Source/Apt/AptNativeHash.h"

class Rva006D6360 : public AptValue
{
	AptNativeHash m_hash;

public:
	Rva006D6360(int type, int size);
};

class Rva00711380 : public Rva006D6360
{
	unsigned int m_bits;		// +0x1C
	int m_arg;			// +0x20

public:
	Rva00711380(int type, int arg);
};

Rva00711380::Rva00711380(int type, int arg) : Rva006D6360(type, 8)
{
	*(unsigned char *)&m_bits = 0;
	m_bits &= 0xFFFFFCFF;
	m_arg = arg;
}

class Rva007113B0Container
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4(const char *key, const char *value);
};

// The writer reaches the pinned AptValue predicates, so this class keeps the
// pinned name and the +0x20 member the body touches.
class BfmeAptValue006DCD20
{
public:
	virtual void vtableSlot0();
	int isXmlAttributes() const;
	int isString() const;
	BfmeAptValue006DCD20 *rva006DD2A0();
	// 0x006DCE50, rowed in Apt/AptValue/Rva006DCE50Finish.cpp: the value's
	// string payload.
	BfmeAptValue006DCD20 *checkedString();

private:
	char m_pad[0x1C];		// +0x04..+0x1F

public:
	Rva007113B0Container *m_20;	// +0x20
};

#include "../../../Libraries/Source/Apt/EAStringC.h"

// ?Rva007113B0@@YG_NPAVBfmeAptValue006DCD20@@PBVEAStringC@@0@Z @ 0x007113B0 (91B)
bool __stdcall Rva007113B0(BfmeAptValue006DCD20 *target, const EAStringC *key, BfmeAptValue006DCD20 *value)
{
	if (static_cast<unsigned char>(target->isXmlAttributes())) {
		BfmeAptValue006DCD20 *attributes = target->rva006DD2A0();

		if (static_cast<unsigned char>(value->isString())) {
			char *valueBuffer = reinterpret_cast<char *>(
				value->checkedString());

			attributes->m_20->slot4(
				key->rva00620090(),
				reinterpret_cast<EAStringC *>(valueBuffer + 8)->rva00620090());
		}
	}
	return true;
}
