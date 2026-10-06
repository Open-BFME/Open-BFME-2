// cl: /Ob0

template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
};

class Rva0036CA00Str
{
private:
	void *m_item;
};

struct Rva0014A470Pod
{
	int a[21];
};

class Rva0014A470
{
	int m_00;
	Rva0036CA00Str m_04;
	int m_08;
	int m_0C;
	int m_10;
	Rva0014A470Pod m_14;
	Rva0014A470Pod m_68;
	Rva0014A470Pod m_BC;
	Rva0014A470Pod m_110;
	Rva0014A470Pod m_164;
	Rva0036CA00Str m_1B8;
	int m_1BC;

public:
	Rva0014A470 &operator=(const Rva0014A470 &other);
};

Rva0014A470 &Rva0014A470::operator=(const Rva0014A470 &other)
{
	// The Rva0036CA00Str op= pin folds with the rowed StringBase<char>::set at 0x366F0.
	reinterpret_cast<StringBase<char> &>(m_04).set(
		reinterpret_cast<const StringBase<char> &>(other.m_04));
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_14 = other.m_14;
	m_68 = other.m_68;
	m_BC = other.m_BC;
	m_110 = other.m_110;
	m_164 = other.m_164;
	reinterpret_cast<StringBase<char> &>(m_1B8).set(
		reinterpret_cast<const StringBase<char> &>(other.m_1B8));
	m_1BC = other.m_1BC;
	return *this;
}
