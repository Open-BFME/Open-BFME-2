// cl: /O1 /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 pointer-range algorithms over the CreateAHeroData* vector
// (see Rva0040A3F9Find.cpp): for_each releasing every element through
// TheHeroManager (rowed 0x21929D), and the 4x unrolled random-access
// __find_if with the two by-value comparison functors rowed at 0x40A16E and
// 0x40A187 (one resp. two dwords of state). Evidence: target bytes of
// 0x40A1AC/0x40A1D7/0x40A283; functor spelling is donor inference.
#include <algorithm>

class CreateAHeroData;

class Rva00219251
{
public:
	void rva0021929D(CreateAHeroData **data);
};

extern Rva00219251 *TheHeroManager;

class Rva0040A16E
{
public:
	bool rva0040A16E(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A16E(p); }
private:
	int m_val0;
};

class Rva0040A187
{
public:
	bool rva0040A187(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A187(p); }
private:
	int m_val0;
	int m_val4;
};

struct Rva0040A1ACRelease
{
	void operator()(CreateAHeroData *p) const { TheHeroManager->rva0021929D(&p); }
};

template Rva0040A1ACRelease _STL::for_each<CreateAHeroData **, Rva0040A1ACRelease>(CreateAHeroData **, CreateAHeroData **, Rva0040A1ACRelease);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A16E>(CreateAHeroData **, CreateAHeroData **, Rva0040A16E, const _STL::random_access_iterator_tag &);
template CreateAHeroData **_STL::__find_if<CreateAHeroData **, Rva0040A187>(CreateAHeroData **, CreateAHeroData **, Rva0040A187, const _STL::random_access_iterator_tag &);
