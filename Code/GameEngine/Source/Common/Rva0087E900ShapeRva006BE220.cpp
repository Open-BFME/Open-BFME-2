// cl: /Ob2 /DNDEBUG /MD /EHs-c-
//
// ?rva006BE220@Rva0087E900Shape@@QAEXPBURva0087E900Coord@@MPAU2@@Z, retail 0x006be220, 50 bytes. Banked partial (score 0.99) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
struct Rva0087E900Coord { float x; float y; float z; };
struct Rva0087E900Shape { char pad[0x10]; Rva0087E900Coord m_field0x10; void rva006BE220(const Rva0087E900Coord *position, float angle, Rva0087E900Coord *dest); };
Rva0087E900Coord *Rva0087E900(Rva0087E900Coord *out, const Rva0087E900Coord *position, const Rva0087E900Shape *shape, float angle);
void Rva0087E900Shape::rva006BE220(const Rva0087E900Coord *position, float angle, Rva0087E900Coord *dest)
{
	Rva0087E900Coord tmp;
	Rva0087E900Coord *p = Rva0087E900(&tmp, position, this, angle);
	*dest = *p;
}
