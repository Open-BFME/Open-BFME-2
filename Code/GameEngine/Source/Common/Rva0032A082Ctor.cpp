// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva0032A082@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x0032A082 48B
// Evidence: chain lane calls rowed 0x003B3417, vtable 0x0080D8FC shared with dtor 0x0032989F, stores +0x14 zeroes +0x68
#include "ascii_string.h"

class BfmeParserRegistryVE
{
public:
	void *bfmeRegister(void *a, void *b, void *c, void *d);
};

class BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *label, void *parentLabel);
	virtual ~BfmeParserBindingBaseVE();
	virtual void bfmeSlot0();
	virtual void bfmeSlot1();
private:
	BfmeParserRegistryVE *m_registry;
	void *m_token;
};

class Rva003B3417 : public BfmeParserBindingBaseVE
{
public:
	Rva003B3417(void *a, void *b, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_a;
	void *m_b;
};

class Rva0032A082 : public Rva003B3417
{
public:
	Rva0032A082(void *unk, BfmeParserRegistryVE *registry, const AsciiString *label);
private:
	void *m_unk14; // +0x14
	void *m_items[20]; // +0x18 (0x50 bytes to +0x68)
	int m_count; // +0x68
};

Rva0032A082::Rva0032A082(void *unk, BfmeParserRegistryVE *registry, const AsciiString *label)
	: Rva003B3417(m_items, &m_count, registry, label),
	m_unk14(unk),
	m_count(0)
{
}
