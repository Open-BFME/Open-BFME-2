// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// stlport
//
// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z, retail 0x0040426D, 321 bytes.
// Slot 3 (offset 0xC) of vtable 0x0083856C (class of ??1AttributeModifierPoolUpdate).
// Donor: BFME1 AttributeModifierPoolUpdateConstructor.cpp plus StealthUpdateXfer
// Xfer declaration (xferVersion 0x28 IsLoading 0x04 xferAsciiString 0x6C
// xferUnsignedInt 0x78 xferInt 0x7C xferBool 0x90). Layout from rowed
// AttributeModifierPoolUpdateCtor.cpp (UpdateModule base 0x20 plus modifier
// vector at +0x20 plus max frame at +0x2C plus 15 pool names at +0x30 plus
// 15 tallies at +0x6C). Evidence: vtable slot 3 callers none callees rowed
// EraseRange 0x2983DA push_back 0x403E3B Rva00368270 0x4034D5 rva004031F3
// 0x4031F3 releaseBuffer 0x36410 BfmeStringRecord 0x40360E UpdateModule xfer
// 0x44DF9F empty string g_Rva0107301CEmptyString Version 1 3 IsLoading gate.
#include <vector>
#include "ascii_string.h"

class Thing;
class ModuleData;
class Object;

typedef unsigned int UnsignedInt;

struct XferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
	unsigned short m_pad;
};

struct XferException
{
	char *text;
	int tag;
};

class Xfer
{
public:
	Xfer();
	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08();
	virtual void slot09();

	virtual Xfer &xferVersion(XferVersion *version);

	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;

	virtual Xfer &xferAsciiString(AsciiString &value);

	virtual void slot28() = 0;
	virtual void slot29() = 0;

	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
	virtual Xfer &xferInt(int &value);

	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;

	virtual Xfer &xferBool(bool &value);
};

extern const char g_Rva0107301CEmptyString[];

class Rva00297360Element
{
public:
	~Rva00297360Element();
private:
	int m_00;
	AsciiString m_04;
	int m_08;
	int m_0C;
};

class Rva00368270
{
public:
	Rva00368270(void *p, AsciiString name);
	~Rva00368270();
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
	~BfmeStringRecord0040360E();
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

// ?xfer@AttributeModifierPoolUpdate@@MAEXPAVXfer@@@Z present-unmatched
void AttributeModifierPoolUpdate::xfer(Xfer *xfer)
{
	char pad[28];
	(void)pad;
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->xferVersion(&version);
	if (xfer->IsLoading()) {
		Rva002983DAVector *vec = reinterpret_cast<Rva002983DAVector *>(&m_modifiers);
		Rva00297360Element *first = vec->m_start;
		Rva00297360Element *last = vec->m_finish;
		vec->EraseRange(first, last);
		int count = 0;
		xfer->xferInt(count);
		for (int i = 0; i < count; ++i) {
			Rva00368270 tmp(0, AsciiString(g_Rva0107301CEmptyString));
			reinterpret_cast<Rva004031F3 *>(&tmp)->rva004031F3(
				reinterpret_cast<Obj *>(xfer), reinterpret_cast<Info *>(&version));
			m_modifiers.push_back(*reinterpret_cast<Rva00297360Element *>(&tmp));
		}
	} else {
		int count = (int)m_modifiers.size();
		xfer->xferInt(count);
		Rva002983DAVector *vec = reinterpret_cast<Rva002983DAVector *>(&m_modifiers);
		Rva00297360Element *cur = vec->m_start;
		Rva00297360Element *end = vec->m_finish;
		while (cur != end) {
			BfmeStringRecord0040360E tmp(*reinterpret_cast<BfmeStringRecord0040360E *>(cur));
			reinterpret_cast<Rva004031F3 *>(&tmp)->rva004031F3(
				reinterpret_cast<Obj *>(xfer), reinterpret_cast<Info *>(&version));
			++cur;
		}
	}
	if (version.m_currentVersion >= 2) {
		unsigned int *tail = reinterpret_cast<unsigned int *>(m_poolCounts);
		int n = 15;
		do {
			xfer->xferUnsignedInt(*reinterpret_cast<UnsignedInt *>((char *)tail - 0x3C));
			xfer->xferInt(*reinterpret_cast<int *>(tail));
			++tail;
		} while (--n != 0);
	}
	UpdateModule::xfer(xfer);
}
