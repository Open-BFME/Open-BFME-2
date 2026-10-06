// cl: /DNDEBUG /MD
//
// ?rva00397238@Rva00397238@@QAEHXZ, retail 0x00397238, 66 bytes.
// Count loop over the ObjectID range at +0x50/+0x54 via the rowed
// GameLogic::findObjectByID at 0x00049DC5 and the rowed
// Object::rva0028BCF4 at 0x0028BCF4; the returned interface is asked
// through its slot 3 (offset 0x0C) and true results are counted.
// Evidence: caller 0x003972BC unblocks 0x003972BC; sibling
// ?rva0039727A@Rva0039727A@@QAEHXZ at 0x0039727A counts the +0x74/+0x78
// range the same way; TheGameLogic 0x009FE78C,
// GameLogic::findObjectByID 0x00049DC5, Object::rva0028BCF4 0x0028BCF4.

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object;
class GameLogic;

extern GameLogic *TheGameLogic;

class Iface00397238
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

class Rva00397238
{
public:
	int rva00397238();
private:
	char m_pad00[0x50];
	ObjectID *m_begin50;
	ObjectID *m_end54;
};

int Rva00397238::rva00397238()
{
	int count = 0;
	for (ObjectID *p = m_begin50; p != m_end54; ++p)
	{
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (obj == 0)
			continue;
		void *iface = obj->rva0028BCF4();
		if (iface == 0)
			continue;
		if (!static_cast<Iface00397238 *>(iface)->s3())
			continue;
		++count;
	}
	return count;
}
