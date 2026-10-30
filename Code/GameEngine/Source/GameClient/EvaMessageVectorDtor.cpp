// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@QAE@XZ retail 0x000B0254 63B
// Evidence: unlock same 63B EH shape as 0x0002CC70 via Destroy 0x000AFF52 plus free 0x00030830; callers 0x001021A0 0x001021AC 0x000B0834 0x001023F2
#include <vector>
// This unit also owns ??$_Destroy@PAUEvaMessageInfo@@@_STL@@YAXPAUEvaMessageInfo@@0@Z,
// retail 0x000AFF52 (25B): it walks [first,last) in 0x1C-byte steps and calls
// 0x00111B25, the rowed ??1Rva00111B25Record, on each element. So the element
// is 0x1C bytes and that is its destructor.
struct Rva00111B25Record
{
public:
	~Rva00111B25Record();
	unsigned char m_bytes[0x1C]; // +0x00
};
struct EvaMessageInfo
{
	// Destruction is the rowed ??1Rva00111B25Record, reached by a qualified call.
	__declspec(dllimport) __forceinline ~EvaMessageInfo() { ((Rva00111B25Record *)this)->Rva00111B25Record::~Rva00111B25Record(); }
	char m_unported[0x1C];
};

template _STL::vector<EvaMessageInfo>::~vector();
