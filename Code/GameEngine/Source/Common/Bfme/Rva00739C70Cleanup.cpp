// 23-byte and 32-byte cleanup routines, 62-byte reset, 109-byte update, and 81-byte destructor
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Release_Ref();
};

struct TexturePtr
{
	TextureBaseClass *m_ptr;
	~TexturePtr()
	{
		if ( m_ptr )
			m_ptr->Release_Ref();
	}
	TextureBaseClass *operator->() { return m_ptr; }
	operator bool() { return m_ptr != 0; }
	TexturePtr& operator=( int val ) { m_ptr = (TextureBaseClass*)val; return *this; }
};

#include "../../../Include/Common/VirtualReleaser00739E00.h"

void Log_DX8_ErrorCode( unsigned int code );

class Member0C00739C70
{
public:
	VirtualReleaser00739E00 *m_obj;

	~Member0C00739C70();
	__declspec(noinline) void clear();
	void reset()
	{
		if ( m_obj )
		{
			m_obj->Release();
			m_obj = 0;
		}
	}
};

class Rva00739C70
{
public:
	~Rva00739C70();
	void cleanup();
	void reset();
	// Retail identity is not recovered; the synthetic name records its exact
	// address while keeping this small predicate attached to the proven object.
	bool rva_00739E50();

	int               m_int0;
	int               m_int4;
	TexturePtr        m_ptr08;
	Member0C00739C70  m_member0c;
	int               m_flags;
};

void Rva00739C70::cleanup()
{
	if ( m_flags & 1 )
	{
		m_member0c.clear();
		m_flags &= ~1;
	}
}

// ?Rva00739C70::reset present-unmatched
void Rva00739C70::reset()
{
	cleanup();
	if ( m_ptr08 )
	{
		m_ptr08->Release_Ref();
		m_ptr08 = 0;
	}
	m_member0c.reset();
}

// The 109-byte lock/update body of this object is retail 0x000724D7, rowed as
// ?rva000724D7@Rva000724AE@@QAEPAXPAH@Z in Rva000724D7Lock.cpp; its unmatched
// copy here called two undefined placeholder members and kept the unit from linking.

// ?Rva00739C70::~Rva00739C70 present-unmatched
// ?Rva00739C70::rva_00739E50 present-unmatched
bool Rva00739C70::rva_00739E50()
{
	return m_ptr08.m_ptr != 0 || m_member0c.m_obj != 0;
}

class Owner00739C90
{
public:
	void cleanup();

	char         m_pad0[ 0x28 ];
	bool         m_dirty28;
	char         m_pad29[ 0x1B ];
	Rva00739C70 *m_subObject;
};

// ?Owner00739C90::cleanup present-unmatched
void Owner00739C90::cleanup()
{
	m_subObject->cleanup();
	m_dirty28 = true;
}
