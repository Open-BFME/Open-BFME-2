// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00102188@@UAE@XZ retail 0x00102188 54B
// Evidence: chain calls vector dtor 0x000B0254 at +0x14 then +0x04; caller deleting dtor 0x001021BE
#include <vector>

struct EvaMessageInfo
{
	~EvaMessageInfo();
};

class __declspec(novtable) Rva00102188
{
public:
	virtual ~Rva00102188();
private:
	_STL::vector<EvaMessageInfo> m_04;
	char m_pad10[0x14 - (4 + 12)];
	_STL::vector<EvaMessageInfo> m_14;
};

Rva00102188::~Rva00102188()
{
}
