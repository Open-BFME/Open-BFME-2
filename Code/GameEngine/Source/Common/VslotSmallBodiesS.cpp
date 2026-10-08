// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch S. As in VslotSmallBodiesA-R, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;
typedef unsigned int UnsignedInt;

// 0x00490628: false while +0x98 is set, else the pinned
// SpecialAbilityUpdate slot it overrides.
class SpecialAbilityUpdate
{
public:
	virtual bool rva0044FC52();
};
class Rva00490628 : public SpecialAbilityUpdate
{
public:
	virtual bool rva0044FC52();
private:
	char m_pad04[0x94];
	bool m_98;
};
bool Rva00490628::rva0044FC52()
{
	if (m_98)
		return false;
	return SpecialAbilityUpdate::rva0044FC52();
}

// 0x0050B95B: looks up the +0x12C key in the registry at VA 0x00DFF000 and
// forwards both arguments to the pinned notify of the entry found.
struct Rva0020AA00Target
{
	void notify(Int a, Int b);
};
class Rva0020AA00Registry
{
public:
	Rva0020AA00Target *lookup(const Int &key);
};
extern class ThingFactory *TheThingFactory;
class Rva0050B95B
{
public:
	void rva0050B95B(Int a, Int b);
private:
	char m_pad00[0x12C];
	Int m_12C;
};
void Rva0050B95B::rva0050B95B(Int a, Int b)
{
	Rva0020AA00Target *t = (*(Rva0020AA00Registry **)&TheThingFactory)->lookup(m_12C);
	if (t)
		t->notify(a, b);
}

// 0x0050BDD5: own virtual slot 6 with the argument and the +0x38 member of
// the second argument, when there is one.
struct Rva0050BDD5Arg
{
	char m_pad00[0x38];
	Int m_38;
};
class FireLogicNugget
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06(Int a, Int *b);
	void doEffectObject(Int a, Rva0050BDD5Arg *b);
};
void FireLogicNugget::doEffectObject(Int a, Rva0050BDD5Arg *b)
{
	if (b)
		v06(a, &b->m_38);
}

// 0x005101C0: 1 when the +0x24 object's rowed 0x0050FF7F answers 1, else 0.
class GameWindow;
class Rva0050F5A6
{
public:
	Int rva0050FF7F(UnsignedInt a, GameWindow *w, UnsignedInt b);
};
class Rva005101C0
{
public:
	Int rva005101C0(UnsignedInt a, GameWindow *w, UnsignedInt b);
private:
	char m_pad00[0x24];
	Rva0050F5A6 *m_24;
};
Int Rva005101C0::rva005101C0(UnsignedInt a, GameWindow *w, UnsignedInt b)
{
	if (m_24 && m_24->rva0050FF7F(a, w, b) == 1)
		return 1;
	return 0;
}

// 0x005117B7: message 0x15 with byte argument 1 and bit 0 of the third runs
// the rowed 0x00511730 with 0 and answers 1; else 0.
void Rva00511730(Int a);
class Rva005117B7
{
public:
	Int rva005117B7(Int msg, unsigned char b, Int c);
};
Int Rva005117B7::rva005117B7(Int msg, unsigned char b, Int c)
{
	if (msg == 0x15)
	{
		switch (b)
		{
		case 1:
			if (c & 1)
			{
				Rva00511730(0);
				return 1;
			}
			break;
		}
	}
	return 0;
}

// 0x005127F3: messages 0x4014 and 0x4031 answer 1; the rest go to the pinned
// base handler.
class _bfme_AptGameWindow
{
public:
	Int rva0051274F(Int msg, UnsignedInt a, UnsignedInt b);
};
class Rva005127F3 : public _bfme_AptGameWindow
{
public:
	Int rva005127F3(Int msg, UnsignedInt a, UnsignedInt b);
};
Int Rva005127F3::rva005127F3(Int msg, UnsignedInt a, UnsignedInt b)
{
	switch (msg)
	{
	case 0x4014:
	case 0x4031:
		return 1;
	}
	return rva0051274F(msg, a, b);
}

// 0x00514878: state 2 at +0x288 is cleared through the rowed 0x00222F55
// (false) on the object at VA 0x00DFE4CC; then +0x5D of the object at VA
// 0x00E01E48 is set.
class Rva00222A8BTarget
{
public:
	void rva00222F55(bool b);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
struct Rva00514878Flags
{
	char m_pad00[0x5D];
	bool m_5D;
};
extern class Shell *TheShell;
class Rva00514878
{
public:
	void rva00514878();
private:
	char m_pad00[0x288];
	Int m_288;
};
void Rva00514878::rva00514878()
{
	if (m_288 == 2)
	{
		m_288 = 0;
		(*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)->rva00222F55(false);
	}
	(*(Rva00514878Flags **)&TheShell)->m_5D = true;
}

// 0x0051E2FB: state 1 at +0x27C runs virtual slot 9 of the object at VA
// 0x00DFDC14 and clears; answers 1.
class Rva0051E2FBTarget
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
	virtual void v08();
	virtual void v09();
};
extern class GameWindowTransitionsHandler *TheTransitionHandler;
class Rva0051E2FB
{
public:
	Int rva0051E2FB();
private:
	char m_pad00[0x27C];
	Int m_27C;
};
Int Rva0051E2FB::rva0051E2FB()
{
	if (m_27C == 1)
	{
		(*(Rva0051E2FBTarget **)&TheTransitionHandler)->v09();
		m_27C = 0;
	}
	return 1;
}

