// cl: /O1 /EHsc /DNDEBUG /MD
//
// ??1Rva004DC9EDEntry@@QAE@XZ, retail 0x004DC9ED, 71 bytes.
// Opaque three-string record destructor: tears down AsciiStrings at +0x00,
// +0x3C and +0x188 through the pinned 0x0036410 teardown with EH states
// 1/0/-1. Called on vector elements by the EmotionTrackerUpdateModuleData
// destructor loop at 0x4B12B7 and by the 0x4263xx cluster (whose 0x426316
// deleting destructor confirms a shared record class); application type
// name unrecovered, hence the address-derived vehicle. The ??_G at
// 0x00426316 calls this body directly.

class AsciiString
{
public:
	~AsciiString();

private:
	char m_pad[4];
};

class Rva004DC9EDEntry
{
public:
	~Rva004DC9EDEntry();

private:
	AsciiString m_string00; // +0x00
	char m_pad04[0x38];
	AsciiString m_string3C; // +0x3C
	char m_pad40[0x148];
	AsciiString m_string188; // +0x188
};

// ??1Rva004DC9EDEntry@@QAE@XZ @0x004DC9ED
Rva004DC9EDEntry::~Rva004DC9EDEntry()
{
}
