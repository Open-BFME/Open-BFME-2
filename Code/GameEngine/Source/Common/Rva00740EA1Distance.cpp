// cl: /MD
// ?Rva00740EA1DistanceSquared@@YAHPBE0@Z, retail 0x00740EA1, 77 bytes.
// Squared distance between two 4-byte vectors via movzx sub imul add.
// Evidence: caller at 0x00741459; no callees; reads 4 bytes each.
typedef unsigned char Byte;
int __cdecl Rva00740EA1DistanceSquared(const Byte *lhs, const Byte *rhs)
{
	int componentDelta0 = (int)rhs[0] - (int)lhs[0];
	int componentDelta1 = (int)rhs[1] - (int)lhs[1];
	int componentDelta2 = (int)rhs[2] - (int)lhs[2];
	int componentDelta3 = (int)rhs[3] - (int)lhs[3];
	return componentDelta0 * componentDelta0 + componentDelta1 * componentDelta1 + componentDelta2 * componentDelta2 + componentDelta3 * componentDelta3;
}
