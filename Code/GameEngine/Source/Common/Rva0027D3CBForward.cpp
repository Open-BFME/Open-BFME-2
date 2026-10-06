// cl: /MD
// ?Rva0027D3CBForward@@YGXPAXHHH@Z, retail 0x0027D3CB, 14 bytes.
// Free __stdcall forwarder via global 0x009FF080 to slot32 (0x80)
// Rva0027D88E (void*,float,float,float) as ints to avoid x87 shuffling
// and keep the tail jmp. Same manager as Rva00306769Forward.
// Caller 0x545140.
extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager0027D3CB
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26();
	virtual void _slot27();
	virtual void _slot28();
	virtual void _slot29(int a, int b);
	virtual void _slot30();
	virtual void _slot31();
	virtual void _slot32(void *water, int a, int b, int c);
};

#define TheRva009FF080Manager0027D3CB (*(Rva009FF080Manager0027D3CB **)&g_00DFF080)

void __stdcall Rva0027D3CBForward(void *water, int a, int b, int c)
{
	TheRva009FF080Manager0027D3CB->_slot32(water, a, b, c);
}

//
// ?rva0027D347@Rva0027D347@@QAEXPAURva0027D347Arg@@H@Z retail 0x0027D347 24 bytes.
// Thiscall with (Arg*,int-dummy-ret8) via same global to slot29 (0x74)
// with (Arg+0xc, this+0). Caller 0x27E768. Same TU/flags as thunk above.
struct Rva0027D347Arg
{
	char m_pad00[0xc];
	int m_field0C;
};

class Rva0027D347
{
public:
	void rva0027D347(Rva0027D347Arg *a, int dummy);
private:
	int m_00;
};

void Rva0027D347::rva0027D347(Rva0027D347Arg *a, int dummy)
{
	TheRva009FF080Manager0027D3CB->_slot29(a->m_field0C, m_00);
}
