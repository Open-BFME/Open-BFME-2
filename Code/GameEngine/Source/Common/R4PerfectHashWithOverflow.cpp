// cl: /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME5: three near-twins of Rva008A9710 (twin 0x008A9710,
// Code/Libraries/Source/EA/Apt/AptStringMethodLookup.cpp). Same two-level
// gperf shape: a byte lookup table indexed by hash key either yields a
// direct wordlist index or (when negative, below -OVERN) an offset into an
// overflow run appended after the first OVERN wordlist entries, linearly
// scanned. Only the length window, MAXHASH, OVERN and the hash callee vary
// per table; the wordlist/lookup array addresses are DIR32 operands and
// cost no pin (masked like any other data relocation).

#include <string.h>

struct R4Word
{
	const char *name;
	int value;
};

#define R4_GPERF_OVERFLOW( NAME, HASHFN, WORDLIST, LOOKUP, MINLEN, MAXLEN, MAXHASH, OVERN ) \
	int HASHFN( const unsigned char *text, int length );                      \
	extern const R4Word WORDLIST[];                                           \
	extern const signed char LOOKUP[];                                        \
	const R4Word *NAME( const char *str, unsigned int len )                   \
	{                                                                         \
		if ( len <= MAXLEN && len >= MINLEN )                                 \
		{                                                                     \
			register int key = HASHFN( (const unsigned char *)str, (int)len ); \
			if ( key <= MAXHASH && key >= 0 )                                 \
			{                                                                 \
				register int index = LOOKUP[ key ];                          \
				if ( index >= 0 )                                             \
				{                                                             \
					register const char *s = WORDLIST[ index ].name;          \
					if ( *str == *s && !strcmp( str + 1, s + 1 ) )            \
						return &WORDLIST[ index ];                            \
				}                                                             \
				else if ( index < -OVERN )                                    \
				{                                                             \
					register int offset = -1 - OVERN - index;                 \
					register const R4Word *wordptr = ( WORDLIST + OVERN ) + LOOKUP[ offset ]; \
					register const R4Word *wordendptr = wordptr - LOOKUP[ offset + 1 ]; \
					while ( wordptr < wordendptr )                            \
					{                                                         \
						register const char *s = wordptr->name;               \
						if ( *str == *s && !strcmp( str + 1, s + 1 ) )        \
							return wordptr;                                   \
						wordptr++;                                            \
					}                                                         \
				}                                                             \
			}                                                                 \
		}                                                                     \
		return 0;                                                             \
	}

// retail 0x00897FD0: length [3,8], MAXHASH 0x25, overflow at 37
R4_GPERF_OVERFLOW( Rva00897FD0, bfmeSkipVF, g00897FD0words, g00897FD0lookup, 3, 8, 0x25, 37 )

// retail 0x008A3DC0: length [3,6], MAXHASH 0x31, overflow at 18
R4_GPERF_OVERFLOW( Rva008A3DC0, bfmeSkipVC, g008A3DC0words, g008A3DC0lookup, 3, 6, 0x31, 18 )

// retail 0x008B60B0: length [3,0x12], MAXHASH 0x39, overflow at 37
R4_GPERF_OVERFLOW( Rva008B60B0, bfmeSkipVH, g008B60B0words, g008B60B0lookup, 3, 0x12, 0x39, 37 )

/* The three lookup and three word tables are established by three matched DIR32
 * witnesses per global. Word records copy retail four-byte values and reproduce
 * each pointed-to string as text; pointer identity is not asserted when no linkable
 * named char object exists.
 */
// g00897FD0words: VA 0x00DDC190 (.data); 37 8-byte records, bounded by 0x00DDC2B8, the next global g00897FD0lookup.
const R4Word g00897FD0words[37] = {
	/* 000-002 */ { "Key", 4 }, { "Stage", 37 }, { "String", 36 },
	/* 003-005 */ { "_level1", 7 }, { "_level10", 21 }, { "_level19", 30 },
	/* 006-008 */ { "_level18", 29 }, { "_level17", 28 }, { "_level16", 27 },
	/* 009-011 */ { "_level15", 26 }, { "_level14", 25 }, { "_level13", 24 },
	/* 012-014 */ { "_level12", 23 }, { "_level11", 22 }, { "Math", 5 },
	/* 015-017 */ { "Mouse", 20 }, { "extern", 17 }, { "_level0", 6 },
	/* 018-020 */ { "this", 2 }, { "_root", 3 }, { "_level7", 13 },
	/* 021-023 */ { "_parent", 16 }, { "_global", 19 }, { "_level8", 14 },
	/* 024-026 */ { "_level2", 8 }, { "_level20", 31 }, { "_level24", 35 },
	/* 027-029 */ { "_level23", 34 }, { "_level22", 33 }, { "_level21", 32 },
	/* 030-032 */ { "_level9", 15 }, { "_target", 1 }, { "_level3", 9 },
	/* 033-035 */ { "_level6", 12 }, { "_level4", 10 }, { "super", 18 },
	/* 036-036 */ { "_level5", 11 },
};

