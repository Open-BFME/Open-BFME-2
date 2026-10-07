// cl: /O1 /arch:SSE /G7 /MD
// stlport
// ?rva00359811@Rva00359811@@QAEIABURva003597C3Element@@_N@Z 0x00359811 27B; branch and set erase call are retail evidence
#include <set>

struct Rva003597C3Element
{
	char bytes[8];
};

bool operator<(const Rva003597C3Element &left, const Rva003597C3Element &right);

class Rva00359811
{
public:
	unsigned int rva00359811(const Rva003597C3Element &key, bool useSecond);
private:
	char m_pad00[0x0c];
	_STL::set<Rva003597C3Element> m_first;
	_STL::set<Rva003597C3Element> m_second;
};

unsigned int Rva00359811::rva00359811(const Rva003597C3Element &key, bool useSecond)
{
	return (useSecond ? m_second : m_first).erase(key);
}
