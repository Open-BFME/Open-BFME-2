// ?rva002EB7B4@Pathfinder@@QAEHPAH0HHPAVRva002E9D09@@@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva002EB7B4@Pathfinder@@QAEHPAH0HHPAVRva002E9D09@@@Z retail
// 0x002EB7B4..0x002EBA88 (724 bytes thiscall ret 0x14). One instantiation
// of BFME 2's Pathfinder::ProcessConvexPoly (WorldBuilder twin 0xD70A30
// from gamelogic/pathfinder/pathfinder.inl with its numEdges < 3 assert at
// line 479) for the Rva002E9D09 visitor; callers 0x002EEDBA / 0x002EEF0B
// in the rectangle walk 0x002EED80. It drops repeated vertices (and a
// closing copy of the first) from the cell-space polygon (xs ys numEdges)
// and returns -1 under three edges; otherwise it scan-converts it from the
// top-most (then left-most) vertex down to the largest y with two 8.8
// fixed-point edge steppers (Rva002E6CFE init 0x002E6CFE; the inline step
// 0x002E6D2F and the wrap helpers 0x002E6D42 / 0x002E6D54 are expanded as
// in retail) walking the previous (left) and next (right) vertices. Each
// cell of a span that getCell 0x002E6D62 finds in the layer goes to the
// visitor (0x002E9D09); its first non-zero answer is returned, else 0.
// Visitor and instantiation names are not recovered.

typedef int Int;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object;
class PathfindCell;

class Rva002E9D09
{
public:
	Int rva002E9D09(Object *cell, Int cellX, Int cellY);
};

// The 8.8 fixed-point edge stepper.
class Rva002E6CFE
{
public:
	void rva002E6CFE(int a, int b, int c);
	bool step()
	{
		m_cur += m_step;
		return --m_count > 0;
	}

	int m_cur; // +0x00
	int m_step; // +0x04
	int m_count; // +0x08
};

class Pathfinder
{
public:
	Int rva002EB7B4(Int *xs, Int *ys, Int numEdges, Int layer, Rva002E9D09 *visitor);
	PathfindCell *getCell(PathfindLayerEnum layer, Int cellX, Int cellY);

	static Int nextIndex(Int i, Int numEdges)
	{
		Int next = i + 1;
		return (next == numEdges) ? 0 : next;
	}
	static Int prevIndex(Int i, Int numEdges)
	{
		if (i != 0)
			return i - 1;
		return numEdges - 1;
	}
};

Int Pathfinder::rva002EB7B4(Int *xs, Int *ys, Int numEdges, Int layer, Rva002E9D09 *visitor)
{
	Int y;
	Int j;
	Int maxY;
	Int i;
	Int left;
	Rva002E6CFE leftEdge;
	Int right;
	Rva002E6CFE rightEdge;
	Int top;
	Int xr;
	Int xl;
	PathfindCell *cell;
	Int result;

	j = 1;
	for (i = 1; i < numEdges; i++)
	{
		if (xs[i] != xs[j - 1] || ys[i] != ys[j - 1])
		{
			xs[j] = xs[i];
			ys[j] = ys[i];
			j++;
		}
	}
	numEdges = j;
	while (numEdges > 2 && xs[0] == xs[numEdges - 1] && ys[0] == ys[numEdges - 1])
		numEdges--;
	if (numEdges < 3)
		return -1;

	top = 0;
	maxY = 0;
	for (i = 1; i < numEdges; i++)
	{
		if (ys[i] < ys[top] || (ys[i] == ys[top] && xs[i] < xs[top]))
			top = i;
		if (ys[i] > maxY)
			maxY = ys[i];
	}

	y = ys[top];
	left = top;
	leftEdge.rva002E6CFE(xs[left], xs[prevIndex(left, numEdges)], ys[prevIndex(left, numEdges)] - ys[left]);
	left = prevIndex(left, numEdges);

	while (ys[top] == ys[nextIndex(top, numEdges)])
		top = nextIndex(top, numEdges);
	right = top;
	rightEdge.rva002E6CFE(xs[right], xs[nextIndex(right, numEdges)], ys[nextIndex(right, numEdges)] - ys[right]);
	right = nextIndex(right, numEdges);

	while (y <= maxY)
	{
		xl = (leftEdge.m_cur + 0x80) / 256;
		xr = (rightEdge.m_cur + 0x80) / 256;
		while (xl <= xr)
		{
			cell = getCell((PathfindLayerEnum)layer, xl, y);
			xl++;
			if (!cell)
				continue;
			result = visitor->rva002E9D09(reinterpret_cast<Object *>(cell), xl - 1, y);
			if (result)
				return result;
		}
		y++;
		if (!leftEdge.step())
		{
			while (leftEdge.m_count == 0)
			{
				Int dy = ys[prevIndex(left, numEdges)] - ys[left];
				if (dy < 0)
					break;
				leftEdge.rva002E6CFE(xs[left], xs[prevIndex(left, numEdges)], dy);
				left = prevIndex(left, numEdges);
			}
		}
		if (!rightEdge.step())
		{
			while (rightEdge.m_count == 0)
			{
				Int dy = ys[nextIndex(right, numEdges)] - ys[right];
				if (dy < 0)
					break;
				rightEdge.rva002E6CFE(xs[right], xs[nextIndex(right, numEdges)], dy);
				right = nextIndex(right, numEdges);
				if (rightEdge.m_count < 0)
					return 0;
			}
		}
	}
	return 0;
}
