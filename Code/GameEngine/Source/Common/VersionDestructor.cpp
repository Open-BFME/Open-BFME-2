// cl: /O1 /EHsc
// Version lifetime recovered from BFME2 retail and Open-BFME-1 version.cpp.
// WinMain deletes TheVersion (VA 0xDFE770) through this destructor.
// Constructor 0x238852 initializes seven strings; initializer 0x23870E
// identifies their fields by ID, MACHINE, USER, GUID, TIME, DATE and CONFIG.
template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const char *text);

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	void releaseBuffer();
	Header *m_data;
};

class AsciiString
{
public:
    AsciiString() {}
    AsciiString(const AsciiString &other) : m_data(other.m_data) {}
    void __cdecl format(const char *fmt, ...);
    const char *str() const { return m_data.m_data ? m_data.m_data->data : ""; }
	~AsciiString()
	{
		m_data.releaseBuffer();
	}
	AsciiString &operator=(const char *text)
	{
		m_data.set(text);
		return *this;
	}

private:
	StringBase<char> m_data;
};

// Opaque version-block parser behind initializeBuildMetadata. Retail
// constructs one from the 512-byte block at 0xA25000, reads the seven
// metadata keys through it, then tears down its inner list.
void __cdecl destroyVersionRecords(void *first, void *last);
namespace _STL
{
void __cdecl free(void *memory);
}
class VersionBlockParserInner
{
public:
	~VersionBlockParserInner()
	{
		destroyVersionRecords(m_start.m_data, m_finish);
	}
private:
	// Start of the 0x18-byte record list; the inline destructor frees the
	// buffer, which is why retail carries one unwind state across the
	// range-destroy call and frees [this] after it.
	struct RecordBuffer
	{
		~RecordBuffer()
		{
			if (m_data)
				_STL::free(m_data);
		}
		void *m_data;
	};
	RecordBuffer m_start;
	void *m_finish;
	void *m_alloc;
};

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
extern int g_versionMinor;
extern int g_versionBuildNum;
extern int g_versionLocalBuildNum;
extern const char g_versionBlock[];
int initVersionGlobals();

class Version
{
public:
    Version();
    AsciiString getAsciiBuildTime();
    AsciiString getAsciiVersion();
    AsciiString getAsciiBuildLocation();
    ~Version();
    // Reconstruction name; the original method spelling is unknown.
    // Retail body reads the seven named build metadata keys.
    void initializeBuildMetadata();
private:
    int m_major, m_minor, m_buildNum, m_localBuildNum;
    AsciiString m_buildTitle;
    AsciiString m_buildLocation;
    AsciiString m_buildUser;
    AsciiString m_buildGuid;
    AsciiString m_buildTime;
    AsciiString m_buildDate;
    AsciiString m_buildConfiguration;
    bool m_showFullVersion;
};
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

AsciiString Version::getAsciiBuildLocation() { return m_buildLocation; }

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
