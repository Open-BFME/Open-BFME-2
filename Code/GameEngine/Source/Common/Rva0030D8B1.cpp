// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??0Rva0030D8B1@@QAE@PAXPAVBfmeParserRegistryVE@@PAVAsciiString@@@Z @0x0030D8B1 104B: derived BfmeParserBindingBaseVE ctor for ObjectsList with empty-string fallback; callers at 0x000AF309; vtable 0x00808A24 via gate; base pin 0x000ABB87
#include "ascii_string.h"

class BfmeParserRegistryVE;
class BfmeParserBindingBaseVE
{
public:
	BfmeParserBindingBaseVE(BfmeParserRegistryVE *registry, void *a, void *b);
	virtual ~BfmeParserBindingBaseVE();
	char m_pad[0x8];
};

class Rva0030D8B1 : public BfmeParserBindingBaseVE
{
public:
	Rva0030D8B1(void *a, BfmeParserRegistryVE *registry, AsciiString *label);
private:
	void *m_0C;
};

Rva0030D8B1::Rva0030D8B1(void *a, BfmeParserRegistryVE *registry, AsciiString *label)
	: BfmeParserBindingBaseVE(registry, (void *)&AsciiString("ObjectsList"), (void *)(label ? label : &AsciiString::TheEmptyString))
	, m_0C(a)
{
}
