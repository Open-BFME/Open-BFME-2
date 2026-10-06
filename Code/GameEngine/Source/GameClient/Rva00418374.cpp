// cl: /Ob2 /EHsc /MD
//
// ?rva00418374@Rva00418374@@QAEPAUOutIter004182F8@@PAU2@PBVRva004181F5@@@Z @0x00418374 36B.
// Insert helper bumping +0x10 count then delegating to rowed rva004182F8
// returning the iterator.
// Evidence: pin rva00212858 rowed rva004182F8, callers 0x004183A0
// 0x0041840F, ret 8 two pointers.
struct OutIter004182F8;
class Rva004181F5;

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
};

class Rva004182F8
{
public:
	OutIter004182F8 *rva004182F8(OutIter004182F8 *it, const Rva004181F5 *p);
};

class Rva00418374
{
public:
	OutIter004182F8 *rva00418374(OutIter004182F8 *it, const Rva004181F5 *p);
private:
	char m_pad00[0x10];
	int m_count10;
};

OutIter004182F8 *Rva00418374::rva00418374(OutIter004182F8 *it, const Rva004181F5 *p)
{
	((Rva000427195 *)this)->rva00212858((unsigned int)m_count10 + 1u);
	((Rva004182F8 *)this)->rva004182F8(it, p);
	return it;
}
