// cl: /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
//
// ?xfer@SpecialAbilityUpdate@@MAEXPAVXfer@@@Z, retail 0x0044F996, 402 bytes.
// Slot 3 (offset 0x0C) of vtable 0x0083FBA8 (class of rowed
// ??1SpecialAbilityUpdate@@UAE@XZ in SpecialAbilityUpdateDtor.cpp).
//
// Donor: ZH SpecialAbilityUpdate.cpp xfer (Version plus base UpdateModule
// xfer plus bool/uint/ObjectID/Coord/int/list/entries/bool/user/bool/float)
// plus BFME2 FlammableUpdateXfer recipe (base UpdateModule xfer via rowed
// 0x0044DF9F then IsLightCRC early-out via Xfer slot 0x10 then Version(1,3)
// via Xfer slot 0x28 reusing [ebp+8] then TheAudio xferAudioHandle at
// AudioManager slot 0x160 for two handles plus version-gated tail).
// Layout is the rowed 0x88-byte class from ctor 0x0044EF5E and friendNew
// 0x0024A847 (UpdateModule base 0x20 plus trailing vptr at +0x20 giving
// +0x24 start plus list<int> at +0x64 plus uint at +0x68 plus float at +0x70
// plus 9 bools plus two audio handles plus gated Coord/uint/int tail).
// Callers include 0x00490CA4 0x00492606 0x00492E31 0x00494E78 0x0049C425.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
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

#include "../../../../Include/Common/BfmeXfer.h"

#include "../../../../Include/Common/XferVersion.h"

typedef unsigned int AudioHandle;

struct BfmeAudioEventPrefix136;
class Xfer;
struct AbilityMiscAudio;
#include "../../../../Include/Common/GameAudio.h"

// TheAudio (VA 0x00DFE6E8) is defined in AnimationSoundClientBehaviorCtor.cpp.
extern AudioManager *TheAudio;

#include "../../../Common/GameLogicObjectLookupView.h"

void XferObjectID(Xfer *xfer, ObjectID *objectID);

typedef _STL::list<int> ListInt;

Xfer *Rva0036ABAFXfer(Xfer *xfer, ListInt *list);

#include "../../../../../Libraries/Include/Lib/Coord3DBase.h"

#include "../../../../Include/Common/ObjectModule.h"

#include "../../../../Include/GameLogic/Module/BehaviorModule.h"
#include "../../../../Include/GameLogic/Module/UpdateModule.h"


class SpecialTrailing { public: virtual void trailingSlot(); };


extern GameLogic *TheGameLogic;

#include "../../../../Include/Common/Overridable.h"
#include "../../../../Include/Common/SpecialPower.h"
class TextureClass;
#include "../../../../../Libraries/Source/WWVegas/WW3D2/MaterialPassClass.h"
enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};
enum WeaponLockType
{
	WEAPONLOCK_LOCKED = 1
};
class Object
{
public:
	bool setWeaponLock(WeaponSlotType weaponSlot, WeaponLockType lockType);
	char m_pad00[0x330];
	MaterialPassClass m_pass330;
};
struct ModuleDataFull
{
	char m_pad00[0x38];
	const SpecialPowerTemplate *m_specialPowerTemplate38;
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialTrailing
{
public:
	void killSpecialObjects();
protected:
	virtual void xfer(Xfer *xfer);
	void validateSpecialObjects();

private:
	int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	unsigned int m_30;
	AudioHandle m_34;
	AudioHandle m_38;
	unsigned int m_3C;
	ObjectID m_40;
	Coord3DBase m_44;
	Coord3DBase m_50;
	int m_5C;
	int m_60;
	ListInt m_64;
	unsigned int m_68;
	unsigned int m_6C;
	float m_70;
	bool m_74;
	unsigned int m_78;
	bool m_7C;
	bool m_7D;
	bool m_7E;
	bool m_7F;
	bool m_80;
	bool m_81;
	bool m_82;
	bool m_83;
	unsigned int m_84;
};

void SpecialAbilityUpdate::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	Xfer::Version version(1, 3);
	*xfer == version;
	*xfer == m_74;
	*xfer == m_3C;
	*xfer == m_28;
	XferObjectID(xfer, &m_40);
	*xfer == m_44;
	*xfer == m_5C;
	*xfer == m_24;
	*xfer == m_2C;
	Rva0036ABAFXfer(xfer, &m_64);
	*xfer == m_68;
	*xfer == m_7D;
	xfer->XferRawBytes(&m_30, 4);
	*xfer == m_7E;
	*xfer == m_7F;
	*xfer == m_80;
	*xfer == m_81;
	*xfer == m_70;
	*xfer == m_82;
	*xfer == m_83;
	*xfer == m_7C;
	TheAudio->xferAudioHandle(xfer, &m_34);
	TheAudio->xferAudioHandle(xfer, &m_38);
	if (version.m_minimum > 1) {
		*xfer == m_78;
		*xfer == m_50;
	}
	if (version.m_minimum >= 3) {
		*xfer == m_60;
	}
}

void SpecialAbilityUpdate::validateSpecialObjects()
{
	ListInt::iterator it = m_64.begin();
	while (it != m_64.end()) {
		ListInt::iterator prev = it;
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
		++it;
		if (!obj) {
			m_64.erase(prev);
			--m_68;
		}
	}
}

void SpecialAbilityUpdate::killSpecialObjects()
{
	const ModuleDataFull *md = (const ModuleDataFull *)m_moduleData;
	const SpecialPowerTemplate *holder = md->m_specialPowerTemplate38;
	int zero = 0;
	for (ListInt::iterator it = m_64.begin(); it != m_64.end(); ++it) {
		Object *obj = TheGameLogic->findObjectByID((ObjectID)*it);
		if (obj)
			TheGameLogic->destroyObject(obj);
	}
	m_64.clear();
	m_68 = zero;
	if (holder->getFO()->m_type != (SpecialPowerType)0x15)
		return;
	Object *object = m_object;
	if (object->m_pass330.Peek_Texture(zero) == 0)
		return;
	object->setWeaponLock((WeaponSlotType)zero, (WeaponLockType)1);
}
