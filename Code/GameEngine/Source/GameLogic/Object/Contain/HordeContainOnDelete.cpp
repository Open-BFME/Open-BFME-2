// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?onDelete@HordeContain@@UAEXXZ, retail 0x0046E697 (83 bytes): primary slot
// shared by the HordeContain tables (0x00C45070 and the two derived copies at
// 0x00C45C58/0x00C46D48), next to the rowed TransportContain slot 0x004672B7.
// It first runs the +0x11C interface's slot 56 (0x0046C327, rowed in
// HordeContainIface11CSlots.cpp), then frees every banner index entry held by
// pointer in the vector at +0x270, clears it (vector<void *>::erase
// 0x0031BD55) and tail-calls the pinned OpenContain::onDelete 0x00464120,
// like HordeSiegeEngineContain::onDelete. Storage-only view: no constructor
// or destructor, so this unit emits no vtables.
#include <vector>

// vector<void*> begin/end/size/operator[]/clear are expanded inline here; their
// out-of-line copies would differ from retail's. Declared imported and force-inlined,
// they are not emitted.
namespace _STL {
template <> void **vector<void *>::erase(void **first, void **last);
template <> __declspec(dllimport) __forceinline
void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void *>::end() { return this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void vector<void *>::clear() { erase(begin(), end()); }
template <> __declspec(dllimport) __forceinline
size_t vector<void *>::size() const { return this->_M_finish - this->_M_start; }
template <> __declspec(dllimport) __forceinline
void *&vector<void *>::operator[](size_t n) { return this->_M_start[n]; }
}

class Object;
class ModuleData;

class OpenContain
{
public:
	virtual void onDelete();
protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_padding0C[0x100 - 0x0C];
};

class TransportContain : public OpenContain
{
private:
	unsigned char m_padding100[0x11C - 0x100];
};

class HordeContainIface11C
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void rva0046C327();	// slot 56
};

struct HordeContainBannerIndexEntry
{
	const void *m_template;
	int m_index;
};

class HordeContain : public TransportContain, public HordeContainIface11C
{
public:
	virtual void onDelete();
private:
	unsigned char m_pad120[0x270 - 0x120];
	_STL::vector<void *> m_bannerIndices;	// +0x270, HordeContainBannerIndexEntry pointers
public:
	virtual void rva0046C327();
};

void HordeContain::onDelete()
{
	rva0046C327();
	for (unsigned int i = 0; i < m_bannerIndices.size(); ++i)
		delete (HordeContainBannerIndexEntry *)m_bannerIndices[i];
	m_bannerIndices.clear();
	OpenContain::onDelete();
}
