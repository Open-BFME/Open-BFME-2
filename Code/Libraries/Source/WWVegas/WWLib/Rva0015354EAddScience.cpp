// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva0015354E@Rva0015354E@@QAEXW4ScienceType@@@Z, retail 0x0015354E 23B.
// Null-checked Science push: if the +0x10 store exists, push the ScienceType
// arg into its vector at +4 via the rowed ThingTemplate push_back 0x002E01C6.
// Evidence: five callers in 0x0014FFF6 pass constant 1 with this from
// [ebp+0x10]; callee is vector<ScienceType>::push_back; stride and shape
// match the ProductionPrerequisite Science pattern; owner unproven so the
// name keeps the address token.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void push_back(const T &x);
};

}

struct Rva0015354EStore
{
	unsigned char m_pad00[4];
	_STL::vector<ScienceType> m_sciences04; // +4
};

class Rva0015354E
{
public:
	void rva0015354E(ScienceType value);

private:
	unsigned char m_pad00[0x10];
	Rva0015354EStore *m_store10; // +0x10
};

void Rva0015354E::rva0015354E(ScienceType value)
{
	Rva0015354EStore *store = m_store10;
	if (store == 0)
		return;
	store->m_sciences04.push_back(value);
}
