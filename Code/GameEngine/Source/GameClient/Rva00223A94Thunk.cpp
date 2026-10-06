// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00223A94@Rva00223A94@@QAEHPBVAsciiString@@@Z @0x00223A94 11B
// Tail-jmp thunk into rowed erase-all 0x00223429: add ecx 0x90 then jmp.
// The table lives at +0x90 of an otherwise unknown owner, so the owner is
// an honest address class. Returns erase count. Callers include 0x002D3B71.
#include "ascii_string.h"

class Rva000427195
{
public:
	int rva00223429(const AsciiString *key);
};

class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);

	char m_pad[0x90];
	Rva000427195 m_table;
};

int Rva00223A94::rva00223A94(const AsciiString *key)
{
	return m_table.rva00223429(key);
}
