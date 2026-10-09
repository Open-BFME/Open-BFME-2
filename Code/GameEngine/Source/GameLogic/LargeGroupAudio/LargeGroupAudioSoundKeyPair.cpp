// cl: /O1 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// LargeGroupAudioSoundKeyPair subject bookkeeping (retail 0x00568920..0x00569863).
//
// Identity (target): WorldBuilder's LargeGroupAudioSoundKeyPair.cpp keeps these
// bodies in retail's order: 0x00568920 (0x0143F9F0) directly before
// setupDuckingTarget 0x00568939 (0x0143FA30), then updateSubject 0x00569628
// (0x014413B0), the unnamed 0x0056979A (0x01441A20) and 0x005697F7
// (0x01441AC0), and unregisterSubject 0x00569863 (0x01441BC0). The WorldBuilder
// asserts in unregisterSubject ("Less than zero units on LGAS grid set") read
// the total weight at +0x64; 0x005697F7 adds the same weight back, and the
// 0x003EDE44 worker dispatches the three subject callbacks. The two unnamed
// bodies keep address-derived method names.
// The subject's vtable slots (previous position, position, weight, keys) are
// read from these callers; the class names of the grid, ducking-slot and
// pending-add helpers stay address-derived.
// 0x00568920 and 0x00568939 moved here from their split-out unit: 0x00568939
// and 0x005697F7 keep THIS in ECX across the 0x00568920 call, which MSVC only
// does for a callee compiled earlier in the same unit.
// Shape notes: BFME 2's Coord2D has a user-declared destructor, which is what
// makes 0x0056979A's caller-side argument copy record its address (a copy
// constructor alone does not). WorldBuilder's 0x005697F7 stores the getKeys()
// result in a local before the overlap test; spelling it that way gives
// retail's register assignment (subject in ESI, THIS in EDI).
// The owning AudioMap destroys each key pair through 0x0056A061. Its
// WorldBuilder twin confirms the destructor identity; the native cleanup
// sequence independently establishes members at 0/C/10/14/20/40/4C/58.
// The first twelve bytes remain an opaque owning container: its destructor
// is the existing 0x003ED94F provider. Automatic member destruction preserves
// all eight retail EH states, including the throwing allocation free.
void __cdecl Rva00030830FreeAllocation(void *);
#include <cstdlib>
#define free Rva00030830FreeAllocation
#include <set>
#include <vector>
#undef free
#include "ascii_string.h"

class ModuleData;

// BFME 2's Coord2D (MathCoord2D.h), kept under the pair name the grid lookup
// 0x005C8176 is pinned with.
struct FloatPair
{
	FloatPair() {}
	FloatPair(const FloatPair &o) : x(o.x), y(o.y) {}
	~FloatPair() {}
	__forceinline bool isExactlyEqualTo(const FloatPair &o) const { return x == o.x && y == o.y; }
	float x;
	float y;
};

struct Rva00568FE4Key { float x; float y; unsigned short w; unsigned short pad; };
struct Rva00568FE4Less {
	bool operator()(const Rva00568FE4Key &a, const Rva00568FE4Key &b) const {
		if (a.x < b.x) return false;
		if (a.x > b.x) return true;
		if (a.y < b.y) return false;
		if (a.y > b.y) return true;
		return a.w < b.w;
	}
};
typedef _STL::multiset<Rva00568FE4Key, Rva00568FE4Less, _STL::allocator<Rva00568FE4Key> > Rva00568FE4Multi;

class Rva005C8176 { public: void *rva005C8176(FloatPair p); };
class LargeGroupAudioGridCell
{
public:
	void addToWeight(unsigned short weight);
	void subtractFromWeight(unsigned short weight);
};
class Rva00569543 { public: void rva005695F2(const ModuleData *m); };
class HostClass005C815B
{
public:
	void method_005C836F(int key, float value);
};

struct Rva00568939Elem
{
	char m_00[8];
	float m_08;
	int m_0c;
	bool m_10;
	char m_pad11[3];
};

