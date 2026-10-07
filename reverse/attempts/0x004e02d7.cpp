// ?rva004E02D7@Rva004E00BAOwner@@QAEXPAVObject@@@Z
// partial score=0.9 date=2026-10-07
// cl: /EHsc /DNDEBUG /MD
#include <vector>
#include <algorithm>

class Object;

class Rva004E00BAOwner
{
public:
	void rva004E00D9();
	void rva004E02D7(Object *object);

private:
	unsigned int m_opaquePrefix;
	_STL::vector<Object *> m_objects;
};

void Rva004E00BAOwner::rva004E02D7(Object *object)
{
	_STL::vector<Object *>::iterator found = _STL::find(m_objects.begin(), m_objects.end(), object);
	if (found != m_objects.end()) {
		m_objects.erase(found);
		rva004E00D9();
	}
}
