// ?rva0053446D@Rva0053446D@@QAEPAHPAH@Z
// partial score=0.93 date=2026-10-07
// ?rva0053446D@Rva0053446D@@QAEPAHPAH@Z
// partial score=0.9 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
#include <map>

// ?rva0053446D@Rva0053446D@@QAEPAHPAH@Z @0x0053446D 83B
// Target evidence: converts the two-int input through 0x0053442A, searches the map at +0x04
// through rowed 0x00357180, then searches the mapped value at +0x14 and returns its value address.
// Structural inference: the outer map value is an inline tree header; owner identity remains address-derived.
void __cdecl Rva0053442ADiv(int *out, int *in);

class Rva0053446D
{
public:
	int *rva0053446D(int *coordinates);

private:
	char m_pad00[4];
	_STL::map<int, void *> m_map04;
};

int *Rva0053446D::rva0053446D(int *coordinates)
{
	struct Tile
	{
		int x;
		int y;
	} tile;
	Rva0053442ADiv((int *)&tile, coordinates);

	*(int *)(void *)&coordinates = tile.x;
	_STL::map<int, void *>::iterator outer = m_map04.find(*(int *)(void *)&coordinates);
	switch (outer == m_map04.end()) {
	case false:
	{
		int y = tile.y;
		_STL::map<int, void *> &inner = *(_STL::map<int, void *> *)&outer->second;
		*(int *)(void *)&coordinates = y;
		_STL::map<int, void *>::iterator value = inner.find(*(int *)(void *)&coordinates);
		if (value != inner.end())
			return (int *)value->second;
		break;
	}
	default:
		break;
	}
	return (int *)-1;
}
