// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// Version lifetime recovered from BFME2 retail and Open-BFME-1 version.cpp.
// WinMain deletes TheVersion (VA 0xDFE770) through this destructor.
// Constructor 0x238852 initializes seven strings; initializer 0x23870E
// identifies their fields by ID, MACHINE, USER, GUID, TIME, DATE and CONFIG.
#include "ascii_string.h"


// Opaque version-block parser behind initializeBuildMetadata. Retail
// constructs one from the 512-byte block at 0xA25000, reads the seven
// metadata keys through it, then tears down its inner list.
void __cdecl destroyVersionRecords(void *first, void *last);
namespace _STL
{
extern "C" void __cdecl free(void *memory) throw(...);
}
// Start of the 0x18-byte record list; the inline destructor frees the
// buffer, which is why retail carries one unwind state across the
// range-destroy call and frees [this] after it.
struct VersionRecordBuffer
{
	~VersionRecordBuffer()
	{
		if (m_data)
			_STL::free(m_data);
	}
	void *m_data;
};
class VersionBlockParserInner
{
public:
	~VersionBlockParserInner()
	{
		destroyVersionRecords(m_start.m_data, m_finish);
	}
private:
	VersionRecordBuffer m_start;
	void *m_finish;
	void *m_alloc;
};

// 0x18-byte version record: key/value buffers at +0/+0xC (fleet
// VersionBlockSearch layout); retail frees value first then key, which is
// the implicit member-destruction order below.
struct VersionBlockEntry
{
	VersionRecordBuffer m_key;
	char m_padAfterKey[8];
	VersionRecordBuffer m_value;
	char m_padTail[8];
};

// Range destroy over the 0x18-byte record list; the explicit element
// destruction below is what emits the element destructor above.
void __cdecl destroyVersionRecords(void *first, void *last)
{
	for (VersionBlockEntry *entry = (VersionBlockEntry *)first; entry != (VersionBlockEntry *)last; entry = (VersionBlockEntry *)((char *)entry + 0x18))
		entry->~VersionBlockEntry();
}

class VersionBlockParser
{
public:
	VersionBlockParser(const char *versionBlock);
	~VersionBlockParser() {}
	const char *lookupVersionValue(const char *key, const char *defaultValue);
private:
	int m_unk0;
	VersionBlockParserInner m_inner;
};

