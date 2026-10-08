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

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_pad;
};

struct XferException
{
	char *text;
	int tag;
};

struct AsciiBuffer
{
	int m_refCount;
	unsigned short m_length;
};

#include "ascii_string.h"


class Xfer
{
public:
	class Version;

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

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);
extern int g_rva008ffd18ThrowInfo;

class Thing;
class ModuleData;
class Object;
class ThingTemplate;

class Rva002D06CA
{
public:
	void *rva002D06CA(const AsciiString *key);
};

extern class ThingFactory *TheThingFactory;

class ThingTemplate
{
public:
	unsigned char m_pad[0x64];
	AsciiString m_name;
};

class BehaviorModuleBase
{
public:
	virtual void unused();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void unused();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
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
	void xfer(Xfer *xfer);
};

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

class SpawnExtraBase
{
public:
	virtual void spawnExtraAnchor();
};

class UpgradeMux
{
public:
	UpgradeMux();
	virtual void upgradeMuxAnchor();

protected:
	virtual void upgradeMuxXfer(Xfer *xfer);

private:
	bool m_upgradeExecuted;
};

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
	XferException error;
	XferVersion version;
	BehaviorModule::xfer(xfer);
	version.m_version = 1;
	version.m_currentVersion = 3;
	xfer->xferVersion(&version);
	if (version.m_currentVersion >= 3)
		UpdateModule::xfer(xfer);
	if (xfer->IsLightCRC())
		return;
	xfer->xferBool(m_initialBurstTimesInited);
	if (version.m_currentVersion >= 2) {
		UpgradeMux::upgradeMuxXfer(xfer);
		xfer->xferUnsignedInt(m_initialBurstCountdown);
	}
	AsciiString tmp;
	tmp = m_spawnTemplate != NULL ? m_spawnTemplate->m_name : AsciiString::TheEmptyString;
	xfer->xferAsciiString(tmp);
	if (xfer->IsLoading()) {
		m_spawnTemplate = NULL;
		if (!tmp.isEmpty()) {
			m_spawnTemplate = (const ThingTemplate *)((Rva002D06CA *)TheThingFactory)->rva002D06CA(&tmp);
			if (m_spawnTemplate == NULL) {
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (const _s__ThrowInfo *)&g_rva008ffd18ThrowInfo); __assume(0);
			}
		}
	}
	xfer->xferInt(m_oneShotCountdown);
	xfer->xferInt(m_framesToWait);
	xfer->xferInt(m_firstBatchCount);
	if (xfer->IsLoading())
		m_replacementTimes.clear();
	Rva00460216XferList(xfer, &m_replacementTimes);
	Rva0036ABAFXfer(xfer, &m_spawnIDs);
	xfer->xferBool(m_active);
	xfer->xferBool(m_aggregateHealthFlag);
	xfer->xferInt(m_spawnCount);
	xfer->xferUnsignedInt(m_selfTaskingSpawnCount);
}
// ?g_rva008ffd18ThrowInfo@@3HA: the global at VA 0xcffd18 is ?g_guardTargetTypeThrowInfo@@3HA.
#pragma comment(linker, "/alternatename:?g_rva008ffd18ThrowInfo@@3HA=?g_guardTargetTypeThrowInfo@@3HA")
