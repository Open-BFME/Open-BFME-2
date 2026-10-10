// ?rva0004CF9A@Rva0004CA4C@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.5 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// NEAR (draft for Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFXParticleSystemManagerRva0004CF9A.cpp):
// statement structure and callees line up; the frame is 4 bytes larger and the EH
// state layout differs: retail keeps state 0 alive for the whole body (its loop
// handles unwind to 0 not -1) and zeroes an otherwise unused local at [ebp-0x54]
// (likely a scoped profiler object with an empty inline dtor; the WorldBuilder twin
// calls PerfGather) and keeps EBX=0 / EDI=this with a [ebp-0x14] this spill.
// Rva0004CABDSevenEight::get is tested with AL: needs a bool pin
// ?get@Rva0004CABDSevenEight@@QBE_NXZ=0x0004CABD (the row spells int).
//
// ?rva0004CF9A@Rva0004CA4C@@QAEXAAVRenderInfoClass@@@Z
// retail 0x0004CF9A..0x0004D47D (1251 bytes) thiscall RET 4 with __EH_prolog.
// Slot 36 of vftable 0x007C4C20 (Rva0004CA4C). The W3DFXParticleSystem.cpp
// counterpart of Zero Hour's W3DParticleSystemManager::doParticles.
#include "../../../../Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class RenderInfoClass;
class FrustumClass;
class ParticleSystem;

class AABoxClass
{
public:
	Coord3D Center;
	Coord3D Extent;
};

class CameraClass
{
public:
	const FrustumClass &Get_Frustum() const
	{
		Update_Frustum();
		return *reinterpret_cast<const FrustumClass *>(m_pad + 0x100);
	}

protected:
	void Update_Frustum() const;			// 0x001340B0

private:
	unsigned char m_pad[0x100];
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

class BaseHeightMapRenderObjClass
{
public:
	Bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, Bool ignoreMaxHeight);	// 0x0006B1FA
};

ParticleSystem *Make001FCBD7();			// 0x001FCBD7

class RvaSmartPtr12
{
public:
	RvaSmartPtr12(ParticleSystem *p)
	{
		m_ptr = p;
		if (m_ptr)
			attach();
		else
		{
			m_pad08 = 0;
			m_pad04 = 0;
		}
	}
	void attach();					// 0x0004CB9A
	RvaSmartPtr12(const RvaSmartPtr12 &that);	// 0x0004CC19
	~RvaSmartPtr12() { if (m_ptr) rva0004CBC0(); }
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &that);	// 0x0004CC3D
	void rva0004CBC0();				// 0x0004CBC0
	ParticleSystem *get() const { return m_ptr; }
	ParticleSystem *operator->() const { return m_ptr ? m_ptr : Make001FCBD7(); }

private:
	ParticleSystem *m_ptr;
	int m_pad04;
	int m_pad08;
};

namespace _STL
{
	template <class T> class allocator {};

	template <class T, class A = allocator<T> >
	class vector
	{
	public:
		void push_back(const T &x);
		T *erase(T *first, T *last);
		T *begin() { return _M_start; }
		T *end() { return _M_finish; }
		Int size() const { return _M_finish - _M_start; }
		T &operator[](Int i) { return _M_start[i]; }
		void clear() { erase(begin(), end()); }

	private:
		T *_M_start;
		T *_M_finish;
		T *_M_end_of_storage;
	};

	template <class T>
	struct _List_node
	{
		_List_node *_M_next;
		_List_node *_M_prev;
		T _M_data;
	};

	template <class T, class A = allocator<T> >
	class list
	{
	public:
		_List_node<T> *_M_node;
	};
}

struct RGBColor
{
	Real red, green, blue;
	Int getAsInt() const;				// 0x00004EA7
};

class Rva001F4D2D { public: Real rva001F4D2D(); };		// 0x001F4D2D
class Rva001F4E1BSlot { public: const RGBColor *get() const; };	// 0x001F4E1B
class Rva001F4DC4 { public: Real rva001F4DC4(); };		// 0x001F4DC4
class Rva001F4DF9 { public: Real rva001F4DF9(); };		// 0x001F4DF9

