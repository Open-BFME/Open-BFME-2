// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva005F8FEE@@UAE@XZ @0x005F8FEE 101B: virtual dtor with derived vtable 0x00879D20 then base 0x007C6F20. Evidence: EH_prolog scopetable 0x007A5AC0; callees rowed ReleaseTreeHintRef 0x0007DEEF twice plus Rva0052413E dtor 0x0052413E plus releaseBuffer 0x00036410 via AsciiString; callers 0x005F9431 thunk 0x005FA141; siblings Rva005F8FCC Rva005F918D.
#include "ascii_string.h"
struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
class Rva0052413E
{
public:
	~Rva0052413E();
};
struct Rva005F8FEEHolder
{
	TargetRef00217D4C *m_ptr;
	~Rva005F8FEEHolder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};
class Rva005F8FEEBase
{
public:
	virtual ~Rva005F8FEEBase() {}
};
class Rva005F8FEE : public Rva005F8FEEBase
{
public:
	virtual ~Rva005F8FEE();
private:
	int m_04;
	int m_08;
	AsciiString m_str0C;
	int m_10;
	int m_14;
	Rva005F8FEEHolder m_holder18;
	Rva0052413E m_vec1C;
	int m_28[3];
	Rva005F8FEEHolder m_holder2C;
};
Rva005F8FEE::~Rva005F8FEE()
{
}
