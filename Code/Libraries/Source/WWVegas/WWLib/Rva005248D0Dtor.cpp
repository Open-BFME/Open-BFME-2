// cl: /EHsc /MD
//
// ??1Rva005248D0@@UAE@XZ @0x005248D0 111B: dtor destroying six non-polymorphic vector-holder bases.
// Stores vtable 0x00802A80 then destroys +0x4C +0x40 +0x34 +0x1C +0x10 +0x04 in reverse
// with EH states 4 3 2 1 0 -1. Callees all rowed QAE dtors; 37 callers incl deleting dtor.
// Native20B unwind actions null-check this before adjusting to each subobject;
// this is a base-lifetime adjustment rather than a member access. Five-state
// EH graph plus reverse destruction and neighbour52493F's six clears establish
// offsets and extents12/12/24/12/12/12 after the derived vptr. Holder identities
// remain neutral address-derived views; the complete111B body is unchanged.

#include "../../../../GameEngine/Include/Common/Rva0052413E.h"

class Rva005241B0
{
public:
	~Rva005241B0();
private:
	char m_pad[12];
};

class Rva00524436
{
public:
	~Rva00524436();
private:
	char m_pad[24];
};

class Rva00524265
{
public:
	~Rva00524265();
private:
	char m_pad[12];
};

class Rva005242D7
{
public:
	~Rva005242D7();
private:
	char m_pad[12];
};

class Rva00524349
{
public:
	~Rva00524349();
private:
	char m_pad[12];
};

class Rva005248D0 : private Rva0052413E, private Rva005241B0,
	private Rva00524436, private Rva00524265, private Rva005242D7,
	private Rva00524349
{
public:
	virtual ~Rva005248D0();
};

Rva005248D0::~Rva005248D0()
{
}
