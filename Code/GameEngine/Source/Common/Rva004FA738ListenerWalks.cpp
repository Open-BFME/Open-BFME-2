// cl: /O1 /DNDEBUG /MD /EHsc
// stlport

// The 0x004FA9B1 family needs _STL::vector<ObjectID> (member at
// +0x14 plus the rowed vector<ObjectID>::erase at 0x0025BF5D).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
//
// Listener-list walks around 0x004FA738.  Each list's forEach packs a vcall
// member-function pointer and its arguments into a stack call record and
// passes it by reference to an EH-guarded walk.  The walk latches the list's
// index at +0x0C with Zero Hour's LatchRestore (Common/LatchRestore.h; retail
// ctor 0x0027EA63, dtor 0x0027EA82, vtable 0x00BFB1CC for a 4-byte type),
// publishes the index before each call and re-reads it after, so a nested
// broadcast that latches the index to 0 for its own pass leaves this pass to
// resume where it was.  The shape is the one recovered byte for byte in
// Rva00308AA4Notifiers.cpp.
//
//   forEach     walk        arguments
//   0x004FA935  0x004FA738  1
//   0x004FA953  0x004FA7A5  2
//   0x004FC320  0x004FC2B3  1
//
// Identity is not recovered: lists and listeners are named after their
// forEach address, records after their walk address, and the argument types
// are inferred from their size only.

template <typename T>
class LatchRestore
{
protected:
	T valueToRestore;
	T &whereToRestore;

public:
	LatchRestore(T &dest, const T &src) : whereToRestore(dest)
	{
		valueToRestore = dest;
		dest = src;
	}

	virtual ~LatchRestore()
	{
		whereToRestore = valueToRestore;
	}
};

// ---- forEach 0x004FA935, walk 0x004FA738
class Rva004FA935Listener
{
public:
	virtual void notify(void *);
};

struct Rva004FA738Call
{
	void (Rva004FA935Listener::*notify)(void *);
	void *arg;
};

class Rva004FA935List
{
public:
	void forEach(void (Rva004FA935Listener::*notify)(void *), void *arg);
	void apply(const Rva004FA738Call &call);

private:
	Rva004FA935Listener **m_begin;		// +0x00
	Rva004FA935Listener **m_end;		// +0x04
	Rva004FA935Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FA935List::forEach(void (Rva004FA935Listener::*notify)(void *), void *arg)
{
	Rva004FA738Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva004FA935List::apply(const Rva004FA738Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg);
		i = m_index;
	}
}

// ---- forEach 0x004FA953, walk 0x004FA7A5
class Rva004FA953Listener
{
public:
	virtual void notify(void *, int);
};

struct Rva004FA7A5Call
{
	void (Rva004FA953Listener::*notify)(void *, int);
	void *arg;
	int value;
};

class Rva004FA953List
{
public:
	void forEach(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);
	void apply(const Rva004FA7A5Call &call);

private:
	Rva004FA953Listener **m_begin;		// +0x00
	Rva004FA953Listener **m_end;		// +0x04
	Rva004FA953Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FA953List::forEach(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value)
{
	Rva004FA7A5Call call;
	call.notify = notify;
	call.arg = arg;
	call.value = value;
	apply(call);
}

void Rva004FA953List::apply(const Rva004FA7A5Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg, call.value);
		i = m_index;
	}
}

// ---- forEach 0x004FC320, walk 0x004FC2B3
class Rva004FC320Listener
{
public:
	virtual void notify(void *);
};

struct Rva004FC2B3Call
{
	void (Rva004FC320Listener::*notify)(void *);
	void *arg;
};

class Rva004FC320List
{
public:
	void forEach(void (Rva004FC320Listener::*notify)(void *), void *arg);
	void apply(const Rva004FC2B3Call &call);

private:
	Rva004FC320Listener **m_begin;		// +0x00
	Rva004FC320Listener **m_end;		// +0x04
	Rva004FC320Listener **m_capacity;	// +0x08
	unsigned int m_index;	// +0x0C
};

void Rva004FC320List::forEach(void (Rva004FC320Listener::*notify)(void *), void *arg)
{
	Rva004FC2B3Call call;
	call.notify = notify;
	call.arg = arg;
	apply(call);
}

void Rva004FC320List::apply(const Rva004FC2B3Call &call)
{
	unsigned int i = 0;
	LatchRestore<unsigned int> latch(m_index, i);
	while (i < (unsigned int)(m_end - m_begin))
	{
		m_index++;
		(m_begin[i]->*call.notify)(call.arg);
		i = m_index;
	}
}

// ---- dual broadcast 0x004FA992: two-argument twin of 0x004FA978
enum ObjectID { INVALID_ID = 0 };

namespace _STL
{
// Declare the rowed vector specializations so this TU calls them without
// emitting second definitions: erase on vector<ObjectID> (0x0025BF5D),
template <> ObjectID *vector<ObjectID, allocator<ObjectID> >::erase(ObjectID *);
}

class Rva004E3184;
struct Arg54;

class Rva002B2672
{
public:
	bool rva002B2672(Arg54 *a, Arg54 *b);
};

