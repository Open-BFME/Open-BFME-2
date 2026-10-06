// cl: /MD
// ?rva006EB650@Rva006EB650@@QAEXABV1@@Z, retail 0x006EB650 (78B).
// Evidence: leaf caller at 0x006EF640; callee ??4EAStringC@@QAEAAV0@ABV0@@Z rowed; layout 0x20B with EAStringC at +0 and conditional -1-kept fields at +14/+18/+1C.
class EAStringC
{
public:
	void *m_pData;
	EAStringC &operator=(const EAStringC &other);
};

class Rva006EB650
{
public:
	EAStringC m_str;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	void rva006EB650(const Rva006EB650 &other);
};

void Rva006EB650::rva006EB650(const Rva006EB650 &other)
{
	m_0c = other.m_0c;
	m_08 = other.m_08;
	m_str = other.m_str;
	m_04 = other.m_04;
	m_10 = other.m_10;
	if (other.m_14 != -1)
		m_14 = other.m_14;
	if (other.m_18 != -1)
		m_18 = other.m_18;
	if (other.m_1c != -1)
		m_1c = other.m_1c;
}
