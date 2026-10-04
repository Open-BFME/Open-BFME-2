// cl: /O1 /DNDEBUG /MD
// ?rva00265AAB@Rva00265AAB@@QAEXPAUObject00265AAB@@PAH@Z @0x00265AAB 78B via ai-gated turret sleep min
// Evidence: Object+0x258 AI with virtual check at +0x1c4; dead bit +0x438 bit0; flags +0x1c8 &0x14; this+0x20c TurretAI with rowed updateTurretAI 0x004D8DEA; min-store to out arg; callers 0x0026A328 0x0026C5A9; ret 8
typedef int Int;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

class TurretAI
{
public:
	UpdateSleepTime updateTurretAI();
};

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

class AICheck113 : public BfmeVirtualSlots<113>
{
public:
	virtual bool check();
};

struct Object00265AAB
{
	char _pad0[0x1c8];
	unsigned char m_1c8;
	char _pad1[0x258 - 0x1c9];
	AICheck113 *m_258;
	char _pad2[0x438 - 0x25c];
	unsigned char m_438;
};

class Rva00265AAB
{
public:
	void rva00265AAB(Object00265AAB *obj, int *out);
private:
	char _pad0[0x20c];
	TurretAI *m_20c;
};

void Rva00265AAB::rva00265AAB(Object00265AAB *obj, int *out)
{
	AICheck113 *ai = obj->m_258;
	if (ai != 0) {
		if (ai->check())
			return;
	}
	if ((obj->m_438 & 1) != 0)
		return;
	if ((obj->m_1c8 & 0x14) != 0)
		return;
	TurretAI *tur = m_20c;
	if (tur == 0)
		return;
	UpdateSleepTime s = tur->updateTurretAI();
	if (s < *out)
		*out = s;
}
