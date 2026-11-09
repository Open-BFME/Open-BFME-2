// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Delete_This@RefCountClass@@UAEXXZ, retail 0x0006ce57, 20 bytes: the canonical header's COMDAT, slot 0 of every
// RefCountClass-derived table. This unit compiles it alone, called outright so that no table comes with it.
#include "../../../Libraries/Source/WWVegas/WWLib/RefCountData.h"

#pragma inline_depth(0)

// ?<EmitRefCountClassDeleteThis> absent-from-retail
void EmitRefCountClassDeleteThis(RefCountClass *object)
{
	object->RefCountClass::Delete_This();
}
