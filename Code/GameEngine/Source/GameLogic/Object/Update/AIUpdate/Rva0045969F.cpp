// cl: /O1 /arch:SSE /G7 /MD
//
// ?rva0045969F@Rva0045969F@@UAEHXZ, retail 0x0045969F 90 bytes.
// Ref-lane body reached via table slot 0x00841194; neighbours are UpdateModule
// rows. Evidence: Thing at this-8 via rowed getDrawable 0x005508E2 plus AI at
// Object+0x258 plus AI pred slot 0x1b8 plus iface at +0x10 slot 8 plus ints at
// +0x14/+0x18 plus returns 1 vs 0x3fffffff. Layout follows sibling
// Rva00459864 (this-0x18) and Rva00495801 AI-slot template precedent.

class Drawable;

class Thing
{
public:
	Drawable *getDrawable() const;
};

class ThingTemplate
{
public:
	char m_pad00[0x10C];
};

template <int N> class AiSlots : public AiSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class AiSlots<0>
{
};

class AI : public AiSlots<110>
{
public:
	virtual bool isIdle();
};

class Object
{
public:
	void *m_vtable;
	ThingTemplate *m_template;
	char m_pad08[0x258 - 0x08];
	AI *m_ai;
};

class PadBase
{
public:
	virtual ~PadBase();
private:
	char m_pad04[0x10 - 0x04];
};

class SubIface
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02(int v);
};

class Rva0045969F : public PadBase, public SubIface
{
public:
	virtual int rva0045969F();
private:
	int m_14;
	int m_18;
};

int Rva0045969F::rva0045969F()
{
	Drawable *d = (*(Thing **)((char *)this - 8))->getDrawable();
	AI *ai = (*(Object **)((char *)this - 8))->m_ai;
	if (d == 0 || ai == 0)
		return 0x3fffffff;
	if (m_14 > 0)
		--m_14;
	if (m_18 <= 0)
		return 1;
	--m_18;
	if (m_18 != 0)
	{
		if (ai->isIdle())
			return 1;
	}
	((SubIface *)this)->s02(1);
	m_18 &= 0;
	return 1;
}