class Rva00568920
{
public:
	bool rva00568920() const;
	void rva00568939(int key);
private:
	char m_pad[0x14];
	Rva00568939Elem *m_begin14;
	Rva00568939Elem *m_end18;
	char m_pad1C[0x10];
	union
	{
		int m_vals[4];
		HostClass005C815B *m_slots[4];
	};
};
class Rva0056887D
{
public:
	Rva0056887D &rva0056887D(const Rva0056887D &src, unsigned short w);
private:
	char m_storage[0xC];
};
struct Rva003CDDB0Range { bool method(const Rva003CDDB0Range *other); };

class LargeGroupAudioSubject
{
public:
	virtual FloatPair getPreviousPosition() = 0;
	virtual FloatPair getPosition() = 0;
	virtual void vslot08() = 0;
	virtual void vslot0C() = 0;
	virtual void vslot10() = 0;
	virtual void vslot14() = 0;
	virtual unsigned short getWeight() = 0;
	virtual const Rva003CDDB0Range *getKeys() = 0;
};

class Rva003ED94FDtor { public: ~Rva003ED94FDtor(); void *header; int flags; };
struct Rva0056A061KeyMap { char opaque[12]; ~Rva0056A061KeyMap(){reinterpret_cast<Rva003ED94FDtor *>(this)->Rva003ED94FDtor::~Rva003ED94FDtor();} };
class OpaqueRefCounted { public: void Release_Ref(); };
struct Rva0056A061Ref { OpaqueRefCounted *value; ~Rva0056A061Ref(){if(value)value->Release_Ref();} };
class Rva00569373 {public: void rva00569373(void *);};
class Rva00569393 {public: void rva005694CD();};
class Rva00568F04 {public: void rva00568F04(void *);};
struct BfmeStringRecord00568CE0 { char opaque00[12]; Rva00568F04 *subject; char opaque10[4]; ~BfmeStringRecord00568CE0(); };
class LargeGroupAudioSoundKeyPair
{
public:
 ~LargeGroupAudioSoundKeyPair();
 void rva0056979A(const FloatPair &pos, unsigned short weight);
 void rva005697F7(LargeGroupAudioSubject *subject);
 void unregisterSubject(LargeGroupAudioSubject *subject);
 void updateSubject(LargeGroupAudioSubject *subject);
private:
 Rva0056A061KeyMap m_keys;
 Rva0056A061Ref m_owner;
 AsciiString m_name;
 _STL::vector<BfmeStringRecord00568CE0> m_subjects;
 Rva00568FE4Multi m_pendingAdds;
 Rva005C8176 *m_grids[4];
 int unknown3C;
 _STL::vector<void *> m_v40;
 _STL::vector<void *> m_v4C;
 _STL::vector<void *> m_v58;
 int m_totalWeight;
};
LargeGroupAudioSoundKeyPair::~LargeGroupAudioSoundKeyPair(){
 reinterpret_cast<Rva00569373 *>(this)->rva00569373((void *)1);
 _STL::vector<BfmeStringRecord00568CE0> *v=&m_subjects;
 for(BfmeStringRecord00568CE0 *it=v->begin();it!=m_subjects.end();++it){if(it->subject)it->subject->rva00568F04(this);}
 reinterpret_cast<Rva00569393 *>(this)->rva005694CD();
}

bool Rva00568920::rva00568920() const
{
	for (int i = 0; i < 4; ++i)
		if (m_vals[i] == 0)
			return false;
	return true;
}

void Rva00568920::rva00568939(int key)
{
	if (!rva00568920())
		return;
	for (Rva00568939Elem *e = m_begin14; e != m_end18; ++e) {
		if (e->m_0c != key)
			continue;
		if (e->m_10)
			return;
		HostClass005C815B **slot = m_slots;
		for (int left = 4; left != 0; --left, ++slot) {
			if (*slot != 0) {
				float f = e->m_08;
				(*slot)->method_005C836F(key, f);
			}
		}
		e->m_10 = true;
		return;
	}
}

