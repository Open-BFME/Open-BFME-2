// ?Rva002DBF66Copy@@YAPAURva002DBF66Rec@@PBU1@0PAU1@@Z
// partial score=0.8 date=2026-10-08
// cl: /Os /MD /EHsc
// ?Rva002DBF66Copy@@YAPAURva002DBF66Rec@@PBU1@0PAU1@@Z @0x002DBF66 71B: cdecl copy of
// 20-byte records. The count is the pointer difference of first and last, and the
// tail of each record (four dwords after the leading word) is copied to dest.
// Returns dest advanced by count records. Address-derived name: the caller and the
// record meaning are not established by this body.
struct Rva002DBF66Quad
{
	int a;
	int b;
	int c;
	int d;
};

struct Rva002DBF66Rec
{
	int w00;
	Rva002DBF66Quad q;
};

Rva002DBF66Rec *Rva002DBF66Copy(const Rva002DBF66Rec *first, const Rva002DBF66Rec *last, Rva002DBF66Rec *dest)
{
	int count = last - first;
	if (count > 0) {
		do {
			dest->q = first->q;
			++first;
			++dest;
		} while (--count);
	}
	return dest;
}