class Particle
{
public:
	Real getSize() { return reinterpret_cast<Rva001F4D2D *>(this)->rva001F4D2D(); }
	const RGBColor *getColor() const { return reinterpret_cast<const Rva001F4E1BSlot *>(this)->get(); }
	Real getSpread() { return reinterpret_cast<Rva001F4DC4 *>(this)->rva001F4DC4(); }
	Real getAlpha() { return reinterpret_cast<Rva001F4DF9 *>(this)->rva001F4DF9(); }

	unsigned char m_pad00[0x1C];
	Coord3D m_pos;					// +0x1C
	unsigned char m_pad28[0x64 - 0x28];
	Particle *m_next;				// +0x64
};

class ParticleStorage
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual Particle *getFirstParticle();		// slot 8 (+0x20)
};

class ParticleDrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual Int doParticles(RenderInfoClass &rinfo, void *box, Int *count);	// slot 4 (+0x10)
};

class AsciiStringData;

class AsciiString
{
public:
	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : "";
	}

private:
	AsciiStringData *m_data;
};

class Rva0004CABDSevenEight
{
public:
	bool get() const;				// 0x0004CABD
};

class ParticleSystem
{
public:
	Bool isSevenOrEight() const { return reinterpret_cast<const Rva0004CABDSevenEight *>(this)->get(); }
	const AsciiString &getParticleTypeName() const { return m_particleTypeName; }

	unsigned char m_pad00[0x0C];
	Int m_0C;					// +0x0C
	AsciiString m_particleTypeName;			// +0x10
	unsigned char m_pad14[0x24 - 0x14];
	UnsignedInt m_sortList;				// +0x24
	unsigned char m_pad28[0xA4 - 0x28];
	ParticleStorage *m_storage;			// +0xA4
	unsigned char m_padA8[0x1C4 - 0xA8];
	ParticleDrawModule *m_drawModule;		// +0x1C4
};

class ParticleSystemManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void setOnScreenParticleCount(Int count);	// slot 15 (+0x3C)

	unsigned char m_pad04[0x4C - 0x04];
	_STL::list<RvaSmartPtr12> m_allParticleSystems;	// +0x4C
};

struct Smudge
{
	unsigned char m_pad00[0x0C];
	Coord3D m_pos;					// +0x0C
	Real m_offsetX;					// +0x18
	Real m_offsetY;					// +0x1C
	Real m_size;					// +0x20
	Real m_opacity;					// +0x24
};

struct SmudgeSet
{
	Smudge *addSmudgeToSet();			// 0x002D2996
};

class SmudgeManager
{
public:
	SmudgeSet *addSmudgeSet();			// 0x002D291B
};

class BfmeB991
{
public:
	unsigned char m_pad00[0x04];
	Int m_04;					// +0x04
	unsigned char m_pad08[0x20 - 0x08];
	Int m_smudgeCountLastFrame;			// +0x20
	unsigned char m_pad24[0x40 - 0x24];
	Int m_color;					// +0x40
};

class GlobalData
{
public:
	unsigned char m_pad00[0x25];
	Bool m_useHeatEffects;				// +0x25
};

class W3DSnowManager
{
public:
	void render(RenderInfoClass &rinfo);		// 0x0009470F
};
class SnowManager;

class WW3D
{
	static bool AreStaticSortListsEnabled;
	friend class Rva0004CA4C;
};

extern BfmeB991 *g_bfmeB991;
extern Int g_bfmeVal991;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern ParticleSystemManager *TheParticleSystemManager;
extern GlobalData *TheWritableGlobalData;
extern unsigned char g_Va00DB5F7D;
extern SnowManager *TheSnowManager;

Real GetGameClientRandomValueReal(Real lo, Real hi, char *file, Int line);	// 0x00234111

static inline Real Fabs(Real val)
{
	Int value = *(Int *)&val;
	value &= 0x7fffffff;
	return *(Real *)&value;
}

class Rva0004CA4C
{
public:
	void rva0004CF9A(RenderInfoClass &rinfo);

private:
	void *m_vtbl;
	unsigned char m_pad04[0x54 - 0x04];
	Int m_54;					// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	Int m_onScreenParticleCount;			// +0x5C
	unsigned char m_pad60[0x68 - 0x60];
	RvaSmartPtr12 m_current;			// +0x68
	unsigned char m_pad74[0xA8 - 0x74];
	Bool m_readyToRender;				// +0xA8
	unsigned char m_padA9[0xAC - 0xA9];
	_STL::vector<RvaSmartPtr12> m_sortLists[2];	// +0xAC
};

