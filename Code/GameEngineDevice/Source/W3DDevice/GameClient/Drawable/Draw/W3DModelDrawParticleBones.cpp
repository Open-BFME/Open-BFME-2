// ?rva000C6E1A@W3DModelDraw@@QAEXXZ
// cl: /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// Native 0x000C6E1A..0x000C7699: complete 2175-byte body, including its final RET.
// The full native control flow, call targets and exception graph are reproduced.
// WorldBuilder 0x0092DD90..0x0092EEBA (4394 bytes) supplies the corresponding
// control flow and field accesses. Zero Hour's
// W3DModelDraw::recalcBonesForClientParticleSystems supplies the bone-placement
// semantics; BFME2 adds persistent records, callbacks and terrain restrictions.
// The existing W3DModelDraw::rva000C6E1A call in doDrawModule (0x000C7BC4) and
// its established symbol pin supply the class spelling. The method's original
// name remains unknown, so the address-derived method name is retained.
//
// This body needs a dedicated family unit. W3DModelDrawParticles.cpp's 143-byte
// sibling requires potentially throwing command/handle declarations for its
// own unwind graph. This body's corresponding calls are nothrow. The cleanup
// sibling uses a different handle-return view, while the original ZH owner
// still has vector-based particle records instead of BFME2's 32-byte list
// payloads. Reusing those views would change existing exact bodies or this
// one's ABI/lifetimes. No shared header or sibling declaration is changed.
//
// The dirty path merges the current condition state's particle-bone list
// (+0x18 -> +0x74) and module-data list (+0x14 -> +0xB4), handles persistence
// against the tracker at +0x64, creates and places each accepted system,
// applies water/land restrictions, and records it. The clean path calls
// secondary-interface slot +0x6C and the existing 0x000C65CB bone update.
//
// Record fields are established by the native 0x000B75AE copy and the
// W3DScriptedModelDrawParticleSysBone INI reader: text +0, trigger +4,
// persistence ID +8, kind +0xC, callback argument +0x10, callback +0x14,
// template +0x18, follow-bone +0x1C, house color +0x1D, land +0x1E, water +0x1F.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "ascii_string.h"
#include "Coord3D.h"

namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };

struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }

// Opaque 4B list proxy: clear() and the base dtor are the pins of
// StlportPod248ElementDtor.cpp (0x239D49 / 0x2FECBC; payload 32B per 0xB92D2). Retail
// tears a local Pod32 list down as an explicit clear, the unwind-state reset, then the
// out-of-line base dtor; the two specializations spell that without a second name for 0x2FECBC.
// dllimport throw(): callers expand it, and no out-of-line copy competes with the link's 0x2FECBC body.
struct Rva000C6D44ListProxy74
{
	void *m_header;
	void clear();
	~Rva000C6D44ListProxy74();
};
namespace _STL {
template <> __declspec(dllimport) __forceinline _List_base<BfmePod32, allocator<BfmePod32> >::~_List_base() throw()
{
	reinterpret_cast<Rva000C6D44ListProxy74 *>(this)->~Rva000C6D44ListProxy74();
}
// push_back calls retail's 37-byte insert (0x000BC180) out of line; bind it there.
template <> list<BfmePod32>::iterator list<BfmePod32>::insert(iterator, const BfmePod32 &);
}

// Copy at retail 0xB75AE (row ??0BfmeStringRecord000B75AE@@QAE@ABU0@@Z).
struct BfmeStringRecord000B75AE {
	AsciiString text;
	unsigned int trigger, persistId, persistKind, callbackArg;
	void (*callback)(unsigned int, unsigned int);
	unsigned int sysTemplate;
	unsigned char followBone, houseColor, onlyOnLand, onlyOnWater;
	BfmeStringRecord000B75AE(const BfmeStringRecord000B75AE &o);
};

