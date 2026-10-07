#pragma once

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
#include "string_base.h"

// The members below are compiled favouring size with frame-pointer omission (as /O1) in
// every unit. Retail's out-of-line copies are the /O1 form (ascii_string.cpp's rows); a
// unit built /O2 or /Oy- otherwise emits its own select-any copy of each inline member
// that differs from them (2026-10-01 census: 82 units lost such copies). Code a member
// inlines into a caller still follows the caller's flags.
#pragma optimize("sy", on)
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
	void set(const char *s);
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
#pragma optimize("", on)

// The existing one-pointer view and thiscall argument agree with that
// worker. Resolve the spelling directly; a five-byte forwarding COMDAT
// would define a different body at the already verified address.
#pragma comment(linker, "/alternatename:?concat@AsciiString@@QAEXPBD@Z=?concat@?$StringBase@D@@QAEXPBD@Z")

// These existing retail spellings share the same one-pointer thiscall ABI:
// set(text) -> StringBase set at 0x55F5 (37 bytes); concat(string) ->
// StringBase concat at 0x6987 (42 bytes). clear is the releaseBuffer worker
// at 0x36410, which clears the pointer as it releases the buffer.
#pragma comment(linker, "/alternatename:?set@AsciiString@@QAEXPBD@Z=?set@?$StringBase@D@@QAEXPBD@Z")
#pragma comment(linker, "/alternatename:?concat@AsciiString@@QAEXABV1@@Z=?concat@?$StringBase@D@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:?clear@AsciiString@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

// BoneFXUpdate retail calls identify this spelling with the 42-byte worker
// at RVA 0x69D6. Its verified callees read lengths and compare bytes; the
// nonthrowing declaration preserves ScriptConditions' retail EH scheduling.
#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHABV1@@Z=?compare@?$StringBase@D@@QBEHABV1@@Z")

// Retail has no AsciiString forwarders for these two: each spelling is the
// StringBase<char> body (trim 0x37CF0, compare(text) 0x69B1). As inline
// forwarders some units emitted them out of line as 5-byte jmp COMDATs that
// every other reference then bound to (2026-10-04 census: 6 and 22 copies).
#pragma comment(linker, "/alternatename:?trim@AsciiString@@QAEXXZ=?trim@?$StringBase@D@@QAEXXZ")
#pragma comment(linker, "/alternatename:?compare@AsciiString@@QBEHPBD@Z=?compare@?$StringBase@D@@QBEHPBD@Z")
