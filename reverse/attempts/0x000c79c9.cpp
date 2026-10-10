// ??1W3DScriptedModelDraw@@UAE@XZ
// partial score=0.9907873709670453 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x000C0DD8
// Bank507: native C79C9..C7BC4 destructor with constructor-proven layout.
// Constructor evidence originally: 1065 bytes. W3DScriptedModelDraw (Thing* ModuleData*) constructor: called
// by W3DScriptedModelDraw::friend_newModuleInstance (0x0006489B) and as the
// base of the Truck/Tank/Supply/Sail/Quadruped/Horde draw ctors.
// Evidence (target): DrawModule base ctor 0x000B19A1 then the two interface
// vptrs at +0x0C/+0x10 and the three final vptrs; member construction order
// and EH states 1..0x12 agree with the destructor 0x000C79C9's unwind order
// (handle +0x1C; vector +0x38; AsciiString +0x54; list +0x64 via 0x00453ADD;
// vectors +0x68/+0x74; set +0xA8 via 0x000D3A71; AsciiString +0xB4; six
// 12-byte vectors +0xC8 via ??_L; three 0x1C entries +0x110 via ??_H;
// vectors +0x164/+0x170; 76-byte bulk-zero member +0x17C via 0x00042526;
// RadiusDecal/RadiusDecalTemplate pairs +0x1D0/+0x1E0 and +0x218/+0x228;
// AsciiString +0x260 and [2] +0x264; Matrix3D +0x290; AsciiString +0x2E4).
// Body stores follow the WorldBuilder twin 0x00927900 (same fields and
// order; BFME2 drops its +0x280 copy and its extra drawable call): reset
// fields; clear the three strings; copy three ModuleData fields (+0x139
// +0x13C +0x140) to the drawable (+0xE4 +0xE8 +0xEC); take the drawable's
// transform (getTransformMatrix 0x0027628E) or identity; +0xBC from
// 0x000B2BA3. Field names are not asserted.

#include "ascii_string.h"
#include "Common/Snapshot.h"

class Thing;
class ModuleData;
class ObjectCreationList;
struct Rva00B6CF1 {~Rva00B6CF1();};
struct BfmeStringRecord000B757D {unsigned word0,word1;AsciiString text;unsigned word2;unsigned char tail0;__declspec(noinline) ~BfmeStringRecord000B757D();};
BfmeStringRecord000B757D::~BfmeStringRecord000B757D(){}
void __cdecl free(void*);
struct Rva000B2BE5Src;

class Rva000BB694 {public:~Rva000BB694();};
namespace _STL {
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T> class char_traits;
template <class C, class Tr, class A> class basic_string;
template <class T> struct less;

template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a) throw();
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};

template <class T, class A = allocator<T> > class vector : public _Vector_base<int, allocator<int> >
{
public:
	vector(const allocator<int> &a = allocator<int>()) : _Vector_base<int, allocator<int> >(a) {}
	~vector();
 T*begin(){return (T*)_M_start;}T*end(){return (T*)_M_finish;}T*erase(T*,T*);void clear(){erase(begin(),end());}
};

template <> class vector<const ObjectCreationList *, allocator<const ObjectCreationList *> >
	: public _Vector_base<int, allocator<int> >
{
public:
	vector(const allocator<const ObjectCreationList *> &a = allocator<const ObjectCreationList *>());
	~vector();
};

template <class T, class A> class _List_base
{
public:
	_List_base(const A &a);
 struct Node {Node*next,*prev;T data;};
 __declspec(noinline) void _M_clear(){Node*cur=_M_node->next;while(cur!=_M_node){Node*old=cur;cur=cur->next;old->data.~T();free(old);}_M_node->next=_M_node;_M_node->prev=_M_node;}
 ~_List_base(){_M_clear();if(_M_node)free(_M_node);}
 Node*_M_node;
};

template <class T, class A = allocator<T> > class list : public _List_base<T, A>
{
public:
	list(const A &a = A()) : _List_base<T, A>(a) {}
};

template <class K, class C, class A> class set
{
public:
	set();
	~set(){((Rva000BB694*)this)->~Rva000BB694();}
private:
	void *m_tree[3];
};
}

// Pointer-chain handle at +0x1C: unlinked through 0x0004CBC0 when set.
class ParticleSystem;
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_previous;
	void *m_next;
};

