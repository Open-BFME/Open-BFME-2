// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1BfmeAssignRecord52@@QAE@XZ @ 0x002B707E 53B
// Evidence: pin ??1BfmeAssignRecord52@@QAE@XZ; calls rowed vector dtor 0x002B703F at +0xC then rowed ??1Rva002B5558 at +0; callers are deleting dtor and __destroy_aux for BfmeAssignRecord52; chain from 0x002B703F.
#include <vector>

struct Rva0040DC56Element
{
	~Rva0040DC56Element();
	int m_pad[4];
};

class Rva002B5558
{
public:
	~Rva002B5558();
private:
	char m_pad[8];
};

class BfmeAssignRecord52
{
public:
	~BfmeAssignRecord52();
private:
	Rva002B5558 m_00;
	char m_pad08[4];
	_STL::vector<Rva0040DC56Element> m_0C;
	char m_pad18[28];
};

BfmeAssignRecord52::~BfmeAssignRecord52()
{
}
