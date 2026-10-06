// cl: /Ob0

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &other);

private:
	void *m_item;
};

class Rva00630D60
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	StringBase<char> m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;

public:
	Rva00630D60 &operator=(const Rva00630D60 &other);
};

Rva00630D60 &Rva00630D60::operator=(const Rva00630D60 &other)
{
	m_00.set(other.m_00);
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_2C = other.m_2C;
	m_30 = other.m_30;
	return *this;
}
