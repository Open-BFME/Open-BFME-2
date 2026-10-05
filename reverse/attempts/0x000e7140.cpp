// ?rva000E7140@Rva000E7140@@QAE_NHMMMPBX@Z
// partial score=0.92 date=2026-10-05
// ?rva000E7140@Rva000E7140@@QAE_NHMMMPBX@Z
// partial score=0.92 date=2026-10-03
// cl: /O1 /MD /G7 /arch:SSE
// ?rva000E7140@Rva000E7140@@QAE_NHMMMPBX@Z 0x000E7140 371B
// Search 0xA0-byte elems at +0x1958 by ID at +0x58 (count +0x4FB58); on hit
// store 3 floats at +0/+4/+8, copy 0x30B from src at +0x10, copy-construct
// Region2D at +0x48 from second array at +0x4FB80 stride 0x5C indexed by
// m_40, scale region by +0xC and translate by the 3 floats, set dirty.
// Evidence: stride/count/dirty match Rva000E7016/Rva000E73CE neighbours,
// Region2D copy row ??0Region2D@@QAE@ABU0@@Z, caller 0x00068017 same 5-arg shape.

struct Region2D
{
	Region2D(const Region2D &that) throw();
	float x_min;
	float y_min;
	float x_max;
	float y_max;
};

struct SrcBlock
{
	int v0;
	int v1;
	int v2;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	int v10;
	int v11;
};

struct Elem
{
	float m_x;
	float m_y;
	float m_z;
	float m_scale;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	unsigned char m_44;
	unsigned char m_45;
	unsigned char m_46;
	unsigned char _pad47;
	Region2D m_region;
	int m_id;
	int m_rest[17];
};

struct Second
{
	Region2D m_region;
	char _pad[0x5C - 16];
};

inline void *__cdecl operator new(unsigned int, void *p) throw() { return p; }
void __cdecl operator delete(void *, void *) throw() {}

class Rva000E7140
{
public:
	bool rva000E7140(int id, float x, float y, float z, const void *src);
private:
	char _pad0[0x1958];
	Elem m_elems[2000];
	int m_count;
	unsigned char m_dirty;
	char _pad1[0x4FB80 - 0x4FB5D];
	Second m_second[64];
};

// ?rva000E7140@Rva000E7140@@QAE_NHMMMPBX@Z present-unmatched
bool Rva000E7140::rva000E7140(int id, float x, float y, float z, const void *src)
{
	char *base = (char *)this;
	char *pid = base + 0x19B0;
	for (int i = 0; i < m_count; ++i, pid += 0xA0)
	{
		if (*(int *)pid != id)
			continue;
		int off = i * 0xA0;
		char *p = base + off;
		*(float *)(p + 0x1958) = x;
		*(float *)(p + 0x195C) = y;
		*(float *)(p + 0x1960) = z;
		const SrcBlock *b = (const SrcBlock *)src;
		*(int *)(p + 0x1968) = b->v0;
		*(int *)(p + 0x196C) = b->v1;
		*(int *)(p + 0x1970) = b->v2;
		*(int *)(p + 0x1974) = b->v3;
		*(int *)(p + 0x1978) = b->v4;
		*(int *)(p + 0x197C) = b->v5;
		*(int *)(p + 0x1980) = b->v6;
		*(int *)(p + 0x1984) = b->v7;
		*(int *)(p + 0x1988) = b->v8;
		*(int *)(p + 0x198C) = b->v9;
		*(int *)(p + 0x1990) = b->v10;
		*(int *)(p + 0x1994) = b->v11;
		int idx2 = *(int *)(p + 0x1998);
		i += 0x29;
		Region2D *dst = (Region2D *)(base + i * 0xA0);
		Region2D *s = (Region2D *)(base + 0x4FB80 + idx2 * 0x5C);
		dst->Region2D::Region2D(*s);
		float sc = *(float *)(p + 0x1964);
		dst->x_min *= sc;
		dst->y_min *= sc;
		dst->x_max *= sc;
		*(float *)(p + 0x19AC) *= sc;
		dst->x_min += *(float *)(p + 0x1958);
		dst->y_min += *(float *)(p + 0x195C);
		dst->x_max += *(float *)(p + 0x1960);
		m_dirty = 1;
		return true;
	}
	return false;
}
