// cl: /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
// Retail runs the 16-byte base constructor at 0x007E86B0 here (vftable
// 0x01129358 plus a zeroed word at +4), not the 9-byte vptr-only body the
// ledger carries as ??0Snapshot@@QAE@XZ. SnapshotDupReplica is the
// TU-local spelling functions.csv already records as that body's object
// symbol.
class SnapshotDupReplica
{
public:
	SnapshotDupReplica();
	virtual void handle() {}
};

class Rva007E8810 : public SnapshotDupReplica
{
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	char m_30;

public:
	Rva007E8810();
};

Rva007E8810::Rva007E8810()
{
	m_08 = 0;
	m_0C = 0;
	m_04 = 0;
	m_10 = 0;
	m_18 = 0;
	m_14 = 0;
	m_28 = 0;
	m_24 = 0;
	m_20 = 0;
	m_1C = 0;
	m_30 = 0;
	m_2C = 4;
}

// Callers elsewhere reach bodies in this unit through spellings pinned to the same
// retail address (same cdecl/thiscall ABI); bind them here.
#pragma comment(linker, "/alternatename:??0Rva007E8810Message@@QAE@XZ=??0Rva007E8810@@QAE@XZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0BfmeMsgVJH@@QAE@XZ=??0Rva007E8810@@QAE@XZ")