// Tracker record, copy at retail 0xB757D.
struct BfmeStringRecord000B757D {
	unsigned int word0, word1; AsciiString text; unsigned int word2; unsigned char tail;
	BfmeStringRecord000B757D(const BfmeStringRecord000B757D &o);
	BfmeStringRecord000B757D() {}
};
inline bool operator==(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 == y.word0; }
inline bool operator<(const BfmeStringRecord000B757D &x, const BfmeStringRecord000B757D &y) { return x.word0 < y.word0; }

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector3Data.h"

#include "../../../../../../Libraries/Source/WWVegas/WWMath/Vector4Data.h"


class Matrix3D
{
public:
	__forceinline Matrix3D() {}
	__forceinline Matrix3D(const Matrix3D &matrix3D) { Row[0] = matrix3D.Row[0]; Row[1] = matrix3D.Row[1]; Row[2] = matrix3D.Row[2]; }
	__forceinline explicit Matrix3D(bool init)
	{
		if (init)
		{
			Row[0].X = 1.0f; Row[0].Y = 0.0f; Row[0].Z = 0.0f; Row[0].W = 0.0f;
			Row[1].X = 0.0f; Row[1].Y = 1.0f; Row[1].Z = 0.0f; Row[1].W = 0.0f;
			Row[2].X = 0.0f; Row[2].Y = 0.0f; Row[2].Z = 1.0f; Row[2].W = 0.0f;
		}
	}
	__forceinline void Scale(float scale)
	{
			Row[0][0] *= scale; Row[1][0] *= scale; Row[2][0] *= scale;
			Row[0][1] *= scale; Row[1][1] *= scale; Row[2][1] *= scale;
			Row[0][2] *= scale; Row[1][2] *= scale; Row[2][2] *= scale;
	}
	__forceinline Vector3 Get_Translation() const { Vector3 v; v.X = Row[0][3]; v.Y = Row[1][3]; v.Z = Row[2][3]; return v; }
	float Get_Z_Rotation(void) const;
	Vector4 Row[3];
};

struct Rva001F3899Arg { float x, y, z; };
struct Rva001F38C1Arg { float v[12]; };
class Rva0055A88BDwordField;

#include "../../../../../../GameEngine/Include/GameLogic/Module/Rva001F3C20Slot.h"
class Rva001F3899Slot : public Rva001F3C20Slot { public: void set(const Rva001F3899Arg &) throw(); };
#include "../../../../../../GameEngine/Include/GameClient/Rva001F38C1Slot.h"
class Rva001F3852ByteOneSetter { public: void enable() throw(); };

class ParticleSystemColorSink { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void setColor(int color); };

class ParticleSystem : public Rva001F38C1Slot
{
public:
	void destroy() throw();
	void rva001F45F4(Bool enabled) throw();
	void rotateLocalTransformZ(float rotation) throw();
	char m_pad[0x1A7];
};
ParticleSystem *Make001FCBD7(void);

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	ParticleSystem *m_system;
	void *m_previous;
	void *m_next;
};

class BfmeParticleSystemHandle : public RvaSmartPtr12
{
public:
	__forceinline ~BfmeParticleSystemHandle() throw() { if (m_system) rva0004CBC0(); }
	operator Bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		if (!m_system)
			return Make001FCBD7();
		return m_system;
	}
};

class ParticleSystemTemplate;
class W3DModelDraw;
#include "../../../../../../GameEngine/Include/GameClient/ParticleSys.h"
extern ParticleSystemManager *TheParticleSystemManager;

#include "../../../../../../GameEngine/Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;

#define RENDEROBJ_SLOT(n) virtual void slot##n();

