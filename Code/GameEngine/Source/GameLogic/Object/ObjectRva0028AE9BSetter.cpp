// cl: /DNDEBUG /MD
//
// ?rva0028AE9B@Object@@QAEXH@Z @0x0028AE9B 23B
// Null-checked dword setter through the pointer at Object+0x84 into
// +0x360 of the pointed-to struct. The +0x360 int is the same offset the
// rowed ObjectRvaSmallGetters TU carries as m_mask360 and the +0x84 slot
// sits beside the rowed +0xA4/+0x240 sub-pointers. Three raw callers.
// Identity beyond those offsets is unproven so the name stays
// address-derived. Flags from the next rowed Object sibling
// (ObjectGetCurrentWeapon.cpp /O1 /DNDEBUG /MD); /O1 selects the retail
// mov-test-je plus mov-mov shape.

struct Rva0028AE9BSub
{
	char m_pad[0x360];
	int m_value; // +0x360
};

class Object
{
public:
	void rva0028AE9B(int value);

private:
	unsigned char m_pad00[0x84];
	Rva0028AE9BSub *m_sub84; // +0x84
};

void Object::rva0028AE9B(int value)
{
	Rva0028AE9BSub *sub = m_sub84;
	if (sub != 0)
		sub->m_value = value;
}
