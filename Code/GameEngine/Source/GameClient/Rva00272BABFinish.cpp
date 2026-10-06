// cl: /DNDEBUG /MD /EHsc
//
// ?rva00272BAB@Drawable@@QAEXHH@Z, retail 0x00272BAB, 60 bytes.
// Dual walk: first draw module at +0x14C forwards two int args to slot
// 0x6C when present, then null-terminated +0x154 array walks slot 0x44.
// Evidence: dual-walk precedent Drawable_rva00272BE7 (+0x14C/+0x154);
// same frameless ret-8 two-arg shape as Drawable_rva0027248A in this
// family; unblocks 0x0046C20B 0x00265173 0x0046FA46 0x002754E3.

class DrawModuleForRva272BAB
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
	virtual void slot60() = 0; virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual void rva00272BABTarget(int a, int b) = 0;
};

class ClientItemForRva272BAB
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
	virtual void slot40() = 0;
	virtual void rva00272BABClient() = 0;
};

class Drawable
{
public:
	void rva00272BAB(int a, int b);
private:
	unsigned char m_pad[0x14C];
	DrawModuleForRva272BAB **m_drawModules;
	unsigned char m_pad150[0x154 - 0x150];
	ClientItemForRva272BAB **m_client;
};

void Drawable::rva00272BAB(int a, int b)
{
	DrawModuleForRva272BAB **mods = m_drawModules;
	if (*mods != 0)
		(*mods)->rva00272BABTarget(a, b);
	for (ClientItemForRva272BAB **p = m_client; p != 0 && *p != 0; ++p)
		(*p)->rva00272BABClient();
}
