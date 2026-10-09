// Banked partial for ?update@LANAPI@@UAEXXZ @ 0x0044AAED 1938B
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
//
// Bank: canonical string definitions are embedded for standalone serving.
// StringBase adds only a LANAPI friend grant for its already-rowed by-value
// return cleanup; no production/shared header is edited. Landing would require
// adopting that access contract in the canonical header, not a private Code copy.
// Provenance BF1 f98983a7d lanapi.cpp plus native BF2 dispatch/layout.
// Full1938 includes80B switch table; only cases13/14 shared-branch shape differs.
// LANAPI message handlers, Zero Hour's GameNetwork/LANAPIhandlers.cpp, as
// LANAPI::update (slot 10, 0x0044AAED) dispatches them by message type
// through its jump table at 0x0084B22F. The sender arrives as a pointer to
// its address, as in Open-BFME-1's handlers.
//
// LANAPI::handleRequestLobbyLeave, retail 0x005815AB (63 bytes), message type
// 7: in the lobby, remove the lobby player (list +0x0C, next +0x10, address
// +0x14) whose address equals the sender's (0x00248CBF) and refresh the
// player list -- BFME 2's slot 33 (0x00248E87) takes no list.
//
// LANAPI::handleJoinDeny, retail 0x00581E3E (105 bytes), message type 5:
// Open-BFME-1's body. A denial addressed to us (IP +0x46 and port +0x4A
// against the local address, slot 64) while a join is pending reports the
// reason (+0x4C) and the game looked up by name (+0x1E, slot 49) to
// OnGameJoin (slot 34) with the message, then clears the pending action.
//
// LANAPI::handleHasMap, retail 0x00581EA7 (217 bytes), message type 10: Zero
// Hour's map check (CRC of the portable map path against +0x40), but BFME 2
// finds the sender among the current game's eight slot addresses (+0x114,
// stride 0x1D0) instead of by name and reports the status byte (+0x44) to
// OnHasMap (slot 39) with the sender's address. Retail tests the counter at
// the bottom of the walk, so the loop is written that way.
//
// LANAPI::handleLobbyAnnounce, retail 0x00581C4E (223 bytes), message type 2:
// Zero Hour's body, the remote half of the rowed RequestSetName. The player is
// looked up by address (slot 63), allocated or unlinked, takes the name (+0x04)
// and the one-character host (+0x1C) and login (+0x1A) fields, is re-added
// and reported to OnNameChange (slot 48). LANPlayer is RequestSetName's view.
//
// LANAPI::handleInActive, retail 0x0058219D (234 bytes), message type 17:
// Zero Hour's body (Open-BFME-1's LANAPI_handleInActive.cpp). The host of a
// game not yet in progress (+0x11) un-accepts the named player's slot when
// the sender owns it (0x00248CDD against slot +0x38), is not us and the start
// timer (+0x20) is idle; BFME 2 then re-sends the game info through slot 26
// with no address and refreshes the slot list with 0x00446A77 where Zero Hour
// sent the options string.
//
// LANAPI::handleRequestGameInfo, retail 0x00581D2D (273 bytes), message type
// 18: Zero Hour's body, the reply half of the rowed RequestGameAnnounce
// (0x0044A214). The host (slot 0's address against ours) or the packet router
// of a game in progress answers the sender with a type-1 announce: the game
// serialized by the writer 0x00447CA9 into the options at +0x42, its name
// (LANGameInfo vslot 23) at +0x1E, the in-progress (+0x11) and direct-connect
// (+0xF68) flags at +0x40/+0x41 and, as in RequestGameAnnounce, 16 bytes from
// the game at +0xCC in the message tail at +0x1C8. The LAN slots are 0x1D0
// bytes from +0xDC.
//
// LANAPI::handleGameOptions, retail 0x00582EB0 (273 bytes), message type 13:
// BFME 2's three-argument form of Zero Hour's handler. Options from the host
// (slot 0's address) of a game not in progress go, with the 0x186-byte blob
// at +0x1E, to slot 46 (BFME's OnGameOptions, as slot 0); the options string
// is regenerated before and after and compared (result unused). On success
// the lobby flag goes off through slot 61 and slot 43 or 42 runs by the third
// argument (update passes false); on failure we leave as RequestGameLeave's
// host path does: OnPlayerLeave (slot 37) with our name, removeGame and
// delete the game, back to the lobby.
//
// LANAPI::handleChat, retail 0x00581F80 (440 bytes), message type 11: Zero
// Hour's body (game name +0x1E, chat type +0x40, text +0x44) reporting to
// OnChat (slot 40), plus BFME 2's first branch: type-1 chat is reported with
// the sender's own name and address wherever we are. In a game the sender is
// found among the current game's slot addresses, its last-heard time set
// through 0x00248D35.
//
// LANAPI::handleJoinAccept, retail 0x00582287 (529 bytes), message type 4:
// Zero Hour's body (Open-BFME-1's LANAPIHandleJoinAcceptRva0068CF00.cpp
// without its LANPreferences block). An accept addressed to us (IP +0x46,
// port +0x4A) while joining makes the game looked up by name (+0x1E) current,
// re-parses its options after entering it -- keeping the 16 bytes at +0xCC
// across the parse (restored by 0x00381D02) -- seats us at the given position
// (+0x4C) with RequestGameCreate's slot sequence, takes the host's login and
// host names (+0x1A/+0x1C) into slot 0 and reports to OnGameJoin; a game that
// is gone reports RET_UNKNOWN. update first calls slot 30 with true.
//
// LANAPI::handleRequestGameLeave, retail 0x00582498 (740 bytes), message
// types 6 and 8 (update passes true for 8, false for 6 and for the leave it
// fabricates for a timed-out player): Zero Hour's body with addresses. In a
// game not in progress, a leaving host (slot 0's address) makes us
// OnHostLeave (slot 36), drop and delete the game and re-add ourselves to the
// lobby players (looked up by the local address, slot 63/64); any other
// player's slot is opened (by the host through setSlot first), reported to
// OnPlayerLeave (slot 37), the acceptances reset (GameInfo vslot 14) and the
// game info re-sent to the sender through slot 26. In the lobby the game
// named at +0x1E is found in the list (+0x10, next +0xF5C); only with the
// flag is it removed and deleted (clearing the current game if it is that
// one) before OnGameList (slot 32) runs.
//
// LANAPI::handleGameAnnounce, retail 0x00581984 (714 bytes), message type 1:
// Open-BFME-1's body (LANAPIhandlers_handleGameAnnounce_Thunk.cpp), Zero
// Hour's with addresses. Our own announces and any while our game is in
// progress are ignored; the game named at +0x1E is looked up (slot 49) or
// created, named (0x00449A81) and added, and its options (+0x42, 0x186 bytes)
// parsed by 0x00449258. BFME 2 also fails an announce whose 16-byte digest
// (+0x1C8), printed by MD5Print, is not all zeros and names no saved game
// (0x004360B3) -- from the direct-connect host only when the parse succeeded.
// A failed game is dropped; otherwise it takes the in-progress (+0x40) and
// direct-connect (+0x41) flags, the time heard (+0xF60) and the digest
// (0x00381D02, as handleJoinAccept), and is joined (slot 16) when it is the
// direct-connect host's (+0x34) with no current game; any other sender's
// announce refreshes OnGameList. Retail keeps the current game in a register
// across the address compare, so it is read once.
//
// LANAPI::handleRequestLocations, retail 0x00581795 (495 bytes), message type
// 0: Zero Hour's body (Open-BFME-1's LANAPIHandleRequestLocationsThunk.cpp).
// In the lobby we broadcast a lobby announce (type 2) and note the resend
// time (+0x3C); as host (slot 0's address is ours) we broadcast a game
// announce (type 1) with the options from 0x0044802D, the name, the
// in-progress flag and the game's 16 bytes at +0xCC, as handleRequestGameInfo
// does. Either way the sender is (re)added to the lobby players exactly as
// handleLobbyAnnounce does it.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) unsigned short * __cdecl wcsncpy( unsigned short *dest, const unsigned short *source, unsigned int count );
extern "C" void * __cdecl memcpy( void *dest, const void *source, unsigned int count );
#pragma function(memcpy)
extern "C" int __cdecl strcmp( const char *left, const char *right );
extern "C" void MD5Print( unsigned char digest[16], char output[33] );

