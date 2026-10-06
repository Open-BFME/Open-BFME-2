// ?rva00575C5D@Rva00575C5D@@QAE_NPBHH@Z
// partial score=0.98 date=2026-10-07
struct Rva00575C5DPoint
{
	int x;
	int y;
};
class Rva005757A5Call
{
public:
	void rva005757A5(void *point);
};
class Rva00575C5D
{
public:
	bool rva00575C5D(const int *bounds, int unused);
};

// ?rva00575C5D@Rva00575C5D@@QAE_NPBHH@Z present-unmatched
// Target evidence: validates two signed endpoint deltas, builds an 8-byte
// point from the lower coordinates, calls 0x005757A5 on this, then reports
// whether the pointer at this+0x28 changed. Field meanings remain inferred.
bool Rva00575C5D::rva00575C5D(const int *bounds, int unused)
{
	int width = bounds[2] - bounds[0];
	if (width <= 0) {
		int height = bounds[3] - bounds[1];
		if (height <= 0) {
			void *old = *(void **)((char *)this + 0x28);
			Rva00575C5DPoint point;
			point.x = bounds[0];
			point.y = bounds[1];
			((Rva005757A5Call *)this)->rva005757A5(&point);
			return (*(void **)((char *)this + 0x28) != old) ? 1 : 0;
		}
	}
	return 0;
}
