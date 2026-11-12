// cl: /MD /EHsc
// ??0Rva005CF8A1@@QAE@PAX@Z @0x005CF8A1 58B
// Ctor stores vtable 0x00875298 at +0, arg at +4, constructs Rva0057416B member at +8.
// Evidence: unlock lane; same 58B shape as Rva005E9FC1 precedent with empty base plus declared-only dtor arming EH state 0; callee rowed 0x0057416B; caller 0x005D0C45 passes through its arg; ret 4.
#include "../../Include/Common/Rva0057416B.h"

struct Rva005CF8A1Base
{
	Rva005CF8A1Base(void *p) : m_04(p) {}
	~Rva005CF8A1Base();
	void *m_04;
};

class Rva005CF8A1 : public Rva005CF8A1Base
{
public:
	Rva005CF8A1(void *p);
	virtual ~Rva005CF8A1() {}
private:
	Rva0057416B m_08;
};

Rva005CF8A1::Rva005CF8A1(void *p)
	: Rva005CF8A1Base(p)
{
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??1Rva005CF8A1Base@@QAE@XZ=??1?$list@URva0073EEE0ListValue@@V?$allocator@URva0073EEE0ListValue@@@_STL@@@_STL@@QAE@XZ")
