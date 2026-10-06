// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ??0Rva000E9280@@QAE@XZ
// retail 0x002B598E, 17 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/R2SmallMemberOps.cpp (reference/open-bfme-1 @
// 6d943426). Byte-identical to retail once relocations are masked (unique hit
// on unclaimed .text). Only the placed body is defined here; the donor's other
// 41 definitions are omitted.
//
// IDENTITY IS NOT RECOVERED.  Class and member names are derived from an
// address; the donor carries no type information beyond the field widths its
// bytes force. The ctor zeroes two ints and stores 3 in a third, so the class
// is three consecutive dwords as written here.
class Rva000E9280
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	Rva000E9280();
};
Rva000E9280::Rva000E9280() { m_at00 = 0; m_at04 = 0; m_at08 = 3; }