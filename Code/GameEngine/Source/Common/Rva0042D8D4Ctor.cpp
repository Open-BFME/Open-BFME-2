// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??0Rva0042D8D4@@QAE@XZ @ 0x0042D8D4 90B: ctor with no args (ret, returns this)
// setting m_0=-1 then m_0=TheRva00222A8BTarget virtual at +0x50 with
// "Apt\\" and "StrategicHUD.apt" plus two zero args. Caller at 0x0023A16C proves shape.
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
class Rva0042D8D4
{
public:
	Rva0042D8D4();
	int m_0;
};
Rva0042D8D4::Rva0042D8D4()
{
	m_0 = -1;
	m_0 = TheRva00222A8BTarget->v20(AsciiString("Apt\\"), AsciiString("StrategicHUD.apt"), 0, 0);
}
