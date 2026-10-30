// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0Base@@@Z @0x0073BFE0 874B: shroud polygon scanline raster via rowed 0x0073BAA0 updater.
// Target-only (no BFME 1 donor). WB twin 0x017E3E10 gives the structure: function-scope locals
// y kept i left right top, two 16-byte edge structs {value step remaining index} kept in memory,
// an inline edge set(x0 x1 dy) with 8.8 fixed-point step and half-step start, an inline bool
// advance(), (value + 128) / 256 column reads, and y++ passed to the per-row updater.
// Drops repeated vertices, starts at the topmost-leftmost vertex, walks the left chain backwards
// and the right chain forwards; returns 0 when the updater fails, 1 when an edge runs out.
// Index wrap is two inline helpers: as macros, cl's tie-breaks put the edge start sum in the
// wrong register at the set sites. Caller DoShroudReveal 0x0073CAF0; twin 0x0073C450 differs
// only in calling the decrement updater 0x0073BB40.
class Gen_008F7CD0;

class Rva0073BAA0Base
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BAA0(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

struct RasterEdge
{
	int value;
	int step;
	int remaining;
	int index;

	__forceinline void set(int startX, int endX, int dy)
	{
		remaining = dy;
		if (remaining > 0)
		{
			step = ((endX - startX) << 8) / dy;
			value = (startX << 8) + step / 2;
		}
	}
	__forceinline bool advance()
	{
		value += step;
		return --remaining > 0;
	}
	__forceinline int x() const { return (value + 128) / 256; }
};

__forceinline int prevIndex(int i, int vertexCount) { return i ? i - 1 : vertexCount - 1; }
__forceinline int nextIndex(int i, int vertexCount) { return i + 1 == vertexCount ? 0 : i + 1; }

char __cdecl Rva0073BFE0Raster(int *xs, int *ys, int vertexCount, Rva0073BAA0Base updater)
{
	int row;
	int kept = 1;
	int i;
	RasterEdge left;
	RasterEdge right;
	int top;

	for (i = 1; i < vertexCount; ++i)
	{
		if (xs[i] != xs[kept - 1] || ys[i] != ys[kept - 1])
		{
			xs[kept] = xs[i];
			ys[kept] = ys[i];
			++kept;
		}
	}
	vertexCount = kept;
	while (vertexCount > 2 && xs[0] == xs[vertexCount - 1] && ys[0] == ys[vertexCount - 1])
		--vertexCount;
	if (vertexCount < 3)
		return 1;

	top = 0;
	for (i = 1; i < vertexCount; ++i)
	{
		if (ys[i] < ys[top] || (ys[i] == ys[top] && xs[i] < xs[top]))
			top = i;
	}
	row = ys[top];
	left.index = top;
	left.set(xs[left.index], xs[prevIndex(left.index, vertexCount)], ys[prevIndex(left.index, vertexCount)] - ys[left.index]);
	left.index = prevIndex(left.index, vertexCount);
	while (ys[top] == ys[nextIndex(top, vertexCount)])
		top = nextIndex(top, vertexCount);
	right.index = top;
	right.set(xs[right.index], xs[nextIndex(right.index, vertexCount)], ys[nextIndex(right.index, vertexCount)] - ys[right.index]);
	right.index = nextIndex(right.index, vertexCount);

	for (;;)
	{
		if (!updater.rva0073BAA0(left.x(), right.x(), row++))
			return 0;
		if (!left.advance())
		{
			while (left.remaining == 0)
			{
				left.set(xs[left.index], xs[prevIndex(left.index, vertexCount)], ys[prevIndex(left.index, vertexCount)] - ys[left.index]);
				left.index = prevIndex(left.index, vertexCount);
				if (left.remaining < 0)
					return 1;
			}
		}
		if (!right.advance())
		{
			while (right.remaining == 0)
			{
				right.set(xs[right.index], xs[nextIndex(right.index, vertexCount)], ys[nextIndex(right.index, vertexCount)] - ys[right.index]);
				right.index = nextIndex(right.index, vertexCount);
				if (right.remaining < 0)
					return 1;
			}
		}
	}
}
