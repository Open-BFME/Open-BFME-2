// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// ?rva003B0869@Rva003B0401@@UAEXHH@Z, retail 0x003B0869..0x003B0C9F (1078B),
// thiscall ret 8; slot 9 of the particle storage module vtable 0x0081DA10
// (slot 0 is the rowed ??_GRva003B0401 0x003B084D, slot 2 its name getter).
//
// Emits up to `count` rounds of storage-module particles: under the DX8
// thread lock, with the module's vertex buffer (+0x1C) locked, every cell of
// TheTriggerManager's map (+0x84) rolls against the particle system's emit
// chance; a cell that passes and is not shrouded for the local player takes
// the lowest free slot (min-heap at +0x34), queues its expiry time in the
// queue at +0x24 and writes the slot's four quad vertices (position, life,
// velocity, birth time, random spin 0..15 and corner index 0..3). The run
// stops once the free slots are exhausted.
//
// Evidence (target): WorldBuilder twin 0x00FAA520 in fxpsstoragemodule.cpp
// (random rolls at lines 411 and 432); callees are rowed or pinned under the
// spellings used here (several are still address-derived views:
// Rva001F553F, Rva003AFA0BVector, Rva003B0412/PrereqUnitRec, Rva002872BA).
//
// Codegen (from the bytes): the particle-system handle falls back to
// Make001FCBD7 through a conditional expression; the cell position is set
// through a three-argument setter (height, then y, then x evaluated) and the
// jitter added through Coord3D-style add; the time base divides by 1000.0f
// (emitted as the 0.001 multiply).

#include "Coord3D.h"
#include "../../../Common/PartitionRangeQueryCallView.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector
{
public:
	bool empty() const { return _M_start == _M_finish; }
	const T &front() const { return *_M_start; }
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T> struct greater
{
};
template <class T, class S, class C> class priority_queue
{
public:
	bool empty() const { return c.empty(); }
	const T &top() const { return c.front(); }
	void pop();
protected:
	S c;
	C comp;
};

struct _Rb_tree_node_base
{
	char _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class _Dummy> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}
typedef _STL::priority_queue<int, _STL::vector<int, _STL::allocator<int> >, _STL::greater<int> > FreeSlotQueue;

// TheTriggerManager's cell map at +0x84: nodes carry the cell coordinate at
// +0x18 / +0x1C.
struct Rva003B0869CellNode : public _STL::_Rb_tree_node_base
{
	unsigned char m_key[8];
	Int x;						// +0x18
	Int y;						// +0x1C
};
struct Rva003B0869CellIterator
{
	Rva003B0869CellIterator(_STL::_Rb_tree_node_base *node) : _M_node(node) {}
	bool operator!=(const Rva003B0869CellIterator &other) const { return _M_node != other._M_node; }
	void operator++() { _M_node = _STL::_Rb_global<bool>::_M_increment(_M_node); }
	_STL::_Rb_tree_node_base *_M_node;
};
class Rva003B0869CellMap
{
public:
	UnsignedInt size() const { return m_count; }
	Rva003B0869CellIterator begin() const { return Rva003B0869CellIterator(m_header->_M_left); }
	Rva003B0869CellIterator end() const { return Rva003B0869CellIterator(m_header); }
private:
	_STL::_Rb_tree_node_base *m_header;
	UnsignedInt m_count;
};
class Rva002872BA
{
public:
	unsigned char m_pad[0x84];
	Rva003B0869CellMap m_cells;			// +0x84
 unsigned char pad8C[4];
 unsigned count90;
};
extern Rva002872BA *TheTriggerManager;

class GameClient;
extern GameClient *TheGameClient;

class TerrainLogic
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);	// slot 6
};
extern TerrainLogic *TheTerrainLogic;

extern PartitionManager *TheShroudManager;

class Player
{
public:
	// Preserve the native +0x54 inline read without an external getter copy.
	__declspec(dllimport) __forceinline Int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_pad[0x54];
	Int m_playerIndex;				// +0x54
};
class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }
private:
	unsigned char m_pad[0x10];
	Player *m_local;				// +0x10
};
extern PlayerList *ThePlayerList;

