// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
//
// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z, retail 0x0040426D, 321 bytes.
// Slot 3 (offset 0xC) of vtable 0x0083856C (class of ??1AttributeModifierPoolUpdate).
// Donor: BFME1 AttributeModifierPoolUpdateConstructor.cpp plus StealthUpdateXfer
// Xfer declaration (xferVersion 0x28 IsLoading 0x04 xferAsciiString 0x6C
// xferUnsignedInt 0x78 xferInt 0x7C xferBool 0x90). Layout from rowed
// constructor in AttributeModifierPoolUpdate.cpp (UpdateModule base 0x20 plus modifier
// vector at +0x20 plus max frame at +0x2C plus 15 category frames at +0x30 plus
// 15 tallies at +0x6C). Evidence: vtable slot 3 callers none callees rowed
// EraseRange 0x2983DA push_back 0x403E3B Rva00368270 0x4034D5 rva004031F3
// 0x4031F3 releaseBuffer 0x36410 BfmeStringRecord 0x40360E UpdateModule xfer
// 0x44DF9F empty string literal Version 1 3 IsLoading gate.
//
// Shape (WorldBuilder twin 0x00E92C60, retail evidence): the 16-byte modifier
// entry views carry their real members so their destructors are the inline
// string release (no call); the 4-byte version struct and the two counts are
// separate frame slots (the store-side count is declared at function scope so
// the sibling arms do not share it); the store loop re-reads the vector end
// each pass. Written from WB and retail, no donor.
// vector at +0x20 plus max frame at +0x2C plus 15 pool names at +0x30 plus
#include <vector>
#include "ascii_string.h"

class Thing;
class ModuleData;
class Object;
class Xfer;
enum UpdateSleepTime
{
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
enum NameKeyType { NAMEKEY_INVALID=-1 };

typedef unsigned int UnsignedInt;


struct XferException
{
	char *text;
	int tag;
};

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
class RealRange;
struct RGBColor;
class RGBAColorReal;
class RGBAColorInt;
struct XferUnknown11;
#include "../../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	unsigned char m_version;
	unsigned char m_currentVersion;
	unsigned short m_pad;
};

class Rva00297360Element
{
public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};

class Rva00368270
{
public:
	Rva00368270(void *p, AsciiString name);
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};

struct Rva004031F3;

struct Obj
{
	virtual void f00(); virtual void f01(); virtual void f02(); virtual void f03();
	virtual void f04(); virtual void f05(); virtual void f06(); virtual void f07();
	virtual void f08(); virtual void f09(); virtual void f10(); virtual void f11();
	virtual void f12(); virtual void f13(); virtual void f14(); virtual void f15();
	virtual void f16(); virtual void f17(); virtual void f18(); virtual void f19();
	virtual void f20(); virtual void f21(); virtual void f22(); virtual void f23();
	virtual void f24(); virtual void f25(); virtual void f26();
	virtual void f27(int *out);
	virtual void f28(); virtual void f29();
	virtual void f30(int *out);
	virtual void f31(Rva004031F3 *ctx);
};

struct Info
{
	char m00;
	unsigned char m01;
};

struct Rva004031F3
{
public:
	void rva004031F3(Obj *obj, Info *info);

private:
	int m00;
	int m01;
	int m02;
	int m03;
};

struct BfmeStringRecord0040360E
{
	BfmeStringRecord0040360E(const BfmeStringRecord0040360E &o);
private:
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
};

class Rva002983DAVector
{
public:
	Rva00297360Element *EraseRange(Rva00297360Element *first, Rva00297360Element *last);
	Rva00297360Element *m_start;
	Rva00297360Element *m_finish;
	Rva00297360Element *m_end;
};

class BehaviorModuleBase
{
	virtual void unused();
public:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update() = 0;
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;

public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual void update();
	void xfer(Xfer *xfer);
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime frame);
};

// One entry of the +0x30 table: retail builds the table through the non-EH vector constructor
// iterator 0x00001423 and the folded null constructor 0x00326BE6, and never destroys it.
struct AttributeModifierCategoryFrame
{
	AttributeModifierCategoryFrame() : frame(0) {}
	unsigned int frame;
};

