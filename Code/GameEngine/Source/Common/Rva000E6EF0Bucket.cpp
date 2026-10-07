// cl: /MD
// ?getPartitionBucket@W3DShrubBuffer@@QAEHPBUFloatPair@@@Z, retail 0x000E6EF0, 216 bytes.
// Clamp world XY to +0x1948/+0x194C min and +0x1950/+0x1954 max, scale each
// axis by 49.9f over its extent, floor via IAT floor and return y*50+x.
// Evidence: retail movss/comiss clamp plus fld/fsub/fdivr/fmul floor/fistp
// pair plus imul 0x32; BFME1 donor Rva001A3060::getBucket uses 49.9f for a
// 50-by-50 grid; neighbours in same Common dir. Caller 0x000E92CD.
// FloatToLong is WWMath::Float_To_Long's fld/fistp inline asm, as the
// matched Bfme5CeilCellExtent.cpp helper writes it.
// Structural inference: each scaled axis is its own float local before the
// floor call, which pops the argument before the fstp as retail does.
extern "C" __declspec(dllimport) double __cdecl floor(double);

__forceinline long FloatToLong(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

struct FloatPair
{
	float x;
	float y;
};

// Retail record accesses: key +0x58, guard +0x84, unsigned state +0x90.
// The 0xA0 stride and 2000 entries place the count at receiver +0x4FB58.
struct ShrubRecord
{
	unsigned char pad00[0x58];
	unsigned key;
	unsigned char pad5C[0x28];
	unsigned guard;
	unsigned char pad88[8];
	unsigned state;
	unsigned char pad94[0x0C];
};

class W3DShrubBuffer
{
public:
	int getPartitionBucket(FloatPair const *p);
	bool rva000E90DB(unsigned key, int mode);
	void rva000E8C2D(int index, int mode);
	unsigned char m_pad0[0x1948];
	float m_minX;
	float m_minY;
	float m_maxX;
	float m_maxY;
	ShrubRecord m_records[2000];
	int m_count;
};

int W3DShrubBuffer::getPartitionBucket(FloatPair const *p)
{
	float x = p->x;
	float y = p->y;
	if (m_minX > x)
		x = m_minX;
	if (m_minY > y)
		y = m_minY;
	if (x > m_maxX)
		x = m_maxX;
	if (y > m_maxY)
		y = m_maxY;
	float sx = x / (m_maxX - m_minX) * 49.9f;
	int ix = FloatToLong((float)floor(sx));
	float sy = y / (m_maxY - m_minY) * 49.9f;
	int iy = FloatToLong((float)floor(sy));
	return iy * 50 + ix;
}

// ?rva000E90DB@W3DShrubBuffer@@QAE_NIH@Z retail 0x000E90DB, 79 bytes.
// Target evidence: native lookup passes the same ECX and index/mode to
// 0x000E8C2D, whose entry reads count +0x4FB58 and whose exit is ret 8.
// Bucket caller 0x000E92CD uses this same count and 0xA0 record stride;
// destructor 0x000E9BAC uses the adjacent +0x4FB60/+0x4FB70 members.
// Its retail vtable 0x007CECB8 names W3DShrubBuffer through 0x000E9C0F.
// The original lookup/update method names and unused record fields remain
// unknown; the member layout here is a structural reconstruction.
bool W3DShrubBuffer::rva000E90DB(unsigned key, int mode)
{
	if (!key)
		return false;
	for (int index = 0; index < m_count; ++index)
	{
		if (m_records[index].key == key && m_records[index].state <= 0 && m_records[index].guard == 0)
		{
			rva000E8C2D(index, mode);
			return true;
		}
	}
	return false;
}
