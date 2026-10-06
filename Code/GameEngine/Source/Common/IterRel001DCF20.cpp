// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/IterRel001DCF20.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?iterRel001DCF20@@YAXPAVObject@@PAX@Z 0x002612AC (26B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Gen_001DCF50::canEnter supplies the context and invokes this callback.
enum Relationship
{
	Relationship_Zero = 0
};

class Object
{
public:
	Relationship getRelationship(const Object *other) const;
};

struct IterUser001DCF20
{
	Object *object;
	unsigned char flag;
};

void iterRel001DCF20(Object *contained, void *userData)
{
	IterUser001DCF20 *context = (IterUser001DCF20 *)userData;
	if (context->object->getRelationship(contained) == 0)
		context->flag = 1;
}
