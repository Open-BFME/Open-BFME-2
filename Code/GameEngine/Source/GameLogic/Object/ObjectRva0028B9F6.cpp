// cl: /DNDEBUG /MD
// ?SwapForExchange@Object@@QAEXPAV1@@Z @0x0028B9F6 143B: Object module
// exchange with another Object. Scans own +0x244 array for the entry whose
// +0x0C sub-object slot2 (+0x08) equals own +0x250, scans other's array for
// the entry whose slot2 equals other's +0x250, swaps the two entries and the
// two +0x250 faces, then sets each swapped module's +0x08 owner to its new
// Object. Evidence: retail dual lea/call [eax+0x08] loops plus swap stores
// plus add eax,0x250 face exchange plus [eax+8] owner stores; ret 4.
class Object;

class Rva0028B9F6Face
{
};

class BehaviorModuleInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual Rva0028B9F6Face *slot02();
};

class BfmeObjectModule
{
public:
	virtual void slot0();

private:
	unsigned int m_data04;
public:
	Object *m_owner08;
};

class BehaviorModule : public BfmeObjectModule, public BehaviorModuleInterface
{
};

class Object
{
	char m_pad244[0x244];
	BehaviorModule **m_modules244;
	char m_pad248[0x250 - 0x248];
	Rva0028B9F6Face *m_face250;

public:
	void SwapForExchange(Object *other);
};

void Object::SwapForExchange(Object *other)
{
	BehaviorModule **a = m_modules244;
	while (*a != 0)
	{
		Rva0028B9F6Face *f = (*a)->slot02();
		if (f == m_face250)
			break;
		++a;
	}
	BehaviorModule **b = other->m_modules244;
	if (other->m_modules244[0] == 0)
		return;
	do
	{
		Rva0028B9F6Face *f = (*b)->slot02();
		if (f == other->m_face250)
			break;
		++b;
	} while (*b != 0);
	BehaviorModule *oldB = *b;
	if (oldB == 0)
		return;
	BehaviorModule *oldA = *a;
	*a = oldB;
	*b = oldA;
	Rva0028B9F6Face *bFace = other->m_face250;
	Rva0028B9F6Face *aFace = m_face250;
	m_face250 = bFace;
	other->m_face250 = aFace;
	(*a)->m_owner08 = this;
	(*b)->m_owner08 = other;
}
