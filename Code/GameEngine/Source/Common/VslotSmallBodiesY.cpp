// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch Y. As in VslotSmallBodiesA-X, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;

class Object;
class Player;
class CommandButton;
struct Coord3D;
enum ObjectID
{
	INVALID_ID = 0
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	char m_pad00[0x40];
	UnsignedInt m_40;
	char m_pad44[0xCC];
	Int m_110;
};
extern GameLogic *TheGameLogic;

struct Rva005D7AECInfo
{
	char m_pad00[0x113];
	unsigned char m_113;
};
class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00297000(const CommandButton *button, Object *target, Int a, Int b);
	Int m_00;
	Rva005D7AECInfo *m_04;
	char m_pad08[0x30];
	Int m_38;
};

// 0x0053EC7D and 0x0053ECD1: window i of the +0x3C array: moved and sized
// from two coordinate pairs; resp. whether it is shown and its rowed push
// button data has a positive +0xF8.
class GameWindow
{
public:
	Int winSetPosition(Int x, Int y);
	Int winSetSize(Int width, Int height);
	bool winIsHidden();
};
void *GadgetButtonGetData(GameWindow *window);
struct Rva0053EC7DPair
{
	Int x;
	Int y;
};
struct Rva0053ECD1ButtonData
{
	char m_pad00[0xF8];
	Int m_F8;
};
class RadialWindowController
{
public:
	void PositionButton(Int i, const Rva0053EC7DPair *pos, const Rva0053EC7DPair *size);
	bool rva0053ECD1(Int i);
private:
	char m_pad00[0x3C];
	GameWindow **m_3C;
};
void RadialWindowController::PositionButton(Int i, const Rva0053EC7DPair *pos, const Rva0053EC7DPair *size)
{
	GameWindow *w = m_3C[i];
	w->winSetPosition(pos->x, pos->y);
	w->winSetSize(size->x, size->y);
}
bool RadialWindowController::rva0053ECD1(Int i)
{
	GameWindow *w = m_3C[i];
	if (!w->winIsHidden())
	{
		Rva0053ECD1ButtonData *data = (Rva0053ECD1ButtonData *)GadgetButtonGetData(w);
		if (data && data->m_F8 > 0)
			return true;
	}
	return false;
}

// 0x0050962B and 0x0050965A: the rowed ObjectCreationList entry points of
// the +0x128 list for the object whose id the first argument holds at
// +0x08, with the second argument.
class ObjectCreationList
{
public:
	void create(void *a, void *b, void *c);
	void create(void *a, void *b, void *c, Int d);
};
struct Rva0050962BArg
{
	Int m_00;
	Int m_04;
	ObjectID m_08;
};
class Rva0050962B
{
public:
	void rva0050962B(const Rva0050962BArg *a, void *b);
	void rva0050965A(const Rva0050962BArg *a, void *b);
private:
	char m_pad00[0x128];
	ObjectCreationList *m_128;
};
void Rva0050962B::rva0050962B(const Rva0050962BArg *a, void *b)
{
	ObjectCreationList *list = m_128;
	if (list)
		list->create(TheGameLogic->findObjectByID(a->m_08), b, 0);
}
void Rva0050962B::rva0050965A(const Rva0050962BArg *a, void *b)
{
	ObjectCreationList *list = m_128;
	if (list)
		list->create(TheGameLogic->findObjectByID(a->m_08), b, 0, 0);
}

