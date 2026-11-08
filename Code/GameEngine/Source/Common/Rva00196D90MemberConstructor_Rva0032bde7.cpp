// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/Common -Ireference/shims/bfmealloc_alloconly
// stlport46

#include <new>
#include <vector>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

struct Rva00196D90Element;

class Dict
{
public:
	Dict( int numPairsToPreAllocate );
	Dict( const Dict &source )
		: m_data( source.m_data )
	{
		if ( m_data != 0 )
			++*(unsigned short *)m_data;
	}

	void *m_data;

private:
	friend struct Rva00196D90Element;
	void releaseData();
};

// Preserve the individual native initialization stores. The address-derived
// record identity remains unknown; no donor or ICF type identity is asserted.
struct Rva00196D90Element
{
	volatile short m_word0;
	volatile short m_word2;
	volatile short m_word4;
	volatile short m_word6;
	volatile int m_word8;
	Dict m_dict;

	Rva00196D90Element()
		: m_word0( 0 ), m_word2( 0 ), m_word4( 0 ), m_word6( 0 ),
		  m_word8( 0 ), m_dict( 0 )
	{
	}

	Rva00196D90Element( const Rva00196D90Element &source )
		: m_word0( source.m_word0 ), m_word2( source.m_word2 ),
		  m_word4( source.m_word4 ), m_word6( source.m_word6 ),
		  m_word8( source.m_word8 ), m_dict( source.m_dict )
	{
	}

	~Rva00196D90Element()
	{
		m_dict.releaseData();
	}

	Rva00196D90Element &operator=( const Rva00196D90Element &source );
};

namespace _STL
{
// The verified18B placement helper and its58B copy cannot throw C++ exceptions.
template <> __declspec(nothrow) void _Construct<Rva00196D90Element, Rva00196D90Element>(Rva00196D90Element *, const Rva00196D90Element &);
	inline Rva00196D90Element *__uninitialized_fill_n(
		Rva00196D90Element *first, unsigned int count,
		const Rva00196D90Element &value, const __false_type &)
	{
		Rva00196D90Element *current = first;
		for ( ; count > 0; --count, ++current )
			_Construct(current, value);
		return current;
	}
}

template _STL::vector<Rva00196D90Element>::vector( unsigned int );
