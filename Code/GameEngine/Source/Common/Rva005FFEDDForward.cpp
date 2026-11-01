// cl: /O1 /arch:SSE /G7 /MD /EHsc
//
// ?rva005FFEDD@Rva005FFEDD@@QAEXABUTreeHintRef00217D4C@@@Z @0x005FFEDD 8B
// Forwarder: this+4 holds Rva005FFC8B object; tail-jmps to its CreateGarrisonPanel.
// Evidence: prev 0x005FFED5 and next 0x005FFEE5 same +4 forwarder precedent;
// callee rowed 0x005FFC8B; callers 0x005FB0DB 0x005FB3A6 0x005FB57B;
// unblocks 0x005FAFE8 0x005FB30A 0x005FB4DF.
#include "../../../Libraries/Source/Apt/AptRefTarget.h"

class Rva005FFC8B
{
public:
	void CreateGarrisonPanel(const TreeHintRef00217D4C &ref);
};

class Rva005FFEDD
{
public:
	void rva005FFEDD(const TreeHintRef00217D4C &ref);
private:
	char m_pad0[4];
	Rva005FFC8B *m_obj;
};

void Rva005FFEDD::rva005FFEDD(const TreeHintRef00217D4C &ref)
{
	m_obj->CreateGarrisonPanel(ref);
}
