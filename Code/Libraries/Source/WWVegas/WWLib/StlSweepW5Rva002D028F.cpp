// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x002D028F (25B) is STLport's __destroy_aux range loop (const __false_type& tag): it calls the destructor rowed as
// ??1Nugget@ModuleInfo@@QAE@XZ (0x002CF51B, ThingTemplate.cpp) on each
// 0x14-byte element. The element type is that row's (identity unresolved beyond it);
// its destructor is only declared here, so this unit emits the loop alone.
#include <memory>

class ModuleInfo
{
public:
	struct Nugget
	{
		~Nugget();
		unsigned char m_bytes[0x14];
	};
};

template void _STL::__destroy_aux<ModuleInfo::Nugget *>(ModuleInfo::Nugget *, ModuleInfo::Nugget *, const _STL::__false_type &);
