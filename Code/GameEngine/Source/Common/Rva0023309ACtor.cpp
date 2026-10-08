// cl: /MD
//
// ??0Rva0023309A@@QAE@XZ @0x0023309A 158B
// retail 0x0023309A (158 bytes). Derived BFME2NativeNetwork ctor: inline base
// ctor calls rowed baseConstruct 0x001B4E63, derived vptr 0x007E82B8, then
// zeroes +0xC..+0x20, tail +0x3028..+0x3060 (+0x3030=1), and clears two
// 0x801-word buffers at +0x22 and +0x1024 in one loop.
// Evidence: callee rowed baseConstruct; caller 0x002331DF; vtable ">:c".
class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase();
private:
	char m_flag;
	int m_value;
};

class Rva0023309A : public BFME2NativeNetworkBase
{
public:
	Rva0023309A();
	virtual ~Rva0023309A();
private:
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned short m_a[0x801];
	unsigned short m_b[0x801];
	char m_gap[0x1002];
	int m_3028;
	int m_302C;
	int m_3030;
	int m_3034;
	int m_3038;
	int m_303C;
	int m_3040;
	int m_3044;
	unsigned char m_3048;
	int m_304C;
	int m_3050;
	int m_3054;
	int m_3058;
	int m_305C;
	int m_3060;
};

Rva0023309A::Rva0023309A()
{
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	m_3028 = 0;
	m_302C = 0;
	m_3030 = 1;
	m_3034 = 0;
	m_3038 = 0;
	m_303C = 0;
	m_3040 = 0;
	m_3044 = 0;
	m_3048 = 0;
	m_304C = 0;
	m_3050 = 0;
	m_3054 = 0;
	m_3058 = 0;
	m_305C = 0;
	m_3060 = 0;
	for (int i = 0; i < 0x801; ++i)
	{
		m_a[i] = 0;
		m_b[i] = 0;
	}
}

// ?CreateIMEManagerInterface@@YAPAVIMEManager@@XZ present-unmatched
// 0x002331BB 53B, retracted from its address-named row for this rename.
// The retail body allocates 0x3064 bytes then invokes the ctor immediately;
// that size matches this object's modeled extent. Its sole caller,
// GameClient::init 0x0023A1BB, calls it with no this pointer where ZH calls
// CreateIMEManagerInterface, and stores the result in TheIMEManager.
class IMEManager;

IMEManager *CreateIMEManagerInterface()
{
	return (IMEManager *)new Rva0023309A;
}
