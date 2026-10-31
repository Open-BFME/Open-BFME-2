// cl: /MD
// ?rva0040D280@ArmySummarySystem@@QAEXPAVObject@@H@Z @0x0040D280 67B.
// ArmySummarySystem member (ret 8) taking Object plus int: PlaceLivingWorld-
// ObjectsForPlayer calls it at 0x002411F4 with ECX = TheGameLogic + 0x184, and
// forwarder 0x0023D0C2 adds the same 0x184. Looks up BfmeY1038 via the army
// lookup 0x0040D008 on its own this, derives int via rowed ArmySummary::rva0040CA24,
// gets Drawable via rowed Thing::getDrawable and when non-null stores via
// rowed Object::setCustomIndicatorColor plus Object::rva0028BAAE.
// Evidence: callees all rowed or pinned; caller jmp at 0x0023D0C8 and call
// at 0x002411F4 in 0x0024104A; neighbours 0x0040D251 and 0x0040D487 share page.
class Drawable;
#include "Thing/thing.h"
class BfmeY1038;
class ArmySummary
{
public:
	int rva0040CA24();
};
class Object : public Thing
{
public:
	void setCustomIndicatorColor(int v);
	void rva0028BAAE(int v);
};
class ArmySummarySystem
{
public:
	void *rva0040D008(int id);
	void rva0040D280(Object *obj, int val);
};
void ArmySummarySystem::rva0040D280(Object *obj, int val)
{
	if (obj == 0)
		return;
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(val);
	if (y == 0)
		return;
	int v = ((ArmySummary *)y)->rva0040CA24();
	Drawable *drawable = obj->getDrawable();
	if (drawable == 0)
		return;
	obj->setCustomIndicatorColor(v);
	obj->rva0028BAAE(val);
}
