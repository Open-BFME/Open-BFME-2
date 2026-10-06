// cl: /DNDEBUG /MD /EHsc
// ??4Rva0043B163@@QAEAAV0@ABV0@@Z @0x0043B163 51B
// Evidence: calls rowed ??4Rva003427DD 0x3427DD; copies +0x7c +0x80 +0x84 then returns this ret4; callers 0x43B8F0 0x43B914 0x43B9A1.
class Rva003427DD
{
public:
	Rva003427DD &operator=(const Rva003427DD &src);
private:
	char m_data[0x7c];
};

class Rva0043B163
{
public:
	Rva0043B163 &operator=(const Rva0043B163 &src);
private:
	Rva003427DD m_00;
	unsigned int m_7c;
	unsigned int m_80;
	unsigned int m_84;
};

Rva0043B163 &Rva0043B163::operator=(const Rva0043B163 &src)
{
	m_00 = src.m_00;
	m_7c = src.m_7c;
	m_80 = src.m_80;
	m_84 = src.m_84;
	return *this;
}
