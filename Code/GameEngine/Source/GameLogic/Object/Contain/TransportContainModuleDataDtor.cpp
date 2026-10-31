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
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_List_node@UBfmePod8@@@_STL@@@_STL@@QBEXPAU?$_List_node@UBfmePo:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> void allocator<_List_node<BfmePod8> >::deallocate(_List_node<BfmePod8> *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?clear@?$_List_base@UBfmePod8@@V?$allocator@UBfmePod8@@@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod8;
namespace _STL { template <> void _List_base<BfmePod8,allocator<BfmePod8> >::clear(); }
// Bind the list teardown to the existing retail provider at 0x002FECBC.
namespace _STL { template <> _List_base<BfmePod8,allocator<BfmePod8> >::~_List_base(); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

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

class MultiIniFieldParse;
class OpenContainModuleData
{
public:
	OpenContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	virtual ~OpenContainModuleData();
	char m_pad04[0x3C];
protected:
	Rva003623E5Member m_filter40; // +0x40
	Rva003623E5Filter m_filter44; // +0x44
	char m_pad48[0x50];
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
