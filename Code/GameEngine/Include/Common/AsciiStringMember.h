// AsciiStringMember: canonical declarations for a string member that units destroy through
// the 0x00036410 releaseBuffer fold; it is one 4-byte data pointer at +0x00.
#ifndef CANONICAL_ASCIISTRINGMEMBER_H
#define CANONICAL_ASCIISTRINGMEMBER_H

class AsciiStringMember
{
public:
	~AsciiStringMember();

	void *m_data;
};

#endif // CANONICAL_ASCIISTRINGMEMBER_H
