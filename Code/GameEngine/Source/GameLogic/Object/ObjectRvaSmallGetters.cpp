// cl: /O1
//
// Three small Object readers (retail 0x0028AD6C/16 + 0x0028ADE0/11 +
// 0x0028ADF7/28). /O1 selects the retail size idioms throughout: jne plus
// inc-from-known-zero for the null-or-one reader, xor-first cmp-mem-reg for
// the flag test, and hoisted xor plus inc for the bit-test's 1<<slot.

struct Rva0028AD6CSub
{
	char m_pad[0x28];				// +0x000..+0x028 unknown
	int m_value;					// +0x028
};

class Object
{
	char m_pad0[0xA4];				// +0x000..+0x0A4 unknown
	Rva0028AD6CSub *m_sub;			// +0x0A4
	char m_pad1[0x358 - 0xA4 - 4];	// +0x0A8..+0x358 unknown
	int m_flag358;					// +0x358
	int m_pad358;					// +0x35C unknown
	int m_mask360;					// +0x360

public:
	int rva0028AD6C() const;
	bool rva0028ADE0() const;
	int rva0028ADF7(int slot) const;
};

// ?rva0028AD6C@Object@@QBEHXZ
int Object::rva0028AD6C() const
{
	const Rva0028AD6CSub *sub = m_sub;
	if (sub == 0)
		return 1;
	return sub->m_value;
}

// ?rva0028ADE0@Object@@QBE_NXZ
// ?rva0028ADE0@Object@@QBE_NXZ present-unmatched
bool Object::rva0028ADE0() const
{
	return m_flag358 != 0;
}

// ?rva0028ADF7@Object@@QBEHH@Z
// ?rva0028ADF7@Object@@QBEHH@Z present-unmatched
int Object::rva0028ADF7(int slot) const
{
	return (m_mask360 & (1 << slot)) != 0 ? 1 : 0;
}
