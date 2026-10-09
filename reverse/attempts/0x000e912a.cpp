// ?rva000E912A@W3DShrubBuffer@@QAEXPBURva000E912APoint@@MH@Z
// partial score=0.8 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// W3DShrubBuffer method at retail 0x000E912A (164 bytes, ret 0xC): runs the keyed shrub removal 0x000E90DB with a
// mode for every shrub record whose position lies within a radius of a point. BFME2 layout: 2000 records of 0xA0
// at +0x1958 (type +0x40, key +0x58), count +0x4FB58. The cursor walks the records 8 bytes in, as the sibling row
// reset 0x000E70D9 does.
typedef int Int;
typedef float Real;

struct Rva000E912APoint
{
	Real x;
	Real y;
	Real z;

	void set(Real newX, Real newY, Real newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	void sub(const Rva000E912APoint *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real lengthSqr(void) const
	{
		return x*x + y*y + z*z;
	}
};

class W3DShrubBuffer
{
public:
	void rva000E912A(const Rva000E912APoint *center, Real radius, Int mode);
	bool rva000E90DB(unsigned int key, Int mode);

private:
	char m_pad[0x4FB58];
	Int m_count;
};

void W3DShrubBuffer::rva000E912A(const Rva000E912APoint *center, Real radius, Int mode)
{
	Int i = 0;
	if (m_count > 0)
	{
		char *row = (char *)this + 0x1960;
		do
		{
			if (*(Int *)(row + 0x38) >= 0)
			{
				Rva000E912APoint delta;
				delta.set(*(Real *)(row - 8), *(Real *)(row - 4), *(Real *)row);
				delta.sub(center);
				if (radius * radius > delta.lengthSqr())
					rva000E90DB(*(unsigned int *)(row + 0x50), mode);
			}
			++i;
			row += 0xA0;
		} while (i < m_count);
	}
}
