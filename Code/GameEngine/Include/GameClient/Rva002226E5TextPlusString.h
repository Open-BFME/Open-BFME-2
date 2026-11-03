// Target facts (retail RVAs): operator+ (0x002226E5) calls Rva000B3F84Pair::init (0x000B3F84), stores its borrowed text pointer and length at +0/+4 and the right AsciiString address at +8, and copies three dwords to its hidden result: sizeof 12. Writer 0x00222D9A calls Rva000B3F84Pair::write (0x000B44F0) on +0 and AsciiStringRef::write (0x0002C5B1) on +8. Length 0x00513B94 adds +4 to the referenced string's length. All three words are payload: the node has no retail virtual functions or vptr, and no named constructor or destructor rows or associated tables exist.
// The conversion at 0x0022309D calls length and write out of line and materializes an owning AsciiString from the borrowed operands. Builder 0x005F17C6 copies the three-word prefix before appending another string reference at +0x0C. Default construction leaves the borrowed operands uninitialized; copies and assignment retain their representation. The builders copy payload directly, and no named copy or assignment rows exist.
// The ledger's operator+ return spelling is struct Rva002226E5TextPlusString. Registered AsciiStringPlusText is distinct: its builder 0x000B49C5 stores the string reference at +0 and text pair at +4/+8, and its length 0x002DBF50 reads those reversed offsets.
#pragma once

#ifndef __BFME2_RVA002226E5TEXTPLUSSTRING_H_
#define __BFME2_RVA002226E5TEXTPLUSSTRING_H_

#include "../Common/Rva000B3F84Pair.h"
#include "../Common/AsciiStringRef.h"

struct Rva002226E5TextPlusString
{
	Rva002226E5TextPlusString() {}
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_left;
	AsciiStringRef m_right;
};

Rva002226E5TextPlusString operator+(const char *left, const AsciiString &right);

#endif
