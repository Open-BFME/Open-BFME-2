// cl: /O1 /MD
// stlport46
// ?rva002E2578@Rva002E2578@@QAEXABV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@Z, retail 0x002E2578, 97 bytes.
// Filter src sciences into the vector at +0x1CC keeping only the non-grantable ones:
// erase the whole range via the rowed erase at 0x00532803, then index loop over src
// testing each with rowed ScienceStore::isScienceGrantable at 0x001FF432 through
// TheScienceStore, pushing kept ones via the rowed push_back at 0x002E01C6. Caller 0x0040F323.
// The argument of isScienceGrantable is an equal-arm conditional (late-folded ?:),
// which reproduces retail's register order for the call (W7-R1 lever).
enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *first, T *last);
	void push_back(const T &v);
	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class ScienceStore
{
public:
	bool isScienceGrantable(ScienceType st) const;
};

extern ScienceStore *TheScienceStore;

class Rva002E2578
{
	char m_pad[0x1CC];
	_STL::vector<ScienceType> m_vec1CC;
public:
	void rva002E2578(const _STL::vector<ScienceType> &src);
};

void Rva002E2578::rva002E2578(const _STL::vector<ScienceType> &src)
{
	_STL::vector<ScienceType> *dst = &m_vec1CC;
	dst->erase(dst->m_start, dst->m_finish);
	for (unsigned int i = 0; i < (unsigned int)(src.m_finish - src.m_start); ++i) {
		if (!TheScienceStore->isScienceGrantable( (dst ? src.m_start[i] : src.m_start[i])))
			dst->push_back(src.m_start[i]);
	}
}
