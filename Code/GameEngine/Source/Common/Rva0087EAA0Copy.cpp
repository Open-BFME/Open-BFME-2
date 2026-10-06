// cl: /Ob0
// bfmeCopyAA at 0x006BE370: backward copy of 0x24-byte elements, ported from
// the BFME1 Rva0087EAA0Copy.cpp donor. Two retail adaptations: the middle
// member is a StringBase<char> assigned via set() (retail calls the shared
// StringBase<char>::set worker at 0x00366F0), and the loop copies a second
// trailing byte at +0x21, which pushes the n<=0 early exit six bytes down
// (true size 138).

template <typename CharType>
class StringBase
{
public:
	void set(const StringBase<CharType> &other);

private:
	void *m_data;
};

struct BfmeCoordAA
{
	int m_x;
	int m_y;
	int m_z;
};

struct BfmeElemAA
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeCoordAA m_10;
	StringBase<char> m_1C;
	char m_20;
	char m_21;
	char m_pad[2];
};

BfmeElemAA *bfmeCopyAA(BfmeElemAA *first, BfmeElemAA *last, BfmeElemAA *dest)
{
	int n = last - first;
	if (n > 0)
	{
		int m = n;
		do
		{
			--last;
			--dest;
			dest->m_00 = last->m_00;
			dest->m_04 = last->m_04;
			dest->m_08 = last->m_08;
			dest->m_0C = last->m_0C;
			dest->m_10 = last->m_10;
			dest->m_1C.set(last->m_1C);
			dest->m_20 = last->m_20;
			dest->m_21 = last->m_21;
		} while (--m);
	}
	return dest;
}
