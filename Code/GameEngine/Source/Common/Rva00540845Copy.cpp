// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ??0Rva00540845@@QAE@ABV0@@Z @0x00540845 67B: copy constructor (sibling of
// the rowed Rva00541F1F copy 0x00541F1F). It copies the rowed polymorphic
// base Rva0053FADE (0x0053FADE), installs vtable 0x00C694F8, then copies the
// member-plus-vector holder at +0x24 (rowed Rva00540517 copy 0x00540517).
// Identities are address-derived.

#include "ascii_string.h"

#include "../../Include/Common/Rva00330757Member.h"

class Rva0053FADE : public Rva00330757Member
{
public:
	Rva0053FADE(const Rva0053FADE &other);
	// the rowed destructor 0x0053FB33 (Rva0053FB33Dtor.cpp); declared so this
	// unit does not emit an implicit copy
	virtual ~Rva0053FADE();

private:
	int m_14;
	AsciiString m_18;
	int m_1C;
	int m_20;
};

class Rva00540517
{
public:
	Rva00540517(const Rva00540517 &that);
	~Rva00540517();

private:
	char m_pad[0x20];
};

class Rva00540845 : public Rva0053FADE
{
public:
	Rva00540845(const Rva00540845 &other);
	virtual ~Rva00540845();

private:
	Rva00540517 m_24;
};

Rva00540845::Rva00540845(const Rva00540845 &other) :
	Rva0053FADE(other),
	m_24(other.m_24)
{
}