// 0x00513838: false after the rowed 0x002233A6(1) on the object at VA
// 0x00DFE4CC when TheGameLogic and the object at VA 0x00E01E48 exist and
// TheGameLogic's +0x110 is not 7; else true.
class Rva00222A8BTarget
{
public:
	void rva002233A6(Int a);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct GlobalA01E48;
extern class Shell *TheShell;
class Rva00513838
{
public:
	bool rva00513838();
};
bool Rva00513838::rva00513838()
{
	if (TheGameLogic && (*(GlobalA01E48 **)&TheShell) && TheGameLogic->m_110 != 7)
	{
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
		return false;
	}
	return true;
}

// 0x0051B125: message 0x15 with byte argument 1 while the words at VA
// 0x00E032E0 and 0x00E04908 are clear answers 1, running the rowed
// 0x0051AF0B with 0 when bit 0 of the third argument is set; else 0.
void Rva0051AF0BEnable(Int a);
extern Int g_Va00E032E0;
extern Int g_Va00A04908;
class Rva0051B125
{
public:
	Int rva0051B125(Int msg, unsigned char b, Int c);
};
Int Rva0051B125::rva0051B125(Int msg, unsigned char b, Int c)
{
	if (msg == 0x15)
	{
		switch (b)
		{
		case 1:
			if (g_Va00E032E0 == 0 && g_Va00A04908 == 0)
			{
				if (c & 1)
					Rva0051AF0BEnable(0);
				return 1;
			}
			break;
		}
	}
	return 0;
}

// 0x004E846A: message 0x15 answers 1, running the rowed 0x004E8220 with 0
// when bit 0 of the third argument is set and the byte argument is 1, or is
// 0x1C/0x9C with bits 2-3 set; other messages answer 0.
class Rva004E8220
{
public:
	void rva004E8220(Int a);
	Int rva004E846A(Int msg, unsigned char b, Int c);
};
Int Rva004E8220::rva004E846A(Int msg, unsigned char b, Int c)
{
	if (msg != 0x15)
		return 0;
	if (c & 1)
	{
		switch (b)
		{
		case 0x1C:
		case 0x9C:
			if (!(c & 0xC))
				break;
		case 1:
			rva004E8220(0);
			break;
		}
	}
	return 1;
}

// 0x005B4C97: 1 while +0x0C is set; message 0x4031 for the +0x08 window
// runs the rowed 0x005B4BDB when the third argument is 0 and answers 1;
// else 0.
class Rva005B4BDB
{
public:
	void rva005B4BDB();
	Int rva005B4C97(Int msg, Int window, Int c);
private:
	Int m_00;
	Int m_04;
	Int m_08;
	bool m_0C;
};
Int Rva005B4BDB::rva005B4C97(Int msg, Int window, Int c)
{
	if (m_0C)
		return 1;
	if (msg == 0x4031 && window == m_08)
	{
		if (!c)
			rva005B4BDB();
		return 1;
	}
	return 0;
}

// 0x005D3CCD: a new +0x20 value is stored between the rowed 0x005D3B9A and
// 0x005D3B26 (both only while +0x30 is set).
namespace StrategicHUD {
class SelectionUIImpl;
}

class StrategicHUD::SelectionUIImpl
{
public:
	void rva005D3B26();
};
class Rva005D3B9A : public StrategicHUD::SelectionUIImpl
{
public:
	void rva005D3B9A();
	void rva005D3CCD(Int value);
private:
	char m_pad00[0x20];
	Int m_20;
	char m_pad24[0x0C];
	bool m_30;
};
void Rva005D3B9A::rva005D3CCD(Int value)
{
	if (value != m_20)
	{
		if (m_30)
			rva005D3B9A();
		m_20 = value;
		if (m_30)
			rva005D3B26();
	}
}

// 0x005EEDF5: the pinned Object 0x00297000 on the argument with the +0x08
// button and the object whose id is held at +0x1C, then forgets the id.
class AISpecialPowerTargetEnemy
{
public:
	void activate(Object *obj);
private:
	Int m_00;
	Int m_04;
	const CommandButton *m_08;
	char m_pad0C[0x10];
	ObjectID m_1C;
};
void AISpecialPowerTargetEnemy::activate(Object *obj)
{
	obj->rva00297000(m_08, TheGameLogic->findObjectByID(m_1C), 1, 0);
	m_1C = INVALID_ID;
}

// 0x005D7AEC: the +0x28 finder's pick for the argument's controlling player;
// unless its +0x04 object has bit 2 of +0x113 set, the pinned 0x005EE8DD
// with the pick's +0x38 position and the argument.
class Rva005EEA20
{
public:
	Object *rva005EEA20(Player *player, bool a, bool b);
};
class Rva005EE816
{
public:
	bool rva005EE8DD(const Coord3D *pos, Object *obj);
};
class AISpellBookBuffTerrain : public Rva005EE816
{
public:
	bool shouldActivate(Object *obj);
private:
	char m_pad00[0x28];
	Rva005EEA20 m_28;
};
bool AISpellBookBuffTerrain::shouldActivate(Object *obj)
{
	Object *pick = m_28.rva005EEA20(obj->getControllingPlayer(), true, true);
	if (pick && !(pick->m_04->m_113 & 4))
		return rva005EE8DD((const Coord3D *)&pick->m_38, obj);
	return false;
}

// 0x004FC23E: virtual slot 8 of the +0x20 object with (+0x1C set, true)
// unless the first argument is set, then the rowed 0x005392C2 on it unless
// the second is.
class Rva005392C2
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08(bool a, bool b);
	void rva005392C2();
};
class Rva004FC23E
{
public:
	void rva004FC23E(Int a, Int b);
private:
	char m_pad00[0x1C];
	Int m_1C;
	Rva005392C2 *m_20;
};
void Rva004FC23E::rva004FC23E(Int a, Int b)
{
	if (!a)
	{
		Rva005392C2 *p = m_20;
		if (p)
			p->v08(m_1C != 0, true);
	}
	if (!b)
	{
		Rva005392C2 *p = m_20;
		if (p)
			p->rva005392C2();
	}
}

