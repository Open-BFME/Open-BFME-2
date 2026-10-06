// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva0033FA64Do@@YAXPBVObject0033FA64@@@Z, retail 0x0033FA64, 21 bytes.
// Calls AIUpdateInterface slot 142 (offset 0x238) with 5 through the
// Object+0x258 pointer. Prev/next show Object+0x258 holds the
// AIUpdateInterface (AIGroupGroupAttackArea precedent) and slot 142 is the
// AIUpdateInterface tail slot (rva00262804 precedent via BfmeVirtualSlots).
// Callers 0x0034F004/0x003500E6 pass the +0x14/+0x18 object. Identity stays
// honest Rva free-function name.

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<142>
{
public:
	virtual void slot142(int);
};

class Object0033FA64
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

void Rva0033FA64Do(const Object0033FA64 *obj)
{
	obj->m_258->slot142(5);
}
