// cl: /O1 /DNDEBUG /MD /GX-
// Rva002F592_ParseArmyPlacementPos (retail 0x002F592, 40 bytes). Parses a
// Coord2D through the rowed parseCoord2D at 0x002F558 into a stack temp
// (instance and userData forwarded), then pushes it through the rowed
// vector<BfmeE8>::push_back at 0x00539A2E onto the store. The element is
// spelled BfmeE8 so the push_back reference mangles to the rowed
// instantiation name (opaque-8B-pod precedent); its float x/y members are
// the Coord2D layout parseCoord2D fills. Serves the ArmyPlacementPos entry
// of the Region table at 0x7E4120 (siblings: Region, ConcurrentRegionBonus).
// The callback name stays address-derived; the owning class is BFME2-new
// (no BFME1 donor).

struct BfmeE8
{
	float x;
	float y;
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, typename A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
};
}

class INI
{
public:
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void Rva002F592_ParseArmyPlacementPos(INI *ini, void *instance, void *store, const void *userData);
};

// ?Rva002F592_ParseArmyPlacementPos@INI@@SAXPAV1@PAX1PBX@Z
void INI::Rva002F592_ParseArmyPlacementPos(INI *ini, void *instance, void *store, const void *userData)
{
	BfmeE8 pos;
	INI::parseCoord2D(ini, instance, &pos, userData);
	((_STL::vector<BfmeE8> *)store)->push_back(pos);
}
