// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x000C0DD8
// 1065 bytes. W3DScriptedModelDraw (Thing* ModuleData*) constructor: called
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

class Thing;
class ModuleData;
class ObjectCreationList;
struct Rva00B6CF1;
struct BfmePod20;
struct Rva000B2BE5Src;

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
	~_List_base();
	void *_M_node;
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
	~set();
private:
	void *m_tree[3];
};
}

// Pointer-chain handle at +0x1C: unlinked through 0x0004CBC0 when set.
// 0x0004CBC0 is the handle unlink (row ?rva0004CBC0@RvaSmartPtr12@@QAEXXZ); the dtor is the inline null test around it.
class RvaSmartPtr12 { public: void rva0004CBC0(); };
struct BfmeParticleSystemHandle
{
	~BfmeParticleSystemHandle();
	void *m_system;
	void *m_previous;
	void *m_next;
};

struct W3DScriptedModelDrawHandle
{
	W3DScriptedModelDrawHandle() : m_system(0), m_previous(0), m_next(0) {}
	~W3DScriptedModelDrawHandle()
	{
		if (m_system != 0)
			reinterpret_cast<RvaSmartPtr12 *>(this)->rva0004CBC0();
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
	RadiusDecal();
	~RadiusDecal();
private:
	unsigned char m_data[0x10];
};

class RadiusDecalTemplate
{
public:
	RadiusDecalTemplate();
	~RadiusDecalTemplate();
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

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	unsigned char m_pad[0xE4];
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

class DrawModule
{
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawModule();
	const ModuleData *getModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }
private:
	const ModuleData *m_moduleData;
	Drawable *m_drawable;
};

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
	_STL::list<BfmePod20> m_64;
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

// ??0W3DScriptedModelDraw@@QAE@PAVThing@@PBVModuleData@@@Z @0x000C0DD8
W3DScriptedModelDraw::W3DScriptedModelDraw(Thing *thing, const ModuleData *moduleData)
	: DrawModule(thing, moduleData)
{
	m_84 = 1;
	m_80 = true;
	m_81 = false;
	m_18 = 0;
	m_14 = 0;
	m_28.reset();
	m_50 = 0;
	m_54 = "";
	m_58 = 0;
	m_4a = true;
	m_4b = false;
	m_4c = false;
	m_5c = 0;
	m_60 = 0;
	m_44 = -1;
	m_48 = false;
	m_49 = false;
	m_b8 = ~g_Va00DE1B40;
	m_a0 = true;
	m_a4 = 0;
	m_1c8 = false;
	m_1c9 = false;
	m_1ca = false;
	m_88 = 0;
	m_90 = 0.0f;
	m_94 = 1.0f;
	m_98 = 1.0f;
	m_9c = 1.0f;
	m_8c = 0.0f;
	m_bc = 0;
	m_c0 = 0;
	m_25c = true;
	m_28c = false;
	m_28d = true;
	m_28e = false;
	m_4d = false;
	m_c4 = 5;
	m_260.clear();
	for (int i = 0; i < 2; ++i)
		m_264[i].clear();
	m_26c = 0.0f;
	m_2c8 = -9999.0f;
	m_2cc = -9999.0f;
	m_2d0 = -9999.0f;
	m_2d4 = -9999.0f;
	Drawable *draw = getDrawable();
	m_1cb = false;
	m_1cc = 0;
	m_214 = -1;
	const W3DScriptedModelDrawModuleDataView *data = (const W3DScriptedModelDrawModuleDataView *)getModuleData();
	if (data != 0 && draw != 0)
	{
		draw->m_e4 = data->m_139;
		draw->m_e8 = data->m_13c;
		draw->m_ec = data->m_140;
	}
	m_270 = false;
	m_274 = 0;
	m_278 = 0;
	m_27c = 0;
	if (draw != 0)
		m_290 = *draw->getTransformMatrix();
	else
		m_290.Make_Identity();
	m_2c0 = 1.0f;
	m_2c4 = -1;
	m_bc = Rva000B2BA3Get(0, 0);
	m_2d8 = true;
	m_2d9 = true;
	m_2da = true;
	m_2dc = 0;
	m_2e0 = 0;
}
