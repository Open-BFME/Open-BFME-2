// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00407AE6@Rva004076EE@@QAEXW4ModelConditionFlagType@@I@Z, retail 0x00407AE6 (19 bytes).
// Leaf method on the Rva004076EE holder (ObjectID at +4): fetch the Object
// via the rowed rva004076EE at 0x004076EE (same this, ecx flows through),
// return when null, otherwise tail-jump to the rowed
// Object::setSpecialModelConditionState at 0x0028AEB2 with the incoming
// (ModelConditionFlagType, unsigned int) args (ret 8). Callees all rowed;
// caller at 0x004087CF passes two stack args.

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

class Object
{
public:
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
};

class Rva004076EE
{
public:
	Object *rva004076EE();
	void rva00407AE6(ModelConditionFlagType mc, unsigned int frames);
};

void Rva004076EE::rva00407AE6(ModelConditionFlagType mc, unsigned int frames)
{
	Object *obj = rva004076EE();
	if (!obj)
		return;
	obj->setSpecialModelConditionState(mc, frames);
}
