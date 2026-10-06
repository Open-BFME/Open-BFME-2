// cl: /DNDEBUG /MD
//
// ?rva0039727A@Rva0039727A@@QAEHXZ, retail 0x0039727A, 66 bytes.
// Count loop over the ObjectID range at +0x74/+0x78 via the rowed
// GameLogic::findObjectByID at 0x00049DC5 and the rowed
// Object::rva0028BCF4 at 0x0028BCF4; the returned interface is asked
// through its slot 3 (offset 0x0C) and true results are counted.
// Evidence: caller 0x003972C9 adds this result to a sibling count;
// the +0x74/+0x78 range and the slot-0x0C call are retail-measured.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class GameLogic;

extern GameLogic *TheGameLogic;

class Iface0039727A
{
public:
	virtual void s0();
	virtual void s1();
	virtual void s2();
	virtual bool s3();
};

class Object
{
public:
	void *rva0028BCF4() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class Rva0039727A
{
public:
	int rva0039727A();
private:
	char m_pad00[0x74];
	ObjectID *m_begin74;
	ObjectID *m_end78;
};

int Rva0039727A::rva0039727A()
{
	int count = 0;
	for (ObjectID *p = m_begin74; p != m_end78; ++p)
	{
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (obj == 0)
			continue;
		void *iface = obj->rva0028BCF4();
		if (iface == 0)
			continue;
		if (!static_cast<Iface0039727A *>(iface)->s3())
			continue;
		++count;
	}
	return count;
}
