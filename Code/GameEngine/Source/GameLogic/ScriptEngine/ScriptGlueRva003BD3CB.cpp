// cl: /O1 /DNDEBUG /MD
//
// ?rva003BD3CB@@YGXPAXMH@Z @0x003BD3CB 58B (dump range 18).
// Frameless stdcall triple: queries TheTerrainLogic slot 0x88 with the
// pointer argument, bails when null or when the 0x00DFEC68 manager is null,
// then tail-calls the pinned SSE 0x002871A4 member on the manager with
// (result + 0x0C, float, int, 0). The float travels in the pushed-ecx slot
// via fstp, the classic MSVC stack-float shape.
class TerrainLogic
{
public:
	virtual void t00();
	virtual void t01();
	virtual void t02();
	virtual void t03();
	virtual void t04();
	virtual void t05();
	virtual void t06();
	virtual void t07();
	virtual void t08();
	virtual void t09();
	virtual void t10();
	virtual void t11();
	virtual void t12();
	virtual void t13();
	virtual void t14();
	virtual void t15();
	virtual void t16();
	virtual void t17();
	virtual void t18();
	virtual void t19();
	virtual void t20();
	virtual void t21();
	virtual void t22();
	virtual void t23();
	virtual void t24();
	virtual void t25();
	virtual void t26();
	virtual void t27();
	virtual void t28();
	virtual void t29();
	virtual void t30();
	virtual void t31();
	virtual void t32();
	virtual void t33();
	virtual void *t34(void *a);
};
extern TerrainLogic *TheTerrainLogic;

class Rva002871A4
{
public:
	void rva002871A4(void *p, float f, int a, int b);
};
extern Rva002871A4 *TheRva002871A4Host;

void __stdcall rva003BD3CB(void *p, float f, int c)
{
	void *r = TheTerrainLogic->t34(p);
	if (r == 0)
		return;
	Rva002871A4 *h = TheRva002871A4Host;
	if (h == 0)
		return;
	h->rva002871A4((char *)r + 0x0C, f, c, 0);
}