class RenderObjClass
{
public:
	virtual void Delete_This();								// +0x00
	RENDEROBJ_SLOT(01) RENDEROBJ_SLOT(02) RENDEROBJ_SLOT(03)
	RENDEROBJ_SLOT(04) RENDEROBJ_SLOT(05) RENDEROBJ_SLOT(06) RENDEROBJ_SLOT(07)
	RENDEROBJ_SLOT(08) RENDEROBJ_SLOT(09) RENDEROBJ_SLOT(10) RENDEROBJ_SLOT(11)
	RENDEROBJ_SLOT(12) RENDEROBJ_SLOT(13) RENDEROBJ_SLOT(14) RENDEROBJ_SLOT(15)
	RENDEROBJ_SLOT(16) RENDEROBJ_SLOT(17) RENDEROBJ_SLOT(18) RENDEROBJ_SLOT(19)
	virtual void Validate_Transform() const;						// +0x50
	virtual void Set_Transform(const Matrix3D &m);						// +0x54
	RENDEROBJ_SLOT(22) RENDEROBJ_SLOT(23)
	RENDEROBJ_SLOT(24) RENDEROBJ_SLOT(25) RENDEROBJ_SLOT(26) RENDEROBJ_SLOT(27)
	RENDEROBJ_SLOT(28) RENDEROBJ_SLOT(29) RENDEROBJ_SLOT(30) RENDEROBJ_SLOT(31)
	RENDEROBJ_SLOT(32) RENDEROBJ_SLOT(33) RENDEROBJ_SLOT(34) RENDEROBJ_SLOT(35)
	RENDEROBJ_SLOT(36) RENDEROBJ_SLOT(37) RENDEROBJ_SLOT(38) RENDEROBJ_SLOT(39)
	RENDEROBJ_SLOT(40) RENDEROBJ_SLOT(41) RENDEROBJ_SLOT(42) RENDEROBJ_SLOT(43)
	RENDEROBJ_SLOT(44) RENDEROBJ_SLOT(45) RENDEROBJ_SLOT(46) RENDEROBJ_SLOT(47)
	RENDEROBJ_SLOT(48) RENDEROBJ_SLOT(49)
	virtual int Get_Bone_Index(const char *bonename);					// +0xC8
	virtual Matrix3D Get_Bone_Transform(int boneindex);					// +0xCC

	const Matrix3D &Get_Transform() const
	{
		Validate_Transform();
		return Transform;
	}
	int m_pad04[5];
	Matrix3D Transform;									// +0x18
};

class Object { public: int getIndicatorColor() const; };
#include "../../../../../../GameEngine/Include/Common/Rva00270260.h"
class Rva000788D3FloatField { public: float get() const; };

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
	int getCurrentClientBonePositions(const char *bone, int a, Coord3D *pos, Matrix3D *xf, int b) const;
	char m_padFC[0xFC];
	Object *m_object;
	char m_pad100[0x114 - 0x100];
	unsigned int m_flags;
	char m_pad118[0x360 - 0x118];
	unsigned int m_trigger;
};


class ParticleStateView { public: char m_pad[0x74]; _STL::list<BfmePod32> m_bones; };
class ParticleDataView { public: char m_pad[0xB4]; _STL::list<BfmePod32> m_bones; };
class ParticleModuleData { public: char m_pad[0x12A]; bool m_useClientBones; };

static __forceinline void Transform_Vector(const Matrix3D &matrix3D, const Vector3 &in, Vector3 *out)
{
	float x = matrix3D.Row[0][0] * in.X + matrix3D.Row[0][1] * in.Y + matrix3D.Row[0][2] * in.Z + matrix3D.Row[0][3];
	float y = matrix3D.Row[1][0] * in.X + matrix3D.Row[1][1] * in.Y + matrix3D.Row[1][2] * in.Z + matrix3D.Row[1][3];
	float z = matrix3D.Row[2][0] * in.X + matrix3D.Row[2][1] * in.Y + matrix3D.Row[2][2] * in.Z + matrix3D.Row[2][3];
	out->X = x;
	out->Y = y;
	out->Z = z;
}

