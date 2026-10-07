// flags: region default (reverse/retail_inventory/flag_regions.csv)
// cl: /EHs-c- /ICode/Libraries/Include
// Four adjust-call-echo members (19B each): push [esp+4], add ecx, -N,
// call <run>, mov eax, [esp+4], ret 4. Each runs its argument through the
// adjusted object at this-N, then returns the argument itself. /O1 keeps
// both argument reads on the stack slot (/O2 caches it in esi).
// 0x0030BEE6 (-0x28 -> 0x0053863E), 0x0030BEF9 (-0x28 -> 0x00538674),
// 0x00330C0F (-0x3C -> 0x0007E03A), 0x00330C22 (-0x3C -> 0x002E3876).
// Callee identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

#include <new>
#include "Lib/Coord3D.h"

enum ObjectID { Rva0053863EObjectID = 0 };

// Local layout view for the already pinned 16-byte conversion constructor.
// Its body is external at 0x0004254E; retail supplies the call, not the type.
namespace _STL
{
template <class T1, class T2> struct pair
{
	template <class U1, class U2>
	pair(const pair<U1, U2> &other);
	T1 first;
	T2 second;
};
}

class Rva0053863ESub
{
public:
	int run(int value);
	void rva0053856F();

private:
	typedef _STL::pair<const ObjectID, Coord3D> CachedValue;
	typedef _STL::pair<ObjectID, Coord3D> OutputValue;
	CachedValue *m_begin;
	CachedValue *m_finish;
	CachedValue *m_end;
	CachedValue m_cached;
	float m_cachedScale;
	unsigned char m_refresh;
};

struct Rva00538674Point
{
	Rva00538674Point() {}
	__forceinline Rva00538674Point(const Rva00538674Point &that)
	{
		x = that.x;
		y = that.y;
	}
	float x, y;
};

class Rva00538674Sub
{
public:
	Rva00538674Point *run(Rva00538674Point *output);
private:
	char m_pad00[0x0C];
	float m_xMin, m_yMin, m_xMax, m_yMax;
	float m_pad1C;
	unsigned char m_dirty;
};

class Rva0007E03ASub
{
public:
	void run(int value);
};

class Rva002E3876Sub
{
public:
	void run(int value);
};

class Rva0030BEE6Owner
{
public:
	int fwd(int value);
};

class Rva0030BEF9Owner
{
public:
	int fwd(int value);
};

class Rva00330C0FOwner
{
public:
	int fwd(int value);
};

class Rva00330C22Owner
{
public:
	int fwd(int value);
};

int Rva0030BEE6Owner::fwd(int value)
{
	((Rva0053863ESub *)((char *)this - 0x28))->run(value);
	return value;
}

int Rva0030BEF9Owner::fwd(int value)
{
	((Rva00538674Sub *)((char *)this - 0x28))->run(
		reinterpret_cast<Rva00538674Point *>(value));
	return value;
}

// Native 538674..5386B7 returns the midpoint of the four floats at C..18.
// Its same-object refresh call uses the existing helper at 53856F; owner and
// original value-type identity are unknown. The caller supplies return storage.
Rva00538674Point *Rva00538674Sub::run(Rva00538674Point *output)
{
	__assume(output != 0);
	if (m_dirty)
		reinterpret_cast<Rva0053863ESub *>(this)->rva0053856F();
	Rva00538674Point result;
	result.x = (m_xMax + m_xMin) * 0.5f;
	result.y = (m_yMax + m_yMin) * 0.5f;
	::new (output) Rva00538674Point(result);
	return output;
}

int Rva00330C0FOwner::fwd(int value)
{
	((Rva0007E03ASub *)((char *)this - 0x3C))->run(value);
	return value;
}

int Rva00330C22Owner::fwd(int value)
{
	((Rva002E3876Sub *)((char *)this - 0x3C))->run(value);
	return value;
}

// Target evidence: 0x0053863E is a 35B Ghidra function. It checks the byte at
// this+0x20, calls 0x0053856F with the same this when set, then copies 16 bytes
// from this+0x0C to the caller's output address through 0x0004254E. The caller
// at 0x0030BEE6 passes this 32-bit value through and ignores the callee result.
// The 16-byte pair type below is only a codegen path to the existing folded
// copy-constructor pin; the retail payload's true type is not established.
// The 32-bit EAX return is established by the final stack load; its semantic
// type is unknown. The caller at 0x0030BEE6 ignores it.
// The helper name is address-derived. Its same-object relation is established
// by the direct call and the helper's accesses to +0x0C and +0x20.
// ?run@Rva0053863ESub@@QAEHH@Z
int Rva0053863ESub::run(int outputAddress)
{
	__assume(outputAddress != 0);
	if (m_refresh)
		rva0053856F();
	OutputValue &output = *reinterpret_cast<OutputValue *>(outputAddress);
	::new (&output) OutputValue(m_cached);
	return outputAddress;
}
