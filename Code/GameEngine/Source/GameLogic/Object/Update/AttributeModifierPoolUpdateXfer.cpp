// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
//
// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z, retail 0x0040426D, 321 bytes.
// Slot 3 (offset 0xC) of vtable 0x0083856C (class of ??1AttributeModifierPoolUpdate).
// Donor: BFME1 AttributeModifierPoolUpdateConstructor.cpp plus StealthUpdateXfer
// Xfer declaration (xferVersion 0x28 IsLoading 0x04 xferAsciiString 0x6C
// xferUnsignedInt 0x78 xferInt 0x7C xferBool 0x90). Layout from rowed
// constructor in AttributeModifierPoolUpdate.cpp (UpdateModule base 0x20 plus modifier
// vector at +0x20 plus max frame at +0x2C plus 15 pool names at +0x30 plus
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
#include <vector>
#include "ascii_string.h"

class Thing;
class ModuleData;
class Object;

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
	~Rva00297360Element();
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
};

class Rva00368270
{
public:
	Rva00368270(void *p, AsciiString name);
private:
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
};

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
	virtual void f31(Rva00297360Element *ctx);
};

struct Info
{
	char m00;
	unsigned char m01;
};

class Rva004031F3
{
public:
	void rva004031F3(Obj *obj, Info *info);
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
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
};

class UpdateModuleInterface
{
public:
	virtual void update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class AttributeModifierPoolUpdate : public UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
private:
	_STL::vector<Rva00297360Element> m_modifiers;
	unsigned int m_maxFrame;
	AsciiString m_poolNames[15];
	unsigned int m_poolCounts[15];
};

// bfme link decl-only begin
namespace _STL { template <> Rva00297360Element * __uninitialized_copy<Rva00297360Element *,Rva00297360Element *>(Rva00297360Element *,Rva00297360Element *,Rva00297360Element *,_STL::__false_type const &); }
namespace _STL { template <> Rva00297360Element * __uninitialized_fill_n<Rva00297360Element *,unsigned int,Rva00297360Element>(Rva00297360Element *,unsigned int,Rva00297360Element const &,_STL::__false_type const &); }
namespace _STL { template <> unsigned int const & max<unsigned int>(unsigned int const &,unsigned int const &); }
namespace _STL { template <> void vector<Rva00297360Element,_STL::allocator<Rva00297360Element> >::_M_clear(); }
namespace _STL { template <> void vector<Rva00297360Element,_STL::allocator<Rva00297360Element> >::_M_insert_overflow(Rva00297360Element *,Rva00297360Element const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> Rva00297360Element * allocator<Rva00297360Element>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<Rva00297360Element *,Rva00297360Element,_STL::allocator<Rva00297360Element> >::deallocate(Rva00297360Element *,unsigned int); }
namespace _STL { template <> void allocator<Rva00297360Element>::deallocate(Rva00297360Element *,unsigned int) const; }
namespace _STL { template <> void vector<Rva00297360Element,_STL::allocator<Rva00297360Element> >::push_back(Rva00297360Element const &); }
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
