// cl: /Ob0

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
};

class Rva0036CA00Str
{
public:
private:
	void *m_item;
};

class Rva00336C90
{
	virtual void handle();
	int m_04;
	int m_08;
	Rva0036CA00Str m_0C;
	Rva0036CA00Str m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	char m_24;
	int m_28;

public:
	Rva00336C90 &operator=(const Rva00336C90 &other);
};

Rva00336C90 &Rva00336C90::operator=(const Rva00336C90 &other)
{
	m_04 = other.m_04;
	m_08 = other.m_08;
	((StringBase<char> *)&m_0C)->set((const StringBase<char> &)other.m_0C);
	((StringBase<char> *)&m_10)->set((const StringBase<char> &)other.m_10);
	m_14 = other.m_14;
	m_18 = other.m_18;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	return *this;
}
