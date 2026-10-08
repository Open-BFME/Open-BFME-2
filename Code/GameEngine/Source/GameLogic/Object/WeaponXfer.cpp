// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target: 0x002CDD47, 579B; Weapon vtable 0x0080214C slot 3.
// Field offsets and Xfer virtual slots follow the target body; template lookup
// signature is corroborated by the matched WeaponStore callee.
#include <vector>
#include "ascii_string.h"

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
class Thing;
class ModuleData;
class Object;
class DamageInfo;

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
	Version(unsigned char a, unsigned char b) : m_a(a), m_b(b) {}
	unsigned char m_a;
	unsigned char m_b;
};

enum ObjectID
{
	OBJECTID_NONE = 0
};

enum WeaponSlotType
{
	WEAPON_SLOT_PRIMARY = 0
};

class WeaponTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad00[8];
	AsciiString m_name;
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};

extern WeaponStore *TheWeaponStore;
extern int g_guardTargetTypeThrowInfo;

struct _s__ThrowInfo;
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(XferException *result, int tag, const char *format, ...);

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferWeaponSlotType(Xfer *xfer, int *slot);
void XferWeaponStatus(Xfer *xfer, int *status);

class Weapon
{
public:
	virtual ~Weapon();
	virtual void v1();
	virtual void v2();
	virtual void xfer(Xfer *xfer);
private:
	const WeaponTemplate *m_template; // +4
	ObjectID m_ownerID; // +8
	WeaponSlotType m_wslot; // +0xC
	int m_status; // +0x10
	unsigned int m_ammoInClip; // +0x14
	unsigned int m_whenWeCanFireAgain; // +0x18
	unsigned int m_whenPreAttackFinished; // +0x1C
	unsigned int m_whenLastReloadStarted; // +0x20
	unsigned int m_lastFireFrame; // +0x24
	unsigned int m_projectileStreamID; // +0x28
	unsigned int m_unknown2C; // +0x2C
	unsigned int m_suspendFXFrame; // +0x30
	int m_maxShotCount; // +0x34
	int m_curBarrel; // +0x38
	int m_numShotsForCurBarrel; // +0x3C
	_STL::vector<const ModuleData *> m_scatterTargets; // +0x40
	bool m_pitchLimited; // +0x4C
	char m_pad4D[3];
	unsigned int m_leechWeaponRangeActive; // +0x50
	int m_unknown54; // +0x54
	int m_tailState; // +0x58
	ObjectID m_extra5C; // +0x5C
};

void Weapon::xfer(Xfer *xfer)
{
	Xfer::Version ver(1, 3);
	*xfer == ver;
	AsciiString nameTmp(m_template ? m_template->getName() : AsciiString(""));
	*xfer == nameTmp;
	if (xfer->IsLoading()) {
		const WeaponTemplate *tmpl = TheWeaponStore->findWeaponTemplate(nameTmp);
		m_template = tmpl;
		if (!tmpl) {
			XferException err;
			bfmeFormatText(&err, 5, 0);
			_CxxThrowException(&err, (const _s__ThrowInfo *)&g_guardTargetTypeThrowInfo);
			__assume(0);
		}
	}
	XferObjectID(xfer, &m_ownerID);
	XferWeaponSlotType(xfer, (int *)&m_wslot);
	*xfer == m_ammoInClip;
	*xfer == m_whenWeCanFireAgain;
	*xfer == m_whenPreAttackFinished;
	*xfer == m_whenLastReloadStarted;
	*xfer == m_lastFireFrame;
	*xfer == m_projectileStreamID;
	*xfer == m_unknown2C;
	*xfer == m_maxShotCount;
	*xfer == m_curBarrel;
	*xfer == m_numShotsForCurBarrel;
	UnsignedShort count = (UnsignedShort)m_scatterTargets.size();
	*xfer == count;
	const ModuleData *tmp;
	if (xfer->IsStoring()) {
		for (const ModuleData **it = (const ModuleData **)m_scatterTargets.begin(); it != (const ModuleData **)m_scatterTargets.end(); ++it) {
			tmp = *it;
			*xfer == *(int *)&tmp;
		}
	} else {
		_STL::vector<void *> *targets = (_STL::vector<void *> *)&m_scatterTargets;
		targets->clear();
		UnsignedShort idx = 0;
		for (; idx < count; ++idx) {
			*xfer == *(int *)&tmp;
			m_scatterTargets.push_back(tmp);
		}
	}
	*xfer == m_pitchLimited;
	*xfer == m_leechWeaponRangeActive;
	*xfer == m_unknown54;
	if (!xfer->IsLightCRC()) {
		XferWeaponStatus(xfer, &m_status);
		*xfer == m_suspendFXFrame;
	}
	if (ver.m_b >= 2)
		*xfer == m_tailState;
	if (ver.m_b >= 3)
		XferObjectID(xfer, &m_extra5C);
}