#include "GameNetwork/Transport.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// Evidence snapshot of canonical string_base.h; no production header edit.

// BFME2 changes against the Open-BFME-1 text this started from, each named by
// a game.dat export (reverse/exports.csv): the CharSource overloads and
// ensureUniqueBufferOfSize(int, bool, const CharSource<T> *, const CharSource<T> *),
// the (const T *, int, int) constructor and set, compare(T), compareNoCase(T),
// and operator<< as a template (??$?6D@@YAAAVDebug@@AAV0@ABV?$StringBase@D@@@Z).
template <typename T>
class CharSource;

// BFME's StringBase<T> is Zero Hour's AsciiString made a template (upstream:
// inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h).
// The members defined in the class below are the ones retail inlines at EVERY
// call site: the image holds no call to their COMDATs (0x0005F270 str,
// 0x0005E4A0 getLength, 0x0005E490 ~StringBase, 0x000680C0 clear, ...), only the
// incremental-link thunk's jmp, and the exports keep the bodies alive. str()
// keeps Zero Hour's function-local TheNullChr, which retail exports as
// ?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB (0x00C7388B; wide 0x00C7388C).
// isEmpty, compare, concat and the rest were header-defined too (their COMDATs
// also sit outside StringBase.cpp's block at 0x00887000-0x00889300), but MSVC
// kept real calls to them at many sites (66 to isEmpty's thunk, 391 to
// compare's), and the tree matches those sites against out-of-line bodies in
// StringBase.cpp, so they stay declared here and defined there.
template <typename T>
class StringBase {
    friend class AsciiString;
    friend class UnicodeString;
    friend class LANAPI;

public:
    void debugIgnoreLeaks();
    bool isEmpty() const;
    bool isNotEmpty() const;
    bool isNone() const;
    bool isNotNone() const;
    int getLength() const
    {
        validate();
        return m_data ? m_data->length : 0;
    }
    const T *str() const
    {
        validate();
        static const T TheNullChr = 0;
        return m_data ? peek() : &TheNullChr;
    }
    const T *find(T c) const;
    // Retail compiles calls to this body (0x00035720) as non-throwing: at
    // 0x004FE4B8 a getMap() temporary is live across the call with no EH
    // state of its own, which only a throw() declaration reproduces.
    T getCharAt(int index) const throw();
    StringBase<T> &operator=(const StringBase<T> &src);
    int compare(const StringBase<T> &str) const;
    int compare(const T *str) const;
    int compare(const T *str, int len) const;
    int compare(T c) const;
    // Non-throwing for the same reason (0x00406A00 / wide 0x00406AA4): the
    // sort comparator at 0x0021B68D compares a translated-label temporary
    // with no EH state of its own and keeps the result in BL.
    int compareNoCase(const StringBase<T> &str) const throw();
    int compareNoCase(const T *str) const;
    int compareNoCase(const T *str, int len) const;
    int compareNoCase(T c) const;
    void concat(const StringBase<T> &str);
    void concat(T c);
    void concat(const T *str);
    void concat(const T *str, int len);
    void concat(const CharSource<T> &src);
    const T *reverseFind(T c) const;
    bool startsWith(const StringBase<T> &str) const;
    bool startsWith(const T *str) const;
    bool startsWith(const T *str, int len) const;
    bool startsWithNoCase(const StringBase<T> &str) const;
    bool startsWithNoCase(const T *str) const;
    bool startsWithNoCase(const T *str, int len) const;
    bool endsWith(const StringBase<T> &str) const;
    bool endsWith(const T *str) const;
    bool endsWith(const T *str, int len) const;
    bool endsWithNoCase(const StringBase<T> &str) const;
    bool endsWithNoCase(const T *str) const;
    bool endsWithNoCase(const T *str, int len) const;
    void set(const StringBase<T> &src);
    void set(const StringBase<T> &src, int start, int len);
    void set(T c);
    void set(const T *str);
    void set(const T *str, int len);
    void set(const T *str, int start, int len);
    void set(const CharSource<T> &src);
    void swap(StringBase<T> &other)
    {
        Header *tmp = m_data;
        m_data = other.m_data;
        other.m_data = tmp;
    }
#ifdef BFME_SB_CLEAR_DECL
    // Per-unit switch, default off: declared only, for a unit whose retail code calls the
    // out-of-line clear (0x0048BA39 for char) instead of expanding it (link census, 2026-10-06).
    void clear();
#else
    void clear()
    {
        releaseBuffer();
    }
#endif
    void __cdecl format(const T *fmt, ...);
    void format_va(const StringBase<T> &fmt, char *args);
    void format_va(const T *fmt, char *args);
    T *getBufferForRead(int len);
    bool nextToken(StringBase<T> *out, const T *delimiters);
    void removeLastChar();
    void toLower();
    void toUpper();
    void trim();

private:
    StringBase() : m_data(0) {}
    StringBase(T c);
    StringBase(const T *str);
    StringBase(const T *str, int len);
    StringBase(const T *str, int start, int len);
    StringBase(const CharSource<T> &src);
    StringBase(const StringBase<T> &src);
    StringBase(const StringBase<T> &src, int start, int len);
    // ??1?$StringBase@D@@AAE@XZ (0x0005E490) and ??1AsciiString@@QAE@XZ
    // (0x0005EE90) are both a bare `jmp releaseBuffer`.
    ~StringBase()
    {
        validate();
        releaseBuffer();
    }
    void validate() const {}
    T *peek() const
    {
        return &m_data->data[0];
    }
    void releaseBuffer();
    void ensureUniqueBufferOfSize(int newLen, bool keepData, const CharSource<T> *src1, const CharSource<T> *src2);

private:
    struct Header {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };

