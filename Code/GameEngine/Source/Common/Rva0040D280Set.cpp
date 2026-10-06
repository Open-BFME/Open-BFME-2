// cl: /MD
// ?Rva0040D280Set@@YGXPAVObject@@H@Z @0x0040D280 67B.
// Free __stdcall (ret 8) taking Object plus int. Looks up BfmeY1038 via
// rowed-pin bfmeFind1038, derives int via rowed Rva0040C985::rva0040CA24,
// gets Drawable via rowed Thing::getDrawable and when non-null stores via
// rowed Object::setCustomIndicatorColor plus Object::rva0028BAAE.
// Evidence: callees all rowed or pinned; caller jmp at 0x0023D0C8 and call
// at 0x002411F4 in 0x0024104A; neighbours 0x0040D251 and 0x0040D487 share page.
class Drawable;
class Thing
{
public:
	Drawable *getDrawable() const;
};
class BfmeY1038;
BfmeY1038 *__stdcall bfmeFind1038(int v);
class Rva0040C985
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
void __stdcall Rva0040D280Set(Object *obj, int val)
{
	if (obj == 0)
		return;
	BfmeY1038 *y = bfmeFind1038(val);
	if (y == 0)
		return;
	int v = ((Rva0040C985 *)y)->rva0040CA24();
	Drawable *d = obj->getDrawable();
	if (d == 0)
		return;
	obj->setCustomIndicatorColor(v);
	obj->rva0028BAAE(val);
}
