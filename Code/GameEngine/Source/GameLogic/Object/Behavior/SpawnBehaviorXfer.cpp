// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?xfer@SpawnBehavior@@MAEXPAVXfer@@@Z, retail 0x00460586, 392 bytes.
// Slot 3 (offset 0x0C) of vtable 0x008426AC (class of ??1SpawnBehavior rowed
// in SpawnBehaviorDtor.cpp). Calls rowed BehaviorModule xfer 0x004C9C7D,
// version {1,3} via Xfer slot 0x28 gating UpdateModule xfer via rowed
// 0x0044DF9F on current>=3, IsLightCRC early-out via Xfer slot 0x10,
// bool at +0x52 via Xfer slot 0x90, UpgradeMux at +0x30 via rowed
// upgradeMuxXfer 0x004CE397, template-name round-trip through TheThingFactory
// with FormatText 0x0060C36E plus Throw 0x00629094, ints at +0x3C/+0x40/+0x44
// via Xfer slot 0x7c, lists at +0x48/+0x4C via rowed helpers, bools at
// +0x50/+0x51 via Xfer slot 0x90, int at +0x54 via slot 0x7c, tail at +0x58
// via slot 0x78. Layout is the rowed SpawnBehaviorCtor shape.
#include <list>

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int>*, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<int>*)0).deallocate(p, n); }
}

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;


// Retail ThrowInfo identifies the 8-byte XferException class and its
// established constructor, copy constructor and destructor providers.
#include "../../../../Include/Common/XferException.h"

struct AsciiBuffer
{
	int m_refCount;
	unsigned short m_length;
};

#include "ascii_string.h"


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
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};


class Thing;
class ModuleData;
class Object;
class ThingTemplate;

#include "../../../../Include/Common/ThingFactory.h"

extern class ThingFactory *TheThingFactory;

#include "../../../../Include/Common/ThingTemplate.h"

// BehaviorModule's xfer is the base call below; no BehaviorModule-derived table is emitted here.
#define BFME_BEHAVIORMODULE_XFER
#include "../../../../Include/GameLogic/Module/UpdateModule.h"

class SpawnBehaviorInterface
{
public:
	virtual void spawnBehaviorAnchor();
};

class DieModuleInterface
{
public:
	virtual void dieAnchor();
};

class DamageModuleInterface
{
public:
	virtual void damageAnchor();
};

#include "../../../../Include/Common/SpawnExtraBase.h"

#include "../../../../Include/GameLogic/Module/UpgradeMux.h"

class SpawnBehavior : public UpdateModule,
	public SpawnBehaviorInterface,
	public DieModuleInterface,
	public DamageModuleInterface,
	public SpawnExtraBase,
	public UpgradeMux
{
protected:
	virtual void xfer(Xfer *xfer);

private:
	const ThingTemplate *m_spawnTemplate;
	int m_oneShotCountdown;
	int m_framesToWait;
	int m_firstBatchCount;
	_STL::list<int> m_replacementTimes;
	_STL::list<int> m_spawnIDs;
	bool m_active;
	bool m_aggregateHealthFlag;
	bool m_initialBurstTimesInited;
	unsigned char m_pad53;
	int m_spawnCount;
	UnsignedInt m_selfTaskingSpawnCount;
	UnsignedInt m_initialBurstCountdown;
	AsciiString *m_templateNameIterator;
};

Xfer *Rva00460216XferList(Xfer *xfer, _STL::list<int> *list);
Xfer *Rva0036ABAFXfer(Xfer *xfer, _STL::list<int> *list);

void SpawnBehavior::xfer(Xfer *xfer)
{
	Xfer::Version version;
	BehaviorModule::xfer(xfer);
	version.m_version = 1;
	version.m_currentVersion = 3;
	*xfer == version;
	if (version.m_currentVersion >= 3)
		UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	*xfer == m_initialBurstTimesInited;
	if (version.m_currentVersion >= 2) {
		UpgradeMux::upgradeMuxXfer(xfer);
		*xfer == m_initialBurstCountdown;
	}
	AsciiString tmp;
	tmp = m_spawnTemplate != NULL ? m_spawnTemplate->m_nameString : AsciiString::TheEmptyString;
	*xfer == tmp;
	if (xfer->IsLoading()) {
		m_spawnTemplate = NULL;
		if (!tmp.isEmpty()) {
			m_spawnTemplate = TheThingFactory->findTemplate(tmp);
			if (m_spawnTemplate == NULL) {
				throw XferException(5, 0);
			}
		}
	}
	*xfer == m_oneShotCountdown;
	*xfer == m_framesToWait;
	*xfer == m_firstBatchCount;
	if (xfer->IsLoading())
		m_replacementTimes.clear();
	Rva00460216XferList(xfer, &m_replacementTimes);
	Rva0036ABAFXfer(xfer, &m_spawnIDs);
	*xfer == m_active;
	*xfer == m_aggregateHealthFlag;
	*xfer == m_spawnCount;
	*xfer == m_selfTaskingSpawnCount;
}