    Header *m_data;
};

template <typename T>
bool operator<(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator==(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const StringBase<T> &right);

template <typename T>
bool operator!=(const StringBase<T> &left, const T *right);

class Debug;
template <typename T>
Debug &operator<<(Debug &debug, const StringBase<T> &str);

template <typename T>
bool operator!=(const T *left, const StringBase<T> &right);
// Evidence snapshot of canonical ascii_string.h; no production header edit.

// BFME2's shared AsciiString: include this instead of declaring a TU-local
// `class AsciiString` (2026-09-30: 941 TUs carried private copies in 341
// versions, and the link census counted their differing inline copies against
// ~500 files). Put /Ireference/shims/bfme2_ascii FIRST among a TU's /I flags so
// this header and the string_base.h beside it win over Open-BFME-1's.
//
// BFME2 compatibility view of Open-BFME-1's WWLib AsciiString. Upstream's
// current class derives from StringBase<char>, so scope exits call the private
// StringBase destructor thunk at 0x0048BA39. BFME2 retail calls the shared
// releaseBuffer worker directly at 0x00036410. Keep the same one-pointer
// layout, but make this wrapper own cleanup so callers emit that verified
// worker call. The method surface follows the BFME1 header; only the class
// relationship, the destructor placement and the format/translate overloads
// (BFME2's rows in WWLib/string_inline.cpp and StringUtf8Translation.cpp)
// differ for the BFME2 target.
//
// string_base.h beside this file is Open-BFME-1's WWLib string_base.h as of
// 77db49c3d, frozen here: the submodule copy keeps changing (aa3e918c4 moved
// five members inline on 2026-09-30) and would change BFME2 codegen with it.
//
// game.dat holds no call to the out-of-line copies of the (char), (text, len),
// (text, start, len) and (AsciiString, start, len) constructors or of
// operator+=(AsciiString / text) (0x00006572, 0x0000655C, 0x0000659E,
// 0x00006584, 0x00006D12, 0x000065E8): retail expands them in place, so they
// are __forceinline here. operator=(char) (1 call) and operator+=(char) (11
// calls) are plain inlines MSVC sometimes kept out of line. ascii_string.cpp
// emits one select-any copy of each for the ledger rows.

#include <string.h>

// The members below are compiled favouring size with frame-pointer omission (as /O1) in
// every unit. Retail's out-of-line copies are the /O1 form (ascii_string.cpp's rows); a
// unit built /O2 or /Oy- otherwise emits its own select-any copy of each inline member
// that differs from them (2026-10-01 census: 82 units lost such copies). Code a member
// inlines into a caller still follows the caller's flags.
class UnicodeString;
class PooledString;
// Per-unit switch, default off (without it this header compiles as before): BFME_ASCII_DTOR_DECL
// declares ~AsciiString only, for a unit whose retail code calls its out-of-line copy 0x0048BA39
// (e.g. inside the compiler's ??_GAsciiString) where /O1 would expand it (link census, 2026-10-06).

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	__forceinline AsciiString(char c) { ((StringBase<char> *)this)->StringBase<char>::StringBase(c); }
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}
	__forceinline AsciiString(const char *s, int len)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s, len);
	}
	__forceinline AsciiString(const char *s, int start, int len)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s, start, len);
	}
	__forceinline AsciiString(const AsciiString &that, int start, int len)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that, start, len);
	}
	AsciiString(const UnicodeString &that);
#ifdef BFME_ASCII_DTOR_DECL
	~AsciiString();
#else
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
#endif

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&that);
		return *this;
	}
	AsciiString &operator=(char c)
	{
		char text = c;
		((StringBase<char> *)this)->set(&text, 1);
		return *this;
	}
	// Retail's out-of-line copy (0x000065B8) calls StringBase<char>::set(const char *)
	// (0x000055F5), which does the strlen.
	AsciiString &operator=(const char *s)
	{
		((StringBase<char> *)this)->set(s);
		return *this;
	}
	AsciiString &operator=(const UnicodeString &that);
	__forceinline AsciiString &operator+=(const AsciiString &that)
	{
		((StringBase<char> *)this)->concat(*(const StringBase<char> *)&that);
		return *this;
	}
	AsciiString &operator+=(char c)
	{
		char text = c;
		((StringBase<char> *)this)->concat(&text, 1);
		return *this;
	}
	__forceinline AsciiString &operator+=(const char *s)
	{
		((StringBase<char> *)this)->concat(s);
		return *this;
	}
	AsciiString &operator+=(const UnicodeString &that);
	AsciiString &operator+=(const PooledString &that);

	void __cdecl format(const char *fmt, ...);
	void __cdecl format(const AsciiString *fmt, ...);
	void translate(const UnicodeString &that);
	void translate(const unsigned short *that);
	const char *str() const { return m_text ? m_text + 8 : ""; }
	int getLength() const { return ((const StringBase<char> *)this)->getLength(); }
	char getCharAt(int i) const { return ((const StringBase<char> *)this)->getCharAt(i); }
	// Inline in BFME, like str() above. INI::parseAudioEventRTS at 0x000BBB60
	// emits it as  mov eax,[..]; test eax,eax; je; cmp word ptr [eax+4],0; je
	// -- that is m_data == NULL || m_data->length == 0 against StringBase's
	// Header {int ref_count; unsigned short length; unsigned short capacity;},
	// which is the same header str()'s +8 comes from.
	bool isEmpty() const { return m_text == 0 || *(const unsigned short *)(m_text + 4) == 0; }
	bool isNotEmpty() const { return ((const StringBase<char> *)this)->isNotEmpty(); }
	bool isNone() const { return ((const StringBase<char> *)this)->isNone(); }
	bool isNotNone() const { return ((const StringBase<char> *)this)->isNotNone(); }
	const char *reverseFind(char c) const { return ((const StringBase<char> *)this)->reverseFind(c); }
	bool nextToken(AsciiString *tok, const char *delims = 0)
	{
		return ((StringBase<char> *)this)->nextToken((StringBase<char> *)tok, delims);
	}
	void clear();
