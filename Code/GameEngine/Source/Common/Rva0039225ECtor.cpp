// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0039225E@@QAE@XZ 100B @0x003921FA: ctor storing vtable 0x00C1A088. Calls rowed BFME2NativeNetwork::baseConstruct via inlined base ctor then rowed list base then inlined Rva0039205C body in retail order then rowed clear. Layout base 0xC plus list<int> at +0xC (size 4) plus Rva0039205C at +0x10 (size 0x18: dword +0 pad +4 ptr +8 bytes +0xC +0xD ints +0x10 +0x14). Evidence: vptr store plus rowed callees plus dtor row at 0x0039225E plus caller at 0x0022ED22 plus Rva0039205C dtor row at 0x0039205C.
#include <list>

class Rva004D9A3C
{
public:
	~Rva004D9A3C();
};

class Rva0039205C
{
public:
	Rva0039205C()
	{
		m_20 = -1;
		m_unk00 = 0;
		m_array08 = 0;
		m_1C = 0;
		m_1D = 0;
		m_pad04 = 0;
		m_24 = 0;
	}
	~Rva0039205C();
private:
	int m_unk00; // +0 -> +0x10
	int m_pad04; // +4 -> +0x14
	Rva004D9A3C *m_array08; // +8 -> +0x18
	unsigned char m_1C; // +0xC -> +0x1C
	unsigned char m_1D; // +0xD -> +0x1D
	int m_20; // +0x10 -> +0x20
	int m_24; // +0x14 -> +0x24
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BFME2NativeNetwork
{
public:
	void baseConstruct();
};

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { ((BFME2NativeNetwork *)this)->baseConstruct(); }
	virtual ~BFME2NativeNetworkBase() { _ReadWriteBarrier(); }
private:
	char m_flag04;
	char m_pad05[3];
	int m_value08;
};

class Rva0039225E : public BFME2NativeNetworkBase
{
public:
	Rva0039225E();
	virtual ~Rva0039225E();
private:
	_STL::list<int, _STL::allocator<int> > m_list0C;
	Rva0039205C m_obj10;
};

Rva0039225E::Rva0039225E()
{
	m_list0C.clear();
}
