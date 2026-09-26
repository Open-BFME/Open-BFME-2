// cl: /O1 /EHsc /DNDEBUG /MD
//
// ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z, retail
// 0x00202C30, 70 bytes. Dedicated TU (abuts the audio sibling at 0x202C76).
//
// Static-LOD twin of getAudioLODIndex (GameLODManagerGetAudioLODIndex.cpp):
// five-entry name table walked with compareNoCase returning the index, -1 on
// miss. No debug-reporting tail; the by-value parameter is destroyed here at
// the end (MSVC callee-destroys rule), which is the trailing releaseBuffer
// call. Retail facts:
// - compareNoCase is DECLARED-only (retail calls the StringBase<char> 1-arg
//   out-of-line body at 0x00037980; defining it inline would fold the call
//   away). AsciiString befriends GameLODManager for the private-base access.
// - The parameter destruction routes through the DECLARED-only StringBase
//   destructor (rowed 0x36410); the implicit AsciiString dtor inlines to that
//   single call (sibling precedent: declared-only dtor keeps 0x36410).
// - The table base (retail 0xDB969C) is DIR32-masked, so any extern spelling
//   verifies; the entry values never enter .text. Retail strings:
//   VeryLow/Low/Medium/High/VeryHigh.
// - /EHsc (not the sibling's /GX-): the by-value parameter forces the EH
//   prolog/teardown pair retail shows. No unwind states: parameters carry
//   none, only stack temps would (winSetText precedent).

typedef int Int;
typedef bool Bool;

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class GameLODManager;
public:
	// throw() (findTerrain precedent): a throwing leaf callee forces an
	// `and [ebp-4],0` state init retail lacks; the leaf compare cannot
	// throw, so the unwind state is omitted while the frame stays.
	Int compareNoCase(const char *other) const throw();
	~StringBase();
private:
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
	friend class GameLODManager;
};

class GameLODManager
{
public:
	Int getStaticGameLODIndex(AsciiString name);
};

// Retail table at 0xDB969C: VeryLow, Low, Medium, High, VeryHigh.
const char *bfmeStaticLODNames[5] = { "VeryLow", "Low", "Medium", "High", "VeryHigh" };

// ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z
Int GameLODManager::getStaticGameLODIndex(AsciiString name)
{
	for (Int i = 0; i < 5; ++i)
	{
		if (name.compareNoCase(bfmeStaticLODNames[i]) == 0)
			return i;
	}

	return -1;
}
