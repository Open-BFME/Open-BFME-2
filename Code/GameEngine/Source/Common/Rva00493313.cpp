// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00493313@Rva00493313@@QBE?AVAsciiString@@XZ @0x00493313 32B: return final-override name at +0x5c.
// Evidence: calls friend_getFinalOverride 0x00288609 then StringBase copy 0x000365F0; ret 4 hidden AsciiString return.
#include "ascii_string.h"

class Overridable {
public:
	const Overridable *friend_getFinalOverride() const;
private:
	char m_pad[0x10];
};

class Rva00493313 : public Overridable {
public:
	AsciiString rva00493313() const;
	const int *getInitiateSound() const;
	const int *getInitiateAtTargetSound() const;
	unsigned char hasPublicTimer() const;
	int getViewObjectDuration() const;
private:
	char m_pad10[0x34 - 0x10];
	int m_34;
	int m_38;
	char m_pad3C[0x4c - 0x3c];
	int m_4C;
	char m_pad50[0x58 - 0x50];
	unsigned char m_58;
	char m_pad59[0x5c - 0x59];
	AsciiString m_name5c;
};

// Four more final-override field reads directly before rva00493313, same
// friend_getFinalOverride 0x00288609 call: the addresses of +0x34 and +0x38
// (0x004932EF, 0x004932F8), the byte at +0x58 (0x00493301) and the dword at
// +0x4C (0x0049330A), 9 bytes each. Field meanings are not established.
const int *Rva00493313::getInitiateSound() const
{
	return &((const Rva00493313 *)friend_getFinalOverride())->m_34;
}
const int *Rva00493313::getInitiateAtTargetSound() const
{
	return &((const Rva00493313 *)friend_getFinalOverride())->m_38;
}
unsigned char Rva00493313::hasPublicTimer() const
{
	return ((const Rva00493313 *)friend_getFinalOverride())->m_58;
}
int Rva00493313::getViewObjectDuration() const
{
	return ((const Rva00493313 *)friend_getFinalOverride())->m_4C;
}
AsciiString Rva00493313::rva00493313() const
{
	const Rva00493313 *fin = (const Rva00493313 *)friend_getFinalOverride();
	return fin->m_name5c;
}
