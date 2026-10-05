// cl: /O1 /MD /G7
// ?rva003B0412@Rva003B0412@@QAEXPBUPrereqUnitRec@@@Z @0x003B0412 33B: pushes
// the prerequisite record into the +0 vector through rowed
// vector<PrereqUnitRec>::push_back at 0x002DF89B, then forwards the vector
// bounds and the +0xc flag byte to pinned 0x003B015D. Evidence: single pointer
// arg (ret 4), ecx stays this for the vector call, byte widens through al.
namespace _STL {
template <class T> class allocator;
template <class T, class Alloc> class vector
{
public:
	void push_back(const T &x);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

struct PrereqUnitRec
{
	unsigned int m_data[3];
};

void rva003B015D(int a1, int a2, char a3);

class Rva003B0412
{
public:
	void rva003B0412(const PrereqUnitRec *rec);

private:
	_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > m_vec;
	unsigned char m_0c;
};

void Rva003B0412::rva003B0412(const PrereqUnitRec *rec)
{
	m_vec.push_back(*rec);
	rva003B015D((int)m_vec._M_start, (int)m_vec._M_finish, m_0c);
}
