// cl: /O1 /DNDEBUG /MD
//
// Small bodies with no ledger owner, batch AB: vtable slots together with
// the unrowed callees they need. As in VslotSmallBodiesA-AA, each class and
// method is address-derived unless the ledger already names it, and models
// only what its body touches. Meanings are not recovered.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

// 0x003F409F (five callers): virtual slot 12, with the argument, of the
// entry the map at VA 0x00DFE1C8 holds under the +0x30 key (rowed
// 0x002120A4), when there is one; the slots 0x0020E39D and 0x0020E779 run
// it on their argument with false, resp. whether its +0x34 equals the +0x04
// object's, and answer true.
class Rva003F409FTarget
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
	virtual void v10();
	virtual void v11();
	virtual void v12(bool b);
};
class Rva002120A4
{
public:
	Int rva002120A4(NameKeyType key);
};
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
class Rva003F409F
{
public:
	void rva003F409F(bool b);
	char m_pad00[0x30];
	NameKeyType m_30;
	Int m_34;
};
void Rva003F409F::rva003F409F(bool b)
{
	Rva003F409FTarget *target = (Rva003F409FTarget *)reinterpret_cast<Rva002120A4 *>(TheLivingWorldManager)->rva002120A4(m_30);
	if (target)
		target->v12(b);
}
class Rva0020E39D
{
public:
	bool rva0020E39D(Rva003F409F *arg);
	bool rva0020E779(Rva003F409F *arg);
private:
	Int m_00;
	Rva003F409F *m_04;
};
bool Rva0020E39D::rva0020E39D(Rva003F409F *arg)
{
	arg->rva003F409F(false);
	return true;
}
bool Rva0020E39D::rva0020E779(Rva003F409F *arg)
{
	arg->rva003F409F(arg->m_34 == m_04->m_34);
	return true;
}

// 0x002B8644 (two callers): appends the argument to the +0x10C vector
// (pinned STLport push_back); the slot 0x002B89BB does so on the object at
// VA 0x00DFEF10 for an argument whose +0x54 matches the +0x04 object's
// +0x14 and whose +0x75 is clear, and answers true.
namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	void push_back(const T &x);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}
class Rva002B8644
{
public:
	void rva002B8644(Int value);
private:
	char m_pad00[0x10C];
	_STL::vector<long, _STL::allocator<long> > m_10C;
};
void Rva002B8644::rva002B8644(Int value)
{
	m_10C.push_back(value);
}
struct Rva002B89BBArg
{
	char m_pad00[0x54];
	Int m_54;
	char m_pad58[0x1D];
	bool m_75;
};
struct Rva002B89BBInfo
{
	char m_pad00[0x14];
	Int m_14;
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002B89BB
{
public:
	bool rva002B89BB(Rva002B89BBArg *arg);
private:
	Int m_00;
	Rva002B89BBInfo *m_04;
};
bool Rva002B89BB::rva002B89BB(Rva002B89BBArg *arg)
{
	if (arg->m_54 == m_04->m_14 && !arg->m_75)
		reinterpret_cast<Rva002B8644 *>(TheLivingWorldLogic)->rva002B8644((Int)arg);
	return true;
}

// 0x0028BC94 (six callers): the first non-NULL answer of virtual slot 28 of
// the behavior interface (+0x0C) of the NULL-terminated module list at
// +0x244; the slot 0x005D99E9 asks it of its second argument unless bit 4
// of that object's +0x04 +0x11A flags is set, and answers whether it found
// one.
class Rva0028BC94Iface
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
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void *v28();
};
class Rva0028BC94Module
{
public:
	virtual void primarySlot();
	Int m_04;
	Int m_08;
	Rva0028BC94Iface m_iface0C;
};
struct Rva005D99E9Info
{
	char m_pad00[0x11A];
	unsigned char m_11A;
};
class Object
{
public:
	void *rva0028BC94();
	Int m_00;
	Rva005D99E9Info *m_04;
	char m_pad08[0x23C];
	Rva0028BC94Module **m_244;
};
void *Object::rva0028BC94()
{
	for (Rva0028BC94Module **m = m_244; *m; ++m)
	{
		void *found = (*m)->m_iface0C.v28();
		if (found)
			return found;
	}
	return 0;
}
class Rva005D99E9
{
public:
	Int rva005D99E9(Int unused, Object *obj);
};
Int Rva005D99E9::rva005D99E9(Int, Object *obj)
{
	if (!(obj->m_04->m_11A & 0x10) && obj->rva0028BC94())
		return 1;
	return 0;
}