extern int g_versionMajor;
// g_versionMajor: matched references place it at VA 0xdfe760 (zero-filled .bss).
int g_versionMajor;
extern int g_versionMinor;
// g_versionMinor: matched references place it at VA 0xdfe764 (zero-filled .bss).
int g_versionMinor;
extern int g_versionBuildNum;
// g_versionBuildNum: matched references place it at VA 0xdfe768 (zero-filled .bss).
int g_versionBuildNum;
extern int g_versionLocalBuildNum;
// g_versionLocalBuildNum: matched references place it at VA 0xdfe76c (zero-filled .bss).
int g_versionLocalBuildNum;
// ?g_versionBlock@@3QBDB @0x00A25000 (512B): retail rts.ver version block
// (VER1 pipe-separated build metadata); 212 file bytes plus zero tail.
extern const char g_versionBlock[512] =
{
	'|', '|', 'V', 'E', 'R', '1', '|', '5', '1', '2', '|', 'B',
	'U', 'I', 'L', 'D', '=', 'P', 'a', 't', 'c', 'h', '1', '0',
	'6', 'b', 'u', 'i', 'l', 'd', '3', '|', 'C', 'O', 'N', 'F',
	'I', 'G', '=', 'R', 'e', 'l', 'e', 'a', 's', 'e', '|', 'D',
	'A', 'T', 'E', '=', '2', '0', '0', '6', '-', '0', '9', '-',
	'2', '5', '|', 'E', 'X', 'E', 'N', 'A', 'M', 'E', '=', 'R',
	'T', 'S', '.', 'e', 'x', 'e', '|', 'G', 'U', 'I', 'D', '=',
	'5', '9', '3', '0', '4', 'E', '6', 'A', '-', '8', '6', '8',
	'F', '-', '4', 'b', 'b', '8', '-', 'B', '3', '8', '9', '-',
	'3', '0', 'A', 'A', '8', '3', 'A', 'C', 'A', 'D', 'E', '8',
	'|', 'I', 'D', '=', 'L', 'O', 'T', 'R', 'B', 'F', 'M', 'E',
	'2', '|', 'M', 'A', 'C', 'H', 'I', 'N', 'E', '=', 'E', 'A',
	'L', 'A', '-', 'R', 'T', 'S', '-', 'B', 'U', 'I', 'L', 'D',
	'2', '|', 'T', 'I', 'M', 'E', '=', '1', '6', ':', '0', '6',
	':', '4', '1', '|', 'U', 'S', 'E', 'R', '=', 'r', 't', 's',
	'b', 'u', 'i', 'l', 'd', '|', 'V', 'E', 'R', 'S', 'I', 'O',
	'N', '=', '1', '.', '6', '.', '2', '4', '2', '9', '.', '3',
	'0', '2', '1', '0', '|', 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
int initVersionGlobals();


#include "../../Include/Common/VersionClass.h"
Version::~Version() {}

// ?forceVersionDelete@@YAXPAVVersion@@@Z absent-from-retail
void forceVersionDelete(Version *version) { delete version; }

Version::Version() { initializeBuildMetadata(); }

AsciiString Version::getAsciiBuildTime()
{
    AsciiString timeStr;
    timeStr.format("%s %s", m_buildDate.str(), m_buildTime.str());
    return timeStr;
}

AsciiString Version::getAsciiVersion()
{
    AsciiString version;
    version.format("%d.%.2d.%d.%d", m_major, m_minor, m_buildNum, m_localBuildNum);
    return version;
}

// Retail 0x00237F25, laid out directly after getAsciiVersion: Zero Hour's
// release getAsciiVersion shape, "%d.%d" over m_major and m_minor. BFME2 kept
// it beside the four-part getAsciiVersion that WinMain calls; no retail call
// reaches this one, so its name is not recoverable.
AsciiString Version::rva00237F25MajorMinor()
{
    AsciiString version;
    version.format("%d.%d", m_major, m_minor);
    return version;
}

// Retail 0x00237F83, laid out right after rva00237F25MajorMinor and before
// getUnicodeVersion: the four version numbers plus the CONFIG and MACHINE
// build-metadata strings ("%d.%d.%d.%d_%s_%s"). No retail call reaches it.
AsciiString Version::rva00237F83ConfiguredVersion()
{
    AsciiString version;
    version.format("%d.%d.%d.%d_%s_%s", m_major, m_minor, m_buildNum, m_localBuildNum,
        m_buildConfiguration.str(), m_buildLocation.str());
    return version;
}

AsciiString Version::getAsciiBuildLocation() { return m_buildLocation; }

AsciiString *Version::getBuildGuid(void) { return &m_buildGuid; }

// Retail 0x00237E63 (93 bytes): text colour for another build's version
// block in the LAN lobby list. Compares our four version ints against the
// block's sixteen bytes, then colours by the block's first int: 1 picks
// between 0xff7aab44 (identical) and 0xff3d5522, 2 picks between
// 0xff747bce and 0xff3a3d67, anything else is grey 0xff646464.
int Version::rva00237E63(const void *other, bool force)
{
	const int *theirs = (const int *)other;
	bool same = !force
		&& m_major == theirs[0]
		&& m_minor == theirs[1]
		&& m_buildNum == theirs[2]
		&& m_localBuildNum == theirs[3];
	switch (theirs[0])
	{
	case 1:
		return same ? 0xff7aab44 : 0xff3d5522;
	case 2:
		return same ? 0xff747bce : 0xff3a3d67;
	default:
		return 0xff646464;
	}
}

void Version::initializeBuildMetadata()
{
	static unsigned char s_initResult = initVersionGlobals() != 0;
	m_major = g_versionMajor;
	m_minor = g_versionMinor;
	m_buildNum = g_versionBuildNum;
	m_localBuildNum = g_versionLocalBuildNum;
	VersionBlockParser parser(g_versionBlock);
	m_buildTitle = parser.lookupVersionValue("ID", "sometitle");
	m_buildUser = parser.lookupVersionValue("USER", "somebody");
	m_buildLocation = parser.lookupVersionValue("MACHINE", "somewhere");
	m_buildGuid = parser.lookupVersionValue("GUID", "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX");
	m_buildTime = parser.lookupVersionValue("TIME", "15:50:55");
	m_buildDate = parser.lookupVersionValue("DATE", "Sep 25 2006");
	m_buildConfiguration = parser.lookupVersionValue("CONFIG", "Release");
	m_showFullVersion = false;
}
