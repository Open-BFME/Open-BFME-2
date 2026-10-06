// cl: /Ob2 /EHsc /MD
// ??1Rva005F4179@@UAE@XZ @ 0x005F4179 54B
// Evidence: retail EH_prolog scope 0x007A51B4 store 0x00C79448 at [this] state 0 lea ecx [esi+8] call rowed ?clear@Rva005F4096@@QAEXXZ @0x005F4096 then store base 0x00BC6F20; same 54B shape as rowed ??1Rva005E129B@@UAE@XZ @0x005E129B; vtable slot 0x00C79448#0; caller 0x005F41BA deleting dtor.
class Rva005F4096
{
public:
	void clear();
};

class Rva005F4179Base
{
public:
	virtual ~Rva005F4179Base() {}
protected:
	int m_04;
};

class Rva005F4179 : public Rva005F4179Base
{
public:
	virtual ~Rva005F4179();
private:
	Rva005F4096 m_08;
};

Rva005F4179::~Rva005F4179()
{
	m_08.clear();
}
