// cl: /O1 /EHsc
// Version lifetime recovered from BFME2 retail and Open-BFME-1 version.cpp.
// WinMain deletes TheVersion (VA 0xDFE770) through this destructor.
// Constructor 0x238852 initializes seven strings; initializer 0x23870E
// identifies their fields by ID, MACHINE, USER, GUID, TIME, DATE and CONFIG.
template <typename T>
class StringBase
{
	friend class AsciiString;

private:
    StringBase() : m_data(0) {}
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
	~AsciiString()
	{
		m_data.releaseBuffer();
	}

private:
	StringBase<char> m_data;
};

class Version
{
public:
    Version();
    ~Version();
    // Address-qualified reconstruction name; original method spelling is unknown.
    // Retail body reads the seven named build metadata keys.
    void initializeBuildMetadata_23870E();
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

Version::Version() { initializeBuildMetadata_23870E(); }
