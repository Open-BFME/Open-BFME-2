// cl: /O1 /MD /arch:SSE
//
// ?Rva0027D815@Rva0062AF7@@UAEMMM@Z retail 0x0027D815 70 bytes.
// Vslot 25 (offset 0x64) of vtable 0x007C5890 primary of ??1Rva0062AF7@@UAE@XZ
// whose slot 2 returns W3DTerrainLogic and slot 15 is isClearLineOfSight.
// Shared with base TerrainLogic vtable 0x007FB2C8 at same address. Calls slot
// 19 (offset 0x4C unclaimed 0x0027D77D 5-arg bool) with x y and two float outs
// plus 0 and returns a minus b on true else pooled 0.0f at retail 0x007BAEAC.
// Identity is class plus slot and method name is honest address name.
// Secondary MI vptrs plus 0x04 plus 0x10 plus 0x14 omitted as body touches
// primary only. Flags per section 4.1: /O1 for EBP frame plus /arch:SSE for
// xorps and movss float zeroing.
class Rva0062AF7
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
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual bool Rva0027D77D(float x, float y, float *a, float *b, bool *c);
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual float Rva0027D815(float x, float y);
};
float Rva0062AF7::Rva0027D815(float x, float y)
{
	float a = 0.0f;
	float b = 0.0f;
	if (!Rva0027D77D(x, y, &a, &b, 0))
		return 0.0f;
	return a - b;
}