class ParticleSystem {public:char pad[0x9C];BfmeParticleSystemHandle*first,*last;};
inline BfmeParticleSystemHandle::~BfmeParticleSystemHandle(){if(m_previous)((BfmeParticleSystemHandle*)m_previous)->m_next=m_next;else ((ParticleSystem*)m_system)->first=(BfmeParticleSystemHandle*)m_next;if(m_next)((BfmeParticleSystemHandle*)m_next)->m_previous=m_previous;else ((ParticleSystem*)m_system)->last=(BfmeParticleSystemHandle*)m_previous;m_previous=0;m_next=0;}
struct W3DScriptedModelDrawHandle
{
	W3DScriptedModelDrawHandle() : m_system(0), m_previous(0), m_next(0) {}
	~W3DScriptedModelDrawHandle()
	{
		if (m_system != 0)
			((BfmeParticleSystemHandle *)this)->~BfmeParticleSystemHandle();
	}
	void *m_system;
	void *m_previous;
	void *m_next;
};

// Packed word at +0x28 (3/27/1 bit fields, top bit kept) and three words.
struct W3DScriptedModelDrawBits
{
	W3DScriptedModelDrawBits() { reset(); }
	void reset()
	{
		m_low = 0;
		m_mid = 0;
		m_flag = 0;
		m_a = 0;
		m_b = 0;
		m_c = 0;
	}
	unsigned int m_low : 3;
	unsigned int m_mid : 27;
	unsigned int m_flag : 1;
	unsigned int m_top : 1;
	int m_a;
	int m_b;
	int m_c;
};

class Rva000C04D4 : public _STL::_Vector_base<int, _STL::allocator<int> >
{
public:
	Rva000C04D4(const _STL::allocator<int> &a = _STL::allocator<int>()) : _STL::_Vector_base<int, _STL::allocator<int> >(a) {}
	~Rva000C04D4();
};

class Rva000C055C : public _STL::_Vector_base<int, _STL::allocator<int> >
{
public:
	Rva000C055C(const _STL::allocator<int> &a = _STL::allocator<int>()) : _STL::_Vector_base<int, _STL::allocator<int> >(a) {}
	~Rva000C055C();
};

// 0x1C-byte entry: the constructor nulls the first word, no destructor.
struct W3DScriptedModelDrawEntry1C
{
	W3DScriptedModelDrawEntry1C();
	void *m_first;
	int m_rest[6];
};

class Rva0042526Member
{
public:
	Rva0042526Member();
private:
	unsigned char m_pad[0x4C];
};

class RadiusDecal
{
public:
 void clear();
	RadiusDecal();
	~RadiusDecal();
private:
	unsigned char m_data[0x10];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate(){((Rva00B6CF1*)this)->~Rva00B6CF1();}
private:
	unsigned char m_data[0x34];
};

class Vector4
{
public:
	Vector4() {}
	__forceinline Vector4 &operator=(const Vector4 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		W = v.W;
		return *this;
	}
	void Set(float x, float y, float z, float w)
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Matrix3D &operator=(const Matrix3D &m)
	{
		Row[0] = m.Row[0];
		Row[1] = m.Row[1];
		Row[2] = m.Row[2];
		return *this;
	}
	void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	Vector4 Row[3];
};

class ThingTemplate {public:char pad[0x4A8];float sinkSize;};
struct Coord3D;
class Drawable
{
public:
 const ThingTemplate*getTemplate()const {return m_template;}
 const Coord3D*getPosition()const;
 void*vptr;const ThingTemplate*m_template;
	const Matrix3D *getTransformMatrix() const;
	unsigned char m_pad[0xE4-8];
	bool m_e4;
	int m_e8;
	int m_ec;
};

struct W3DScriptedModelDrawModuleDataView
{
	unsigned char m_pad[0x139];
	bool m_139;
	int m_13c;
	int m_140;
};

class DrawableModule:public Snapshot {protected:virtual ~DrawableModule();const ModuleData*m_moduleData;Drawable*m_drawable;};
class DrawModule:public DrawableModule {public:DrawModule(Thing*,const ModuleData*);virtual ~DrawModule(){}const ModuleData*getModuleData()const{return m_moduleData;}Drawable*getDrawable()const{return m_drawable;}virtual void loadPostProcess();virtual void crc(Xfer*);virtual void xfer(Xfer*);};

class W3DScriptedModelDrawInterfaceC
{
public:
	virtual void interfaceC();
};

class W3DScriptedModelDrawInterface10
{
public:
	virtual void interface10();
};

extern int g_Va00DE1B40;
int Rva000B2BA3Get(const Rva000B2BE5Src *src, bool *out);

