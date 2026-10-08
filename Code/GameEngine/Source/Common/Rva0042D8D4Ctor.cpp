// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0042D8D4@@QAE@XZ @ 0x0042D8D4 90B: ctor with no args (ret, returns this)
// setting m_0=-1 then m_0=TheRva00222A8BTarget virtual at +0x50 with
// "Apt\\" and "StrategicHUD.apt" plus two zero args. Caller at 0x0023A16C proves shape.
// ??1Rva0042D8D4@@QAE@XZ @ 0x0042D480 19B: when the Apt window manager
// g_bfmeAptWindowManager (the same global as TheRva00222A8BTarget, VA
// 0x00DFE4CC) is set, its pinned ?method@Rva00224B7DTarget@@QAE_NH@Z 0x00224B7D
// is called with the handle m_0, as in Rva005EC09BDtor.cpp. Callers: the
// Rva0023A128 destructor 0x00239D7A (member at +0x14) and its ctor's unwind.
#include "ascii_string.h"
class Rva00222A8BTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual int v20(AsciiString a, AsciiString b, int c, int d);
};
extern Rva00222A8BTarget *TheRva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00224B7DTarget
{
public:
	bool method(int value);
};
class Rva0042D8D4
{
public:
	Rva0042D8D4();
	~Rva0042D8D4();
	int m_0;
};
Rva0042D8D4::Rva0042D8D4()
{
	m_0 = -1;
	m_0 = TheRva00222A8BTarget->v20(AsciiString("Apt\\"), AsciiString("StrategicHUD.apt"), 0, 0);
}
Rva0042D8D4::~Rva0042D8D4()
{
	if (g_bfmeAptWindowManager)
		((Rva00224B7DTarget *)g_bfmeAptWindowManager)->method(m_0);
}
