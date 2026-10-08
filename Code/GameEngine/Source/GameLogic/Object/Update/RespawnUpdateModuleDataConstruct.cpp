// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0RespawnUpdateModuleData@@QAE@XZ, retail 0x004AFB4E, 149 bytes.
// Target evidence: own __EH_prolog head (scope 0xB8E6DF) after the genuine
// C9 C2 08 00 tail of the 35B insert at 0x004AFB2B; slot-0 ??_G at 0x004AFBE3
// follows. Installs vtable 0xC556F8 (DIR32-masked) over the Snapshot base
// (state 0), builds the +0x08 filter through rowed 0x003623E5 (state 1), three
// 0x4C bulk-zero members at +0x0C/+0x58/+0xA4 through rowed 0x00042526, the
// +0x10C rules map through rowed 0x00242F01 (map<long,LadderPref> default ctor,
// the folded body this tree uses), nulls the AsciiStrings at +0x118/+0x11C and
// zeroes +0xF0..+0x104 and the +0x108 byte in the body.
// Identity: ModuleFactory-registered friend_newModuleData@RespawnUpdateModuleData
// (0x0024F92E) allocates 0x120 and calls this body.
// Layout agrees with RespawnUpdateModuleDataDtor.cpp (filter +0x08, tree
// +0x10C, strings +0x118/+0x11C, size 0x120 from factory 0x0024F92E).
// The rules tree element type is carried from the ledger's 0x00242F01 row;
// LadderPref is declared here only for its 0x10 size (node 0x24).
#include "Common/Snapshot.h"

#include "ascii_string.h"

class LadderPref
{
public:
	LadderPref();
	LadderPref(const LadderPref &source);
	~LadderPref();

private:
	void *m_name;
	void *m_address;
	unsigned short m_port;
	long m_lastPlayDate;
};

#include <map>

class Rva00360D26Member
{
public:
	Rva00360D26Member();
	~Rva00360D26Member();

private:
	unsigned m_unknown;
};

class Rva0042526Member
{
public:
	Rva0042526Member();

private:
	unsigned char m_pad[0x4C];
};

class RespawnUpdateModuleData : public Snapshot
{
public:
	RespawnUpdateModuleData();
	virtual ~RespawnUpdateModuleData();

private:
	unsigned m_field04; // +0x04
	Rva00360D26Member m_filter; // +0x08
	Rva0042526Member m_block0C; // +0x0C
	Rva0042526Member m_block58; // +0x58
	Rva0042526Member m_blockA4; // +0xA4
	unsigned m_fieldF0; // +0xF0
	unsigned m_fieldF4; // +0xF4
	unsigned m_fieldF8; // +0xF8
	unsigned m_fieldFC; // +0xFC
	unsigned m_field100; // +0x100
	unsigned m_field104; // +0x104
	unsigned char m_flag108; // +0x108
	_STL::map<long, LadderPref> m_rules; // +0x10C
	AsciiString m_str118; // +0x118
	AsciiString m_str11C; // +0x11C
};

// ??0RespawnUpdateModuleData@@QAE@XZ
RespawnUpdateModuleData::RespawnUpdateModuleData()
{
	m_fieldF0 = 0;
	m_fieldF4 = 0;
	m_fieldF8 = 0;
	m_fieldFC = 0;
	m_field100 = 0;
	m_field104 = 0;
	m_flag108 = 0;
}
