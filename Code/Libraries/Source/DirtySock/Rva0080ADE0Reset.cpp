// cl: /Od /GZ /MD /DNDEBUG
// _Rva0080ADE0 @ 0x00676CE0 (542B). Ported from Open-BFME-1
// Code/Libraries/Source/DirtySock/Rva0080ADE0CommStateReset.cpp: layout,
// constants and all calls are identical; only the backend release differs
// (BFME1 bfmeGo1019C vs BFME2 Rva007F0030Free at 0x0065CF10, read from the
// retail REL32 at +0xA1).
// Dedicated TU (Y2Rva00806580Module.cpp already defines the pump family).
void *Rva007F0000Alloc(int size);
extern "C" void Rva007FD3F0( void *socket );
extern "C" void Rva0080AD00( int a, int b, unsigned char *state );
#include <string.h>
void bfmeGo1019C(int a);


struct Rva0080ADE0Object
{
	void *m_socket;
	void **m_callbackTable;
	char m_gap08[ 0x110 ];
	int m_state;
	int m_mode;
	void *m_backend;
};

typedef void ( __cdecl *Rva0080ADE0Shutdown )( void **callbackTable );

extern "C" int __cdecl Rva0080ADE0( struct Rva0080ADE0Object *object, int releaseState )
{
	int i;
	unsigned char *backend;
	int result;

	if ( object->m_socket != 0 )
	{
		Rva007FD3F0( object->m_socket );
		object->m_socket = 0;
	}

	if ( object->m_callbackTable != 0 )
	{
		( (Rva0080ADE0Shutdown)object->m_callbackTable[ 3 ] )(
			object->m_callbackTable );
		object->m_callbackTable = 0;
	}

	object->m_state = 0;
	object->m_mode = 1;

	if ( releaseState == 0 )
	{
		if ( object->m_backend != 0 )
		{
			bfmeGo1019C((int)object->m_backend);
			object->m_backend = 0;
		}
	}

	if ( releaseState != 0 )
	{
		if ( object->m_backend == 0 )
		{
			object->m_backend = Rva007F0000Alloc( 0x88C0 );
			if ( object->m_backend != 0 )
			{
				memset( object->m_backend, 0, 0x88C0 );
				Rva0080AD00( 0, 0, (unsigned char *)object->m_backend + 0x86BC );
			}
		}
	}

	backend = (unsigned char *)object->m_backend;
	if ( backend != 0 )
	{
		*(int *)( backend + 0x81B4 ) = 0x10;
		for ( i = 0; i < *(int *)( backend + 0x81B4 ); i++ )
		{
			backend[ 0x81B8 + i ] = (unsigned char )( i + 0x30 );
		}
		*(int *)( backend + 0x00 ) = 0;
		*(int *)( backend + 0x04 ) = 0;
		*(int *)( backend + 0x4008 ) = 0;
		*(int *)( backend + 0x400C ) = 0;
		*(int *)( backend + 0x4010 ) = 0;
		*(int *)( backend + 0x8018 ) = 0;
		*(int *)( backend + 0x801C ) = 0;
		*(int *)( backend + 0x8024 ) = 0;
		*(int *)( backend + 0x80A8 ) = 0;
		*(int *)( backend + 0x812C ) = 0;
	}

	if ( releaseState != 0 && backend == 0 )
		result = -8;
	else
		result = 0;

	return result;
}