// 0x0053ECAC: clears (true) or sets (false) status 0x200 of window i of the
// +0x3C array. A virtual: slot 3 of RadialWindowController's vtable
// 0x00C6944C, as in WorldBuilder's twin table.
class GameWindow
{
public:
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
};
class RadialWindowController
{
public:
	virtual void EnableButtonInput(Int i, bool clear);
private:
	char m_pad04[0x38];
	GameWindow **m_3C;
};
void RadialWindowController::EnableButtonInput(Int i, bool clear)
{
	GameWindow *w = m_3C[i];
	if (clear)
		w->winClearStatus(0x200);
	else
		w->winSetStatus(0x200);
}

// 0x00540131 and 0x005411A3: overrides of the rowed chunk writer 0x0053F8E9
// that chain to it and then write their members.
class DataChunkOutput;
class Rva0053FB33
{
public:
	virtual void rva0053F8E9(DataChunkOutput *out);
};
class Rva0053FF1D
{
public:
	void rva0053FF1D(DataChunkOutput *out);
};
class Rva00540F0B
{
public:
	void rva00540F0B(DataChunkOutput *out);
};
class Rva00540F4D
{
public:
	void rva00540F4D(DataChunkOutput *out);
};
class Rva00540131 : public Rva0053FB33
{
public:
	virtual void rva0053F8E9(DataChunkOutput *out);
private:
	char m_pad04[0x20];
	Rva0053FF1D m_24;
};
void Rva00540131::rva0053F8E9(DataChunkOutput *out)
{
	Rva0053FB33::rva0053F8E9(out);
	m_24.rva0053FF1D(out);
}
class Rva005411A3 : public Rva0053FB33
{
public:
	virtual void rva0053F8E9(DataChunkOutput *out);
private:
	char m_pad04[0x20];
	Rva00540F0B m_24;
	char m_pad25[0x1F];
	Rva00540F4D m_44;
};
void Rva005411A3::rva0053F8E9(DataChunkOutput *out)
{
	Rva0053FB33::rva0053F8E9(out);
	m_24.rva00540F0B(out);
	m_44.rva00540F4D(out);
}

// 0x00541F02: hands this object to virtual slot 1 of the argument.
class Rva00541F02;
class Rva00541F02Visitor
{
public:
	virtual void v00();
	virtual void v01(Rva00541F02 *o);
};
class Rva00541F02
{
public:
	void rva00541F02(Rva00541F02Visitor *v);
};
void Rva00541F02::rva00541F02(Rva00541F02Visitor *v)
{
	v->v01(this);
}

// 0x005450B5 and 0x005451F3: clear model-condition bit 256 (resp. 257) of
// the object reached through +0x18/+0x14 (the word array at Object+0x10C, as
// in ObjectWeaponSetFlags.cpp) and notify it through the pinned 0x0028AE6D.
class Rva0010CConditionBits
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void clear(UnsignedInt bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[20];
};
class Object
{
public:
	void rva0028AE6D();
	char m_pad00[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
struct Rva005450B5Holder
{
	char m_pad00[0x14];
	Object *m_14;
};
class Rva005450B5
{
public:
	void rva005450B5(Int unused);
	void rva005451F3(Int unused);
private:
	char m_pad00[0x18];
	Rva005450B5Holder *m_18;
};
void Rva005450B5::rva005450B5(Int)
{
	Object *o = m_18->m_14;
	if (o->m_conditionBits.test(256) != 0)
	{
		o->m_conditionBits.clear(256);
		o->rva0028AE6D();
	}
}
void Rva005450B5::rva005451F3(Int)
{
	Object *o = m_18->m_14;
	if (o->m_conditionBits.test(257) != 0)
	{
		o->m_conditionBits.clear(257);
		o->rva0028AE6D();
	}
}

// 0x00545222: whether the +0x04 object's +0x04 count (999999 without the
// object) is zero.
struct Rva00545222Info
{
	Int m_00;
	Int m_04;
};
class Rva00545222
{
public:
	bool rva00545222() const;
private:
	Int m_00;
	Rva00545222Info *m_04;
};
bool Rva00545222::rva00545222() const
{
	Int count = m_04 ? m_04->m_04 : 999999;
	if (count == 0)
		return true;
	return false;
}

// 0x0057A4C9: the rowed 0x005D4BD4 with 0.0 on the +0x28 object, when there
// is one.
class Rva005D4BD4
{
public:
	void rva005D4BD4(float f);
};
class Rva0057A4C9
{
public:
	void rva0057A4C9();
private:
	char m_pad00[0x28];
	Rva005D4BD4 *m_28;
};
void Rva0057A4C9::rva0057A4C9()
{
	if (m_28)
		m_28->rva005D4BD4(0.0f);
}
