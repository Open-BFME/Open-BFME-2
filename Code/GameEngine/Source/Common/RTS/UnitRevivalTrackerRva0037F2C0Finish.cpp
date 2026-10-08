// cl: /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /O1 /Ob1 /EHsc /DNDEBUG /MD /arch:SSE /G7
// stlport
// ?rva0037F2C0@Rva0037F2C0@@QAEHPAVObject@@_N@Z @0x0037F2C0 111B via UnitRevivalTracker vector at +4, UnitRevivalEntry from Object, size-1 return
#include <vector>

class Object;

class UnitRevivalEntry
{
public:
	UnitRevivalEntry(Object *object);
	~UnitRevivalEntry();
	char m_pad00[0x94];
	int m_94;
	char m_pad98[0xD8 - 0x98];
};

class Rva0037F2C0
{
public:
	int rva0037F2C0(Object *object, bool flag);
private:
	int m_00;
	_STL::vector<UnitRevivalEntry> m_vec;
};

int Rva0037F2C0::rva0037F2C0(Object *object, bool flag)
{
	UnitRevivalEntry entry(object);
	if (flag)
		entry.m_94 = 0;
	m_vec.push_back(entry);
	int count = (int)m_vec.size() - 1;
	return count;
}
