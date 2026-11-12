// Seven bodies of GNU gperf's generated `in_word_set` lookup, verbatim down to
// the order of its two length tests:
//
//     if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH) {
//         int key = hash (str, len);
//         if (key <= MAX_HASH_VALUE && key >= 0) {
//             const char *s = wordlist[key].name;
//             if (*str == *s && !strcmp (str + 1, s + 1))
//                 return &wordlist[key];
//         }
//     }
//     return 0;
//
// WHY GPERF AND NOT SOME OTHER TABLE LOOKUP.  Four details together leave very
// little room.  The length window is tested with an UNSIGNED pair (ja/jb) while
// the key window is tested SIGNED (jg/jl) -- that is gperf's `unsigned int len`
// against its `register int key`, and hand-written code would not mix them.
// The first character is compared SEPARATELY before the rest of the string,
// which is gperf's `*str == *s && !strcmp (str + 1, s + 1)` and nobody else's
// idea.  The successful return is the ELEMENT ADDRESS, not the element, so the
// table is gperf's `wordlist` of structs whose first field is the key string.
// And the whole compare is the MSVC strcmp INTRINSIC expanded inline -- the
// unrolled two-bytes-per-iteration loop ending `sbb ecx,ecx / sbb ecx,-1` --
// so `!strcmp(...)` is in the source and the call was never emitted.
//
// FOUR AXES, ALL READ OFF IMMEDIATES OR RELOCATIONS: MAX_WORD_LENGTH (0x08 to
// 0x14), MIN_WORD_LENGTH (2, 3 or 4), MAX_HASH_VALUE (0x0B to 0xD3) and the
// hash function's REL32.  Every row has its own hash function, and each hash
// function sits a fixed distance below its lookup, which is what a single gperf
// run per table produces.  The wordlist base is a DIR32 operand and so costs no
// pin; its stride is 8 in every row, so every table is an array of
// {const char *, four bytes}.
//
// The 132-byte row at 0x008D48F0 is not a second shape: its MAX_HASH_VALUE is
// 0xD3, which no longer fits in a signed byte, so `cmp eax,imm8` grows to
// `cmp eax,imm32`.
//
// IDENTITY IS NOT RECOVERED.  Names are derived from addresses.  The VALUE
// field of the table entries is never read here, so its type is not recovered
// either -- only that it is four bytes wide.

#include <string.h>

#include "../../Include/Common/R4Word.h"

#define R4_GPERF( NAME, HASHFN, WORDLIST, MINLEN, MAXLEN, MAXHASH )           \
	int HASHFN( const char *str, unsigned int len );                          \
	extern const R4Word WORDLIST[];                                           \
	const R4Word *NAME( const char *str, unsigned int len );                  \
	const R4Word *NAME( const char *str, unsigned int len )                   \
	{                                                                         \
		if ( len <= MAXLEN && len >= MINLEN )                                 \
		{                                                                     \
			register int key = HASHFN( str, len );                            \
			if ( key <= MAXHASH && key >= 0 )                                 \
			{                                                                 \
				register const char *s = WORDLIST[ key ].name;                \
				if ( *str == *s && !strcmp( str + 1, s + 1 ) )                \
					return &WORDLIST[ key ];                                  \
			}                                                                 \
		}                                                                     \
		return 0;                                                             \
	}

R4_GPERF( Rva008A44A0, Gen008A3EE0, g008A44A0, 4, 0x0E, 0x10 )
R4_GPERF( Rva008ABF40, Gen008AB970, g008ABF40, 4, 0x11, 0x1D )
R4_GPERF( Rva008B5610, Gen008B5050, g008B5610, 4, 0x0B, 0x0B )
R4_GPERF( Rva008B8AD0, Gen008B8510, g008B8AD0, 3, 0x08, 0x1B )
R4_GPERF( Rva008D48F0, Gen008D42C0, g008D48F0, 2, 0x14, 0xD3 )
R4_GPERF( Rva008D4F80, Gen008D4980, g008D4F80, 3, 0x0B, 0x24 )
R4_GPERF( Rva008D5DC0, Gen008D57B0, g008D5DC0, 4, 0x0F, 0x4C )

