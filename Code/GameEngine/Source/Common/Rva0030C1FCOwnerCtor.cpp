// stlport
// cl: /O1 /arch:SSE /G7 /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
//
// ??0Rva0030C1FCOwner@@QAE@H@Z, retail 0x0030C4DE (317 bytes, EH, RET 8: one
// int and the hidden most-derived flag): the constructor of the river area
// whose destructor 0x0030C40A (Rva0030C1FCOwnerDtor.cpp) and broadcast slots
// (Rva0030C1FCNotifiers.cpp) are rowed; RiverAreasDataChunkParser::parse
// 0x0030C6C8 and the river importer 0x00329339 allocate it (new 0x94).
// Target evidence: it installs the destructor's tables (0x00C088FC at +0,
// 0x00C088E0 on the shared interface 0x00C6EE28 at +0x90 behind a vtordisp)
// over the rowed primary base Rva0053805DBase 0x005380A8 and the listener
// list 0x00330757 (a second base at +0x30, as in the destructor), then
// builds four AsciiStrings at +0x40 (eh vector constructor iterator), 1.0 at
// +0x50..+0x58, the water transparency setting's +0x40 at +0x5C, -1 at +0x60,
// 0 at +0x64 and the quad strip at +0x68 (rowed constructor 0x005388AB),
// whose storage the int reserves (rowed QuadStrip2D 0x0053892C, WorldBuilder
// RiverArea::reserveStipSpace). The strings default to the setting's +0x3C
// texture, "Noise0000.tga", "TWAlphaEdge.tga" and
// "WaterSurfaceBubbles.tga". Field meanings are not established; names are
// address-derived.
#include "ascii_string.h"
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
#include "../../../Libraries/Include/Lib/Region2D.h"
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &point):x(point.x),y(point.y) {}
 float x,y;
};

typedef _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > Rva0030BEA2Vector;
namespace _STL { template<> BfmeE16 &Rva0030BEA2Vector::operator[](size_type); }
class Rva0053863ESub { public: Region2D run(); float rva00538661(); };
class Rva00538674Sub { public: Rva0030B72CPoint run(); };

void __cdecl Rva00030830GameFree(void *);

// The interface dtor only restores its table (row 0x0057A243, 7B), inline as in
// Rva0030C1FCOwnerDtor.cpp: retail's deleting dtor stores the table, no call.
class Rva00330C50Interface
{
public:
 ~Rva00330C50Interface() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

// The base as Rva0053805DBaseCtor.cpp lays it out.
#include "../../Include/Common/Rva0007DF07.h"

#include "../../Include/Common/Rva00330757Member.h"

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual Rva00330C50Interface
{
public:
	Rva0053805DBase();
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

#include "../../Include/Common/Overridable.h"
#include "../../Include/GameClient/Water.h"

static __forceinline const Overridable *finalOverride(const Overridable *self)
{
	if (Overridable *next = const_cast<Overridable *>(self)->friend_getNextOverride())
		return next->friend_getFinalOverride();
	return self;
}

template <class T> class OVERRIDE
{
public:
	const T *operator->() const
	{
		if (!m_overridable)
			return 0;
		// Retail inlines the first step of the walk and calls the outline
		// friend_getFinalOverride (0x001E35DF) for the rest.
		return (const T *)finalOverride(m_overridable);
	}
private:
	T *m_overridable;
};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;

// The quad strip at +0x68: rowed constructor 0x005388AB (Rva005388ABCtor.cpp)
// and reserve 0x0053892C (rowed on QuadStrip2D).
#include "../../Include/Common/QuadStrip2D.h"

class Rva005388AB
{
public:
	Rva005388AB();
	~Rva005388AB() { if (m_data) Rva00030830GameFree(m_data); }
private:
	void *m_data;
	unsigned char m_pad04[0x24 - 0x04];
};

class Rva0030C1FCOwner : public Rva0053805DBase, public Rva00330757Member
{
public:
	Rva0030C1FCOwner(int count);
	virtual ~Rva0030C1FCOwner();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
private:
	AsciiString m_40[4];		// +0x40
	float m_50;			// +0x50
	float m_54;
	float m_58;
	float m_5C;			// +0x5C
	int m_60;			// +0x60
	int m_64;			// +0x64
	mutable Rva005388AB m_68;		// +0x68
};

Rva0030C1FCOwner::Rva0030C1FCOwner(int count)
	: m_50(1.0f), m_54(1.0f), m_58(1.0f), m_5C(TheWaterTransparency->m_riverTransparencyMultiplier), m_60(-1), m_64(0)
{
	reinterpret_cast<QuadStrip2D *>(&m_68)->rva0053892C(count);
	m_40[0] = TheWaterTransparency->m_standingWaterTexture;
	m_40[1] = "Noise0000.tga";
	m_40[2] = "TWAlphaEdge.tga";
	m_40[3] = "WaterSurfaceBubbles.tga";
}

// The seven slots of native C088E0. The shared virtual base lies at +90;
// the compiler therefore addresses the +68 quad strip at receiver-28.
// These overrides also emit the seven native vtordisp thunks 30C4A6..30C4DE.
int Rva0030C1FCOwner::slot0() const
{
 const Rva0030BEA2Vector &entries = *reinterpret_cast<const Rva0030BEA2Vector *>(&m_68);
 return (int)entries.size() * 2;
}
Rva0030B72CPoint Rva0030C1FCOwner::slot1(int index) const
{
 Rva0030BEA2Vector &entries = *reinterpret_cast<Rva0030BEA2Vector *>(&m_68);
 int count = entries.size();
 const float *point;
 if (index == 0) point = &entries[0].x;
 else if (--index < count) point = &entries[index].z;
 else point = &entries[count * 2 - index - 1].x;
 return *reinterpret_cast<const Rva0030B72CPoint *>(point);
}
int Rva0030C1FCOwner::slot2() const { return m_64; }
Region2D Rva0030C1FCOwner::slot3()
{ return reinterpret_cast<Rva0053863ESub *>(&m_68)->run(); }
float Rva0030C1FCOwner::slot4() const { return 0.0f; }
float Rva0030C1FCOwner::slot5() const
{ return reinterpret_cast<Rva0053863ESub *>(&m_68)->rva00538661(); }
Rva0030B72CPoint Rva0030C1FCOwner::slot6() const
{ return reinterpret_cast<Rva00538674Sub *>(&m_68)->run(); }
