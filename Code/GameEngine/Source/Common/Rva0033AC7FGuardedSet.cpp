// cl: /O1 /MD
//
// ?rva0033AC7F@Rva0033AC7F@@QAE_NAAV?$StringBase@G@@@Z @0x0033AC7F 35B
// Guarded wide-string getter: returns false when the member at +0x48 is
// empty, else copies it into the out-param via the pinned
// ?set@?$StringBase@G@@QAEXABV1@@Z and returns true. Evidence: rowed
// ?isEmpty@?$StringBase@G@@QBE_NXZ call plus pinned set call, single caller
// at 0x0040681B. Owning class unproven, hence honest Rva names.

template <typename T>
class StringBase
{
public:
	bool isEmpty() const;
	void set(const StringBase &src);

private:
	unsigned char m_storage[8];
};

class AsciiString : public StringBase<char>
{
public:
	// Inline, as retail expands it: StringBase<char>::set (0x000366F0) is called directly, not the
	// out-of-line copy at 0x00001733 the ledger rows ??4AsciiString on (link census, 2026-10-06).
	AsciiString &operator=(const AsciiString &src) { set(src); return *this; }
};

class Rva0033AC7F
{
public:
	bool rva0033AC7F(StringBase<unsigned short> &dst);
	bool rva0033ACA2(StringBase<unsigned short> &dst);
	bool rva0033ACC5(AsciiString &dst);

private:
	unsigned char m_pad[0x48];
	StringBase<unsigned short> m_str;
	StringBase<unsigned short> m_str2;
	unsigned char m_pad58[0x60 - 0x58];
	AsciiString m_asc;
};

bool Rva0033AC7F::rva0033AC7F(StringBase<unsigned short> &dst)
{
	if (!m_str.isEmpty()) {
		dst.set(m_str);
		return true;
	}
	return false;
}

bool Rva0033AC7F::rva0033ACA2(StringBase<unsigned short> &dst)
{
	if (!m_str2.isEmpty()) {
		dst.set(m_str2);
		return true;
	}
	return false;
}

bool Rva0033AC7F::rva0033ACC5(AsciiString &dst)
{
	if (!m_asc.isEmpty()) {
		dst = m_asc;
		return true;
	}
	return false;
}