static __forceinline void Transform_VectorLand(const Matrix3D &matrix3D, const Vector3 &in, Vector3 *out)
{
	// Retail takes this product's register operand from the initialized input X.
	// The volatile-qualified reference preserves that read with MSVC 7.1;
	// the complete emitted arithmetic and its exception graph are byte-checked.
	const volatile float &inputX = in.X;
	float x = inputX * matrix3D.Row[0][0] + (in.Y * matrix3D.Row[0][1] + in.Z * matrix3D.Row[0][2]) + matrix3D.Row[0][3];
	float y = in.X * matrix3D.Row[1][0] + in.Y * matrix3D.Row[1][1] + in.Z * matrix3D.Row[1][2] + matrix3D.Row[1][3];
	float z = in.X * matrix3D.Row[2][0] + in.Y * matrix3D.Row[2][1] + in.Z * matrix3D.Row[2][2] + matrix3D.Row[2][3];
	out->X = x;
	out->Y = y;
	out->Z = z;
}

class DrawSecondary
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26();
	virtual void slot6C(bool flag);
};

class W3DModelDraw
{
public:
	void rva000C6E1A();
	void rva000C65CB();	// bone-attached render object update (0x000C65CB)
private:
	char m_pad00[4];
	ParticleModuleData *m_data;							// +0x04
	Drawable *m_drawable;								// +0x08
	DrawSecondary m_secondary;							// +0x0C
	void *m_pad10;
	ParticleDataView *m_particleData;						// +0x14
	ParticleStateView *m_state;							// +0x18
	char m_pad1C[0x48 - 0x1C];
	bool m_dirty;									// +0x48
	bool m_hidden;									// +0x49
	char m_pad4A[0x50 - 0x4A];
	RenderObjClass *m_renderObject;							// +0x50
	char m_pad54[0x64 - 0x54];
	_STL::list<BfmeStringRecord000B757D> m_tracked;					// +0x64
};