#if defined(BFME_ASCII_KEEP_CHAR_SET_BODY)
	// Keep native receiver/argument evaluation at callers while the StringBase worker owns the call.
	__declspec(dllimport) __forceinline void set(const char *s) { ((StringBase<char> *)this)->set(s); }
#else
	void set(const char *s);
#endif
	#if defined(BFME_ASCII_KEEP_COPY_SET_BODY)
	// These callers require the original class method surface for exact codegen;
	// their verified objects emit no public copy-set COMDAT.
	void set(const AsciiString &s) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&s); }
#else
	// The public spelling folds to StringBase<char>::set at RVA 0x366F0.
	void set(const AsciiString &s);
	__forceinline void setCopyInline(const AsciiString &s) { ((StringBase<char> *)this)->set(*(const StringBase<char> *)&s); }
#endif
	// Retail call sites pin this spelling to the same 37-byte worker as
	// StringBase<char>::concat(const char *) at RVA 0x00005629.
	void concat(const char *s);
	void concat(char c) { ((StringBase<char> *)this)->concat(c); }
	void concat(const AsciiString &s);
	void toLower() { ((StringBase<char> *)this)->toLower(); }
	void toUpper() { ((StringBase<char> *)this)->toUpper(); }
	void trim();
	void removeLastChar() { ((StringBase<char> *)this)->removeLastChar(); }
	const char *find(char c) const { return ((const StringBase<char> *)this)->find(c); }
	bool startsWith(const char *p) const { return ((const StringBase<char> *)this)->startsWith(p); }
	// Zero Hour's overloads (Common/AsciiString.h): its ports call them with an AsciiString.
	bool startsWith(const AsciiString &s) const { return startsWith(s.str()); }
	bool startsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->startsWithNoCase(p); }
	bool startsWithNoCase(const AsciiString &s) const { return startsWithNoCase(s.str()); }
	bool endsWith(const char *p) const { return ((const StringBase<char> *)this)->endsWith(p); }
	bool endsWith(const AsciiString &s) const { return endsWith(s.str()); }
	bool endsWithNoCase(const char *p) const { return ((const StringBase<char> *)this)->endsWithNoCase(p); }
	bool endsWithNoCase(const AsciiString &s) const { return endsWithNoCase(s.str()); }
	int compare(const char *p) const;
	int compareNoCase(const char *p) const { return ((const StringBase<char> *)this)->compareNoCase(p); }
	int compare(const AsciiString &s) const throw();
	int compareNoCase(const AsciiString &s) const { return ((const StringBase<char> *)this)->compareNoCase(*(const StringBase<char> *)&s); }

	static const AsciiString TheEmptyString;

private:
	char *m_text;
};

inline bool operator==(const AsciiString &a, const AsciiString &b) { return a.compare(b) == 0; }
inline bool operator!=(const AsciiString &a, const AsciiString &b) { return a.compare(b) != 0; }
inline bool operator<(const AsciiString &a, const AsciiString &b) { return a.compare(b) < 0; }

// The existing one-pointer view and thiscall argument agree with that
// worker. Resolve the spelling directly; a five-byte forwarding COMDAT
// would define a different body at the already verified address.

// These existing retail spellings share the same one-pointer thiscall ABI:
// set(text) -> StringBase set at 0x55F5 (37 bytes); concat(string) ->
// StringBase concat at 0x6987 (42 bytes). clear is the releaseBuffer worker
// at 0x36410, which clears the pointer as it releases the buffer.

// BoneFXUpdate retail calls identify this spelling with the 42-byte worker
// at RVA 0x69D6. Its verified callees read lengths and compare bytes; the
// nonthrowing declaration preserves ScriptConditions' retail EH scheduling.

// Retail has no AsciiString forwarders for these two: each spelling is the
// StringBase<char> body (trim 0x37CF0, compare(text) 0x69B1). As inline
// forwarders some units emitted them out of line as 5-byte jmp COMDATs that
// every other reference then bound to (2026-10-04 census: 6 and 22 copies).
// Evidence snapshot of canonical unicode_string.h; no production header edit.

// BFME2's shared UnicodeString: include this instead of declaring a TU-local
// `class UnicodeString` (2026-10-01: 217 TUs carried private copies in 145
// versions). Put /Ireference/shims/bfme2_ascii FIRST among a TU's /I flags so
// this header and the string_base.h beside it win over Open-BFME-1's.
//
// Zero Hour's UnicodeString made a StringBase<unsigned short> subclass, as the
// Open-BFME-1 WWLib header has it and as most private copies wrote it. Retail
// inlines the members everywhere: game.dat holds no call to the out-of-line
// copies of the copy and text constructors, the (unsigned short), (const
// unsigned short *, int) and (const unsigned short *, int, int) constructors,
// operator= or the other operator+= overloads; those are __forceinline here.
// operator+=(unsigned short) is a plain inline: retail calls its copy from 8
// sites and expands it in place elsewhere (LanguageFilter::unHaxor). The exports keep one copy of each alive, which
// WWLib/unicode_string.cpp emits as select-any COMDATs for the ledger rows.
// string_base.h's inline ~StringBase makes ~UnicodeString the bare
// `jmp releaseBuffer` retail has at 0x005B804E. The other members follow game.dat's exports (reverse/exports.csv):
// format(const unsigned short *, ...), format(const UnicodeString *, ...),
// translate(const AsciiString &), translate(const char *),
// UnicodeString(const AsciiString &). TheEmptyString is non-const, the spelling
// the tree converged on (c4cb0cd6ba).

