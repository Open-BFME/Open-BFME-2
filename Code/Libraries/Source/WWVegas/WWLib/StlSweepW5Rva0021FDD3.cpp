// STLport 4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x0021FDD3 (25B) is STLport's _Destroy range destroy (the __destroy_aux loop inlined): it calls the destructor rowed as
// ??1CreateAHeroClass@CreateAHeroManager@@QAE@XZ (0x0021F8F3, Rva0021F876Dtor.cpp) on each
// 0x20-byte element. The element type is that row's (identity unresolved beyond it);
// its destructor is only declared here, so this unit emits the loop alone.
#include <memory>

class CreateAHeroManager
{
public:
	class CreateAHeroClass
	{
	public:
		~CreateAHeroClass();
	private:
		unsigned char m_bytes[0x20];
	};
};

template void _STL::_Destroy<CreateAHeroManager::CreateAHeroClass *>(CreateAHeroManager::CreateAHeroClass *, CreateAHeroManager::CreateAHeroClass *);
