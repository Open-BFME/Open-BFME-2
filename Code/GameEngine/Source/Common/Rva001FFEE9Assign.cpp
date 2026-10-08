// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// class-gate: allow UnicodeString 4B members at plus14-18 prove 4B view vs shared larger (retail plus14-18 4B apart with set calls)
// ??4Rva001FFEE9@@QAEAAV0@ABV0@@Z @0x001FFEE9 81B
// Copy-assign with 0x10 pad then int plus two UnicodeString via rowed set plus custom plus1C via pinned 0x1FFD6B plus tail ints/byte; base 5B ICF via pinned placeholder 0x1FD28E; 8B pad20 unproven gap; UnicodeString 4B for plus18.
class Rva001FD28E
{
public:
	void rva001FD28E(void *p);
};
// UnicodeString is StringBase<WideChar>; its set is the inherited
// StringBase<unsigned short>::set, the row at 0x00037150 the calls land on.
template <class T> class StringBase
{
public:
	void set(const StringBase<T> &that);
private:
	void *m_data;
};
class UnicodeString : public StringBase<unsigned short>
{
};
class Rva001FFD6B
{
public:
	void rva001FFD6B(void *p);
};
class Rva001FFEE9
{
public:
	Rva001FFEE9 &operator=(const Rva001FFEE9 &that);
private:
	char m_pad00[0x10];
	int m_10;
	UnicodeString m_14;
	UnicodeString m_18;
	char m_1C[4];
	char m_pad20[8];
	int m_28;
	int m_2C;
	unsigned char m_30;
};
Rva001FFEE9 &Rva001FFEE9::operator=(const Rva001FFEE9 &that)
{
	((Rva001FD28E *)this)->rva001FD28E((void *)&that);
	m_10 = that.m_10;
	m_14.set(that.m_14);
	m_18.set(that.m_18);
	((Rva001FFD6B *)&m_1C)->rva001FFD6B((void *)&that.m_1C);
	m_28 = that.m_28;
	m_2C = that.m_2C;
	m_30 = that.m_30;
	return *this;
}