class WW3D
{
public:
	static UnsignedInt Get_Sync_Time() { return SyncTime; }
private:
	static UnsignedInt SyncTime;
};
extern Int g_009BA4E8;

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertex_buffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array() { return Vertices; }
	private:
		VertexBufferClass *VertexBuffer;
		void *Vertices;
		int m_08;
	};
 // Same12B lock ABI; the native append cleanup uses the owned WriteLock destructor.
 // The dtor is declared, not defined: retail folds ??1AppendLockClass onto
 // ??1WriteLockClass at 0x00139530 (pin 2998), so this unit emits no copy
 // of its own. Emitting the implicit derived dtor produced a short thunk
 // the link kept ahead of the folded body (S ??1AppendLockClass). The
 // stack lock in AddParticle below calls the same mangled name either way.
 class AppendLockClass : public WriteLockClass { public: AppendLockClass(VertexBufferClass*, unsigned, unsigned, int); ~AppendLockClass(); };

};

class GameClientRandomVariable
{
public:
	Real getValue() const;
};

struct Rva003AFA0BVector
{
	Real x;
	Real y;
	Real z;
};

class ParticleSystem
{
public:
	unsigned rva001F3C6B();
 Rva003AFA0BVector rva001F54C5(const Rva003AFA0BVector *pos);
	const GameClientRandomVariable &getLifetime() const { return *(const GameClientRandomVariable *)m_lifetime; }
private:
	unsigned char m_pad00[0xc];
 int type0C;
 unsigned char gap10[4];
	unsigned char m_lifetime[0x14];		// +0x14
};
ParticleSystem *Make001FCBD7();

class Rva001F553F
{
public:
	Real rva001F5445();
	Coord3D *rva001F553F(Coord3D *result, UnsignedInt a, UnsignedInt b);
};

class BfmeParticleSystemPtr
{
public:
	operator ParticleSystem *() const { return target; }
	bool isValid() const { return target != 0; }
	ParticleSystem *operator->() const
	{
		return target ? target : Make001FCBD7();
	}
private:
	ParticleSystem *target;
};

struct PrereqUnitRec
{
	Real time;
	Int slot;
	Int unused;
};
struct Rva003AFD22Node;
struct Rva003B02F4Entry { Real time; Int slot; Rva003AFD22Node *node; };
struct Rva003B02F4Greater {};
typedef _STL::priority_queue<Rva003B02F4Entry, _STL::vector<Rva003B02F4Entry, _STL::allocator<Rva003B02F4Entry> >, Rva003B02F4Greater> ExpiryQueue;
class Rva003B0412 : public ExpiryQueue { public:void rva003B0412(const PrereqUnitRec*); };
class ModuleData;
class Rva003B0433 : public FreeSlotQueue { public:void rva003B0433(const ModuleData*&); };


struct Rva003B0869Vertex
{
	Coord3D pos;					// +0x00
	Real lifetime;					// +0x0C
	Rva003AFA0BVector velocity;			// +0x10
	Real birth;					// +0x1C
	Real spin;					// +0x20
	Real corner;					// +0x24
};

class DX8ThreadLock
{
public:
	DX8ThreadLock() { BFME_DX8_Thread_Lock(); }
	~DX8ThreadLock() { BFME_DX8_Thread_Assert(); }
};

class Rva003B0401
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
	virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
	virtual void rva003B0869(Int unused, Int count);	// slot 9
private:
	BfmeParticleSystemPtr m_system;			// +0x04
	unsigned char m_pad08[0x1C - 0x08];
	VertexBufferClass *m_vertexBuffer;		// +0x1C
	unsigned char m_pad20[0x24 - 0x20];
	Rva003B0412 m_expiry;				// +0x24
	FreeSlotQueue m_freeSlots;			// +0x34
};

static __forceinline void setCoord(Coord3D &c, Real x, Real y, Real z)
{
	c.x = x;
	c.y = y;
	c.z = z;
}

static __forceinline void addCoord(Coord3D &c, const Coord3D *a)
{
	c.x += a->x;
	c.y += a->y;
	c.z += a->z;
}

