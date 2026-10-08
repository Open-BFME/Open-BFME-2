// cl: /GX- /DNDEBUG /MD
//
// ?getAudioLODIndex@GameLODManager@@QAEHABVAsciiString@@@Z, retail 0x00202C76,
// 124 bytes. Dedicated TU.
//
// BFME1 GameLODManager::getAudioLODIndex port
// (reference/open-bfme-1 Code/GameEngine/Source/Common/GameLODManagerGetAudioLODIndex.cpp:
// two-entry bfmeTabEYC table walked with compareNoCase returning the index;
// debug-reporting tail otherwise; miss -1). BFME2 adaptations proven by the
// retail bytes:
// - compareNoCase is DECLARED-only (retail calls the StringBase<char> 1-arg
//   out-of-line body at 0x00037980; BFME1's TU defines it inline, which would
//   fold the call away). AsciiString befriends GameLODManager for the
//   private-base access; friendship is compile-time only.
// - The reporting tail logs through Debug virtuals plus the matched
//   Debug/StringBase operator<< at 0x000028E8: slot60(), 3-arg slot6C,
//   slot38 Invalid-name literal (whose return feeds operator<< with the name),
//   slot38 "'", slot4C(2). The enabled check reads the Debug singleton flag
//   through the matched row at 0x000387C0; the record call reuses the established
//   Debug::SkipNext pin at 0x00038790.
// - TheBfmeAwakenDebug is TU-local DEFINED (COMMON merges; its DIR32 patches
//   from retail like theDebug) and bfmeTabEYC is TU-local DEFINED (its base
//   disp32 patches from retail; entry values never enter .text).

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
	Int compareNoCase(const char *other) const;
private:
	BfmeStringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
	friend class GameLODManager;
public:
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString() {}
};

class Debug
{
public:
	static Bool SkipNext(Bool skip);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual Debug &slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(Int report);
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual Debug *slot6C(Int first, Int second, Int third);
};

template <typename T> Debug &operator<<(Debug &debug, const StringBase<T> &text);

class GameLODManager
{
public:
	Int getAudioLODIndex(const AsciiString &name);
};

// The global at this VA is theDebug; this name aliases it rather than
// defining a second variable the rest of the game never sees.
extern class Debug *theDebug;

const char *bfmeTabEYC[2] = { "Low", "High" };

Bool bfmeRva000387C0(void);

// ?getAudioLODIndex@GameLODManager@@QAEHABVAsciiString@@@Z
Int GameLODManager::getAudioLODIndex(const AsciiString &name)
{
	for (Int i = 0; i < 2; ++i)
	{
		if (name.compareNoCase(bfmeTabEYC[i]) == 0)
			return i;
	}

	if (bfmeRva000387C0())
	{
		Debug::SkipNext(true);
		theDebug->slot60();
		// Nested (no named report temp): retail keeps the slot6C result in
		// eax straight into the slot38 dispatch, and evaluates the
		// operator<< name operand first (push [esp+8] before the lit push).
		operator<<(theDebug->slot6C(0, 0, 0)->slot38("GameLODManager::getAudioLODIndex - Invalid LOD name '"), name).slot38("'").slot4C(2);
	}

	return -1;
}
