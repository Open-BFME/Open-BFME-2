#pragma once
// Target-owned views from native store351570 and reconstruction35164E.
// Field offsets and accessed extents are retail facts; original type names
// and unobserved behavior remain unasserted. BFME1 6c1e0b51 supplies the
// AICommandParmsStorage semantic guide, not target identity proof.
#include "ascii_string.h"

struct BfmeVec12
{
	float x, y, z;
};
class Rva0035149F
{
public:
	BfmeVec12 *m_start;
	BfmeVec12 *m_finish;
	BfmeVec12 *m_end;
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};
class Rva003427DD
{
public:
	char m_data[0x7C];
	Rva003427DD &operator=(const Rva003427DD &src);
};
struct Rva00351570_Has74
{
	char m_pad[0x74];
	int m_74;
};
struct Rva00351570_MidB
{
	char m_pad[0x10];
	AsciiString m_10;
	AsciiString m_14;
};
struct Rva00351570_MidA
{
	char m_pad[0x30];
	Rva00351570_MidB *m_30;
};
