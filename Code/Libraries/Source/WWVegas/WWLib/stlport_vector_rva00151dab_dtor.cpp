// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@VRva00151DAB@@V?$allocator@VRva00151DAB@@@_STL@@@_STL@@QAE@XZ, retail 0x00152118, 63 bytes.
// Vector<Rva00151DAB> dtor EH via rowed _Destroy 0x0015209B and free 0x00030830.
// Same 63B EH shape as rowed vector<Rva00153729> dtor 0x00153BED.
#include <vector>

class Rva00151DAB
{
public:
	~Rva00151DAB();

private:
	unsigned char m_pad[8];
};

template _STL::vector<Rva00151DAB>::~vector();