/* Retail DIR32 witnesses in the matched rows establish each table VA (two per table).
 * Each table reproduces the 8-byte {name pointer, value} records read from retail.
 * Four-byte values are copied; their semantics are not established by these lookups.
 * Name pointers reproduce the pointed-to text only: the target strings have no linkable
 * named char objects in this TU, so pointer identity is not asserted. Retail empty-name
 * pointers target VA 0x00BBAC1C, whose text is empty; its typed data object is not
 * defined here, so only the empty text is reproduced by the local literal.
 */
#define R4_EMPTY_WORD { "", 0 }
// g008A44A0: VA 0x00DDC558 (.data); 17 records, bounded by 0x00DDC5E0, the next table g008ABF40.
const R4Word g008A44A0[17] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ R4_EMPTY_WORD, { "load", 1 }, R4_EMPTY_WORD,
	/* 006-008 */ { "loaded", 6 }, R4_EMPTY_WORD, { "toString", 7 },
	/* 009-011 */ { "send", 2 }, R4_EMPTY_WORD, { "contentType", 8 },
	/* 012-014 */ R4_EMPTY_WORD, { "getBytesTotal", 4 }, { "getBytesLoaded", 5 },
	/* 015-016 */ R4_EMPTY_WORD, { "sendAndLoad", 3 },
};

// g008ABF40: VA 0x00DDC5E0 (.data); 30 records, bounded by 0x00DDC6D0, the next table g008B5610.
const R4Word g008ABF40[30] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ R4_EMPTY_WORD, { "text", 12 }, R4_EMPTY_WORD,
	/* 006-008 */ { "border", 4 }, { "hscroll", 6 }, { "maxChars", 8 },
	/* 009-011 */ { "textWidth", 15 }, { "textHeight", 14 }, { "length", 7 },
	/* 012-014 */ { "_height", 19 }, { "variable", 17 }, { "maxscroll", 9 },
	/* 015-017 */ { "background", 2 }, { "borderColor", 5 }, { "mouseWheelEnabled", 21 },
	/* 018-020 */ { "autoSize", 1 }, { "multiline", 10 }, { "backgroundColor", 3 },
	/* 021-023 */ { "scroll", 11 }, R4_EMPTY_WORD, { "wordWrap", 18 },
	/* 024-026 */ { "textColor", 13 }, R4_EMPTY_WORD, { "_width", 20 },
	/* 027-029 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "type", 16 },
};

// g008B5610: VA 0x00DDC6D0 (.data); 12 records, bounded by 0x00DDC730, the known g008B60B0words table.
const R4Word g008B5610[12] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ R4_EMPTY_WORD, { "stop", 3 }, { "start", 2 },
	/* 006-008 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 009-011 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "attachSound", 1 },
};

// g008B8AD0: VA 0x00DDC0B0 (.data); 28 records, bounded by 0x00DDC190, the known g00897FD0words table.
const R4Word g008B8AD0[28] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ { "pop", 4 }, { "sort", 9 }, { "shift", 6 },
	/* 006-008 */ { "sortOn", 12 }, { "unshift", 7 }, { "toString", 13 },
	/* 009-011 */ { "join", 3 }, R4_EMPTY_WORD, { "concat", 2 },
	/* 012-014 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "push", 5 },
	/* 015-017 */ R4_EMPTY_WORD, { "length", 1 }, R4_EMPTY_WORD,
	/* 018-020 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "slice", 11 },
	/* 021-023 */ { "splice", 10 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 024-026 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 027-027 */ { "reverse", 8 },
};

