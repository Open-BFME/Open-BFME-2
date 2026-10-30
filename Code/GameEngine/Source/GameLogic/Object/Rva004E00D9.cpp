// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?rva004E00D9@Rva004E02D7Owner@@QAEXXZ @0x004E00D9 98B: clear of the owner's two pointer vectors, byte-identical
// in shape to Rva00283CB3::rva00283505 (Map/TerrainLogicRva00283CE7.cpp): destroy and free every element of the
// vector at +0x10 (rowed destructor 0x00281A06), clear it, then pass every element of the vector at +4 to the
// same-receiver member 0x004DFF2C (rowed as Rva004DFF2C::rva004DFF2C in Rva004DFF2CGroupMerge.cpp). Target evidence:
// retail body read byte for byte; the follow-up call's callee read at its REL32. Class identity unresolved; names
// are address-derived.
#include <vector>
// Keep vector<void*> accessors inline without emitting this unit's /O1 COMDAT
// copies: retail's out-of-line ones are the /Od bodies at 0x00023B90-0x00023C20.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const
{ return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline
void *&vector<void*>::operator[](size_t __n)
{ return *(begin() + __n); }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool vector<void*>::empty() const { return this->_M_start == this->_M_finish; }
template <> __declspec(dllimport) __forceinline
void vector<void*>::clear() { erase(begin(), end()); }
}

class Object;

class Rva00281A06 { public: ~Rva00281A06(); };

class Rva00281A76;
typedef void *(__cdecl *Rva004DFE4FCallback)(void *key);

class Rva004DFF2C
{
public:
 virtual float padding() = 0;
 void rva004DFF2C(void *key);
private:
 char m_pad04[0xC];
 _STL::vector<Rva00281A76 *> m_groups;
 int m_1C;
 Rva004DFE4FCallback m_callback;
};

class Rva004E02D7Owner
{
public:
	void rva004E00D9();

private:
	char unknown00[4];
	_STL::vector<void *> records;
	_STL::vector<void *> holders;
};

void Rva004E02D7Owner::rva004E00D9()
{
	void **end = holders.end();
	for (void **i = holders.begin(); i != end; ++i)
		delete (Rva00281A06 *)*i;
	holders.clear();
	if (!records.empty()) {
		void **last = records.end();
		for (void **i = records.begin(); i != last; ++i)
			((Rva004DFF2C *)this)->rva004DFF2C(*i);
	}
}
