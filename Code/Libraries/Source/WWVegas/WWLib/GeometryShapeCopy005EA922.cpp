// cl: /O1 /MD
// ??0Rva005EA922@@QAE@ABU0@@Z @0x005EA922 68B copy ctor 8 dwords plus refcounted ptr at +0x20.
// Evidence: called by _Construct 0x005EA9A9 for UGeometryShape; copies 0..0x1C plain then refcounted ptr at +0x20 with inc [ecx+4]; unblocks 0x005EA9A9.

struct Rva005EA922 {
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
	void *m20;
	Rva005EA922(const Rva005EA922 &other);
};

Rva005EA922::Rva005EA922(const Rva005EA922 &other)
	: m00(other.m00),
	  m04(other.m04),
	  m08(other.m08),
	  m0C(other.m0C),
	  m10(other.m10),
	  m14(other.m14),
	  m18(other.m18),
	  m1C(other.m1C),
	  m20(other.m20)
{
	if (m20)
		((int *)m20)[1]++;
}
