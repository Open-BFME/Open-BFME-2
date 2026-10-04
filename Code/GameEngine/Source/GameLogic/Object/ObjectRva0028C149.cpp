// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva0028C149@Object@@QAE_NHPAMH@Z @ 0x0028C149 (21B).
// Object attribute query through the pool: returns false when the
// rowed findAttributeModifierPoolUpdate 0x0028BDD7 finds no pool,
// otherwise tail-jumps to the pinned AttributeModifierPoolUpdate
// 0x00403382 with the same (int, float*, int) args. Evidence: LINK body
// (1 file waits); callers at 0x001D91C9, 0x002A74E3, 0x002C9904 and 9 more
// pass three stack args (ret 0xC); neighbours share /O1 /DNDEBUG /MD /EHsc.

typedef float Real;
typedef bool Bool;
typedef int Int;

class AttributeModifierPoolUpdate
{
public:
	Bool rva00403382(Int attribute, Real *value, Int arg);
};

class Object
{
public:
	Bool rva0028C149(Int attribute, Real *value, Int arg);

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate() const;
};

Bool Object::rva0028C149(Int attribute, Real *value, Int arg)
{
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (!pool)
		return false;
	return pool->rva00403382(attribute, value, arg);
}