void Rva0004CA4C::rva0004CF9A(RenderInfoClass &rinfo)
{
	if (!m_readyToRender)
		return;
	m_readyToRender = false;

	g_bfmeVal991 = 0;
	if (g_bfmeB991)
		g_bfmeB991->m_smudgeCountLastFrame = 0;

	const FrustumClass &frustum = rinfo.Camera.Get_Frustum();
	AABoxClass bbox;
	TheTerrainRenderObject->getMaximumVisibleBox(frustum, &bbox, true);

	Real bcX = bbox.Center.x;
	Real bcY = bbox.Center.y;
	Real bcZ = bbox.Center.z;
	Real beX = bbox.Extent.x;
	Real beY = bbox.Extent.y;
	Real beZ = bbox.Extent.z;

	SmudgeSet *set = 0;
	if (g_bfmeB991)
		set = reinterpret_cast<SmudgeManager *>(g_bfmeB991)->addSmudgeSet();

	m_current = 0;

	_STL::list<RvaSmartPtr12> &particleSysList = TheParticleSystemManager->m_allParticleSystems;
	for (_STL::_List_node<RvaSmartPtr12> *it = particleSysList._M_node->_M_next; it != particleSysList._M_node; it = it->_M_next)
	{
		RvaSmartPtr12 sys(it->_M_data);
		if (!sys.get())
			continue;
		if (sys->m_0C == 6)
			continue;

		if (WW3D::AreStaticSortListsEnabled && sys->m_sortList > 0 && sys->m_sortList < 2)
		{
			m_sortLists[sys->m_sortList].push_back(sys);
			continue;
		}

		if (*((UnsignedInt *)sys->getParticleTypeName().str()) == 0x44554D53)
		{
			if (g_bfmeB991 && g_bfmeB991->m_04 != 1 && TheWritableGlobalData->m_useHeatEffects)
			{
				Bool colorSet = false;
				if (!sys->isSevenOrEight())
				{
					for (Particle *p = sys->m_storage->getFirstParticle(); p; p = p->m_next)
					{
						Real psize = p->getSize();
						if (Fabs(p->m_pos.x - bcX) > psize + beX)
							continue;
						if (Fabs(p->m_pos.y - bcY) > psize + beY)
							continue;
						if (Fabs(p->m_pos.z - bcZ) > psize + beZ)
							continue;
						if (!colorSet)
						{
							g_bfmeB991->m_color = p->getColor()->getAsInt();
							colorSet = true;
						}
						Smudge *smudge = set->addSmudgeToSet();
						Real spread = p->getSpread();
						smudge->m_pos.x = p->m_pos.x;
						smudge->m_pos.y = p->m_pos.y;
						smudge->m_pos.z = p->m_pos.z;
						Real offsetY = GetGameClientRandomValueReal(-spread, spread,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp", 195);
						smudge->m_offsetX = GetGameClientRandomValueReal(spread * -2.0f, spread * 2.0f,
							"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\W3DFXParticleSystem.cpp", 195);
						smudge->m_offsetY = offsetY;
						smudge->m_size = psize;
						smudge->m_opacity = p->getAlpha();
						g_bfmeVal991++;
					}
				}
			}
			continue;
		}

		if (sys->m_drawModule)
		{
			m_current = sys;
			m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
			m_current = 0;
		}
	}

	if (WW3D::AreStaticSortListsEnabled)
	{
		unsigned char saved = g_Va00DB5F7D;
		if (saved)
			g_Va00DB5F7D = 0;
		for (Int k = 1; k >= 0; k--)
		{
			_STL::vector<RvaSmartPtr12> &list = m_sortLists[k];
			for (Int j = list.size() - 1; j >= 0; j--)
			{
				RvaSmartPtr12 sys(list[j]);
				if (!sys.get())
					continue;
				if (sys->m_drawModule)
				{
					m_current = sys;
					m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
					m_current = 0;
				}
			}
			list.clear();
		}
		if (saved)
			g_Va00DB5F7D = 1;
	}

	TheParticleSystemManager->setOnScreenParticleCount(m_onScreenParticleCount);
	if (TheSnowManager)
		reinterpret_cast<W3DSnowManager *>(TheSnowManager)->render(rinfo);
}
