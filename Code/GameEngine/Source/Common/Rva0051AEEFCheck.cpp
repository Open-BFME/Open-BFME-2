// cl: /O1
// ?rva0051AEEF@Rva0051AEEF@@QBE_NXZ @ 0x0051AEEF, 20 bytes.
// Two-byte-flag predicate: xor eax,eax; cmp [ecx+0xB4],al; je; cmp
// [ecx+0xB6],al; je; inc eax; ret. Evidence: single caller at 0x0051B450 in
// the 398B body at 0x0051B369; neighbours are tiny getters/setters sharing
// frameless shapes; owner and meaning unproven so names are address-derived.
class Rva0051AEEF
{
public:
	bool rva0051AEEF() const;
private:
	char m_pad[0xB4];
	bool m_b4;
	char m_padB5;
	bool m_b6;
};

bool Rva0051AEEF::rva0051AEEF() const
{
	return m_b4 && m_b6;
}
