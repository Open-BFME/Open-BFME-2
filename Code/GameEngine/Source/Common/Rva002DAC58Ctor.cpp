// cl: /O1 /MD /EHsc
// ??0Rva002DAC58@@QAE@XZ @0x002DAC34 36B: ctor via rowed baseConstruct 0x001B4E63 plus lists at +0xC/+0x10 plus global g_00DFF088.
// Evidence: vtable 0x00803D64 store; callees baseConstruct 0x001B4E63; data g_00DFF088 0x009FF088; caller 0x0022E874; neighbour dtor 0x002DAC58.
extern int g_00DFF088;

extern "C" const void *const vtbl_00C03D64[];  // ??_7Rva002DAC58@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C03D64=??_7Rva002DAC58@@6B@")

class BFME2NativeNetwork
{
public:
	BFME2NativeNetwork *baseConstruct();
};

struct Rva002DAC58Node;

class Rva002DAC58
{
	int m_pad00[3];
	Rva002DAC58Node *m_list0C;
	Rva002DAC58Node *m_list10;
public:
	Rva002DAC58();
};

Rva002DAC58::Rva002DAC58()
{
	((BFME2NativeNetwork *)this)->baseConstruct();
	m_list0C = 0;
	m_list10 = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00C03D64);
	g_00DFF088 = 1;
}
