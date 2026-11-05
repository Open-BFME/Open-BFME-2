#pragma once

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
// UnicodeString(const AsciiString &). TheEmptyString is const, as the export
// ?TheEmptyString@UnicodeString@@2V1@B spells it.
#include "string_base.h"

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

	static const UnicodeString TheEmptyString;
};
