// cl: /O1 /Ob2 /EHsc /MD
// ??1Rva005E129B@@UAE@XZ @0x005E129B 54B chain via 0x005E1246 landing.
// Evidence: retail EH_prolog scope 0x007A31FD store g_00C77998 at [this] state 0 lea ecx [esi+8] call rowed ?rva005E1246@Rva005E1246@@QAEXXZ @0x005E1246 then store base g_00BC6F20; derived caller 0x005E12D1 calls as base; same 54B shape as rowed ??1Rva00221C15@@QAE@XZ @0x00221C78.
class Rva005E1246
{
public:
	void rva005E1246();
};

class Rva005E129BBase
{
public:
	virtual ~Rva005E129BBase() {}
protected:
	int m_04;
};

class Rva005E129B : public Rva005E129BBase
{
public:
	virtual ~Rva005E129B();
private:
	Rva005E1246 m_08;
};

Rva005E129B::~Rva005E129B()
{
	m_08.rva005E1246();
}
