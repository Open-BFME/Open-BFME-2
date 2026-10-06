// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?Rva0033FA79Do@@YAXPBVObject0033FA79@@@Z, retail 0x0033FA79, 21 bytes.
// Calls AIUpdateInterface slot 142 (offset 0x238) with 0 through the
// Object+0x258 pointer. Twin of 0x0033FA64 (slot142 with 5); same
// BfmeVirtualSlots precedent. Callers 0x0034A117/0x0034C0AA/0x0034C0C6.
// Identity stays honest Rva free-function name.

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

class Object0033FA79
{
public:
	char m_pad00[0x258];
	AIUpdateInterface *m_258;
};

void Rva0033FA79Do(const Object0033FA79 *obj)
{
	obj->m_258->slot142(0);
}