// g008A3DC0words: VA 0x00DDC490 (.data); 18 8-byte records, bounded by 0x00DDC520, the next global g008A3DC0lookup.
const R4Word g008A3DC0words[18] = {
	/* 000-002 */ { "pow", 15 }, { "floor", 13 }, { "cos", 2 },
	/* 003-005 */ { "ceil", 11 }, { "round", 4 }, { "exp", 12 },
	/* 006-008 */ { "random", 16 }, { "max", 6 }, { "sqrt", 17 },
	/* 009-011 */ { "abs", 7 }, { "acos", 8 }, { "sin", 1 },
	/* 012-014 */ { "atan2", 3 }, { "log", 14 }, { "min", 5 },
	/* 015-017 */ { "tan", 18 }, { "asin", 9 }, { "atan", 10 },
};

// g008B60B0words: VA 0x00DDC730 (.data); 37 8-byte records, bounded by 0x00DDC858, the next global g008B60B0lookup.
const R4Word g008B60B0words[37] = {
	/* 000-002 */ { "UTC", 37 }, { "setHours", 22 }, { "setMinutes", 24 },
	/* 003-005 */ { "setSeconds", 26 }, { "setUTCHours", 30 }, { "setYear", 35 },
	/* 006-008 */ { "setUTCMinutes", 32 }, { "setUTCSeconds", 34 }, { "setMilliseconds", 23 },
	/* 009-011 */ { "setFullYear", 21 }, { "setUTCMilliseconds", 31 }, { "setUTCFullYear", 29 },
	/* 012-014 */ { "getDay", 2 }, { "getHours", 4 }, { "getUTCDay", 12 },
	/* 015-017 */ { "getMinutes", 6 }, { "getSeconds", 8 }, { "getUTCHours", 14 },
	/* 018-020 */ { "getYear", 19 }, { "getUTCMinutes", 16 }, { "getUTCSeconds", 18 },
	/* 021-023 */ { "getMilliseconds", 5 }, { "getFullYear", 3 }, { "getUTCMilliseconds", 15 },
	/* 024-026 */ { "getUTCFullYear", 13 }, { "setDate", 20 }, { "setTime", 27 },
	/* 027-029 */ { "setMonth", 25 }, { "setUTCDate", 28 }, { "setUTCMonth", 33 },
	/* 030-032 */ { "toString", 36 }, { "getDate", 1 }, { "getTime", 9 },
	/* 033-035 */ { "getMonth", 7 }, { "getUTCDate", 11 }, { "getUTCMonth", 17 },
	/* 036-036 */ { "getTimezoneOffset", 10 },
};

// g00897FD0lookup: VA 0x00DDC2B8 (.data); 38 signed bytes, maxhash 0x25, highest overflow offset 28; bounded before g008A3DC0words at 0x00DDC490.
const signed char g00897FD0lookup[38] = {
	/* 000-009 */ -1, -1, -1, 0, -1, 1, 2, 3, -56, 14,
	/* 010-019 */ 15, 16, 17, 18, 19, 20, 21, 22, -33, -10,
	/* 020-029 */ 23, -1, 24, -66, -1, 30, 31, 32, -12, -5,
	/* 030-037 */ 33, -1, 34, -1, -1, 35, -1, 36,
};

// g008A3DC0lookup: VA 0x00DDC520 (.data); 50 signed bytes, maxhash 0x31, highest overflow offset 47; bounded before g008A44A0 at 0x00DDC558.
const signed char g008A3DC0lookup[50] = {
	/* 000-009 */ -1, -1, -1, 0, -1, 1, -1, -1, 2, 3,
	/* 010-019 */ 4, -1, -1, 5, -1, -1, 6, -1, 7, 8,
	/* 020-029 */ -1, -1, -1, 9, 10, -1, -1, -1, 11, -1,
	/* 030-039 */ 12, -1, -1, 13, -1, -1, -1, -1, 14, -1,
	/* 040-049 */ -1, -1, -1, 15, -1, -1, -1, -2, -2, -66,
};

// g008B60B0lookup: VA 0x00DDC858 (.data); 58 signed bytes, maxhash 0x39, highest overflow offset 50; end VA 0x00DDC892.
const signed char g008B60B0lookup[58] = {
	/* 000-009 */ -1, -1, -1, 0, -1, -1, -35, -2, 1, -1,
	/* 010-019 */ -44, 4, 5, -84, -1, 8, 9, -1, 10, 11,
	/* 020-029 */ -1, 12, -1, 13, 14, -82, 17, 18, -73, -1,
	/* 030-039 */ 21, 22, -1, 23, 24, -18, -2, -80, 27, -1,
	/* 040-049 */ 28, 29, -12, -2, -22, -2, -31, -2, 30, -1,
	/* 050-057 */ -6, -2, -88, 33, -1, 34, 35, 36,
};