class AttributeModifierPoolUpdate : public UpdateModule
{
public:
	AttributeModifierPoolUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~AttributeModifierPoolUpdate();
	virtual NameKeyType getModuleNameKey() const;
	int rva004031C9(int index);
	unsigned char isCategoryDisabled(int index);
	bool rva00403170(unsigned frame, const void *entry, int includeCategories);
	bool rva00403382(int attribute, float *bonus, int name);
	void rva00403415(int *mask, int value);
	bool rva00403448(int attribute, float *multiplier, int name, int includeCategories);
	void rva00403744(const AsciiString &name);
	bool addModifierToPool(const AsciiString &name, int duration);
protected:
	virtual void xfer(Xfer *xfer);
private:
	_STL::vector<Rva00297360Element> m_modifiers;
	unsigned int m_maxFrame;
	AttributeModifierCategoryFrame m_categoryFrames[15];
	unsigned int m_poolCounts[15];
};

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

// Retail's placement copy here is the rowed _Construct<BfmeStringRecord0040360E> at 0x00403639;
// bind the calls to that row rather than an unprovided _Construct<Rva00297360Element>.
struct BfmeStringRecord0040360E;
namespace _STL { template <> void _Construct<BfmeStringRecord0040360E, BfmeStringRecord0040360E>(
	BfmeStringRecord0040360E *, const BfmeStringRecord0040360E &); }
namespace _STL
{
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva00297360Element *dest, const Rva00297360Element &source)
{
	_Construct<BfmeStringRecord0040360E, BfmeStringRecord0040360E>(
		reinterpret_cast<BfmeStringRecord0040360E *>(dest),
		*reinterpret_cast<const BfmeStringRecord0040360E *>(&source));
}
}

// bfme link decl-only begin
namespace _STL { template <> void vector<Rva00297360Element,_STL::allocator<Rva00297360Element> >::_M_clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<Rva00297360Element *,Rva00297360Element,_STL::allocator<Rva00297360Element> >::deallocate(Rva00297360Element *,unsigned int); }
namespace _STL { template <> void allocator<Rva00297360Element>::deallocate(Rva00297360Element *,unsigned int) const; }
// bfme link decl-only end
void AttributeModifierPoolUpdate::xfer(Xfer *xfer)
{
	int storeCount;
	Xfer::Version version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->operator==(version);
	if (xfer->IsLoading()) {
		Rva002983DAVector *vec = reinterpret_cast<Rva002983DAVector *>(&m_modifiers);

		Rva00297360Element *last = vec->m_finish;
		Rva00297360Element *first = vec->m_start;
		vec->EraseRange(first, last);
		int count = 0;
		xfer->operator==(count);
		for (int i = 0; i < count; ++i) {
			Rva00368270 tmp(0, AsciiString(""));
			reinterpret_cast<Rva004031F3 *>(&tmp)->rva004031F3(
				reinterpret_cast<Obj *>(xfer), reinterpret_cast<Info *>(&version));
			m_modifiers.push_back(*reinterpret_cast<Rva00297360Element *>(&tmp));
		}
	} else {
		{
		storeCount = (int)(m_modifiers.end()-m_modifiers.begin());
		xfer->operator==(storeCount);
		}
		Rva002983DAVector *vec = reinterpret_cast<Rva002983DAVector *>(&m_modifiers);
		for (Rva00297360Element *cur = vec->m_start; cur != vec->m_finish; ++cur) {
			BfmeStringRecord0040360E tmp(*reinterpret_cast<BfmeStringRecord0040360E *>(cur));
			reinterpret_cast<Rva004031F3 *>(&tmp)->rva004031F3(
				reinterpret_cast<Obj *>(xfer), reinterpret_cast<Info *>(&version));
		}
	}
	if (version.m_currentVersion >= 2) {
		unsigned int *tail = reinterpret_cast<unsigned int *>(m_poolCounts);
		int n = 15;
		do {
			xfer->operator==(*reinterpret_cast<UnsignedInt *>((char *)tail - 0x3C));
			xfer->operator==(*reinterpret_cast<int *>(tail));
			++tail;
		} while (--n != 0);
	}
	UpdateModule::xfer(xfer);
}