// g008D48F0: VA 0x00DDD0C8 (.data); 212 records, bounded by 0x00DDD768, the next table g008D5DC0.
const R4Word g008D48F0[212] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "_name", 14 },
	/* 006-008 */ { "escape", 28 }, { "setMask", 122 }, R4_EMPTY_WORD,
	/* 009-011 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 012-014 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 015-017 */ { "removeTextField", 119 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 018-020 */ { "_visible", 8 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 021-023 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 024-026 */ { "_url", 16 }, { "createTextField", 114 }, R4_EMPTY_WORD,
	/* 027-029 */ { "_x", 1 }, R4_EMPTY_WORD, { "nextFrame", 113 },
	/* 030-032 */ R4_EMPTY_WORD, { "extern", 23 }, { "_xmouse", 21 },
	/* 033-035 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 036-038 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "_soundbuftime", 19 },
	/* 039-041 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 042-044 */ R4_EMPTY_WORD, { "setTextFormat", 125 }, { "prevFrame", 108 },
	/* 045-047 */ { "_focusrect", 18 }, { "_alpha", 7 }, { "onPress", 211 },
	/* 048-050 */ { "unescape", 27 }, { "onRelease", 212 }, { "createEmptyMovieClip", 116 },
	/* 051-053 */ { "onLoad", 207 }, { "onMouseWheel", 218 }, R4_EMPTY_WORD,
	/* 054-056 */ { "play", 107 }, { "removeMovieClip", 109 }, { "onReleaseOutside", 213 },
	/* 057-059 */ { "onEnterFrame", 203 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 060-062 */ R4_EMPTY_WORD, { "_width", 9 }, { "onKeyUp", 205 },
	/* 063-065 */ R4_EMPTY_WORD, { "onMouseUp", 210 }, { "onSetFocus", 216 },
	/* 066-068 */ { "onData", 200 }, { "_xscale", 3 }, R4_EMPTY_WORD,
	/* 069-071 */ R4_EMPTY_WORD, { "isNaN", 26 }, { "onMouseMove", 209 },
	/* 072-074 */ { "_y", 2 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 075-077 */ R4_EMPTY_WORD, { "unloadMovie", 121 }, { "_ymouse", 22 },
	/* 078-080 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 081-083 */ { "getURL", 102 }, { "Boolean", 29 }, { "_framesloaded", 13 },
	/* 084-086 */ R4_EMPTY_WORD, { "onRollOver", 215 }, { "getNewTextFormat", 123 },
	/* 087-089 */ R4_EMPTY_WORD, { "localToGlobal", 127 }, R4_EMPTY_WORD,
	/* 090-092 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "_highquality", 17 },
	/* 093-095 */ { "onUnload", 217 }, { "getBounds", 117 }, R4_EMPTY_WORD,
	/* 096-098 */ R4_EMPTY_WORD, { "_height", 10 }, R4_EMPTY_WORD,
	/* 099-101 */ { "stop", 110 }, R4_EMPTY_WORD, { "onMouseDown", 208 },
	/* 102-104 */ { "_target", 12 }, { "getTextFormat", 124 }, { "onRollOut", 214 },
	/* 105-107 */ R4_EMPTY_WORD, { "setInterval", 24 }, R4_EMPTY_WORD,
	/* 108-110 */ R4_EMPTY_WORD, { "onKeyDown", 204 }, { "onDragOver", 202 },
	/* 111-113 */ { "_droptarget", 15 }, { "_yscale", 4 }, R4_EMPTY_WORD,
	/* 114-116 */ R4_EMPTY_WORD, { "swapDepths", 120 }, R4_EMPTY_WORD,
	/* 117-119 */ { "hitTest", 118 }, { "_currentframe", 5 }, R4_EMPTY_WORD,
	/* 120-122 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 123-125 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 126-128 */ { "onKillFocus", 206 }, R4_EMPTY_WORD, { "getDepth", 115 },
	/* 129-131 */ { "onDragOut", 201 }, R4_EMPTY_WORD, { "gotoAndPlay", 103 },
	/* 132-134 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 135-137 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 138-140 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 141-143 */ { "gotoAndStop", 104 }, { "_totalframes", 6 }, R4_EMPTY_WORD,
	/* 144-146 */ { "_rotation", 11 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 147-149 */ R4_EMPTY_WORD, { "duplicateMovieClip", 101 }, R4_EMPTY_WORD,
	/* 150-152 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 153-155 */ { "clearInterval", 25 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 156-158 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "_quality", 20 },
	/* 159-161 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 162-164 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 165-167 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 168-170 */ { "getBytesTotal", 112 }, { "getBytesLoaded", 111 }, R4_EMPTY_WORD,
	/* 171-173 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "loadVariables", 106 },
	/* 174-176 */ { "startDrag", 126 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 177-179 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 180-182 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 183-185 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 186-188 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 189-191 */ { "loadMovie", 105 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 192-194 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 195-197 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 198-200 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 201-203 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 204-206 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 207-209 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 210-211 */ R4_EMPTY_WORD, { "attachMovie", 100 },
};

// g008D4F80: VA 0x00DDCFA0 (.data); 37 records, bounded by 0x00DDD0C8, the next table g008D48F0.
const R4Word g008D4F80[37] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ { "url", 16 }, { "size", 14 }, R4_EMPTY_WORD,
	/* 006-008 */ { "target", 13 }, { "leading", 9 }, { "tabStops", 12 },
	/* 009-011 */ { "underline", 15 }, { "align", 1 }, { "rightMargin", 11 },
	/* 012-014 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "font", 6 },
	/* 015-017 */ { "color", 5 }, { "indent", 7 }, R4_EMPTY_WORD,
	/* 018-020 */ R4_EMPTY_WORD, { "bold", 3 }, { "leftMargin", 10 },
	/* 021-023 */ { "bullet", 4 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 024-026 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "italic", 8 },
	/* 027-029 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 030-032 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 033-035 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 036-036 */ { "blockIndent", 2 },
};

// g008D5DC0: VA 0x00DDD768 (.data); 77 records, bounded by max hash 0x4C; end VA 0x00DDD9D0.
const R4Word g008D5DC0[77] = {
	/* 000-002 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 003-005 */ R4_EMPTY_WORD, { "send", 110 }, R4_EMPTY_WORD,
	/* 006-008 */ { "status", 112 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 009-011 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "nextSibling", 9 },
	/* 012-014 */ { "insertBefore", 7 }, { "getBytesTotal", 104 }, { "getBytesLoaded", 105 },
	/* 015-017 */ R4_EMPTY_WORD, { "appendChild", 1 }, R4_EMPTY_WORD,
	/* 018-020 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "firstChild", 5 },
	/* 021-023 */ { "sendAndLoad", 111 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 024-026 */ { "cloneNode", 4 }, { "childNodes", 3 }, R4_EMPTY_WORD,
	/* 027-029 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 030-032 */ { "attributes", 2 }, { "ignoreWhite", 106 }, R4_EMPTY_WORD,
	/* 033-035 */ R4_EMPTY_WORD, { "lastChild", 8 }, { "load", 107 },
	/* 036-038 */ R4_EMPTY_WORD, { "loaded", 108 }, { "hasChildNodes", 6 },
	/* 039-041 */ R4_EMPTY_WORD, R4_EMPTY_WORD, { "removeNode", 15 },
	/* 042-044 */ R4_EMPTY_WORD, { "createElement", 101 }, { "createTextNode", 102 },
	/* 045-047 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 048-050 */ { "parseXml", 109 }, { "nodeType", 11 }, R4_EMPTY_WORD,
	/* 051-053 */ R4_EMPTY_WORD, { "contentType", 100 }, R4_EMPTY_WORD,
	/* 054-056 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 057-059 */ { "docTypeDecl", 103 }, R4_EMPTY_WORD, { "toString", 16 },
	/* 060-062 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 063-065 */ R4_EMPTY_WORD, { "nodeName", 10 }, R4_EMPTY_WORD,
	/* 066-068 */ { "parentNode", 13 }, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 069-071 */ R4_EMPTY_WORD, { "nodeValue", 12 }, R4_EMPTY_WORD,
	/* 072-074 */ R4_EMPTY_WORD, R4_EMPTY_WORD, R4_EMPTY_WORD,
	/* 075-076 */ R4_EMPTY_WORD, { "previousSibling", 14 },
};
#undef R4_EMPTY_WORD
