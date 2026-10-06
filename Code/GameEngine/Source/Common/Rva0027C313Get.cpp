// Retail 0x0027C313, 29 bytes (first of 87B packet; second starts 0x0027C330):
// INT_MAX clamps to 0 else tail-jmps to TerrainLogic slot 0x8c. Called 3x
// from 0x0027C330 which becomes chain-ready.
class TerrainLogic
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
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual int slot35(int v);
};

extern TerrainLogic *TheTerrainLogic;

// ?Rva0027C313Get@@YGHH@Z
int __stdcall Rva0027C313Get(int v)
{
	if (*(volatile int *)&v == 0x7fffffff)
		return 0;
	return TheTerrainLogic->slot35(v);
}
