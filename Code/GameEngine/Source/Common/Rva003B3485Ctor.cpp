// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// ??0Rva003B3485@@QAE@PAX0PAVBfmeParserRegistryVE@@PBVAsciiString@@@Z @0x003B3485 110B
// Evidence: unlock lane, ScriptGroup literal, base pin 0x000ABB87, prev Bfme5TinyTwentySix next Rva003B3536Load
// callees StringBase ctor row plus BfmeParserBindingBaseVE pin plus releaseBuffer row, TheEmptyString,
// two owner fields at +0xc/+0x10. Identity: honest-address thiscall ctor with 4 stack args ret 16.
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

class Rva003B3485 : public BfmeParserBindingBaseVE
{
public:
	Rva003B3485(void *a, void *b, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
private:
	void *m_a;
	void *m_b;
};

Rva003B3485::Rva003B3485(void *a, void *b, BfmeParserRegistryVE *registry, const AsciiString *parentLabel)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("ScriptGroup"), (void *)(parentLabel ? parentLabel : &AsciiString::TheEmptyString)),
	m_a(a), m_b(b)
{
}
