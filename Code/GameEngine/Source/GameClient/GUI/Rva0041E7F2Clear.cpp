// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfme_windowvideo /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Source/GameClient /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ?rva0041E7F2@Rva0041E7F2@@QAEXXZ @0x0041E7F2 59B.
// Drains the void* vector at +0x1C: each element's slot-0 virtual
// (EA deleteInstance shape, cf. Shell::doPop 0x0035BDC2 and
// AnimateWindowManager::clearWinList) is called with 0 and the result
// freed via operator delete, then the vector is cleared (erase range
// via clear()). Evidence: callees rowed operator delete 0x0002FD60
// and vector<void*>::erase 0x0031BD55 (via clear), caller dtor
// 0x0041E875 (which then frees +0x1C buffer and 3 StringBases) and
// its deleting dtor 0x0041E8F6; unlocks 0x0041E875.
#include <vector>

void __cdecl operator delete(void *p);

struct Rva0041E7F2Deleter
{
	virtual void *deleteInstance(int flags);
};

class Rva0041E7F2
{
public:
	void rva0041E7F2();
private:
	char m_pad[28];
	_STL::vector<void *> m_vec;
};

void Rva0041E7F2::rva0041E7F2()
{
	for (_STL::vector<void *>::iterator it = m_vec.begin(); it != m_vec.end(); ++it)
	{
		void *p = *it;
		void *q = p ? ((Rva0041E7F2Deleter *)p)->deleteInstance(0) : 0;
		::operator delete(q);
	}
	m_vec.clear();
}