class Rva000BC9B1 {public:void rva000BC9B1(bool);};class Rva000C7699 {public:void rva000C7699();};class Rva000B3C61 {public:void rva000B3C61(int);};class Rva000B3348 {public:void rva000B3348(Matrix3D*);};
class W3DScriptedModelDraw : public DrawModule, public W3DScriptedModelDrawInterfaceC, public W3DScriptedModelDrawInterface10
{
public:
	W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData);
	virtual ~W3DScriptedModelDraw();

	virtual void interfaceC();
	virtual void interface10();

private:
	int m_14;
	int m_18;
	W3DScriptedModelDrawHandle m_1c;
	W3DScriptedModelDrawBits m_28;
	_STL::vector<Rva00B6CF1> m_38;
	int m_44;
	bool m_48;
	bool m_49;
	bool m_4a;
	bool m_4b;
	bool m_4c;
	bool m_4d;
	int m_50;
	AsciiString m_54;
	int m_58;
	int m_5c;
	int m_60;
	_STL::list<BfmeStringRecord000B757D> m_64;
	Rva000C04D4 m_68;
	Rva000C04D4 m_74;
	bool m_80;
	bool m_81;
	int m_84;
	int m_88;
	float m_8c;
	float m_90;
	float m_94;
	float m_98;
	float m_9c;
	bool m_a0;
	int m_a4;
	_STL::set<AsciiString, _STL::less<AsciiString>, _STL::allocator<AsciiString> > m_a8;
	AsciiString m_b4;
	int m_b8;
	int m_bc;
	int m_c0;
	int m_c4;
	_STL::vector<const ObjectCreationList *> m_c8[6];
	W3DScriptedModelDrawEntry1C m_110[3];
	Rva000C055C m_164;
	_STL::vector<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > m_170;
	Rva0042526Member m_17c;
	bool m_1c8;
	bool m_1c9;
	bool m_1ca;
	bool m_1cb;
	int m_1cc;
	RadiusDecal m_1d0;
	RadiusDecalTemplate m_1e0;
	int m_214;
	RadiusDecal m_218;
	RadiusDecalTemplate m_228;
	bool m_25c;
	AsciiString m_260;
	AsciiString m_264[2];
	float m_26c;
	bool m_270;
	int m_274;
	int m_278;
	int m_27c;
	int m_280[3];
	bool m_28c;
	bool m_28d;
	bool m_28e;
	Matrix3D m_290;
	float m_2c0;
	int m_2c4;
	float m_2c8;
	float m_2cc;
	float m_2d0;
	float m_2d4;
	bool m_2d8;
	bool m_2d9;
	bool m_2da;
	int m_2dc;
	int m_2e0;
	AsciiString m_2e4;
};


class Rva00083CB2 {public:char pad[0x38];int m_38;char pad2[0x1311-0x3C];char m_1311;};
class Rva00083CD7Host {public:__declspec(noinline) void clear(Rva00083CB2*p){p->m_38=0;p->m_1311=0;}};
class TerrainTracksRenderObjClassSystem;extern TerrainTracksRenderObjClassSystem*TheTerrainTracksRenderObjClassSystem;
#define g_TerrainTracks ((Rva00083CD7Host*)TheTerrainTracksRenderObjClassSystem)
class Rva000ADF90 {public:void rva000ADF90(const Coord3D*,float,unsigned char);};class GameClientNative {public:char pad[0x37C0];Rva000ADF90*terrain;};
class BaseHeightMapRenderObjClass;extern BaseHeightMapRenderObjClass*TheTerrainRenderObject;
#define g_GameClientNative ((GameClientNative*)TheTerrainRenderObject)
W3DScriptedModelDraw::~W3DScriptedModelDraw(){
 ((Rva000BC9B1*)this)->rva000BC9B1(false);((Rva000C7699*)this)->rva000C7699();
 m_170.clear();
 if(m_60 && g_TerrainTracks){g_TerrainTracks->clear((Rva00083CB2*)m_60);m_60=0;}
 ((Rva000B3C61*)this)->rva000B3C61(0);((Rva000B3C61*)this)->rva000B3C61(1);((Rva000B3C61*)this)->rva000B3C61(2);((Rva000B3348*)this)->rva000B3348(0);
 const ThingTemplate*t=getDrawable()->getTemplate();const float*sizePtr=&t->sinkSize;
 if(*sizePtr>1.0f){const Coord3D*p=getDrawable()->getPosition();float size=*sizePtr;Rva000ADF90*terrain=g_GameClientNative->terrain;terrain->rva000ADF90(p,size,true);}
 m_1d0.clear();
}
