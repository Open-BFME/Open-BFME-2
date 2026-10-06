// cl: /MD /EHsc
//
// ?Rva00248CBF@BfmeNetAddress@@QBE_NPBU1@@Z, retail 0x00248CBF, 30 bytes.
// Const 6-byte key equality (dword +0 word +4), 1 if equal else 0.
// Evidence: pinned name plus cmp jne twice plus xor inc plus ret 4,
// 39 callers plus donor-adjacent 0x00248CDD twin.

struct BfmeNetAddress
{
	bool Rva00248CBF(const BfmeNetAddress *other) const;

	unsigned int m_key0;
	unsigned short m_key4;
};

bool BfmeNetAddress::Rva00248CBF(const BfmeNetAddress *other) const
{
	return m_key0 == other->m_key0 && m_key4 == other->m_key4;
}
