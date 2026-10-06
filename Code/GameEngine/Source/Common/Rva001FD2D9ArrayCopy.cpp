// cl: /MD
// ?rva001FD2D9@Rva001FD2D9@@QAEPAUCoord3D@@PAU2@H@Z @0x001FD2D9 66B.
// Bounds-checked copy of Coord3D from array at +0x70 (10 entries stride 12)
// to dest; zeroes dest via SSE when index out of range 0-9; returns dest.
// Evidence: unlock lane caller at 0x00241EFD in 0x00241C75; both retail paths
// leave dest in EAX so return type is Coord3D* per shape-lever row 31.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Rva001FD2D9
{
public:
	Coord3D *rva001FD2D9(Coord3D *dest, int index);

private:
	unsigned char m_pad00[0x70];
	Coord3D m_arr70[10];
};

Coord3D *Rva001FD2D9::rva001FD2D9(Coord3D *dest, int index)
{
	if (index < 0 || index >= 10) {
		dest->x = 0.0f;
		dest->y = 0.0f;
		dest->z = 0.0f;
		return dest;
	}
	Coord3D *src = &m_arr70[index];
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
	return dest;
}
