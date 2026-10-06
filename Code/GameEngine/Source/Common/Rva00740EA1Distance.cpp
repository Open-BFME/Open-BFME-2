// cl: /MD
// ?Rva00740EA1DistanceSquared@@YAHPBE0@Z, retail 0x00740EA1, 77 bytes.
// Squared distance between two 4-byte vectors via movzx sub imul add.
// Evidence: caller at 0x00741459; no callees; reads 4 bytes each.
typedef unsigned char Byte;
int __cdecl Rva00740EA1DistanceSquared(const Byte *a, const Byte *b)
{
	int d0 = (int)b[0] - (int)a[0];
	int d1 = (int)b[1] - (int)a[1];
	int d2 = (int)b[2] - (int)a[2];
	int d3 = (int)b[3] - (int)a[3];
	return d0 * d0 + d1 * d1 + d2 * d2 + d3 * d3;
}
