// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/Open2Twins006.cpp
// Trimmed to the served ??1Open2Store880FC0 dtor only; the donor's
// 8F75D0/9A2680 twins and Force wrappers have no ledger rows here.
// Repair: retail installs the Snapshot-base vptr at +0xC, not the donor's
// +8, and reads the map member at +0x10, so SubsystemInterface runs 12
// bytes here (one pad word after m_name).

#include <map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
	// Retail installs the Snapshot-base vptr at +0xC (not the donor's +8),
	// so this base runs 12 bytes here, not 8.
	int m_bfmePad08;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Open2Held880FC0;

typedef std::map<NameKeyType, Open2Held880FC0 *, std::less<NameKeyType> > Open2Map880FC0;

struct Rva009F5970StateInit
{
	float value[6];
};

class T_009f4fb0
{
public:
	void m(Rva009F5970StateInit *value);
};

class Open2Store880FC0 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store880FC0();
	virtual void init();

private:
	Open2Map880FC0 *m_map;
};

// @??1Open2Store880FC0@@UAE@XZ 0x00880FC0
Open2Store880FC0::~Open2Store880FC0()
{
	delete m_map;
}

// ?init@Open2Store880FC0@@UAEXXZ 0x00625560 67B slot1 of 0x0087C6B0 calls T_009f4fb0::m at 0x006276E0 with zeroed state
void Open2Store880FC0::init()
{
	Rva009F5970StateInit state;
	state.value[0] = 0.0f;
	state.value[1] = 0.0f;
	state.value[2] = 0.0f;
	state.value[3] = 0.0f;
	state.value[4] = 0.0f;
	state.value[5] = 0.0f;
	((T_009f4fb0 *)m_map)->m(&state);
}
