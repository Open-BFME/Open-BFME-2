// Target facts (retail RVAs): write(char *) at 0x0002C5B1 loads the AsciiString pointer at +0, reads that string's buffer length at +4 and text at +8, calls memcpy, and returns the length with ret 4; the member remains declared out of line.
// 0x000BBD1C calls that writer on adjacent references at +0 and +4; 0x0002BF2F stores an AsciiString address at +0 and the derived char at +4; 0x0059B3E9 places a reference between +8 and +0xC. AsciiStringRef is four bytes, has no base or virtual functions, and contains no vptr.
// 0x001F13E0 and 0x001F13EA initialize two adjacent references with AsciiString addresses before conversion at 0x001F13ED; construction only retains the address. No named AsciiStringRef constructor or destructor rows or associated retail vtables exist.
#pragma once

#ifndef __BFME2_ASCIISTRINGREF_H_
#define __BFME2_ASCIISTRINGREF_H_

class AsciiString;

struct AsciiStringRef
{
	AsciiStringRef() {}
	AsciiStringRef(const AsciiString &string) : m_string(&string) {}

	int write(char *dst);

	const AsciiString *m_string;
};

#endif