class AsciiString;

class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString() {}
	__forceinline UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	__forceinline UnicodeString(unsigned short c) : StringBase<unsigned short>(c) {}
	__forceinline UnicodeString(const unsigned short *s) : StringBase<unsigned short>(s) {}
	__forceinline UnicodeString(const unsigned short *s, int len) : StringBase<unsigned short>(s, len) {}
	__forceinline UnicodeString(const unsigned short *s, int start, int len) : StringBase<unsigned short>(s, start, len) {}
	UnicodeString(const UnicodeString &that, int start, int len) : StringBase<unsigned short>(that, start, len) {}
	UnicodeString(const AsciiString &that);
	~UnicodeString() {}

	__forceinline UnicodeString &operator=(const UnicodeString &that)
	{
		set(that);
		return *this;
	}
	__forceinline UnicodeString &operator=(unsigned short c)
	{
		unsigned short text = c;
		set(&text, 1);
		return *this;
	}
	__forceinline UnicodeString &operator=(const unsigned short *s)
	{
		set(s);
		return *this;
	}
	__forceinline UnicodeString &operator+=(const UnicodeString &that)
	{
		concat(that);
		return *this;
	}
	UnicodeString &operator+=(unsigned short c)
	{
		unsigned short text = c;
		concat(&text, 1);
		return *this;
	}
	__forceinline UnicodeString &operator+=(const unsigned short *s)
	{
		concat(s);
		return *this;
	}

	void __cdecl format(const unsigned short *fmt, ...);
	void __cdecl format(const UnicodeString *fmt, ...);
	void translate(const AsciiString &that);
	void translate(const char *that);

	static UnicodeString TheEmptyString;
};

// Retail registers no unwind state for a name compared with text:
// StringBase<unsigned short>::compare is taken not to throw (as in
// LANAPIAddGame.cpp).
template <> int StringBase<unsigned short>::compare( const unsigned short *str ) const throw();

// The ledger's inequality test of two addresses (0x00248CDD) is a method of
// a class named by its address; an empty base puts it on BfmeNetAddress.
class Rva00248CDD
{
public:
	Bool rva00248CDD( const Rva00248CDD &other ) const;
};

struct BfmeNetAddress : public Rva00248CDD
{
	Bool Rva00248CBF( const BfmeNetAddress *other ) const;

 BfmeNetAddress(){}
 BfmeNetAddress(unsigned ip,unsigned short port):m_ip(ip),m_port(port){}
 BfmeNetAddress *self(){return this;}

	UnsignedInt m_ip;
	UnsignedShort m_port;
};

class LANPlayer
{
public:
	~LANPlayer();
 LANPlayer() : m_lastHeard( 0 ), m_next( 0 )
	{
		m_address.m_ip = 0;
		m_address.m_port = 0;
	}

	LANPlayer *getNext( void ) { return m_next; }
	const BfmeNetAddress *getAddress( void ) const { return &m_address; }

	UnicodeString m_name;				// +0x00
	UnicodeString m_login;				// +0x04
	UnicodeString m_host;				// +0x08
	UnsignedInt m_lastHeard;			// +0x0C
	LANPlayer *m_next;				// +0x10
	BfmeNetAddress m_address;			// +0x14
};

UnsignedInt ComputeCRC( const UnsignedByte *buf, UnsignedInt len, UnsignedInt crc );

class CRC
{
public:
	CRC( void ) { crc = 0; }
	__forceinline void computeCRC( const void *buf, Int len ) { crc = ComputeCRC( (const UnsignedByte *)buf, len, crc ); }
	UnsignedInt get( void ) { return crc; }

private:
	UnsignedInt crc;
};

class GameState
{
public:
	AsciiString realMapPathToPortableMapPath( const AsciiString &in ) const;
};
extern GameState *TheGameState;

enum
{
	MAX_SLOTS = 8,
	g_lanGameNameLength = 16,
	g_lanMaxOptionsLength = 0x186
};

#define BFME_VSLOT(n) virtual void slot##n( void ) = 0;
#define BFME_GSLOT(n) virtual void slot##n( void );

struct GameSlotConnectInfo
{
	Int m_nat;
	UnsignedShort m_port;
};

// A zeroed connection info built at the call, as setState's no-connection
// argument.
struct NoConnectInfo : public GameSlotConnectInfo
{
	NoConnectInfo( void ) { m_nat = 0; m_port = 0; }
	const GameSlotConnectInfo *self( void ) const { return this; }
};

enum SlotState
{
	SLOT_OPEN = 0,
	SLOT_PLAYER = 6
};

class GameSlot
{
public:
	virtual ~GameSlot( void );
	void setState( SlotState state, UnicodeString name, const GameSlotConnectInfo *connectInfo );
	void setAddress( const BfmeNetAddress &address ) { m_address = address; }
	void unAccept( void );

	UnsignedByte m_pre38[0x38 - 4];
	BfmeNetAddress m_address;			// +0x38
	UnsignedByte m_pad40[0x1AC - 0x40];
};

class LANGameSlot : public GameSlot
{
public:
	LANGameSlot( void );
	LANGameSlot( const LANGameSlot &other );
	virtual ~LANGameSlot( void );

	void setLogin( AsciiString name );
	void setHost( AsciiString name );
	void setLastHeard( UnsignedInt time ) { m_lastHeard = time; }

private:
	UnsignedByte m_user[0x1C];			// +0x1AC LANPlayer
	UnsignedByte m_serial[4];			// +0x1C8
	UnsignedInt m_lastHeard;			// +0x1CC
};

// The slots seen from their addresses: same stride, starting at slot +0x38.
struct LANSlotAddress
{
	BfmeNetAddress m_address;
	UnsignedByte m_rest[sizeof( LANGameSlot ) - 8];
};

class GameInfo
{
public:
	virtual void *destroyDelete(unsigned);
	BFME_GSLOT(01) BFME_GSLOT(02) BFME_GSLOT(03) BFME_GSLOT(04)
	BFME_GSLOT(05) BFME_GSLOT(06) BFME_GSLOT(07) BFME_GSLOT(08) BFME_GSLOT(09)
	BFME_GSLOT(10) BFME_GSLOT(11) BFME_GSLOT(12) BFME_GSLOT(13)
	virtual void resetAccepted( void );		// slot 14
	BFME_GSLOT(15) BFME_GSLOT(16) BFME_GSLOT(17) BFME_GSLOT(18) BFME_GSLOT(19)
	BFME_GSLOT(20) BFME_GSLOT(21) BFME_GSLOT(22)
	virtual UnicodeString getName( void );	// slot 23