class Rva002E2903Player;

class LivingWorldBuildingNuggetSpawnArmy
{
public:
	Rva002E2903Player *getOwningPlayer();
};

class Rva004FA659
{
public:
	void rva004FA659();
};

class Rva004FAA81Owner;

class Rva004FA992
{
public:
	void rva004FA992(void (Rva004FA953Listener::*notify)(void *, int), void *arg, int value);
};

class Rva004FA992Owner
{
	friend class Rva004FAA81Owner;
public:
	virtual void v00();	// slot 0 (unrecovered; declared only)
	virtual void v01();	// slot 1 (unrecovered; declared only)
	virtual void v02();	// slot 2 (unrecovered; declared only)
	virtual void v03();	// slot 3 (unrecovered; declared only)
	virtual bool checkId(ObjectID id, Rva004E3184 *ctx);	// slot 4 (name unrecovered; declared only)
	virtual void v05();	// slot 5 (unrecovered; declared only)
	virtual void v06();	// slot 6 (unrecovered; declared only)
	virtual bool v07(int p);	// slot 7: gate on the int param (name unrecovered; declared only)
		void rva004FA9B1(int index);

private:
	// +0x00 vptr (was modelled as int m_00 before the slot-4 virtual call
	// in 0x004FA9B1 proved the owner polymorphic; broadcast only touches
	// +0x04 so its bytes are unchanged by the remodel).
	Rva004FA953List m_list;	// +0x04
	_STL::vector<ObjectID> m_ids;	// +0x14
	int m_20;	// +0x20
};

// ---- owner method 0x004FA9B1 (208B): indexed notify with a LivingWorld
// player find, a guarded ModuleData refresh, vector erase and the hardcoded
// channel broadcast to 0x004FA992.
extern Rva002B2672 *g_Va00DFEF10;
Rva002B2672 *g_Va00DFEF10;

class Rva004E3184
{
	friend class Rva004FAA81Owner;
public:
	Rva004E3184(int v);
	virtual ~Rva004E3184();

private:
	// Mostly size-only view (0x58B total with the vptr): the real layout
	// (Snapshot base plus AsciiStrings plus vector) is owned by
	// Rva004E3184Dtor.cpp, whose view stops at m_50, but the int-ctor
	// 0x004E30D5 stores through +0x55. Only +0x48 is named: the int-ctor
	// sets it to 1 and 0x004FAA81 uses it as its retry loop bound.
	char m_pad44[0x44];
	int m_48;	// +0x48
	char m_pad4C[0x0C];
};

class Rva002E2903Player
{
public:
	void rva002E0764(Rva004E3184 *ctx);
	bool rva002E112A(Rva004E3184 *ctx);
	void rva002E074E(Rva004E3184 *ctx);
};

struct Rva003F0F13Elem
{
	float a;
	float b;
};

class Rva003F0F13
{
public:
	void rva003F0F13(Rva003F0F13Elem *out);
	bool rva003F0259(Rva004E3184 *ctx);
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int id, unsigned int *index);
	int rva002B65B7(Rva004E3184 *ctx, Rva002E2903Player *player, int v);
};

struct Rva004FAA81Target
{
	char m_pad[0x13C];
	int id;	// +0x13C LivingWorld id (cf rowed 0x004E0705Find)
};

struct Rva004FAA81Link
{
	char m_pad[0x24];
	Rva004FAA81Target *target;	// +0x24
};

class Rva004FAA81Owner
{
public:
	void rva004FAA81();

private:
	int m_00;	// +0x00 (unread)
	Rva004FAA81Link *m_link;	// +0x04
	int m_08;	// +0x08 (unread)
	Rva004FA992Owner m_owner;	// +0x0C
};

typedef void (Rva004FA953Listener::*Rva004FA953Notify)(void *, int);

void Rva004FA992Owner::rva004FA9B1(int index)
{
	// Hardcoded dispatch-table channel: the value 0x009CB260 (a runtime-filled
	// .data table of code addresses, called through by the 0x004FA7A5 walk)
	// flows into the member-pointer slot. MSVC has no int-to-member-pointer
	// conversion, so the constant is punned through the local and propagated
	// into the push.
	Rva004FA953Notify notify;
	*(int *)&notify = 0x009CB260;
	if (index < 0)
		return;
	if ((unsigned int)index >= m_ids.size())
		return;
	if (!g_Va00DFEF10->rva002B2672((Arg54 *)((char *)this - 12), (Arg54 *)index))
		return;
	if (!index)
		m_20 &= index;
	ObjectID *elem = &m_ids[index];
	Rva002E2903Player *player = ((LivingWorldBuildingNuggetSpawnArmy *)((char *)this - 12))->getOwningPlayer();
	if (player)
	{
		Rva004E3184 tmp(0);
		if (checkId(*elem, &tmp))
			player->rva002E0764(&tmp);
	}
	m_ids.erase(elem);
	((Rva004FA659 *)((char *)this - 12))->rva004FA659();
	((Rva004FA992 *)this)->rva004FA992(notify, ((char *)this - 12) ? this : 0, index);
}