void LargeGroupAudioSoundKeyPair::updateSubject(LargeGroupAudioSubject *subject)
{
	if (!((Rva003CDDB0Range *)this)->method(subject->getKeys()))
		return;
	FloatPair oldPos = subject->getPreviousPosition();
	FloatPair newPos = subject->getPosition();
	if (oldPos.isExactlyEqualTo(newPos))
		return;
	unsigned short weight = subject->getWeight();
	if (((Rva00568920 *)this)->rva00568920())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (m_grids[i] != 0)
			{
				LargeGroupAudioGridCell *oldCell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(oldPos);
				LargeGroupAudioGridCell *newCell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(newPos);
				if (oldCell != newCell)
				{
					if (oldCell != 0)
					{
						oldCell->subtractFromWeight(weight);
						((Rva00569543 *)this)->rva005695F2((const ModuleData *)oldCell);
					}
					if (newCell != 0)
					{
						newCell->addToWeight(weight);
						((Rva00569543 *)this)->rva005695F2((const ModuleData *)newCell);
					}
				}
			}
		}
	}
	else
	{
		Rva00568FE4Key key;
		key.x = oldPos.x;
		key.y = oldPos.y;
		key.w = weight;
		Rva00568FE4Multi::iterator it = m_pendingAdds.find(key);
		if (it != m_pendingAdds.end())
			m_pendingAdds.erase(it);
		key.x = newPos.x;
		key.y = newPos.y;
		key.w = weight;
		m_pendingAdds.insert(key);
	}
}

void LargeGroupAudioSoundKeyPair::rva0056979A(const FloatPair &pos, unsigned short weight)
{
	for (int i = 0; i < 4; ++i)
	{
		if (m_grids[i] != 0)
		{
			LargeGroupAudioGridCell *cell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(pos);
			if (cell != 0)
			{
				cell->addToWeight(weight);
				((Rva00569543 *)this)->rva005695F2((const ModuleData *)cell);
			}
		}
	}
}

void LargeGroupAudioSoundKeyPair::rva005697F7(LargeGroupAudioSubject *subject)
{
	const Rva003CDDB0Range *keys = subject->getKeys();
	if (!((Rva003CDDB0Range *)this)->method(keys))
		return;
	FloatPair pos = subject->getPosition();
	unsigned short weight = subject->getWeight();
	m_totalWeight += weight;
	if (((Rva00568920 *)this)->rva00568920())
		rva0056979A(pos, weight);
	else
	{
		Rva0056887D record;
		m_pendingAdds.insert((const Rva00568FE4Key &)record.rva0056887D((const Rva0056887D &)pos, weight));
	}
}

void LargeGroupAudioSoundKeyPair::unregisterSubject(LargeGroupAudioSubject *subject)
{
	if (!((Rva003CDDB0Range *)this)->method(subject->getKeys()))
		return;
	FloatPair pos = subject->getPreviousPosition();
	unsigned short weight = subject->getWeight();
	m_totalWeight -= weight;
	if (((Rva00568920 *)this)->rva00568920())
	{
		for (int i = 0; i < 4; ++i)
		{
			if (m_grids[i] != 0)
			{
				LargeGroupAudioGridCell *cell = (LargeGroupAudioGridCell *)m_grids[i]->rva005C8176(pos);
				if (cell != 0)
				{
					cell->subtractFromWeight(weight);
					((Rva00569543 *)this)->rva005695F2((const ModuleData *)cell);
				}
			}
		}
	}
	else
	{
		Rva00568FE4Key key;
		key.x = pos.x;
		key.y = pos.y;
		key.w = weight;
		Rva00568FE4Multi::iterator it = m_pendingAdds.find(key);
		if (it != m_pendingAdds.end())
			m_pendingAdds.erase(it);
	}
}
