// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// Three slots of the +0x20 interface vtable 0x00C403C8 that GettingBuiltBehavior's
// ctor 0x004542FA installs, over the work list at +0x40 (+0x20 from the
// subobject this). Its 20-byte entries are Rva004530ED: an Object ID, a
// position and a float (Rva004530EDFinish.cpp: the default ctor 0x004530D0
// and the copy ctor 0x004530ED). Slot 24 calls 0x004530ED on an existing
// out-parameter with no EH state, so it is read as the entry's operator=,
// whose bytes would equal the copy ctor's (eax = this) and fold onto it by
// ICF: an inference, not target evidence. Appends go through the list's
// out-of-line push_back 0x00453B06 (pinned): the STLport list is viewed here
// by its node layout only, so this unit emits none of the list's own bodies
// (whose STLport instantiation differs from retail's: retail keeps
// _M_create_node out of insert and its _Construct has no EH state). Method identities are not established; names
// are by address, as in GettingBuiltBehaviorIfaceSlots.cpp.
//
// - slot 18, retail 0x00453B20 (91 bytes): an Object whose ID is not yet
//   listed is appended with its +0x38 position and +0x44 float;
// - slot 24, retail 0x00453B7B (118 bytes): assigns entry `index` out; 1 when
//   the index is out of range, 2 when its Object is gone, else 3 if the
//   Object's +0x438 bit 0 is set or 0;
// - slot 25, retail 0x00453E5C (213 bytes): with a +0x7C ID, a non-empty list
//   and bit 4 of the template's +0x11B byte, true when the owner has status 2
//   and slots 14..16 all answer false, else whether a listed Object with a
//   higher ID has status 2 and its interface's slots 14 and 15 answer false.
//   The guard as one boolean and the list walk as an inline helper give
//   retail's block order and late ebx/edi pushes.

class Object;

struct Coord3D
{
	float x, y, z;
};

class Rva004530ED
{
public:
	Rva004530ED();
	Rva004530ED(const Rva004530ED &rhs);
	Rva004530ED &operator=(const Rva004530ED &rhs);
	int m_id; // +0x00
	Coord3D m_pos; // +0x04
	float m_10; // +0x10
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

struct Rva00453E5CTemplate
{
	unsigned char m_pad000[0x11B];
	unsigned char m_11B; // +0x11B
};

class GettingBuiltBehaviorInterface;

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	void *rva0028BD17() const;
	unsigned char m_pad000[0x04];
	const Rva00453E5CTemplate *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_38; // +0x38
	float m_44; // +0x44
	unsigned char m_pad048[0x74 - 0x48];
	int m_74; // +0x74 (ID)
	unsigned char m_pad078[0x7C - 0x78];
	int m_7C; // +0x7C (an Object ID)
	unsigned char m_pad080[0x438 - 0x80];
	unsigned char m_438; // +0x438
};

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

extern GameLogic *TheGameLogic;

namespace _STL
{
template <class T> class allocator;

template <class T> struct _List_node
{
	_List_node *_M_next;
	_List_node *_M_prev;
	T _M_data;
};

// STLport 4.5.3 list<T>: one pointer to the sentinel node.
template <class T, class A> class list
{
public:
	typedef _List_node<T> *iterator;
	iterator begin() const { return m_node->_M_next; }
	iterator end() const { return m_node; }
	bool empty() const { return m_node->_M_next == m_node; }
	unsigned int size() const
	{
		unsigned int n = 0;
		for (iterator it = begin(); it != end(); it = it->_M_next)
			++n;
		return n;
	}
	void push_back(const T &x);
private:
	_List_node<T> *m_node;
};
}

typedef _STL::list<Rva004530ED, _STL::allocator<Rva004530ED> > Rva00453B20List;

template <int N> class Rva00453B20Slots : public Rva00453B20Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00453B20Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class GettingBuiltBehaviorInterface : public Rva00453B20Slots<14>
{
public:
	virtual bool rva004543BE() = 0;
	virtual bool rva004543C2() = 0;
	virtual bool rva004543C6() = 0;
	virtual void gap17() = 0;
	virtual void rva00453B20(Object *obj) = 0;
	virtual void gap19() = 0; virtual void gap20() = 0; virtual void gap21() = 0;
	virtual void gap22() = 0; virtual void gap23() = 0;
	virtual int rva00453B7B(int index, Rva004530ED *out) = 0;
	virtual bool rva00453E5C() = 0;
};

class GettingBuiltBehaviorHead
{
public:
	virtual ~GettingBuiltBehaviorHead();
protected:
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class GettingBuiltBehavior : public GettingBuiltBehaviorHead, public GettingBuiltBehaviorInterface
{
public:
	virtual void rva00453B20(Object *obj);
	virtual int rva00453B7B(int index, Rva004530ED *out);
	virtual bool rva00453E5C();
private:
	__forceinline bool anyLaterBuilding(int myId)
	{
		for (Rva00453B20List::iterator it = m_40.begin(); it != m_40.end(); it = it->_M_next)
		{
			Rva004530ED entry(it->_M_data);
			if (entry.m_id > myId)
			{
				Object *other = TheGameLogic->findObjectByID(entry.m_id);
				if (other)
				{
					GettingBuiltBehaviorInterface *gbi = interfaceOf(other);
					if (gbi && !gbi->rva004543BE() && !gbi->rva004543C2() && other->testStatus((ObjectStatusTypes)2))
						return true;
				}
			}
		}
		return false;
	}
	static GettingBuiltBehaviorInterface *interfaceOf(Object *obj)
	{
		return (GettingBuiltBehaviorInterface *)obj->rva0028BD17();
	}
	unsigned char m_pad24[0x40 - 0x24];
	Rva00453B20List m_40; // +0x40
};

void GettingBuiltBehavior::rva00453B20(Object *obj)
{
	for (Rva00453B20List::iterator it = m_40.begin(); it != m_40.end(); it = it->_M_next)
	{
		if (obj->m_74 == it->_M_data.m_id)
			return;
	}
	Rva004530ED entry;
	entry.m_id = obj->m_74;
	entry.m_pos = obj->m_38;
	entry.m_10 = obj->m_44;
	m_40.push_back(entry);
}

int GettingBuiltBehavior::rva00453B7B(int index, Rva004530ED *out)
{
	if (index >= m_40.size())
		return 1;
	int i = 0;
	for (Rva00453B20List::iterator it = m_40.begin(); it != m_40.end(); it = it->_M_next)
	{
		if (i > index)
			break;
		if (i++ >= index)
		{
			Object *obj = TheGameLogic->findObjectByID(it->_M_data.m_id);
			if (obj)
			{
				*out = it->_M_data;
				return (obj->m_438 & 1) ? 3 : 0;
			}
			return 2;
		}
	}
	return 1;
}

bool GettingBuiltBehavior::rva00453E5C()
{
	Object *me = m_object;
	int myId = me->m_7C;
	bool ok = myId != 0 && !m_40.empty() && (me->m_template->m_11B & 0x10);
	if (!ok)
		return false;
	if (me->testStatus((ObjectStatusTypes)2) && !rva004543BE() && !rva004543C2() && !rva004543C6())
		return true;
	return anyLaterBuilding(myId);
}
