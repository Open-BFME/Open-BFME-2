// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfmecamera /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/reference/shims/objectdlink /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// stlport
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include "ObjectDlinkPmf.h"

// Address-derived reconstruction.  The retail body lazily allocates the
// seven-dword object stored at +0x54 and forwards its argument with a true
// flag.  Names remain descriptive because no trustworthy class identity is
// known.

extern int Gen01083E78;

class Rva001705A0Inner
{
public:
	Rva001705A0Inner();
	void apply( int value, bool enabled );
	void applyAlternate( int value, bool enabled );

private:
	int *m_vtable;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
};

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

// Zero Hour's DLINK_ITERATOR (GameCommon.h). BFME2's Object carries a vbptr
// at +0x68 (ObjectDlinkPmf.h), so the iterator's GetNextFunc is a
// virtual-inheritance member pointer and advance() is the 32-byte body at
// 0x00263526; retail calls it as DLINK_ITERATOR<Object>::advance from the
// Team member walks (e.g. 0x0039E5B9, 0x003C9A80).
template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

	DLINK_ITERATOR( OBJCLASS *cur, GetNextFunc getNextFunc )
		: m_cur( cur ), m_getNextFunc( getNextFunc ) {}

	void advance()
	{
		if ( m_cur )
			m_cur = (m_cur->*m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;
};

class Rva001705A0Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;
};

class Rva001705A0ObjectIDView
{
public:
	unsigned char m_pad[0x74];
	ObjectID m_id;
	ObjectID getID() const { return m_id; }
};

class Rva001705A0IDVectorView
{
public:
	_STL::vector<ObjectID> m_ids;
};

// ??0Rva001705A0Inner@@ present-unmatched
inline Rva001705A0Inner::Rva001705A0Inner()
{
	m_vtable = &Gen01083E78;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
}

// ?apply@Rva001705A0Inner@@ present-unmatched
void Rva001705A0Inner::apply( int value, bool enabled )
{
	if ( value == 0 )
		return;

	if ( enabled )
		((Rva001705A0IDVectorView *)((char *)this + 4))->m_ids.clear();

	Rva001705A0Team *team = (Rva001705A0Team *)value;
	for ( DLINK_ITERATOR<Object> iter =
			DLINK_ITERATOR<Object>( team->m_head,
				Object::dlink_next_TeamMemberList );
			!iter.done(); iter.advance() )
	{
		Rva001705A0ObjectIDView *object =
			(Rva001705A0ObjectIDView *)iter.cur();
		((Rva001705A0IDVectorView *)((char *)this + 4))->m_ids.push_back( object->getID() );
	}
}

class Rva001705A0Owner
{
public:
	void setValue( int value );

private:
	char m_pad00[ 0x54 ];
	Rva001705A0Inner *m_inner;
};

// ?setValue@Rva001705A0Owner@@ present-unmatched
void Rva001705A0Owner::setValue( int value )
{
	if ( m_inner == 0 )
		m_inner = new Rva001705A0Inner;
	m_inner->apply( value, true );
}

class Rva00170610Owner
{
public:
	void setValue( int value );

private:
	char m_pad00[ 0x54 ];
	Rva001705A0Inner *m_inner;
};

// ?setValue@Rva00170610Owner@@ present-unmatched
void Rva00170610Owner::setValue( int value )
{
	if ( m_inner == 0 )
		m_inner = new Rva001705A0Inner;
	m_inner->applyAlternate( value, true );
}
