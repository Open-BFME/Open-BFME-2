// cl: /DNDEBUG /MD
//
// ?rva004AE988@Rva004AE988@@QAEXXZ, retail 0x004AE988 114B. Chain via 0x001E431E.
// Random pick from 0x54 stride array at this+4 base+8 end+0xC via
// GetGameLogicRandomValue 0 count-1 file 0x114 then bool ne0 at +0x21 then
// rva001E431E plus setDisabled 4 plus setWakeFrame with +0x4C sleep plus +0x20.
// Caller 0x004C1E6D.

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class Object;
enum DisabledType
{
	Disabled_04 = 4
};

enum UpdateSleepTime
{
	Sleep_00 = 0
};

class Object
{
public:
	void setDisabled(DisabledType t);
};

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime t);
};

class Rva001E431E
{
public:
	void rva001E431E(const int *x);
};

struct Elem54
{
	unsigned char m_pad[0x4c];
	UpdateSleepTime m_sleep;
	unsigned char m_pad2[0x54 - 0x4c - 4];
};

struct ArrayHolder
{
	unsigned char m_pad[8];
	Elem54 *m_base;
	Elem54 *m_end;
};

class Rva004AE988 : public UpdateModule
{
public:
	void rva004AE988();
private:
	unsigned char m_pad00[4];
	ArrayHolder *m_04;
	Object *m_08;
	unsigned char m_pad0C[0x20 - 0x0C];
	unsigned char m_20;
	unsigned char m_21;
};

void Rva004AE988::rva004AE988()
{
	ArrayHolder *h = m_04;
	int count = (int)(((char *)h->m_end - (char *)h->m_base) / 0x54);
	Object *obj = m_08;
	if (count < 1)
		return;
	int r = GetGameLogicRandomValue(0, count - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\DetachableRiderUpdate.cpp", 0x114);
	unsigned char b = (r != 0);
	m_21 = b;
	Elem54 *e = (Elem54 *)((char *)h->m_base + (unsigned int)b * 0x54);
	((Rva001E431E *)obj)->rva001E431E((const int *)e);
	obj->setDisabled(Disabled_04);
	m_20 = 1;
	UpdateSleepTime st = *(UpdateSleepTime *)((char *)h->m_base + (unsigned int)m_21 * 0x54 + 0x4c);
	setWakeFrame(obj, st);
}
