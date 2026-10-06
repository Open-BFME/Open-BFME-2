// cl: /EHsc
// ?rva00237E28@Rva00237E28@@QAEXPAV1@@Z 0x00237E28 29B
// Evidence: leaf unlock body, 16B this->dest copy, ret 4; neighbours Rva00237E1F (same flags) and Vector4::Set.

class Rva00237E28
{
public:
	void rva00237E28(Rva00237E28 *dest);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
};

void Rva00237E28::rva00237E28(Rva00237E28 *dest)
{
	dest->m_00 = m_00;
	dest->m_04 = m_04;
	dest->m_08 = m_08;
	dest->m_0C = m_0C;
}
