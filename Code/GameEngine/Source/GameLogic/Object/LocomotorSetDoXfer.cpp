// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /Ireference/open-bfme-1/inputs/vendor/stlport /O1 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
//
// ?DoXfer@LocomotorSet@@UAEXPAVXfer@@@Z, retail 0x001E8730, 413 bytes.
// Target identity: WorldBuilder names 0x005E8730 LocomotorSet::DoXfer in
// Locomotor.cpp (lines 3753-3765); its target body xfers the LocomotorSet
// vector and scalar fields. The BFME1 GeneralsMD donor calls this operation
// LocomotorSet::xfer and supplies the save/load order and error behavior.
// Target-specific: Version(1,2) and a trailing bool at object +0x15 are read
// from retail; the GeneralsMD layout ends at m_downhillOnly +0x14.
// Retail's call at 0x005E888E targets the 49-byte pointer-vector insertion
// helper at RVA 0x004DFCB0, already matched under vector<const ModuleData *>.
// The call uses the same 4-byte pointer reference ABI; the Locomotor* field
// identity and its three-pointer layout are established separately by target
// accesses at +0x04/+0x08/+0x0C.
#include <vector>
#include "ascii_string.h"
#include "Common/Snapshot.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
typedef unsigned short UnsignedShort;
typedef bool Bool;

class AsciiString;
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
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
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
	virtual void SkipBadBlock(Snapshot &, unsigned int);
	virtual Xfer &XferRawBytes(void *, unsigned int);
	virtual Xfer &operator==(bool &);
	virtual Xfer &operator==(char &);
	virtual Xfer &operator==(unsigned char &);
	virtual Xfer &operator==(short &);
	virtual Xfer &operator==(unsigned short &);
	virtual Xfer &operator==(int &);
	virtual Xfer &operator==(unsigned int &);
	virtual Xfer &operator==(__int64 &);
	virtual Xfer &operator==(float &);
	virtual Xfer &operator==(AsciiString &);
	virtual Xfer &operator==(UnicodeString &);
	virtual Xfer &operator==(PooledString &);
	virtual Xfer &operator==(Coord3DBase &);
	virtual Xfer &operator==(ICoord3D &);
	virtual Xfer &operator==(Region3D &);
	virtual Xfer &operator==(IRegion3D &);
	virtual Xfer &operator==(Coord2D &);
	virtual Xfer &operator==(ICoord2D &);
	virtual Xfer &operator==(Region2D &);
	virtual Xfer &operator==(IRegion2D &);
	virtual Xfer &operator==(RealRange &);
	virtual Xfer &operator==(RGBColor &);
	virtual Xfer &operator==(RGBAColorReal &);
	virtual Xfer &operator==(RGBAColorInt &);
	virtual Xfer &operator==(Snapshot &);
	virtual Xfer &operator==(XferUnknown11 &) = 0;
	virtual Xfer &operator==(Version &);
	virtual Xfer &XferEnum(const char *, void *, unsigned int);

protected:
	virtual void XferData(unsigned int, void *, unsigned int) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}
	unsigned char m_current;
	unsigned char m_minimum;
};

class Locomotor : public Snapshot
{
public:
	virtual ~Locomotor();
	AsciiString getTemplateName() const;
};

class LocomotorTemplate;
class ModuleData;
class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int);
	Locomotor *newLocomotor(const LocomotorTemplate *, Bool);
};
extern LocomotorStore *TheLocomotorStore;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &);
};
extern NameKeyGenerator *TheNameKeyGenerator;


typedef std::vector<Locomotor *> LocomotorVector;
// This only names the already-matched generic pointer-vector insertion body.
typedef std::vector<const ModuleData *> ModuleDataPointerVector;
class LocomotorSet : public Snapshot
{
public:
	virtual void DoXfer(Xfer *xfer);

private:
	LocomotorVector m_locomotors;             // +0x04
	int m_validLocomotorSurfaces;             // +0x10
	Bool m_downhillOnly;                      // +0x14
	Bool m_targetVersionTwoFlag;              // +0x15
};

struct XferException
{
	char *text;
	int tag;
};
struct _s__ThrowInfo;
extern int g_guardTargetTypeThrowInfo;
extern "C" XferException *__cdecl bfmeFormatText(XferException *, int, ...);
extern "C" void __stdcall _CxxThrowException(void *, const _s__ThrowInfo *);

static __forceinline LocomotorTemplate *requireLocomotorTemplate(LocomotorTemplate *lt)
{
	if (lt == 0) {
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
		__assume(0);
	}
	return lt;
}

void LocomotorSet::DoXfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	Xfer::Version version(1, 2);
	*xfer == version;

	Locomotor **vectorState = reinterpret_cast<Locomotor **>(&m_locomotors);
	UnsignedShort count = static_cast<UnsignedShort>(vectorState[1] - vectorState[0]);
	*xfer == count;

	if (xfer->IsStoring()) {
		for (LocomotorVector::iterator it = m_locomotors.begin(); it != m_locomotors.end(); ++it) {
			Locomotor *loco = *it;
			AsciiString name = loco->getTemplateName();
			*xfer == name;
			*xfer == *loco;
		}
	} else {
		if (vectorState[0] != vectorState[1])
		{
			XferException error;
			bfmeFormatText(&error, 4, 0);
			_CxxThrowException(&error, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
			__assume(0);
		}

		for (UnsignedShort i = 0; i < count; ++i) {
			AsciiString name;
			*xfer == name;
			LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(
				TheNameKeyGenerator->nameToKey(name));
			Locomotor *loco = TheLocomotorStore->newLocomotor(
				requireLocomotorTemplate(lt), false);
			*xfer == *loco;
			reinterpret_cast<ModuleDataPointerVector *>(&m_locomotors)->push_back(
				*reinterpret_cast<const ModuleData * const *>(&loco));
		}
	}

	*xfer == m_validLocomotorSurfaces;
	*xfer == m_downhillOnly;
	if (version.m_minimum >= 2)
		*xfer == m_targetVersionTwoFlag;
}
