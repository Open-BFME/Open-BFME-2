// Retail 0x00758CC0 (30 B): true when the +0x08 and +0x0C words of two records
// agree. Open-BFME-1 lands two byte-identical twins of this body
// (Rva009A2F40.cpp: Rva009A2F40::method and Rva009A2F70::method, BFME 1
// 0x009A2F40 / 0x009A2F70, each followed by a 12-byte key getter); game.dat
// holds one copy, so it lands once under a name derived from its own address.
// IDENTITY IS NOT RECOVERED.
class Rva00758CC0
{
public:
 unsigned int m_00, m_04;
 int m_a, m_b; // retail offsets +0x08 and +0x0C
 unsigned char method(const Rva00758CC0 *other);
 unsigned int combineWords() const;
};
unsigned char Rva00758CC0::method(const Rva00758CC0 *other)
{
 if (m_a == other->m_a && m_b == other->m_b) return 1;
 return 0;
}

// BF1 f98983a7 Rva009A2F40.cpp's clean twin getters supply this unsigned
// shift-and-add expression. Native758CE0..758CEC is independently INT3
// bounded after the existing758CC0 comparison; it reads the same measured
// words8/C, shifts word8 left16 then adds the full wordC modulo32bits.
// Retain this reference-pair home/view without claiming a packed coordinate,
// original owner or complete allocation size from its accessed prefix.
unsigned int Rva00758CC0::combineWords() const
{
 return ((unsigned int)m_a << 16) + (unsigned int)m_b;
}
