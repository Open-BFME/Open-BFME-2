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
	Bool rva00403448(Int attribute, Real *value, Int arg, Int arg2);
};

class Object
{
public:
	Bool rva0028C149(Int attribute, Real *value, Int arg);
	Bool rva0028C15E(Int attribute, Real *value, Int arg, Int arg2);

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

// ?rva0028C15E@Object@@QAE_NHPAMHH@Z @ 0x0028C15E (21B). Four-argument
// twin of the query above (ret 0x10): false without a pool, otherwise
// tail-jumps to 0x00403448, the pool's multiplicative sibling of
// 0x00403382 (seeds *value with a constant, multiplies matching modifiers
// and forwards its fourth argument where 0x00403382 pushes literal 1).
Bool Object::rva0028C15E(Int attribute, Real *value, Int arg, Int arg2)
{
	AttributeModifierPoolUpdate *pool = findAttributeModifierPoolUpdate();
	if (!pool)
		return false;
	return pool->rva00403448(attribute, value, arg, arg2);
}
