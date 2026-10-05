// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??0TransportContainModuleData@@QAE@XZ, retail 0x00468301, 468 bytes.
// TransportContain data ctor over INI table 0x00C44648 (Slots at +0x98,
// ExitPitchRate at +0x9C, ExitBone at +0xA0, HealthRegen at +0xA8, ExitDelay
// at +0xAC, five FixedStorages at +0xB0/+0xCC/+0xE8/+0x104/+0x120, bools at
// +0x13C..+0x142, GrabWeapon at +0x144, FireGrab at +0x148, Condition at
// +0x14C (-1), ShouldThrow at +0x150, ThrowDelay at +0x154, ThrowVelocity at
// +0x158 (3 floats), LandingWarhead at +0x164, FadeFilter at +0x168,
// FadeEnter at +0x16C, FadeExit at +0x16D, EnterFade at +0x170, ExitFade at
// +0x174, FadeReverse at +0x178, ReleaseSnappyness at +0x17C (0.7f)).
// Donor is ZH TransportContain.cpp (slot 0, pitch 0, exit-bone empty,
// health 0, delay 0, INFANTRY mask). Base is the pinned OpenContainModuleData
// ctor at 0x00465124 (0x98 bytes, vtable 0x00C43658); derived installs
// vtable 0x00C442F8. Callers are the TransportContain data factory plus
// derived base-calls from HordeTransport 0x00477D64 and SiegeEngine
// 0x0047C93A. Shape follows DynamicPortalBehaviourModuleDataCtor (Fixed
// temps from 0x00DFEFA4 through initFromStorages/applyFilter) over
// ProductionUpdateModuleDataCtor (EH states via empty-base trick).
#include <list>
#include <vector>

struct BfmePod8
{
	int a[2];
};

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

#include "ascii_string.h"

extern unsigned char g_00DFEFA4StoragePrototype[28];

class BfmeFixedStorage0004543D
{
public:
	__declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva003623E5Member
{
public:
	Rva003623E5Member();
	~Rva003623E5Member();
	void initFromStorages(BfmeFixedStorage0004543D first, BfmeFixedStorage0004543D second);

private:
	int m_x;
};

class Rva003623E5Filter
{
public:
	Rva003623E5Filter();
	~Rva003623E5Filter();
	void applyFilter(BfmeFixedStorage0004543D storage);

private:
	int m_x;
};

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

protected:
	unsigned char m_pad04[0x40 - 4];
	Rva003623E5Member m_filter40;
	Rva003623E5Filter m_filter44;
	unsigned char m_pad48[0x98 - 0x48];
};

struct ThrowOutVelocity
{
	ThrowOutVelocity() : m_x(0.0f), m_y(0.0f), m_z(0.0f) {}
	float m_x;
	float m_y;
	float m_z;
};

class TransportContainModuleData : public OpenContainModuleData
{
public:
	TransportContainModuleData();
	virtual ~TransportContainModuleData();

private:
	int m_slotCapacity;
	float m_exitPitchRate;
	AsciiString m_exitBone;
	_STL::list<BfmePod8> m_initialPayload;
	float m_healthRegen;
	int m_exitDelay;
	BfmeFixedStorage0004543D m_typeOneForWeaponSet;
	BfmeFixedStorage0004543D m_typeTwoForWeaponSet;
	BfmeFixedStorage0004543D m_typeOneForWeaponState;
	BfmeFixedStorage0004543D m_typeTwoForWeaponState;
	BfmeFixedStorage0004543D m_typeThreeForWeaponState;
	bool m_forceOrientationContainer;
	bool m_canGrabStructure;
	bool m_scatterNearbyOnExit;
	bool m_orientLikeContainerOnExit;
	bool m_goAggressiveOnExit;
	bool m_resetMoodCheckTimeOnExit;
	bool m_destroyRidersWhoAreNotFreeToExit;
	int m_grabWeapon;
	bool m_fireGrabWeaponOnVictim;
	int m_conditionForEntry;
	bool m_shouldThrowOutPassengers;
	int m_throwOutPassengersDelay;
	ThrowOutVelocity m_throwOutVelocity;
	int m_throwOutPassengersLandingWarhead;
	Rva003623E5Member m_fadeFilter;
	bool m_fadePassengerOnEnter;
	bool m_fadePassengerOnExit;
	float m_enterFadeTime;
	float m_exitFadeTime;
	bool m_fadeReverse;
	float m_releaseSnappyness;
	_STL::vector<BfmeE16> m_upgradeTrigger;
};

TransportContainModuleData::TransportContainModuleData()
	: OpenContainModuleData()
	, m_slotCapacity(0)
	, m_exitPitchRate(0.0f)
	, m_healthRegen(0.0f)
	, m_exitDelay(0)
	, m_typeOneForWeaponSet(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype))
	, m_typeTwoForWeaponSet(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype))
	, m_typeOneForWeaponState(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype))
	, m_typeTwoForWeaponState(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype))
	, m_typeThreeForWeaponState(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype))
	, m_forceOrientationContainer(true)
	, m_canGrabStructure(false)
	, m_scatterNearbyOnExit(true)
	, m_orientLikeContainerOnExit(false)
	, m_goAggressiveOnExit(false)
	, m_resetMoodCheckTimeOnExit(true)
	, m_destroyRidersWhoAreNotFreeToExit(false)
	, m_grabWeapon(0)
	, m_fireGrabWeaponOnVictim(true)
	, m_conditionForEntry(-1)
	, m_shouldThrowOutPassengers(false)
	, m_throwOutPassengersDelay(0)
	, m_throwOutVelocity()
	, m_throwOutPassengersLandingWarhead(0)
	, m_fadePassengerOnEnter(false)
	, m_fadePassengerOnExit(false)
	, m_enterFadeTime(0.0f)
	, m_exitFadeTime(0.0f)
	, m_fadeReverse(false)
	, m_releaseSnappyness(0.7f)
{
	m_filter40.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
	m_filter44.applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
	m_fadeFilter.initFromStorages(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)),
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(g_00DFEFA4StoragePrototype)));
}
