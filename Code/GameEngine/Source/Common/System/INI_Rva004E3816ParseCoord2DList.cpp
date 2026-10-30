// cl: /DNDEBUG /MD /GX- /D_STLP_USE_STATIC_LIB
// stlport
// ?Rva004E3816Parse@INI@@SAXPAV1@PAX1PBX@Z @0x004E3816 39B: INI list-parse
// twin of INI_Rva002F592ParseArmyPlacementPos (0x002F592, 40B) in the same
// dir with identical flags and callees (rowed parseCoord2D at 0x002F558,
// rowed vector<BfmeE8>::push_back at 0x00539A2E). Parses a Coord2D through
// parseCoord2D into a stack temp, then push_backs onto the store vector.
// Differs by 1B (push 0 for userData vs push [ebp+0x14]): this body drops
// the outer userData and forwards NULL. Element spelled BfmeE8 so push_back
// mangles to the rowed name. No callers, no vtable; honest Rva name.
struct BfmeE8
{
	float x;
	float y;
};

#include <vector>

namespace _STL
{
// Bind the append to the rowed worker.
template <> void vector<BfmeE8, allocator<BfmeE8> >::push_back(const BfmeE8 &value);
}

class INI
{
public:
	static void parseCoord2D(INI *ini, void *instance, void *store, const void *userData);
	static void Rva004E3816Parse(INI *ini, void *instance, void *store, const void *userData);
};

void INI::Rva004E3816Parse(INI *ini, void *instance, void *store, const void *)
{
	BfmeE8 pos;
	INI::parseCoord2D(ini, instance, &pos, 0);
	((_STL::vector<BfmeE8> *)store)->push_back(pos);
}
