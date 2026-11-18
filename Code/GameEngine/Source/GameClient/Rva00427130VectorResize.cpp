// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameClient
// Address-derived conversion of the one-argument Eva message-vector resize at
// 0x00427130.  The constructor at 0x004271B0 calls this entry on the
// 0x18 default-check-info vector member with 0x11.  Its 28-byte seed is the parsed
// message record: four literal head words followed by the proven 12-byte
// STLport tree header whose 24-byte sentinel allocation is visible here.

#include "../../Include/Common/ScalarTypes.h"

// Existing STLport allocator body at 0x0082E540.  This is a typed use of the
// resolver's already-owned address, not a new ledger pin or alias.
namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( UnsignedInt bytes );
};
}

// This declaration deliberately keeps the existing retail callee's canonical
// COFF identity.  The target body only relies on the 28-byte ABI; its local
// seed has no caller-side destructor, matching the retail epilogue.
struct BfmeSubERF
{
	void *m_header;
	UnsignedInt m_count;
	UnsignedInt m_unported;

	BfmeSubERF() : m_header( 0 )
	{
		m_header = _STL::__new_alloc::allocate( 0x18 );
		m_count = 0;
		*(unsigned char *)m_header = 0;
		((UnsignedInt *)m_header)[1] = 0;
		((UnsignedInt *)m_header)[2] = (UnsignedInt)m_header;
		((UnsignedInt *)m_header)[3] = (UnsignedInt)m_header;
	}
};

struct BfmeItemERF
{
	UnsignedInt m_head0;
	UnsignedInt m_head1;
	UnsignedInt m_head2;
	UnsignedInt m_head3;
	BfmeSubERF m_bfmeSubERF;

	BfmeItemERF();
	BfmeItemERF( const BfmeItemERF &that );
	~BfmeItemERF();
};

// The callee's row (VectorResizeRva003F6EA1.cpp, 0x003F6EA1) spells the
// vector and its 28-byte by-value record by address-derived names. The record
// it takes is the one BfmeItemERF's constructor (0x003F609E) builds here, so
// the argument view only renames that record for the call.
struct Rva003F6EA1Record : BfmeItemERF
{
	Rva003F6EA1Record() {}
	~Rva003F6EA1Record();
};

class Rva003F6EA1Vector
{
public:
	void resize( UnsignedInt count, Rva003F6EA1Record value );
};

class Rva00427130Vector
{
public:
	void resize( UnsignedInt count );
};

void Rva00427130Vector::resize( UnsignedInt count )
{
	((Rva003F6EA1Vector *)this)->resize( count, Rva003F6EA1Record() );
}
