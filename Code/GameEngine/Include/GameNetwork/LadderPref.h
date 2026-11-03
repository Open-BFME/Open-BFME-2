// Target facts (game.dat 1.06; addresses are RVAs): LadderPref has no virtual functions or bases. Copy constructor 0x005BA3F5 calls StringBase<unsigned short> copy 0x00037050 at +0 and StringBase<char> copy 0x000365F0 at +4, then copies a word at +8 and a dword at +0xC; destructor 0x005BA3C0 releases +4 through 0x00036410 and +0 through 0x00036E70. Neither stores a vptr. The by-value LadderPref argument of 0x005E03F6 is popped by RET 0x10 at 0x005E046C, proving sizeof 0x10.
// Target facts: 0x005E01A4 and 0x005E01A7 inline default construction by zeroing only the two string pointers. Pair constructor 0x005DFB91 calls the copy constructor; 0x005E0419 calls non-const operator== 0x005DFC0B, 0x005E044E calls assignment 0x005DFB48, and 0x005E045A calls the destructor. Comparison reads the narrow string at +4 and port word at +8; assignment copies the same four fields. These rowed methods have no bodies here; the copy constructor retains inline linkage and is not inlined at its calls. LadderPreferences, a separate class, calls UserPreferences at 0x005DFFE4 and stores VA 0x00C77788 at 0x005DFFF0; that table does not belong to LadderPref.
// Donor facts: Zero Hour Common/LadderPreferences.h names the fields name, address, port and lastPlayDate with types UnicodeString, AsciiString, UnsignedShort and time_t; the target uses a four-byte signed timestamp. Field names and the comparison name follow that declaration; layout and call boundaries follow retail.

#pragma once

#ifndef __BFME2_LADDERPREF_H_
#define __BFME2_LADDERPREF_H_

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/bfme2_ascii/unicode_string.h"

class LadderPref
{
public:
	LadderPref();
	inline __declspec(noinline) LadderPref(const LadderPref &other);
	~LadderPref();
	LadderPref &operator=(const LadderPref &other);
	bool operator==(const LadderPref &other);

	UnicodeString name;
	AsciiString address;
	unsigned short port;
	long lastPlayDate;
};

#endif
