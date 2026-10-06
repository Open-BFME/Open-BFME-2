// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// ??1TransportContainModuleData@@UAE@XZ, retail 0x004684F1, 104 bytes.
// Target evidence: vtable 0x00C442F8 (installed by the matched ctor
// 0x00468301) has slot 0 = scalar deleting dtor 0x004684D5, which calls this
// body; HordeTransportContainModuleData's dtor 0x00477D8F is a 5-byte jmp
// here. Teardown order +0x180 vector, +0x168 fade filter (0x00360D26), +0xA4
// list, +0xA0 exit bone (0x00036410), then base dtor 0x00257481, which the
// OpenContainModuleData vtable 0x00C43658 deleting dtor 0x00465221 also calls.
// Layout copied from TransportContainModuleDataCtor.cpp (ctor-derived; member
// names there are ZH-donor spellings). novtable: retail stores no vptr here.
#include <list>
#include <vector>

struct BfmePod8
{
	int a[2];
};

// The +0x180 member is a 12-byte vector whose elements have a destructor:
// retail's teardown at 0x004684F1 calls the rowed vector dtor 0x00467FCC
// (RvaVectorDtorFamily.cpp: range destroy 0x00467DCD, then free), not a
// trivially destructible vector's base dtor.
struct Elem00467DCD;

struct Rva00467FCC
{
	~Rva00467FCC();
	Elem00467DCD *m_start;
	Elem00467DCD *m_finish;
	Elem00467DCD *m_end;
};

#include "ascii_string.h"

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

class __declspec(novtable) TransportContainModuleData : public OpenContainModuleData
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
	Rva00467FCC m_upgradeTrigger;
};

TransportContainModuleData::~TransportContainModuleData()
{
}
