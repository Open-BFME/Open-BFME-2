// cl: /MD
// ?Rva002DBD80Make@@YA?AURva002DBD80Val@@HPBG@Z @0x002DBD80 52B
// Evidence: unlock lane; callee initWide 0x002342D5 rowed; hidden-pointer return with int+pair 12B temp copied via movsd x3.
class Rva000B3F84Pair
{
public:
	Rva000B3F84Pair() {}
	Rva000B3F84Pair *initWide(const unsigned short *src);
	const char *m_ptr;
	int m_len;
};
struct Rva002DBD80Val
{
	Rva002DBD80Val() {}
	int m_00;
	Rva000B3F84Pair m_pair;
};
Rva002DBD80Val Rva002DBD80Make(int x, const unsigned short *s)
{
	Rva000B3F84Pair tmp;
	tmp.initWide(s);
	Rva002DBD80Val v;
	v.m_00 = x;
	v.m_pair = tmp;
	return v;
}