void W3DModelDraw::rva000C6E1A()
{
	if (m_dirty)
	{
		Drawable *drawable = m_drawable;
		if (drawable)
		{
			if (m_state && !(drawable->m_flags & 8))
			{

				_STL::list<BfmePod32> bones;
				for (_STL::list<BfmePod32>::iterator it = m_state->m_bones.begin(); it != m_state->m_bones.end(); ++it)
					bones.push_back(*it);
				for (_STL::list<BfmePod32>::iterator it = m_particleData->m_bones.begin(); it != m_particleData->m_bones.end(); ++it)
					bones.push_back(*it);
				for (_STL::list<BfmePod32>::iterator it = bones.begin(); it != bones.end(); ++it)
				{
					BfmeStringRecord000B75AE rec(*(const BfmeStringRecord000B75AE *)&*it);
					bool skip = false;
					if (rec.persistId)
					{
						if (m_tracked.empty())
						{
							skip = (rec.persistKind == 1 || rec.persistKind == 2);
						}
						else
						{
							for (_STL::list<BfmeStringRecord000B757D>::iterator t = m_tracked.begin(); t != m_tracked.end(); ++t)
							{
								BfmeStringRecord000B757D &entry = *t;
								if (entry.word2 == rec.persistId)
								{
									int kind = rec.persistKind;
									if (kind == 3 || entry.tail)
									{
										skip = true;
										break;
									}
									if (kind == 2 || kind == 1)
									{
										BfmeParticleSystemHandle found = TheParticleSystemManager->findParticleSystemByID((ParticleSystemID)entry.word0);
										if (found.m_system)
											found.m_system->destroy();
										if (kind == 1)
											m_tracked.erase(t);
										if (kind == 2)
											entry.tail = 1;
										skip = true;
										break;
									}
								}
							}
						}
					}
					if (skip)
						continue;
					if (!rec.sysTemplate)
						continue;
					BfmeParticleSystemHandle sys = TheParticleSystemManager->createParticleSystem(
						(const ParticleSystemTemplate *)rec.sysTemplate, true);
					if (!sys.m_system)
						continue;
					if (rec.trigger)
					{
						unsigned int current = drawable->m_trigger;
						if (current != rec.trigger)
							continue;
					}
					Coord3D pos = { 0.0f, 0.0f, 0.0f };
					float rotation = 0.0f;
					int boneIndex = 0;
					if (m_renderObject)
						*(volatile int *)&boneIndex = m_renderObject->Get_Bone_Index(rec.text.str());
					else
						*(volatile int *)&boneIndex = 0;
					ParticleModuleData *data = m_data;
					if (data->m_useClientBones)
					{
						Matrix3D xf;

						const char *name = rec.text.str();
						Drawable *d = m_drawable;
						if (d->getCurrentClientBonePositions(name, 0, 0, &xf, 1))
							((Rva001F38C1Slot *)sys.operator->())->set(*(const Rva001F38C1Arg *)&xf);
					}
					else if (rec.followBone)
					{
						if (boneIndex && m_renderObject)
						{
							Matrix3D xf = m_renderObject->Get_Bone_Transform(boneIndex);
							((Rva001F38C1Slot *)sys.operator->())->set(*(const Rva001F38C1Arg *)&xf);
						}
						else
						{
							((Rva001F3899Slot *)sys.operator->())->set(*(const Rva001F3899Arg *)&pos);
							sys->rotateLocalTransformZ(0.0f);
						}
					}
					else
					{
						if (boneIndex && m_renderObject)
						{
							Matrix3D originalTransform = m_renderObject->Get_Transform();
							Matrix3D tmp(true);
							tmp.Scale(((Rva000788D3FloatField *)m_drawable)->get());
							m_renderObject->Set_Transform(tmp);
							const Matrix3D boneTransform = m_renderObject->Get_Bone_Transform(boneIndex);
							Vector3 vpos = boneTransform.Get_Translation();
							pos = *(Coord3D *)&vpos;
							rotation = boneTransform.Get_Z_Rotation();
							m_renderObject->Set_Transform(originalTransform);
						}
						((Rva001F3899Slot *)sys.operator->())->set(*(const Rva001F3899Arg *)&pos);
						sys->rotateLocalTransformZ(rotation);
					}
					if (rec.onlyOnWater)
					{
						Vector3 in = *(Vector3 *)&pos;
						Vector3 out = *(Vector3 *)&pos;
						Transform_Vector(*drawable->getTransformMatrix(), in, &out);
						if (!TheTerrainLogic->isUnderwater(out.X, out.Y, 0, 0, 0))
						{
							sys->destroy();
							continue;
						}
					}
					else if (rec.onlyOnLand)
					{
						Vector3 in = *(Vector3 *)&pos;
						Vector3 out = *(Vector3 *)&pos;
						Transform_VectorLand(*drawable->getTransformMatrix(), in, &out);
						if (TheTerrainLogic->isUnderwater(out.X, out.Y, 0, 0, 0))
						{
							sys->destroy();
							continue;
						}
					}
					((Rva001F3C20Slot *)sys.operator->())->set((const Rva0055A88BDwordField *)drawable);
					sys->rva001F45F4(false);
					*((unsigned char *)sys.operator->() + 0x1A7) = rec.followBone;
					Object *object = drawable->m_object;
					if (object && rec.houseColor)
					{
						ParticleSystem *ps = sys.operator->();
						int color = object->getIndicatorColor();
						ParticleSystemColorSink *sink = *(ParticleSystemColorSink **)((char *)ps + 0x1AC);
						if (sink)
							sink->setColor(color);
					}
					if (((Rva00270260 *)drawable)->rva00270260() || m_hidden)
						((Rva001F3852ByteOneSetter *)sys.operator->())->enable();
					BfmeStringRecord000B757D tracker;
					tracker.word0 = *(unsigned int *)((char *)sys.operator->() + 0xA8);
					tracker.word1 = boneIndex;
					tracker.text = rec.text;
					tracker.word2 = rec.persistId;
					tracker.tail = 0;
					if (rec.callback)
						rec.callback(rec.callbackArg, *(unsigned int *)((char *)sys.operator->() + 0xA8));
					if (*((unsigned char *)sys.operator->() + 0x1A7))
						m_tracked.push_front(tracker);
					else
						m_tracked.push_back(tracker);
				}
				reinterpret_cast<Rva000C6D44ListProxy74 *>(&bones)->clear();
			}
			m_dirty = false;
		}
	}
	else
	{
		m_secondary.slot6C(true);
		rva000C65CB();
	}
}
