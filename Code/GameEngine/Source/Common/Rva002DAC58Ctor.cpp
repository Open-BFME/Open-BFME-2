// cl: /O1 /MD /EHsc
// ??0Rva002DAC58@@QAE@XZ @0x002DAC34 36B: ctor via rowed baseConstruct 0x001B4E63 plus lists at +0xC/+0x10 plus global g_00DFF088.
// Evidence: vtable 0x00803D64 store; callees baseConstruct 0x001B4E63; data g_00DFF088 0x009FF088; caller 0x0022E874; neighbour dtor 0x002DAC58.
extern int g_00DFF088;

class __declspec(novtable) BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
	__forceinline BFME2NativeNetwork() { baseConstruct(); }
private:
	virtual void unused() = 0;
	char m_flag;
	int m_value;
};

struct Rva002DAC58Node;

class Rva002DAC58 : public BFME2NativeNetwork
{
public:
	Rva002DAC58();
private:
	Rva002DAC58Node *m_list0C;
	Rva002DAC58Node *m_list10;
};

Rva002DAC58::Rva002DAC58()
	: m_list0C(0)
	, m_list10(0)
{
	g_00DFF088 = 1;
}