	AsciiString getMap( void ) const;
	GameSlot *getSlot( Int slotNum );
	void enterGame( void );
	Bool isGameInProgress( void ) const { return m_inProgress; }
	void setGameInProgress( Bool inProgress ) { m_inProgress = inProgress; }

private:
	UnsignedByte m_pre11[0x11 - 4];
	Bool m_inProgress;				// +0x11
	UnsignedByte m_preCC[0xCC - 0x12];
public:
	UnsignedByte m_bfmeCC[16];			// +0xCC
};

// getLANSlot (0x00447773), under the ledger's class name. Retail calls it
// directly at each use, with no inline wrapper between.
class Rva00447773 : public GameInfo
{
public:
	void *rva00447773( Int index );
 void *rva00449522(Int index);
};

// getSlotNum (0x004483BC), under the ledger's class name, that of the
// LANGameInfo destructor.
class Rva004482FB : public Rva00447773
{
public:
	Int rva004483BC( UnicodeString name );
};

class LANGameInfo : public Rva004482FB
{
public:
	LANGameInfo( void );
	void setName( UnicodeString name );
	Bool amIHost( void ) const;			// amIHost
	void setSlot( Int slotNum, LANGameSlot slotInfo );
	const BfmeNetAddress *getAddress( Int slot ) const { return &m_slots[slot].m_address; }
	const LANSlotAddress *getSlotAddresses( void ) const { return (const LANSlotAddress *)&m_slots[0].m_address; }
	Bool getIsDirectConnect( void ) const { return m_isDirectConnect; }
	void setIsDirectConnect( Bool isDirectConnect ) { m_isDirectConnect = isDirectConnect; }
	LANGameInfo *getNext( void ) { return m_next; }
	void setLastHeard( UnsignedInt lastHeard ) { m_lastHeard = lastHeard; }
 UnsignedInt getLastHeard()const{return m_lastHeard;}

private:
	LANGameSlot m_slots[MAX_SLOTS];			// +0xDC, addresses from +0x114
	LANGameInfo *m_next;				// +0xF5C
	UnsignedInt m_lastHeard;			// +0xF60
	UnsignedByte m_preF68[0xF68 - 0xF64];
	Bool m_isDirectConnect;				// +0xF68
};

class NetworkInterface
{
public:
	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	virtual void update(); BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) virtual void RequestGameStart(Bool); virtual void RequestGameStartTimer(Int);
 virtual void RequestGameOptions(AsciiString,Bool,BfmeNetAddress*); BFME_VSLOT(26) BFME_VSLOT(27) virtual void RequestGameAnnounce(); virtual void RequestSetName(UnicodeString);
 virtual void RequestLobbyLeave(Bool); virtual void ResetGameStartTimer(); BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42)
	virtual Bool isPacketRouter( void ) = 0;	// slot 43
};
extern NetworkInterface *TheNetwork;

AsciiString GenerateGameOptionsString( void );
AsciiString GameInfoToAsciiString( const GameInfo *game, Bool isPublic );
Bool ParseAsciiStringToGameInfo( GameInfo *game, AsciiString options, Bool isPublic );
Bool ParseGameOptionsString( LANGameInfo *game, AsciiString options, const void *data, Int length );

// The saved game filed under a printed digest (0x004360B3), as
// MpGameSetupSlots.cpp declares it.
struct TreeHintOpaque0043671B;
TreeHintOpaque0043671B *Rva004360B3( AsciiString key );

// The 16 bytes at a game's +0xCC, restored by 0x00381D02 under the ledger's
// class name.
class Rva00381D02
{
public:
	void rva00381D02( void *source );
};

// setPlayerLastHeard (0x00248D35), under the ledger's class name; retail
// calls it on the current game directly.
class Rva00248D35
{
public:
	void rva00248D35( Int index, Int value );
};

// BFME 1's writeLANGameInfo: serializes the game into a message's options.
void Rva00447CA9( LANGameInfo *game, char *buffer, Int size );

// fillCurrentLANGameInfo: the current game's options, as Open-BFME-1 names
// BFME's helper.
void Rva0044802D( char *buffer, Int size );

void Rva00446A77Enable( void );

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY,
		RET_UNKNOWN
	};

	enum ChatType
	{
		LANCHAT_NORMAL = 0,
		LANCHAT_TYPE1,
		LANCHAT_EMOTE,
		LANCHAT_SYSTEM
	};
};

#pragma pack(push, 1)
struct LANMessage
{
	Int LANMessageType;
	WideChar name[11];				// +0x04
	char userName[2];				// +0x1A
	char hostName[2];				// +0x1C
	union
	{
		struct
		{
			WideChar gameName[20];			// +0x1E
			UnsignedInt playerIP;			// +0x46
			UnsignedShort playerPort;		// +0x4A
			LANAPIInterface::ReturnType reason;	// +0x4C
		} JoinDeny;
		struct
		{
			WideChar gameName[20];			// +0x1E
			UnsignedInt playerIP;			// +0x46
			UnsignedShort playerPort;		// +0x4A
			Int slotPosition;			// +0x4C
		} GameJoined;
		struct
		{
			WideChar gameName[17];			// +0x1E
			UnsignedInt mapCRC;			// +0x40
			Bool hasMap;				// +0x44
		} MapStatus;
		struct
		{
			WideChar gameName[g_lanGameNameLength + 1];	// +0x1E
			Bool inProgress;			// +0x40
			Bool isDirectConnect;			// +0x41
			char options[g_lanMaxOptionsLength];	// +0x42
			UnsignedByte bfmeTail[16];		// +0x1C8
		} GameInfo;
		struct
		{
			char options[g_lanMaxOptionsLength];	// +0x1E
		} GameOptions;
		struct
		{
			WideChar gameName[17];			// +0x1E
		} GameToLeave;
		struct
		{
			WideChar gameName[17];			// +0x1E
			LANAPIInterface::ChatType chatType;	// +0x40
			WideChar message[101];			// +0x44
		} Chat;
	};
};
#pragma pack(pop)

class LANAPI
{
public:
	enum PendingAction
	{
		ACT_NONE = 0,
		ACT_JOIN
	};

