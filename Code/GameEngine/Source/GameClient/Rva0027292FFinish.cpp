// cl: /DNDEBUG /MD /EHsc
//
// ?setTerrainDecalSize@Drawable@@QAEXMM@Z, retail 0x0027292F, 22 bytes.
// First-module forwarder over draw modules at this+0x14C to the module's
// virtual slot 0x64. Evidence: BFME1 donor Drawable::setTerrainDecalSize in
// reference/open-bfme-1/Code/GameEngine/Source/GameClient/Drawable.cpp
// (DrawModule** dm = getDrawModules(); if (*dm) (*dm)->setTerrainDecalSize);
// retail +0x14C matches the landed pristine twin 0x00272945; 2-float ret-8
// shape.
//
// The module slot is declared (int, int) on purpose: /O1 refuses to
// tail-call a float-argument virtual and emits an x87 copy instead. The
// ABI for two 4-byte stack arguments is identical, so forwarding the same
// two 32-bit values with an integer-typed declaration reproduces retail's
// tail jmp [edx+0x64] exactly; the values forwarded are the float bits.
class BfmeDrawModuleForDecalSize
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0; virtual void slot4C() = 0;
	virtual void slot50() = 0; virtual void slot54() = 0;
	virtual void slot58() = 0; virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void setTerrainDecalSize(int x, int y) = 0;
};

class Drawable
{
public:
	void setTerrainDecalSize(float x, float y);
private:
	char m_pad[0x14C];
	BfmeDrawModuleForDecalSize **m_drawModules;
};

// ?setTerrainDecalSize@Drawable@@QAEXMM@Z
void Drawable::setTerrainDecalSize(float x, float y)
{
	BfmeDrawModuleForDecalSize **p = m_drawModules;
	if (*p)
		(*p)->setTerrainDecalSize(*(int *)&x, *(int *)&y);
}
