// cl: /Oy- /DNDEBUG /MD /EHsc
// stlport
// ?rva004D6BF0@Rva004D6BF0@@QAEXPAX@Z retail 0x004D6BF0 57B.
// Vector find-and-erase void with null check: loads CreateAHeroData* at arg+0x74 into
// stack temp then finds it in the vector at this+4 via rowed find at 0x0020E873 and erases
// via rowed erase at 0x0025BF5D when present. EBP frame needs /Oy- like Rva0025BF8C.
#include <vector>
#include <algorithm>
class CreateAHeroData;
enum ObjectID
{
	OBJECTID_INVALID = 0
};
class Rva004D6BF0
{
public:
	void rva004D6BF0(void *arg);
private:
	char m_pad[4];
	_STL::vector<ObjectID> m_vec04;
};
void Rva004D6BF0::rva004D6BF0(void *arg)
{
	if (!arg)
		return;
	CreateAHeroData *hero = *(CreateAHeroData **)((char *)arg + 0x74);
	CreateAHeroData **begin = (CreateAHeroData **)m_vec04.begin();
	CreateAHeroData **end = (CreateAHeroData **)m_vec04.end();
	CreateAHeroData **it = _STL::find(begin, end, hero);
	if (it != end) {
		m_vec04.erase((ObjectID *)it);
	}
}