static __forceinline void writeVertex(Rva003B0869Vertex *v, const Coord3D &pos, Real lifetime,
	const Rva003AFA0BVector &velocity, Real birth, Real spin, Real corner)
{
	v->pos.x = pos.x;
	v->pos.y = pos.y;
	v->pos.z = pos.z;
	v->lifetime = lifetime;
	v->velocity.x = velocity.x;
	v->velocity.y = velocity.y;
	v->velocity.z = velocity.z;
	v->birth = birth;
	v->spin = spin;
	v->corner = corner;
}

void Rva003B0401::rva003B0869(Int unused, Int count)
{
	if (!m_system.isValid() || !TheTriggerManager || !TheTerrainLogic || !TheGameClient)
		return;

	DX8ThreadLock threadLock;

	Rva003B0869CellMap *cells = &TheTriggerManager->m_cells;
	if (cells->size() > 0)
	{
		Real now = (Real)(WW3D::Get_Sync_Time() * g_009BA4E8) / 1000.0f;
		VertexBufferClass::WriteLockClass lock(m_vertexBuffer, 0);
		Rva003B0869Vertex *verts = (Rva003B0869Vertex *)lock.Get_Vertex_Array();
		Int localPlayer = ThePlayerList ? ThePlayerList->getLocalPlayer()->getPlayerIndex() : 0;

		for (Int i = 0; i < count; i++)
		{
			if (m_freeSlots.empty())
				break;
			for (Rva003B0869CellIterator it = cells->begin(); it != cells->end(); ++it)
			{
				if (m_freeSlots.empty())
					break;
				if (GetGameClientRandomValueReal(0.0f, 1.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsstoragemodule.cpp", 411)
					> ((Rva001F553F *)m_system.operator->())->rva001F5445())
					continue;

				const Rva003B0869CellNode *cell = (const Rva003B0869CellNode *)it._M_node;
				Coord3D pos;
				setCoord(pos, (Real)cell->x, (Real)cell->y, TheTerrainLogic->getGroundHeight((Real)cell->x, (Real)cell->y, 0));
				Coord3D offset;
				const Coord3D *jitter = ((Rva001F553F *)m_system.operator->())->rva001F553F(&offset, 0, 1);
				addCoord(pos, jitter);

				if (!TheShroudManager || TheShroudManager->getShroudStatusForPlayer(localPlayer, &pos) != 0)
					continue;

				Rva003AFA0BVector velocity = m_system->rva001F54C5((const Rva003AFA0BVector *)&pos);
				UnsignedInt lifetime = (UnsignedInt)m_system->getLifetime().getValue();
				Int slot = m_freeSlots.top();
				m_freeSlots.pop();

				PrereqUnitRec rec;
				rec.slot = slot;
				rec.time = (Real)lifetime + now;
				rec.unused = 0;
				m_expiry.rva003B0412(&rec);

				Real spin = GetGameClientRandomValueReal(0.0f, 15.0f, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsstoragemodule.cpp", 432);
				Rva003B0869Vertex *v = &verts[slot * 4];
				writeVertex(v, pos, (Real)lifetime, velocity, now, spin, 0.0f);
				v++;
				writeVertex(v, pos, (Real)lifetime, velocity, now, spin, 1.0f);
				v++;
				writeVertex(v, pos, (Real)lifetime, velocity, now, spin, 2.0f);
				v++;
				writeVertex(v, pos, (Real)lifetime, velocity, now, spin, 3.0f);
			}
		}
	}
}

// WB FA9D70 names FXParticleSystem::GPUParticleSystemStorageModule::AddParticle.
// Native3B0578..3B07B8 full576 RET4; C1D9B0 GPUParticle and C1DA10 TerrainFire
// slot5 both select it. Slot2 C1D9B0 selects the owned GPUParticle name getter.
// The owned1078B sibling above supplies the time/expiry/quad-writing pattern;
// native evidence independently gives particle vel10/pos1C/lifetime34/linked74,
// module vertexBuffer1C/expiry24/freeSlots34, and the random call's line286.
// Particle and base-storage names stay neutral; PrereqUnitRec is an existing
//12B ABI carrier, with its third word carrying the particle pointer here.
// Append's cleanup uses the native shared113B WriteLock destructor. The
// inheritance below is a layout/lifetime view, not an original hierarchy claim.
struct Rva003AFD22Node { virtual ~Rva003AFD22Node();char pad04[0x10-4];Rva003AFA0BVector vel;Coord3D pos;char gap28[0x34-0x28];unsigned life34;char gap38[0x74-0x38];bool linked74; };
// Native common storage API prefix: vptr plus through1B. C1D950 slot5
// binds the existing58B list-attachment body. The original base name remains
// unknown; its use as a C++ base is a structural view, not a recovered name.
class Rva003AFD22 {public:
 virtual void slot00();virtual void slot01();virtual void slot02();virtual void slot03();virtual void slot04();
 virtual void AddParticle(Rva003AFD22Node*);
 virtual void slot06();virtual void slot07();virtual void slot08();virtual void slot09();virtual void rva003B07B8();
 void rva003AFD22(Rva003AFD22Node*);char prefix[0x1c-4];};
namespace FXParticleSystem {
class GPUParticleSystemStorageModule : public Rva003AFD22 {public:virtual void AddParticle(Rva003AFD22Node*);virtual void rva003B07B8();VertexBufferClass*vb1C;int unused20;Rva003B0412 expiry24;Rva003B0433 slots34;};
void GPUParticleSystemStorageModule::AddParticle(Rva003AFD22Node*p){
 if(slots34.empty()||p->linked74)return;
 DX8ThreadLock threadLock;
 rva003AFD22(p);
 int slot=slots34.top();slots34.pop();
 PrereqUnitRec rec;rec.slot=slot;rec.time=(Real)(WW3D::Get_Sync_Time()*g_009BA4E8)/1000.0f+(Real)p->life34;rec.unused=(Int)p;
 expiry24.rva003B0412(&rec);
 VertexBufferClass::AppendLockClass lock(vb1C,slot*4,4,0);
 Rva003B0869Vertex*v=(Rva003B0869Vertex*)lock.Get_Vertex_Array();
 Real birth=(Real)(WW3D::Get_Sync_Time()*g_009BA4E8)/1000.0f;
 Real life=(Real)p->life34;
 Real spin=GetGameClientRandomValueReal(0.0f,15.0f,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsstoragemodule.cpp",286);
 writeVertex(v,p->pos,life,p->vel,birth,spin,0.0f);++v;
 writeVertex(v,p->pos,life,p->vel,birth,spin,1.0f);++v;
 writeVertex(v,p->pos,life,p->vel,birth,spin,2.0f);++v;
 writeVertex(v,p->pos,life,p->vel,birth,spin,3.0f);
}
}

// Native3B07B8..3B0835 full125 RET0; WB FAA340 unnamed, GPUParticle and
// TerrainFire storage vtables both select slot10. Expired12B records contain
// float time plus integer slot plus virtual-dtor particle pointer. ::delete
// reproduces flag0 virtual destruction followed by the owned global delete.
// The legacy33B push API spells its four-byte input as ModuleData*: the value
// here is explicitly an integer-bit carrier, never a dereferenced pointer.
// Original update name is unknown. The slot-valued pointer PHI delays the
// slot spill until after the particle null test, as the native body does.
namespace FXParticleSystem {
void GPUParticleSystemStorageModule::rva003B07B8(){
 Real now=(Real)(WW3D::Get_Sync_Time()*g_009BA4E8)/1000.0f;
 while(!expiry24.empty()){
  const Rva003B02F4Entry&r=expiry24.top();
  if(!(now>r.time))break;
  Rva003AFD22Node*node=(r.slot?r.node:r.node);const ModuleData*word=(const ModuleData*)r.slot;::delete node;
  expiry24.pop();slots34.rva003B0433(word);
 }
}
}

// Native 1F3C6B..1F3C9A RET0; WB B11AF0 leaves the method unnamed.
// Storage ctor3B0454 invokes this on its particle-system handle. Type8
// selects the TriggerManager +90 count; the count meaning remains unproven.
// Reuse the home global owner instead of the old conflicting data aliases.
unsigned ParticleSystem::rva001F3C6B(){ unsigned result=128; if(type0C==8&&TheTriggerManager){unsigned n=3*TheTriggerManager->count90;if(n>0){if(n>2048)n=2048;result=n;}}return result;}
