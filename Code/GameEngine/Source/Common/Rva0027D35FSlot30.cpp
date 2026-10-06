// cl: /MD
// ?rva0027D35F@Rva0027D35F@@QAEXPAURva0027D35FArg@@H@Z, retail 0x0027D35F, 25 bytes.
// Thiscall (Arg*,int-dummy-ret8) via global 0x009FF080 to slot30 (0x78)
// with (Arg+0xc, this byte+0). Caller 0x27EA13. Neighbours 0x27D347 (slot29)
// and 0x27D3CB (slot32) use the same global under /O1; /G7 drops the movzx
// to retail mov cl + push ecx. No donor: honest address name.
extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager0027D35F
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
	virtual void _slot30(int a, unsigned char b);
	virtual void _slot31();
	virtual void _slot32(void *water, int a, int b, int c);
};

#define TheRva009FF080Manager0027D35F (*(Rva009FF080Manager0027D35F **)&g_00DFF080)

struct Rva0027D35FArg
{
	char m_pad00[0xc];
	int m_field0C;
};

class Rva0027D35F
{
public:
	void rva0027D35F(Rva0027D35FArg *a, int dummy);
private:
	unsigned char m_00;
};

void Rva0027D35F::rva0027D35F(Rva0027D35FArg *a, int dummy)
{
	TheRva009FF080Manager0027D35F->_slot30(a->m_field0C, m_00);
}
