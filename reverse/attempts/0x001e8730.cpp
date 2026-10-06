// ?xfer@LocomotorSet@@MAEXPAVXfer@@@Z
// partial score=0.55 date=2026-10-06
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
// stlport
//
// ?xfer@LocomotorSet@@MAEXPAVXfer@@@Z, retail 0x001E8730, 413 bytes
// (Ghidra FUN_005e8730; next function 0x001E88CE).
// Slot 3 of the LocomotorSet vtable at 0x00BDE950 (slots: dtor 0x001E8F03,
// name 0x001E70BC returning "LocomotorSet", xfer here, findLocomotor).
// Source path recorded beside the vtable names this TU Locomotor.cpp.
//
// Donor: the LocomotorSet::xfer body already present-unmatched in the sibling
// TU Code/GameEngine/Source/GameLogic/Object/Locomotor.cpp. BFME 2 keeps the
// donor's shape (Version 1/2 pair through slot 0x28, WORD count through slot
// 0x80, save walk of template names through slot 0x6C plus snapshots through
// slot 0x30, load emptiness guard via FormatText 0x0060C36E plus Throw
// 0x00629094, per-entry lookup 0x001E6FEA plus newLocomotor 0x001E4A81 plus
// push_back 0x004DFCB0, tail Int +0x10 through slot 0x7C then Bool +0x14
// through slot 0x90). Layout matches the landed sibling
// LocomotorSet_addLocomotor_Rva001E88CE.cpp: locomotors vector +4, valid
// surfaces +0x10, downhill-only +0x14.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

template <typename T> struct BfmeStringData;

#include "ascii_string.h"


typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef int Int;
typedef Int NameKeyType;

class UnicodeString;
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
class Snapshot
{
};
class RGBAColorReal;
class RGBAColorInt;
typedef UnsignedByte XferVersion;

enum XferMode
{
	XFER_SAVE,
	XFER_LOAD
};

class Xfer
{
public:
	virtual ~Xfer();
	XferVersion m_versionData;
	XferVersion m_versionCurrent;

	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual Bool IsCRC() const;
	virtual Bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void xferSnapshot(Snapshot *snapshot);
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual Xfer &xferVersion(XferVersion *versionData, XferVersion currentVersion);
	virtual void v13() = 0;
	virtual XferMode getXferMode();
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void xferAsciiString(AsciiString *str);
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void xferInt(Int *value);
	virtual void xferBool(Bool *value);
	virtual void v33() = 0;
	virtual void xferUnsignedShort(UnsignedShort *value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

class Locomotor : public Snapshot
{
public:
	AsciiString getTemplateName();
};

class LocomotorTemplate;
class LocomotorStore;

NameKeyType Rva0009FA65NameToKey(const AsciiString &str);

class LocomotorStore
{
public:
	const LocomotorTemplate *findLocomotorTemplate(NameKeyType key);
	Locomotor *newLocomotor(const LocomotorTemplate *tmpl);
};

extern LocomotorStore *TheLocomotorStore;

class LocomotorSet
{
protected:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void xfer(Xfer *xfer);
private:
	_STL::vector<Locomotor *> m_locomotors;
	Int m_validLocomotorSurfaces;
	Bool m_downhillOnly;
};

void LocomotorSet::xfer(Xfer *xfer)
{
	LocomotorSet *me = this;
	UnsignedShort count = (UnsignedShort)me->m_locomotors.size();
	if (xfer->getXferMode() == XFER_SAVE) {
		for (Locomotor **p = me->m_locomotors.begin(); p != me->m_locomotors.end(); ++p) {
			AsciiString name = (*p)->getTemplateName();
			xfer->xferAsciiString(&name);
			xfer->xferSnapshot(*p);
		}
		return;
	}
	if (!me->m_locomotors.empty()) {
		throw XferException(4, (const char *)0);
	}
	AsciiString name;
	for (UnsignedShort i = 0; i < count; ++i) {
		xfer->xferAsciiString(&name);
		const LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(Rva0009FA65NameToKey(name));
		Locomotor *loco = TheLocomotorStore->newLocomotor(lt);
		xfer->xferSnapshot(loco);
		me->m_locomotors.push_back(loco);
	}
	xfer->xferInt(&me->m_validLocomotorSurfaces);
	xfer->xferBool(&me->m_downhillOnly);
}
