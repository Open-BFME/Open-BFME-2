// Target facts (retail RVAs): operator+ (0x000B49C5) stores the borrowed AsciiString address at +0 and the pair initialized by 0x000B3F84 at +4/+8, then copies three dwords to its hidden result: sizeof 12. write (0x000BBD41) calls AsciiStringRef::write (0x0002C5B1) on +0 and Rva000B3F84Pair::write (0x000B44F0) on +4; length (0x002DBF50) dereferences the string at +0 and adds the text length at +8.
// This class has no retail virtual functions or vptr. No named constructor or destructor rows or associated tables exist; operator+ constructs and copies only the three payload words. The registered AsciiStringRef supplies the four-byte prefix; the next pair begins at +0x0C in writer 0x0059B1A2. The return spelling of operator+ is struct AsciiStringPlusText.
// The conversion to AsciiString (0x000BC4F7) calls length and the byte writer out of line; the node borrows its operands and owns no string storage. Row 0x002DD111 (spelled operator UnicodeString here) belongs to the separate UTF-16 node built by 0x002DBD80 and is not declared.
#pragma once

#ifndef __BFME2_ASCIISTRINGPLUSTEXT_H_
#define __BFME2_ASCIISTRINGPLUSTEXT_H_

#include "AsciiStringRef.h"
#include "Rva000B3F84Pair.h"

struct AsciiStringPlusText : AsciiStringRef
{
	int length() const;
	int write(char *dst);
	operator AsciiString();

	Rva000B3F84Pair m_right;
};

AsciiStringPlusText operator+(const AsciiString &left, const char *right);

#endif
