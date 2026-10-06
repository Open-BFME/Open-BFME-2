// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameClient/GUI/Rva00788A00Assign.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00788A00Assign@@YAXPAVRva007882F0PointerMap@@II@Z 0x000AB469 (28B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
struct Rva007882F0Value { unsigned value; };
class Rva007882F0PointerMap
{
public:
	Rva007882F0Value *lookup(unsigned key);
};

// ?Rva00788A00Assign@@YAXPAVRva007882F0PointerMap@@II@Z
void Rva00788A00Assign(Rva007882F0PointerMap *owner, unsigned key, unsigned value)
{
	if (owner) {
		Rva007882F0Value *entry = owner->lookup(key);
		if (entry) entry->value = value;
	}
}