// 0x004B65A5 (interface at +0x10): the rowed 0x001E431E resp. 0x001E42F2
// on the object with the module data's +0x164 resp. +0x118 condition flags,
// each only when the pinned ModelConditionFlags 0x000B3EB3 test holds.
class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
};
class Rva001E431E
{
public:
	void rva001E431E(const Int *flags);
};
class Rva001E42F2
{
public:
	void rva001E42F2(const Int *flags);
};
struct Rva004B65A5Data
{
	char m_pad00[0x118];
	ModelConditionFlags m_118;
	char m_pad119[0x4B];
	ModelConditionFlags m_164;
};
class Rva004B65A5Primary
{
public:
	virtual void primarySlot();
protected:
	Rva004B65A5Data *m_moduleData; // +0x04
	Rva001E431E *m_object; // +0x08
	Int m_0C;
};
class Rva004B65A5Iface
{
public:
	virtual void rva004B65A5() = 0;
};
class Rva004B65A5 : public Rva004B65A5Primary, public Rva004B65A5Iface
{
public:
	void rva004B65A5();
};
void Rva004B65A5::rva004B65A5()
{
	Rva001E431E *obj = m_object;
	Rva004B65A5Data *data = m_moduleData;
	if (data->m_164.rva000B3EB3())
		obj->rva001E431E((const Int *)&data->m_164);
	if (data->m_118.rva000B3EB3())
		((Rva001E42F2 *)obj)->rva001E42F2((const Int *)&data->m_118);
}

// 0x0043D41E: message 0x15 answers 1 for byte arguments 1, 0x1C and 0x29;
// with bit 0 of the third argument, byte 1 runs the rowed 0x0043D3DA then
// 0x0043C7C9 (each with 0) and the others only the latter; else 0.
class Rva0043D3DA
{
public:
	void rva0043D3DA(Int a);
	void rva0043C7C9(Int a);
	Int rva0043D41E(Int msg, unsigned char b, Int c);
};
Int Rva0043D3DA::rva0043D41E(Int msg, unsigned char b, Int c)
{
	if (msg != 0x15)
		return 0;
	switch (b)
	{
	case 0x1C:
	case 0x29:
		if (c & 1)
			rva0043C7C9(0);
		break;
	case 1:
		if (c & 1)
		{
			rva0043D3DA(0);
			rva0043C7C9(0);
		}
		break;
	default:
		return 0;
	}
	return 1;
}

// 0x004A3B95: a module xfer: version 1, the rowed UpdateModule::xfer, then
// (unless light CRC) the ten object ids at +0xCC through the rowed
// XferObjectID.
class Xfer
{
public:
	void Version1();
	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
};
void XferObjectID(Xfer *xfer, ObjectID *id);
class UpdateModule
{
public:
	virtual void primarySlot();
	void xfer(Xfer *xfer);
};
class Rva004A3B95 : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	char m_pad04[0xC8];
	ObjectID m_CC[10]; // +0xCC
};
void Rva004A3B95::xfer(Xfer *xfer)
{
	xfer->Version1();
	UpdateModule::xfer(xfer);
	if (!xfer->IsLightCRC())
	{
		for (Int i = 0; i < 10; i++)
			XferObjectID(xfer, &m_CC[i]);
	}
}

// 0x004EE113: when the two ids differ, counts at +0xD8 the first matching
// the +0xE0 id, else at +0xD4 the second matching it.
class Rva004EE113
{
public:
	void rva004EE113(Int unused, Int a, Int b);
private:
	char m_pad00[0xD4];
	Int m_D4;
	Int m_D8;
	Int m_DC;
	Int m_E0;
};
void Rva004EE113::rva004EE113(Int, Int a, Int b)
{
	if (a != b)
	{
		if (a == m_E0)
			m_D8++;
		else if (b == m_E0)
			m_D4++;
	}
}

// 0x00573E2B: state 3 clears +0x54 and sets +0x58 to the current frame plus
// 30 per unit of the Int at VA 0x00DBA4E4; the state is stored at +0x10.
extern Int g_Va00DBA4E4;
class Rva00573E2B
{
public:
	void rva00573E2B(Int state);
private:
	char m_pad00[0x10];
	Int m_10;
	char m_pad14[0x40];
	bool m_54;
	char m_pad55[0x03];
	Int m_58;
};
void Rva00573E2B::rva00573E2B(Int state)
{
	if (state == 3)
	{
		m_54 = false;
		m_58 = (Int)((float)TheGameLogic->m_40 + (float)g_Va00DBA4E4 * 30.0f);
	}
	m_10 = state;
}

// 0x00516EA7: sets +0x27C and runs the rowed 0x002233A6(1) on the object at
// VA 0x00DFE4CC when there is one.
class Rva00516EA7
{
public:
	void rva00516EA7();
private:
	char m_pad00[0x27C];
	bool m_27C;
};
void Rva00516EA7::rva00516EA7()
{
	m_27C = true;
	if ((*(Rva00222A8BTarget **)&g_bfmeAptWindowManager))
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva002233A6(1);
}