	BFME_VSLOT(00) BFME_VSLOT(01) BFME_VSLOT(02) BFME_VSLOT(03) BFME_VSLOT(04)
	BFME_VSLOT(05) BFME_VSLOT(06) BFME_VSLOT(07) BFME_VSLOT(08) BFME_VSLOT(09)
	virtual void update(); BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void RequestGameJoin( LANGameInfo *game, const BfmeNetAddress &ip );	// slot 16
	BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) virtual void RequestGameStart(Bool); virtual void RequestGameStartTimer(Int);
 virtual void RequestGameOptions(AsciiString,Bool,BfmeNetAddress*);
	virtual void rva004497EC( Bool isPublic, BfmeNetAddress *ip );	// slot 26
	BFME_VSLOT(27) virtual void RequestGameAnnounce(); virtual void RequestSetName(UnicodeString);
 virtual void RequestLobbyLeave(Bool); virtual void ResetGameStartTimer();
	virtual void OnGameList( LANGameInfo *gameList );	// slot 32
	virtual void rva00248E87( void );		// slot 33, the player list refresh
	virtual void OnGameJoin( LANAPIInterface::ReturnType ret, LANGameInfo *theGame, LANMessage *msg );
	BFME_VSLOT(35)
	virtual void OnHostLeave( void );		// slot 36
	virtual void OnPlayerLeave( UnicodeString player );	// slot 37
	BFME_VSLOT(38)
	virtual void OnHasMap( const BfmeNetAddress *ip, Bool status );
	virtual void OnChat( const UnicodeString &player, const BfmeNetAddress *ip,
		const UnicodeString &message, LANAPIInterface::ChatType format );	// slot 40
	BFME_VSLOT(41)
	virtual void OnGameStart( void );		// slot 42
	virtual void OnWOTRGameStart( void );		// slot 43
	BFME_VSLOT(44) BFME_VSLOT(45)
	virtual Bool rva0024924D( const BfmeNetAddress &sender, Int playerSlot, const void *data, Int length );	// slot 46
	BFME_VSLOT(47)
	virtual void OnNameChange( BfmeNetAddress *from, UnicodeString newName );
	virtual LANGameInfo *LookupGame( UnicodeString gameName );
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53)
	virtual Bool AmIHost( void );			// slot 54
	BFME_VSLOT(55) BFME_VSLOT(56)
	virtual void fillInLANMessage( LANMessage *msg ) = 0;	// slot 57
	virtual void checkMOTD(); BFME_VSLOT(59)
	BFME_VSLOT(60)
	virtual void rva00248E2F( Bool value );		// slot 61
	BFME_VSLOT(62)
	virtual LANPlayer *LookupPlayer( const BfmeNetAddress *who );
	virtual BfmeNetAddress *getLocalAddress( void ) = 0;

	void Rva004495A2( LANMessage *msg, UnsignedInt ip );	// sendMessage

