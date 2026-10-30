// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include /ICode/GameEngine/Source/Common
// Small GameEngine bodies from .text gaps no Ghidra function covers (sixth
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named below, so each keeps an
// address-derived name and a view of only the members it touches. Callees and
// globals use the ledger's existing spellings.

#include "Lib/Coord3D.h"
#include "GameLogicObjectLookupView.h"

class AsciiString;
class Object;

// --- 0x0026FBBC (51B): with the image collection present, cache every
// upgrade template's button image once (+0x14 flag; templates linked from
// +0x0C through +0x64), then the rowed UpgradeCenter 0x0026F93C.
class UpgradeTemplate
{
public:
	void cacheButtonImage();								// 0x0026F216
	char m_pad[0x64];
	UpgradeTemplate *m_next;								// +0x64
};

class ImageCollection;
extern ImageCollection *TheMappedImageCollection;

class UpgradeCenter
{
public:
	void rva0026F93C();										// 0x0026F93C
	virtual void reset();
private:
	char m_pad[0x08];										// after the vftable pointer
	UpgradeTemplate *m_upgradeList;							// +0x0C
	char m_pad10[0x14 - 0x10];
	bool m_buttonImagesCached;								// +0x14
};

void UpgradeCenter::reset()
{
	if (TheMappedImageCollection && !m_buttonImagesCached)
	{
		for (UpgradeTemplate *upgrade = m_upgradeList; upgrade; upgrade = upgrade->m_next)
			upgrade->cacheButtonImage();
		m_buttonImagesCached = true;
	}
	rva0026F93C();
}

// --- 0x0029A436 (25B): the +0x00 object's +0x20 angle = value - pi/2;
// 0x0029A452 (23B): its +0x08 point = the given point.

struct Rva0029A436Data
{
	char m_pad[8];
	Coord3D m_08;
	char m_pad14[0x20 - 0x14];
	float m_20;
};

class Rva0029A436
{
public:
	void setAngle(float angle);
	void setPosition(const Coord3D *pos);
private:
	Rva0029A436Data *m_00;
};

void Rva0029A436::setAngle(float angle)
{
	if (m_00)
		m_00->m_20 = angle - 1.5707963705062866f;
}

void Rva0029A436::setPosition(const Coord3D *pos)
{
	if (m_00)
		m_00->m_08 = *pos;
}

// --- 0x0029F72F (51B): whether the selection can do any action but the
// first (rowed InGameUI::canSelectedObjectsDoAction over types 2..20).
class InGameUI
{
public:
	enum ActionType { ACTIONTYPE_NONE = 0 };
	enum SelectionRules { SELECTION_ANY = 0 };
	bool canSelectedObjectsDoAction(ActionType action, const Object *obj, SelectionRules rule, bool additional) const;	// 0x0029C823
	bool canSelectedObjectsNonAttackInteractWithObject(const Object *obj, SelectionRules rule) const;
};

bool InGameUI::canSelectedObjectsNonAttackInteractWithObject(const Object *obj, SelectionRules rule) const
{
	for (int action = 1; action < 21; ++action)
	{
		if (action == 1)
			continue;
		if (canSelectedObjectsDoAction((ActionType)action, obj, rule, false))
			return true;
	}
	return false;
}

// --- 0x0059F0F7 (17B): vtable 0x00C7122C over two cleared words;
// 0x0059F108 (34B): nothing to check is fine, else TheGameSpyInfo's virtual
// slot 54 decides.
class Rva0059F0F7
{
public:
	Rva0059F0F7();
	virtual ~Rva0059F0F7() {}
private:
	int m_04;
	int m_08;
};

Rva0059F0F7::Rva0059F0F7() : m_04(0), m_08(0)
{
}

class GameSpyInfoInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53();
	virtual bool s54(void *what);
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class Rva0059F108
{
public:
	bool rva0059F108(void *what);
};

bool Rva0059F108::rva0059F108(void *what)
{
	if (!what)
		return true;
	if (!TheGameSpyInfo)
		return false;
	return TheGameSpyInfo->s54(what);
}

// --- 0x002E7F1E (17B) / 0x002E7F2F (15B) / 0x002E7F3E (20B): a 0x800-byte
// buffer with head and tail indices: construct, clear, not empty.
class Rva002E7F1E
{
public:
	Rva002E7F1E();
	void clear();
	bool isNotEmpty() const;
private:
	char m_buffer[0x800];
	int m_head;												// +0x800
	int m_tail;												// +0x804
};

Rva002E7F1E::Rva002E7F1E() : m_head(0), m_tail(0)
{
}

void Rva002E7F1E::clear()
{
	m_tail = 0;
	m_head = 0;
}

bool Rva002E7F1E::isNotEmpty() const
{
	return m_head != m_tail;
}

// --- 0x0039B4B8 (52B): the experience level named by the string (rowed
// lookup 0x0028951F on TheExperienceLevelSystem) goes to the rowed 0x0039B24F
// with 1 and the flag.
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);			// 0x0009FA65
};
extern NameKeyGenerator *TheNameKeyGenerator;

