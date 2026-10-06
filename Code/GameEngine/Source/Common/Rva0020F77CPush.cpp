// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0020F77C@Rva0020F77C@@QAEXPAVObjectCreationNugget@@@Z @0x0020F77C 25B.
// Vector push-back through the ICF-shared ObjectCreationNugget* push_back
// at 0x004DFCB0 (pinned): the int/pointer param is copied to a same-slot
// temporary (the redundant mov pair retail keeps) whose address feeds the
// by-ref push into the vector at this+0x5C. Strict holder type unproven;
// the nugget spelling is for the shared worker.
#include <vector>

class ObjectCreationNugget;

class Rva0020F77C
{
public:
	void rva0020F77C(ObjectCreationNugget *x);
private:
	char m_pad00[0x5C];
	_STL::vector<ObjectCreationNugget *> m_vec5C;
};

void Rva0020F77C::rva0020F77C(ObjectCreationNugget *x)
{
	ObjectCreationNugget *y = x;
	m_vec5C.push_back(y);
}
