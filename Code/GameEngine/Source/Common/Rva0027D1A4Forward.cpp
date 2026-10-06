// cl: /MD
// ?Rva0027D1A4Forward@@YGXPAXMH@Z, retail 0x0027D1A4, 34 bytes.
// Free __stdcall null-guarded forwarder via global 0x009FF080 to slot16 (0x40)
// with (void*, float, int). Callers 0x4C3B6C/0x4C4A03. Same manager family as
// Rva0027D3CBForward/Rva00306769Forward. No donor: honest address name.
extern class G00DFF080Obj *g_00DFF080;

class Rva009FF080Manager0027D1A4
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
	virtual void _slot16(void *a, float b, int c);
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
	virtual void _slot29();
	virtual void _slot30();
	virtual void _slot31();
	virtual void _slot32();
};

#define TheRva009FF080Manager0027D1A4 (*(Rva009FF080Manager0027D1A4 **)&g_00DFF080)

void __stdcall Rva0027D1A4Forward(void *a, float b, int c)
{
	Rva009FF080Manager0027D1A4 *manager = TheRva009FF080Manager0027D1A4;
	if (manager == 0)
		return;
	manager->_slot16(a, b, c);
}