class Overridable;
class Rva0028951F
{
public:
	const Overridable *rva0028951F(int key);				// 0x0028951F
};

class ExperienceLevelSystem;
extern ExperienceLevelSystem *TheExperienceLevelSystem;

struct Rva0039B24FInput;

class Rva0039B24F
{
public:
	void rva0039B24F(Rva0039B24FInput *level, bool count, bool flag);	// 0x0039B24F
	void rva0039B4B8(const AsciiString &name, bool flag);
};

// --- 0x0044F7EA (52B): the first object of the +0x64 id list (rowed
// GameLogic::findObjectByID) whose +0x78 equals the other object's +0x74.
extern GameLogic *TheGameLogic;

struct Rva0044F7EAObject
{
	char m_pad[0x74];
	int m_74;
	int m_78;
};

struct Rva0044F7EANode
{
	Rva0044F7EANode *m_next;
	Rva0044F7EANode *m_prev;
	ObjectID m_id;
};

class Rva0044F7EA
{
public:
	Object *rva0044F7EA(const Rva0044F7EAObject *other);
private:
	char m_pad[0x64];
	Rva0044F7EANode *m_ids;									// +0x64 list header
};

Object *Rva0044F7EA::rva0044F7EA(const Rva0044F7EAObject *other)
{
	Rva0044F7EANode *end = m_ids;
	for (Rva0044F7EANode *it = end->m_next; it != end; it = it->m_next)
	{
		Object *obj = TheGameLogic->findObjectByID(it->m_id);
		if (obj && ((Rva0044F7EAObject *)obj)->m_78 == other->m_74)
			return obj;
	}
	return 0;
}

// --- 0x00575DFE (52B): the +0x04 holder takes the +0x08 value with the
// +0x0C or the +0x10 argument (rowed 0x00575AE1 / 0x00575B7B), else alone
// (rowed 0x00575A3F).
class Rva00575A3F
{
public:
	void rva00575A3F(int a);								// 0x00575A3F
	void rva00575AE1(int a, int b);							// 0x00575AE1
	void rva00575B7B(int a, int b);							// 0x00575B7B
};

class Rva00575DFE
{
public:
	void rva00575DFE();
private:
	int m_00;
	Rva00575A3F *m_holder;
	int m_08;
	int m_0C;
	int m_10;
};

void Rva00575DFE::rva00575DFE()
{
	if (m_0C)
		m_holder->rva00575AE1(m_08, m_0C);
	else if (m_10)
		m_holder->rva00575B7B(m_08, m_10);
	else
		m_holder->rva00575A3F(m_08);
}

// --- 0x00362FC3 (53B): for a positive duration, mark +0x31 and record the
// GameClient frame (virtual slot 31) at +0x40, the end at +0x44 and 1.0 at
// +0x3C.
class GameClient
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30();
	virtual unsigned int getFrame();
};
extern GameClient *TheGameClient;

class Rva00362FC3
{
public:
	void rva00362FC3(unsigned int frames);
private:
	char m_pad[0x31];
	bool m_31;
	char m_pad32[0x3C - 0x32];
	float m_3C;
	unsigned int m_40;
	unsigned int m_44;
};

void Rva00362FC3::rva00362FC3(unsigned int frames)
{
	if (frames > 0)
	{
		m_31 = true;
		unsigned int now = TheGameClient->getFrame();
		m_40 = now;
		m_44 = now + frames;
		m_3C = 1.0f;
	}
}

// --- 0x004CD07C (53B, cdecl): the first module of the object's +0x244 list
// whose +0x0C interface answers virtual slot 39, answered again.
class Rva004CD07CInterface
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38();
	virtual void *s39();
};

struct Rva004CD07CModule
{
	char m_pad[0x0C];
	Rva004CD07CInterface m_interface;						// +0x0C
};

struct Rva004CD07CObject
{
	char m_pad[0x244];
	Rva004CD07CModule **m_modules;							// +0x244
};

void *Rva004CD07C(Rva004CD07CObject *obj)
{
	for (Rva004CD07CModule **m = obj->m_modules; *m; ++m)
		if ((*m)->m_interface.s39())
			return (*m)->m_interface.s39();
	return 0;
}

// --- 0x002D06F0 / 0x002D0702 / 0x002D0714 (18B each): copy constructors
// through the records' rowed assignments.
struct Rva002D0136
{
	Rva002D0136(const Rva002D0136 &that);
	Rva002D0136 &operator=(const Rva002D0136 &that);		// 0x002D0136
};

struct Rva002D01A9
{
	Rva002D01A9(const Rva002D01A9 &that);
	Rva002D01A9 &operator=(const Rva002D01A9 &that);		// 0x002D01A9
};

struct Rva002D021C
{
	Rva002D021C(const Rva002D021C &that);
	Rva002D021C &operator=(const Rva002D021C &that);		// 0x002D021C
};

Rva002D0136::Rva002D0136(const Rva002D0136 &that) { *this = that; }
Rva002D01A9::Rva002D01A9(const Rva002D01A9 &that) { *this = that; }
Rva002D021C::Rva002D021C(const Rva002D021C &that) { *this = that; }
