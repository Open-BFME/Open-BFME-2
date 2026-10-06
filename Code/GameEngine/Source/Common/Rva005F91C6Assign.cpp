// cl: /O1 /EHs /MD
//
// ??4Rva005F91C6@@QAEAAU0@ABU0@@Z @0x005F91C6 45B: memberwise assignment of a
// record holding a TreeHintRef00217D4C at +0 (rowed operator= 0x002174A4), two
// plain words at +4/+8 and a UnicodeString at +0xC whose assignment is the
// rowed StringBase<unsigned short>::set (0x00037150). No REL32 caller found;
// owner unknown, so the name is address-derived.

struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);

	void *m_ref;
};

template <class T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	T *m_data;
};

typedef StringBase<unsigned short> UnicodeString;

struct Rva005F91C6
{
	Rva005F91C6 &operator=(const Rva005F91C6 &other);

	TreeHintRef00217D4C m_00;
	int m_04;
	int m_08;
	UnicodeString m_0C;
};

Rva005F91C6 &Rva005F91C6::operator=(const Rva005F91C6 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_08 = other.m_08;
	m_0C = other.m_0C;
	return *this;
}
