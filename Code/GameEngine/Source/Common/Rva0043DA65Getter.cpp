// cl: /DNDEBUG /MD
// ?rva0043DA65@Rva0043DA65@@QAEHXZ @0x0043DA65 24B
// Validated int-field getter: pushes m_field8 through virtual slot 1
// (bool return, test al), clears to 0 when validation fails, returns it.
// Evidence: callers 0x0043DF22/0x0043E132 load member+0x5C as this then use
// return as GameInfo* for getSlot; 48 waiting callers; neighbours
// GlobalGetterSingles/DispByteOneSetters.

class Rva0043DA65
{
public:
	int rva0043DA65();

private:
	virtual void slot0();
	virtual bool validate(int value);
	int m_unk4;
	int m_value;
};

int Rva0043DA65::rva0043DA65()
{
	if (!validate(m_value))
		m_value = 0;
	return m_value;
}
