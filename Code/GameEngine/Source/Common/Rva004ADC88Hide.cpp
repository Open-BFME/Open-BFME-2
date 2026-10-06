// cl: /O1 /arch:SSE /DNDEBUG /MD
//
// ?rva004AD9E0@Rva004ADC88@@QAEXXZ @0x004AD9E0 77B.
// ?rva004ADC88@Rva004ADC88@@QAEXXZ @0x004ADC88 96B.
// 0x004AD9E0 drops the object at +8: 0x0028BAC0, leaveGroup, hide its
// drawable, notify TheAI's +0x10 shim, then GameLogic::destroyObject.
// 0x004ADC88 runs the virtual at 0x00451B92, writes 1.0f at the drawable's
// +0xB0, clears status 0x4A, and tail-calls 0x004AD9E0 when the byte at
// +0x8C is set and the string at [this+4]+0xD0 is not empty.

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Object;
class Drawable
{
public:
	char m_pad[0xB0];
	float m_scale;
};

class Thing
{
public:
	Drawable *getDrawable() const;
};

class Object : public Thing
{
public:
	void leaveGroup();
	void setStatus(ObjectStatusTypes status, bool set);
};

class GameLogic
{
public:
	void destroyObject(Object *obj);
};

extern GameLogic *TheGameLogic;

class AI;

class Pathfinder
{
public:
	void RemoveObjectFromPathfindMap(Object *obj);
};

class AI
{
public:
	char m_pad[0x10];
	Pathfinder *m_shim;
};

extern AI *TheAI;

class SpecialAbilityUpdate
{
public:
	virtual void rva00451B92();
};

class Rva0028BAC0
{
public:
	void rva0028BAC0();
};

class Rva002716Holder
{
public:
	void rva00271601(unsigned char hidden);
};

template <typename T>
class StringBase
{
public:
	bool isEmpty() const;
};

class Rva004ADC88
{
public:
	void rva004AD9E0();
	void rva004ADC88();

private:
	char m_pad[4];
	void *m_other;
	Object *m_obj;
	char m_padC[0x8C - 0x0C];
	unsigned char m_flag;
};

void Rva004ADC88::rva004AD9E0()
{
	Object *obj = m_obj;
	((Rva0028BAC0 *)obj)->rva0028BAC0();
	obj->leaveGroup();
	if (obj->getDrawable() != 0)
		((Rva002716Holder *)obj->getDrawable())->rva00271601(1);
	if (TheAI != 0)
		TheAI->m_shim->RemoveObjectFromPathfindMap(obj);
	TheGameLogic->destroyObject(obj);
}

void Rva004ADC88::rva004ADC88()
{
	((SpecialAbilityUpdate *)this)->SpecialAbilityUpdate::rva00451B92();
	void *other = m_other;
	if ((*(Object *volatile *)&m_obj)->getDrawable() != 0)
		(*(Object *volatile *)&m_obj)->getDrawable()->m_scale = 1.0f;
	(*(Object *volatile *)&m_obj)->setStatus((ObjectStatusTypes)0x4A, false);
	if (m_flag != 0 && ((StringBase<char> *)((char *)other + 0xD0))->isEmpty() == 0)
		rva004AD9E0();
}
