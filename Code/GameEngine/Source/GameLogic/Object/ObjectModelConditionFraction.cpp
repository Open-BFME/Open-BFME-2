// platformsdk
// ?rva002949AE@Object@@QAEXHHM@Z
// Object::rva002949AE (0x002949AE, 303 B): apply a model condition to a random
// fraction of the contained objects, or to this object when it has no contain.
// The BitFlags-style helper with unsigned bit index keeps retail's in-place test
// and the late lea for the set path.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
#include <windows.h>

class Object;

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

class ObjectSMCHelper
{
public:
	void setModelConditionState(ModelConditionFlagType flag, unsigned int value);
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

struct Rva00291793Node
{
public:
	Rva00291793Node *m_next; // +0x00
	Rva00291793Node *m_prev; // +0x04
	Object *m_object; // +0x08
};

struct Rva00291793List
{
	Rva00291793Node *m_head;
};

class Rva00291793
{
public:
	int rva00291793();
	Rva00291793Node *head() const { return m_p04->m_head; }
	char m_pad00[0x4];
private:
	Rva00291793List *m_p04; // +0x04
};

class Rva002949AEContain
{
public:
#define BFME_SLOT(n) virtual void slot##n();
	BFME_SLOT(00) BFME_SLOT(01) BFME_SLOT(02) BFME_SLOT(03) BFME_SLOT(04) BFME_SLOT(05)
	BFME_SLOT(06) BFME_SLOT(07) BFME_SLOT(08) BFME_SLOT(09) BFME_SLOT(10) BFME_SLOT(11)
	BFME_SLOT(12) BFME_SLOT(13) BFME_SLOT(14) BFME_SLOT(15) BFME_SLOT(16) BFME_SLOT(17)
	BFME_SLOT(18) BFME_SLOT(19) BFME_SLOT(20) BFME_SLOT(21) BFME_SLOT(22) BFME_SLOT(23)
	BFME_SLOT(24) BFME_SLOT(25) BFME_SLOT(26) BFME_SLOT(27) BFME_SLOT(28) BFME_SLOT(29)
	BFME_SLOT(30) BFME_SLOT(31) BFME_SLOT(32) BFME_SLOT(33) BFME_SLOT(34) BFME_SLOT(35)
	BFME_SLOT(36) BFME_SLOT(37) BFME_SLOT(38) BFME_SLOT(39) BFME_SLOT(40) BFME_SLOT(41)
	BFME_SLOT(42) BFME_SLOT(43) BFME_SLOT(44) BFME_SLOT(45) BFME_SLOT(46) BFME_SLOT(47)
	BFME_SLOT(48) BFME_SLOT(49) BFME_SLOT(50) BFME_SLOT(51) BFME_SLOT(52) BFME_SLOT(53)
	BFME_SLOT(54) BFME_SLOT(55) BFME_SLOT(56) BFME_SLOT(57) BFME_SLOT(58) BFME_SLOT(59)
	BFME_SLOT(60) BFME_SLOT(61) BFME_SLOT(62) BFME_SLOT(63) BFME_SLOT(64) BFME_SLOT(65)
#undef BFME_SLOT
	virtual Rva00291793 slot66();	// +0x108
};

struct Rva002949AEFlags
{
	unsigned int m_bits[(0x230 - 0x10C) / 4];
	__forceinline bool test(unsigned int bit) const { return (m_bits[bit / 32] & (1u << (bit % 32))) != 0; }
	__forceinline void set(unsigned int bit) { m_bits[bit / 32] |= (1u << (bit % 32)); }
};

class Object
{
public:
	void *rva0029439D();
	void rva0028AE6D();
	void rva002949AE(int status, int value, float fraction);

	__forceinline void applyRva002949AE(int status, int value)
	{
		if (value)
			m_smcHelper->setModelConditionState((ModelConditionFlagType)status, value);
		else if (!m_flags.test(status))
		{
			m_flags.set(status);
			rva0028AE6D();
		}
	}

private:
	char m_pad000[0x10C];
	Rva002949AEFlags m_flags;	// +0x10C
	ObjectSMCHelper *m_smcHelper;	// +0x230
};

void Object::rva002949AE(int status, int value, float fraction)
{
	Rva002949AEContain *contain = (Rva002949AEContain *)rva0029439D();
	if (contain)
	{
		Rva00291793 items = contain->slot66();
		int remaining = contain->slot66().rva00291793();
		int wanted = (int)(remaining * fraction + 0.5f);
		wanted = max(1, min(wanted, remaining));
		for (Rva00291793Node *node = items.head()->m_next; node != items.head(); node = node->m_next)
		{
			if (GetGameLogicRandomValue(1, remaining--, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Object.cpp", 3093) <= wanted)
			{
				--wanted;
				node->m_object->applyRva002949AE(status, value);
			}
		}
	}
	else
	{
		applyRva002949AE(status, value);
	}
}
