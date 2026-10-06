// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /DNDEBUG /MD
//
// ??0Rva0044B27F@@QAE@ABV0@@Z @0x0044B27F 107B: copy constructor of a
// 0x1D0-byte save element (callers 0x0044B6E9 0x00582402 0x0058265D
// 0x00582D16). It copies the rowed polymorphic save-element base
// BfmeSaveElement002295D7 (0x002295D7 0x1AC bytes), installs vtable
// 0x00C3E4FC, copies the LANPlayer member at +0x1AC (rowed copy 0x0044A901),
// the AsciiString at +0x1C8 and the plain field at +0x1CC. Identities are
// address-derived; field meanings are not recovered.

#include "ascii_string.h"

struct BfmeSaveElement002295D7
{
	BfmeSaveElement002295D7(const BfmeSaveElement002295D7 &other);
	virtual ~BfmeSaveElement002295D7();

	char m_pad[0x1A8];
};

class LANPlayer
{
public:
	LANPlayer(const LANPlayer &other);
	~LANPlayer();

private:
	char m_pad[0x1C];
};

class Rva0044B27F : public BfmeSaveElement002295D7
{
public:
	Rva0044B27F(const Rva0044B27F &other);
	virtual ~Rva0044B27F();

private:
	LANPlayer m_1AC;
	AsciiString m_1C8;
	int m_1CC;
};

Rva0044B27F::Rva0044B27F(const Rva0044B27F &other) :
	BfmeSaveElement002295D7(other),
	m_1AC(other.m_1AC),
	m_1C8(other.m_1C8),
	m_1CC(other.m_1CC)
{
}
