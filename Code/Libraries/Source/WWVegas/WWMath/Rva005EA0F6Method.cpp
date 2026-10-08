// cl: /DNDEBUG /MD /EHs-c- /O1 /G7 /arch:SSE
// ?rva005EA0F6@Rva005EA183@@QAEXXZ @0x005EA0F6 47B, twin of 0x005EA0C0
// (Rva005EA0C0Method.cpp) with vtable 0xC78134 instead of 0xC78174.
// Target evidence: callee of ShowBattleStepStateHandler::Done when the dialog
// Impl's +0x10 is clear; new 8 stores the Impl at +4 and vptr 0xC78134
// (DIR32-masked), hands it to the +0x14 holder through rowed 0x00575674 and
// tail-calls the holder object's slot 1. The 0xC78134 table's slot 1 is the
// matched ClosingStateHandler::Startup 0x005EA46F, so this enters the closing
// state; slot 0 is ??_G 0x005EA28F and slot 7 the bool getter 0x0047A699.
// The state class stays address-named here (owner reconciliation pending).
class Rva005EA183;

class __declspec(novtable) Rva005EA0F6StateBase
{
public:
	Rva005EA0F6StateBase(Rva005EA183 *owner) : m_owner(owner) {}
	virtual void *slot00(unsigned int flags);
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10(void *, void *);
	virtual void slot14(void *, void *);
	virtual void slot18(void *, void *);
	virtual bool slot1C();

private:
	Rva005EA183 *m_owner; // +0x04
};

class Rva005EA0F6State : public Rva005EA0F6StateBase
{
public:
	Rva005EA0F6State(Rva005EA183 *owner) : Rva005EA0F6StateBase(owner) {}
	virtual void slot04();
};

class Object
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
};

class Rva00575674
{
public:
	void rva00575674(Object *p);
	Object *m_ptr;
};

class Rva005EA183
{
public:
	void rva005EA0F6();

private:
	char m_pad[0x14];
	Rva00575674 m_holder; // +0x14
};

void Rva005EA183::rva005EA0F6()
{
	Rva005EA0F6State *state = new Rva005EA0F6State(this);
	m_holder.rva00575674((Object *)state);
	return m_holder.m_ptr->f1();
}