protected:
	void removePlayer( LANPlayer *player );
	void addPlayer( LANPlayer *player );
	void removeGame( LANGameInfo *game );
	void addGame( LANGameInfo *game );
	void handleRequestLobbyLeave( LANMessage *msg, const BfmeNetAddress *sender );
	void handleLobbyAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinDeny( LANMessage *msg, const BfmeNetAddress *sender );
	void handleHasMap( LANMessage *msg, const BfmeNetAddress *sender );
	void handleInActive( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameInfo( LANMessage *msg, const BfmeNetAddress *sender );
	void handleGameOptions( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleChat( LANMessage *msg, const BfmeNetAddress *sender );
	void handleJoinAccept( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestGameLeave( LANMessage *msg, const BfmeNetAddress *sender, Bool flag );
	void handleGameAnnounce( LANMessage *msg, const BfmeNetAddress *sender );
	void handleRequestLocations( LANMessage *msg, const BfmeNetAddress *sender );
 void handleRequestJoin(LANMessage*,const BfmeNetAddress*);
 public:
 void rva005815EA(LANMessage*,const BfmeNetAddress*);
 void rva00581641(LANMessage*,const BfmeNetAddress*);
 void rva005816A3(LANMessage*,const BfmeNetAddress*);
 void rva00582138(LANMessage*,const BfmeNetAddress*);
 void rva005816E3(LANMessage*,const BfmeNetAddress*);

	UnsignedByte m_pre0C[0x0C - 4];
	LANPlayer *m_lobbyPlayers;			// +0x0C
	LANGameInfo *m_games;				// +0x10
	UnicodeString m_name;				// +0x14
	AsciiString m_userName;				// +0x18
	AsciiString m_hostName;				// +0x1C
	UnsignedInt m_gameStartTime;			// +0x20
	Int m_gameStartSeconds;				// +0x24
	Int m_pendingAction;				// +0x28
	UnsignedInt m_expiration;			// +0x2C
	UnsignedInt m_actionTimeout;			// +0x30
	BfmeNetAddress m_directConnectRemoteAddress;	// +0x34
	UnsignedInt m_lastResendTime;			// +0x3C
	Bool m_isInLANMenu;				// +0x40
	Bool m_inLobby;					// +0x41
	LANGameInfo *m_currentGame;			// +0x44
 unsigned unknown48[2];Transport *m_transport;unsigned unknown54;unsigned m_lastUpdate;
};

#undef BFME_VSLOT
#undef BFME_GSLOT

extern LANAPI *TheLAN;


extern Bool LANbuttonPushed;
Bool LANSocketErrorDetected=false;

extern "C" __declspec(dllimport) WideChar *__cdecl wcsncpy(WideChar*,const WideChar*,unsigned);
class Rva004482B7 {public:StringBase<unsigned short> rva004482B7(Int);};
class GameTextInterface {public:
 virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();
 virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();
 virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();
 virtual UnicodeString fetch(const char*,Bool *exists=0);virtual void s16();
 virtual const UnicodeString *fetchPointer(const char*,Bool *exists=0);
};
extern GameTextInterface *TheGameText;
// Layout-only access to the two packed native rings; Transport stays canonical.
#pragma pack(push,1)
struct LANReceivePacket { unsigned crc; unsigned char data[1024];unsigned length;unsigned ip;unsigned short port;};
#pragma pack(pop)
struct LANTransportRings {LANReceivePacket out[128],in[128];};
void LANAPI::update() {
 if(LANbuttonPushed)return;
 UnsignedInt now=timeGetTime();
 if(now>m_lastUpdate+200)m_lastUpdate=now;else return;
 if(!m_transport->update(0) && !LANSocketErrorDetected && m_isInLANMenu==true)LANSocketErrorDetected=true;
 for(int i=0;i<128 && !LANbuttonPushed;++i) {
  Bool flag=false;
  if(((LANTransportRings*)m_transport)->in[i].length>0) {
   BfmeNetAddress sender(((LANTransportRings*)m_transport)->in[i].ip,((LANTransportRings*)m_transport)->in[i].port);
   if(sender.Rva00248CBF(getLocalAddress())){((LANTransportRings*)m_transport)->in[i].length=0;continue;}
   LANMessage *msg=(LANMessage*)((LANTransportRings*)m_transport)->in[i].data;
   switch(msg->LANMessageType) {
    case 0:handleRequestLocations(msg,&sender);break;
    case 1:handleGameAnnounce(msg,&sender);break;
    case 2:handleLobbyAnnounce(msg,&sender);break;
    case 18:handleRequestGameInfo(msg,&sender);break;
    case 3:handleRequestJoin(msg,&sender);break;
    case 4:RequestLobbyLeave(true);handleJoinAccept(msg,&sender);break;
    case 5:handleJoinDeny(msg,&sender);break;
    case 8:flag=true;
    case 6:handleRequestGameLeave(msg,&sender,flag);break;
    case 7:handleRequestLobbyLeave(msg,&sender);break;
    case 9:rva005815EA(msg,&sender);break;
    case 10:handleHasMap(msg,&sender);break;
    case 11:handleChat(msg,&sender);break;
    case 12:rva00581641(msg,&sender);break;
    case 13:handleGameOptions(msg,&sender,false);break;
    case 14:handleGameOptions(msg,&sender,true);break;
    case 15:rva005816A3(msg,&sender);break;
    case 16:rva00582138(msg,&sender);break;
    case 17:handleInActive(msg,&sender);break;
    case 19:rva005816E3(msg,&sender);break;
   }
   ((LANTransportRings*)m_transport)->in[i].length=0;
  }
 }
 if(LANbuttonPushed)return;
 UnsignedInt resendNow=*(volatile UnsignedInt*)&now;
 if(resendNow>2000+m_lastResendTime) {
  m_lastResendTime=resendNow;
  if(m_inLobby)RequestSetName(m_name);
  else if(m_currentGame && !m_currentGame->isGameInProgress()) {
   if(AmIHost()) {rva004497EC(true,BfmeNetAddress(0,0).self());RequestGameAnnounce();}
   else {
    AsciiString text;text.format("User=%s",m_userName.str());
    RequestGameOptions(text,true,BfmeNetAddress(0,0).self());
    text.format("Host=%s",m_hostName.str());RequestGameOptions(text,true,BfmeNetAddress(0,0).self());
    RequestGameOptions("HELLO",false,BfmeNetAddress(0,0).self());
   }
  } else if(m_currentGame)RequestGameAnnounce();
 }
 LANPlayer *player=m_lobbyPlayers;
 Bool playerListChanged=false,gameListChanged=false;
 while(player) {
  if(player->m_lastHeard+20000<now) {
   LANPlayer *next=player->getNext();removePlayer(player);delete player;player=next;playerListChanged=true;
  }else player=player->getNext();
 }
 LANGameInfo *game=m_games;
 while(game) {
  if(game!=m_currentGame && game->getLastHeard()+20000<now) {
   removeGame(game);LANGameInfo*next=game->getNext();::operator delete(game->destroyDelete(0));game=next;gameListChanged=true;
  } else game=game->getNext();
 }
 if(m_currentGame && !m_currentGame->isGameInProgress()) {
  if(!AmIHost()) {
   if((UnsignedInt)m_currentGame->rva00449522(0)+20000<now) {
   LANMessage msg;fillInLANMessage(&msg);msg.LANMessageType=8;
   wcsncpy(msg.name,((Rva004482B7*)m_currentGame)->rva004482B7(0).str(),10);msg.name[10]=0;
   handleRequestGameLeave(&msg,m_currentGame->getAddress(0),false);
   UnicodeString text;text=TheGameText->fetch("LAN:HostNotResponding");OnChat(UnicodeString::TheEmptyString,getLocalAddress(),text,LANAPIInterface::LANCHAT_SYSTEM);
   }
  } else {
   int p=1;BfmeNetAddress none(0,0);_ReadWriteBarrier();
   for(;p<8;++p) {
    LANGameInfo *current=m_currentGame;
    if(current->getAddress(p)->Rva00248CDD::rva00248CDD(none) && (UnsignedInt)current->rva00449522(p)+20000<now) {
     LANMessage msg;fillInLANMessage(&msg);UnicodeString text;
     text.format(TheGameText->fetchPointer("LAN:PlayerDropped"),((Rva004482B7*)m_currentGame)->rva004482B7(p).str());
     msg.LANMessageType=6;wcsncpy(msg.name,((Rva004482B7*)m_currentGame)->rva004482B7(p).str(),10);msg.name[10]=0;
     handleRequestGameLeave(&msg,m_currentGame->getAddress(p),false);OnChat(UnicodeString::TheEmptyString,getLocalAddress(),text,LANAPIInterface::LANCHAT_SYSTEM);
    }
   }
  }
 }
 if(playerListChanged)rva00248E87();if(gameListChanged)OnGameList(m_games);
 if(m_pendingAction!=ACT_NONE && now>m_expiration) {
  switch(m_pendingAction) {
   case 1:OnGameJoin(LANAPIInterface::RET_TIMEOUT,0,0);m_currentGame=0;m_inLobby=true;break;
   case 2:OnGameJoin(LANAPIInterface::RET_TIMEOUT,0,0);m_currentGame=0;m_inLobby=true;break;
   case 3:OnPlayerLeave(m_name);m_currentGame=0;m_inLobby=true;break;
  }m_pendingAction=ACT_NONE;
 }
 if(m_gameStartTime && m_gameStartSeconds && m_gameStartTime<=now)RequestGameStartTimer(m_gameStartSeconds);
 else if(m_gameStartTime && m_gameStartTime<=now){ResetGameStartTimer();RequestGameStart(false);}
 static UnsignedInt lastMOTDCheck=0;
 if(now>lastMOTDCheck+30000){checkMOTD();lastMOTDCheck=now;}
}
