// cl: /DNDEBUG /MD
//
// ?rva00373EC6@Rva00373EC6@@QBE_NXZ @0x00373EC6 38B:
// Null-checked mask predicate: holder at +0x08 (masks at +0x284), required
// mask at +0x48 plus exempt mask at +0xC8 (128B each) tested through rowed
// ?rva0033A453@Rva0033A453@@QBE_NPBX0@Z at 0x0033A453.
// Caller at 0x0028F4D1 iterates Object+0x4B4 list and returns first element
// whose predicate is true; landing unblocks 0x0028F4BC.
class Rva0033A453
{
public:
	bool rva0033A453(const void *required, const void *exempt) const;
};

struct Rva00373EC6Holder
{
	char m_pad[0x284];
	Rva0033A453 m_masks;
};

class Rva00373EC6
{
public:
	bool rva00373EC6() const;
private:
	char m_pad0[8];
	Rva00373EC6Holder *m_holder; // +0x08
	char m_pad1[0x48 - 0x0C];
	char m_required[0x80]; // +0x48
	char m_exempt[0x80]; // +0xC8
};

bool Rva00373EC6::rva00373EC6() const
{
	if (m_holder == 0)
		return false;
	if (m_holder->m_masks.rva0033A453(m_required, m_exempt))
		return true;
	return false;
}
