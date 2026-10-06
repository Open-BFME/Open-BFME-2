// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003955AFCall@@YGXHHMHH@Z RVA 0x003955AF size 43 unlock via global g_00A027B8 slot16 virtual at +0x40 with float plus or-0x100 plus trailing 0 free __stdcall 5 args.
extern class Rva00A027B8 *g_00A027B8;
class Rva00A027B8
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16(int a1, int a2, float f, int a4, int a5, int a6);
};
void __stdcall Rva003955AFCall(int a1, int a2, float f, int a4, int a5)
{
	g_00A027B8->slot16(a1, a2, f, a4 | 0x100, a5, 0);
}
