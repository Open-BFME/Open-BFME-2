// ?rva003805BB@Rva003805BB@@QAE_NM_N@Z
// partial score=0.99 date=2026-10-09
// Semantic reference: BFME1 9cbfb551fe Player_addSkillPoints.cpp; BFME2 fields from native 003805BB..003806D4 RET8.
// Near match: 281B; compiler FSTP/POP/POP at +E9 versus native POP/FSTP/POP. All other instructions agree.
// cl: /Ireference/shims/bfme2_ascii /GX- /O1 /G7 /arch:SSE
// ?rva00380200@Rva00380200@@QAEPAVAsciiString@@XZ @ 0x00380200 (13B): getter returning +4 or AsciiString::TheEmptyString. Callers 0x00380230 0x00380265 push result. Twin of EmptyString fallback pattern.
// ?rva0038020D@Rva00380200@@QAEXXZ @ 0x0038020D (110B): caches at +0x20 the
// value the store (0x00DFE0EC, pinned get 0x002000D7) config for level
// m_14 + 1 reports for this name (0x7FFFFFFF when absent), and at +0x24 the
// one for level m_14 (0 when absent), through the config method 0x00200157
// (pinned from these call sites: thiscall ret 4 taking the name by reference,
// returning a dword field). Retail keeps the config in edx across the
// rva00380200 call, which cl only does when that getter was compiled earlier
// in the same TU; the TU is /O1 so the getter is called rather than inlined.
#include "ascii_string.h"

class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
class ModuleData;
class Object;
class Xfer
{
public:
	class Version;
	Xfer();
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);
protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};
class Xfer::Version
{
public:
	unsigned char m_major;
	unsigned char m_minor;
	Version(unsigned char a, unsigned char b) : m_major(a), m_minor(b) {}
};


// Matched DIR32 references place this static object at VA 0x00DE0878. Its
// four retail bytes are zero, the null StringBase buffer of an empty string.
const AsciiString AsciiString::TheEmptyString;

struct Rva002000D7Config
{
	int rva00200157(const AsciiString &name);
};
class Rva002000D7Store
{
public:
	Rva002000D7Config *get(int);
};
extern class RankInfoStore *TheRankInfoStore;

class Rva00380200
{
	int m_00;
	AsciiString *m_ptr;
	char m_pad08[4];
	float m_0C;
	float m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
public:
	AsciiString *rva00380200();
	void rva0038020D();
    int rva003802DF();
	void rva00380499(Xfer *xfer);
};

AsciiString *Rva00380200::rva00380200()
{
	if (m_ptr)
		return m_ptr;
	return const_cast<AsciiString *>(&AsciiString::TheEmptyString);
}

void Rva00380200::rva0038020D()
{
	Rva002000D7Config *config = (*(Rva002000D7Store **)&TheRankInfoStore) ? (*(Rva002000D7Store **)&TheRankInfoStore)->get(m_14 + 1) : 0;
	m_20 = config ? config->rva00200157(*rva00380200()) : 0x7fffffff;
	config = (*(Rva002000D7Store **)&TheRankInfoStore) ? (*(Rva002000D7Store **)&TheRankInfoStore)->get(m_14) : 0;
	m_24 = config ? config->rva00200157(*rva00380200()) : 0;
}

// Retail 0x00380499 is a complete 126-byte RET4 body on the same receiver
// as 0x0038020D. Virtual Xfer slots prove floats at +0x0C/+0x10, ints at
// +0x14/+0x18/+0x1C/+0x28, Version {1,2}, and the load-only cache refresh.
// The original class and member names remain unidentified.
void Rva00380200::rva00380499(Xfer *xfer)
{
    Xfer::Version version(1, 2);
    *xfer == version;
    *xfer == m_0C;
    *xfer == m_10;
    *xfer == m_14;
    *xfer == m_18;
    *xfer == m_1C;
    if (version.m_minor >= 2)
        *xfer == m_28;
    if (xfer->IsLoading())
        rva0038020D();
}

// Complete native RET4 body 0x0058AE53..0x0058AEB6. The same Xfer slots
// as matched 0x00380499 establish Version {1,2}, unsigned int +0x0C,
// floats +0x10/+0x14 and bool +0x18. Retail repeats the +0x0C transfer
// within the version-2 arm. Original receiver/member names are unknown.
class Rva0058AE53
{
    char m_pad00[0x0C];
    unsigned int m_0C;
    float m_10;
    float m_14;
    bool m_18;
public:
    void rva0058AE53(Xfer *xfer);
};

void Rva0058AE53::rva0058AE53(Xfer *xfer)
{
    Xfer::Version version(1, 2);
    *xfer == version;
    *xfer == m_0C;
    if (version.m_minor >= 2)
    {
        *xfer == m_10;
        *xfer == m_14;
        *xfer == m_18;
        *xfer == m_0C;
    }
}

class GameLogic;
extern GameLogic *TheGameLogic;
extern "C" __declspec(dllimport) double floor(double);
struct Rva003805BBMultipliers {
    float *begin,*end,*capacity;
    int size() const { return static_cast<int>(end-begin); }
};
class Rva003805BB {
public:
    virtual ~Rva003805BB();
    virtual bool slot1(int);
    bool rva003805BB(float,bool);
    AsciiString *side;
    Rva003805BBMultipliers *multipliers;
    float points,scale;
    int level,base,unknown1C,next,previous,limit;
};
static __forceinline const float &minimumPoints(const float &cap,const float &candidate)
{
    return cap<candidate ? cap : candidate;
}
// Proven x87 conversion blocker: ordinary C++ emits _ftol2 and omits retail's
// single-precision floor-result store. /QIfist cannot coexist with /arch:SSE.
// BFME1 Player_addSkillPoints.cpp uses this same two-instruction FISTP helper.
static __forceinline int floorInteger(float input)
{
    int result;
    __asm {
        fld [input]
        fistp [result]
    }
    return result;
}
bool Rva003805BB::rva003805BB(float delta,bool useMultipliers)
{
    delta*=scale;
    if (limit>0 && level>=limit) return false;
    if (useMultipliers && *reinterpret_cast<const int *>(reinterpret_cast<const char *>(TheGameLogic)+0x114)!=3 && multipliers) {
        int index=level-base;
        if (index>=multipliers->size()) index=multipliers->size()-1;
        if (index>=0) delta*=multipliers->begin[index];
    }
    if (delta==0.0f) return false;
    Rva00380200 *getter=reinterpret_cast<Rva00380200 *>(this);
    int capLevel=getter->rva003802DF();
    int capPoints=reinterpret_cast<Rva002000D7Store *>(TheRankInfoStore)->get(capLevel)->rva00200157(*getter->rva00380200());
    float candidate=points+delta;
    float cap=static_cast<float>(capPoints);
    bool gained=false;
    float total=minimumPoints(cap,candidate);
    points=total;
    float floored=static_cast<float>(floor(static_cast<double>(total)));
    int integerPoints=floorInteger(floored);
    while (integerPoints>=next) {
        bool changed=slot1(level+1);
        gained|=changed;
        if (!changed) break;
    }
    return gained;
}



