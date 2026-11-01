// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target: 0x002CDD47, 579B; Weapon vtable 0x0080214C slot 3.
// Field offsets and Xfer virtual slots follow the target body; template lookup
// signature is corroborated by the matched WeaponStore callee.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void ** __copy_ptrs<void **, void **>(void **, void **, void **, __true_type); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::erase(void **, void **); }
// bfme link decl-only end
// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
// Preserve STLport's clear operation without emitting an unused competing
// out-of-line copy in this unit.
template<> __declspec(dllimport) __forceinline void vector<void*>::clear()
{ erase(begin(),end()); }
}

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

#include "../../../Include/Common/BfmeXfer.h"

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

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;

// Retail ThrowInfo names the 8-byte XferException class and its rowed
// copy constructor and destructor (see Common/System/XferException.cpp).
#include "../../../Include/Common/XferException.h"

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
		const WeaponTemplate *weaponTemplate = TheWeaponStore->findWeaponTemplate(nameTmp);
		m_template = weaponTemplate;
		if (!weaponTemplate) {
			throw XferException(5, 0);
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
	const ModuleData *moduleData;
	if (xfer->IsStoring()) {
		for (const ModuleData **it = (const ModuleData **)m_scatterTargets.begin(); it != (const ModuleData **)m_scatterTargets.end(); ++it) {
			moduleData = *it;
			*xfer == *(int *)&moduleData;
		}
	} else {
		_STL::vector<void *> *targets = (_STL::vector<void *> *)&m_scatterTargets;
		targets->clear();
		UnsignedShort idx = 0;
		for (; idx < count; ++idx) {
			*xfer == *(int *)&moduleData;
			m_scatterTargets.push_back(moduleData);
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
