// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata
// stlport
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/Open2Twins006.cpp
// Trimmed to the served ??1Open2Store880FC0 dtor only; the donor's
// 8F75D0/9A2680 twins and Force wrappers have no ledger rows here.
// Repair: retail installs the Snapshot-base vptr at +0xC, not the donor's
// +8, and reads the map member at +0x10, so SubsystemInterface runs 12
// bytes here (one pad word after m_name).

#include <map>
#include "Common/Snapshot.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	void *m_name;
	// Retail installs the Snapshot-base vptr at +0xC (not the donor's +8),
	// so this base runs 12 bytes here, not 8.
	int m_bfmePad08;
};

// Snapshot is the canonical BFME2 base from reference/shims/moduledata/Common/Snapshot.h
// (virtual dtor then crc/xfer/loadPostProcess, vtable 0x00BBB554).

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

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};

class BfmeFlagTarget
{
public:
	virtual ~BfmeFlagTarget();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual void pad7();
	virtual void pad8();
	virtual void pad9();
	virtual void bfmeDescribe(BfmeFlagPair *flags);
};

class BfmeSinkA
{
public:
	void bfmeAccept(BfmeFlagTarget *target);
};

class Gen_00881040
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkA *m_bfmeSink;
};

void Gen_00881040::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

class Open2Held8F75D0;

typedef std::map<NameKeyType, Open2Held8F75D0 *, std::less<NameKeyType> > Open2Map8F75D0;

class Open2Store8F75D0 : public SubsystemInterface, public Snapshot
{
public:
	Open2Store8F75D0();
	virtual ~Open2Store8F75D0();

private:
	Open2Map8F75D0 *m_map;
};

// @??1Open2Store8F75D0@@UAE@XZ 0x00739980
Open2Store8F75D0::~Open2Store8F75D0()
{
	delete m_map;
}

// Constructor recovery from BFME1 revision6583b3c1ff21db4a561285717028fdafc780b7db
// game/GameEngine/Source/Common/System/Rva008F7510ShroudManagerCtor.cpp.
// Target7398D0..73995F is143B; CF1250/CF1240 lead to this existing
// owner's rowed deleting destructor739E40 and its Snapshot adjustment739960.
// The rowed739970 literal names the subsystem ShroudManager. Retail calls
// rowed base1B4E63 (12B prefix) and allocates70B before rowed214B ctor73E310.
// The donor's purpose is independently supported; its original class spelling
// is unknown. Reuse the established Open2Store8F75D0 opaque owner instead of
// introducing a second class for the same target. The legacy destructor's map
// pointer spelling is retained as a teardown ABI view; the constructor does
// not assert that the allocated implementation is that STL map type.
class ShroudManagerImpl008FBA40CtorView {
public: ShroudManagerImpl008FBA40CtorView();
private: unsigned char storage[0x70];
};
#pragma comment(linker, "/alternatename:??0ShroudManagerImpl008FBA40CtorView@@QAE@XZ=??0ShroudManagerImpl@@QAE@XZ")
Open2Store8F75D0::Open2Store8F75D0()
{
 m_map = reinterpret_cast<Open2Map8F75D0 *>(new ShroudManagerImpl008FBA40CtorView);
}

class BfmeSinkB
{
public:
	void bfmeAccept(BfmeFlagTarget *target);
};

class Gen_008F7650
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkB *m_bfmeSink;
};

void Gen_008F7650::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

class Open2Held9A2680;

typedef std::map<NameKeyType, Open2Held9A2680 *, std::less<NameKeyType> > Open2Map9A2680;

class Open2Store9A2680 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store9A2680();

private:
	Open2Map9A2680 *m_map;
};

// @??1Open2Store9A2680@@UAE@XZ 0x00758310
Open2Store9A2680::~Open2Store9A2680()
{
	delete m_map;
}


