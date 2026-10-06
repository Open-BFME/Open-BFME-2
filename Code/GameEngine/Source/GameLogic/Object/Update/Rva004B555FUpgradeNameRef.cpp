// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva004B555F@Rva004B555F@@QAEABVAsciiString@@XZ retail 0x004B555F 21B
// Upgrade-mask name ref via +4 entry; tail-jmp to rowed rva004CE3B9 at 0x004CE3B9 else TheEmptyString.
// Evidence: retail bytes plus rowed callee Rva004CE3B9UpgradeName.cpp plus callers 0x0029239B 0x002972F7 plus TheEmptyString 0x009E0878; unlocks 0x002972DE.
#include "ascii_string.h"

class Rva004CE3B9
{
public:
	const AsciiString &rva004CE3B9();
};

class Rva004B555F
{
public:
	const AsciiString &rva004B555F();
private:
	char m_pad[4];
	unsigned char *m_entry; // +4
};

const AsciiString &Rva004B555F::rva004B555F()
{
	if (m_entry)
		return ((Rva004CE3B9 *)(m_entry + 8))->rva004CE3B9();
	return AsciiString::TheEmptyString;
}
