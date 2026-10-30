// cl: /Od /GZ /GS /DNDEBUG
// platformsdk
/* Built without /MD: retail calls the msvcrt _mbscpy import stub with a
 * direct e8, as a library compiled against the static CRT headers does. */
#include <windows.h>
#include <string.h>
#include <mbstring.h>

struct CommTAPIRef
{
	void *m_ops[ 14 ];
	char m_gap38[ 0x14 ];
	char m_name[ 0x2C ];
	void *m_transport;
	char m_gap7C[ 0x0C ];
	int m_lineHandle;
	int m_callHandle;
	int m_state;
	char m_gap94[ 0x104 ];
	DWORD m_workerId;
};

extern "C"
{
	void Rva008139A0( void *comm );
	void Rva00813A50( void );
	void Rva00813D00( void );
	void Rva00813E30( void );
	void Rva00813E50( void );
	void Rva00813F20( void );
	void Rva00813F90( void );
	void Rva00814040( void );
	void Rva00814070( void );
	void Rva008140A0( void );
	// Rva00812FD0 is the retail cdecl worker entry and returns its status in EAX.
	int Rva00812FD0( void *comm );
	unsigned int Rva007FEA00( void );
	void *CommSerialConstruct( int first, int second, int third );
}

void CommTAPIUnresolve( void );
void CommTAPICallback( void );
void CommTAPITick( void );

extern "C" CommTAPIRef *CommTAPIConstruct( int first, int second, int third )
{
	void *threadHandle;
	CommTAPIRef *comm;

	comm = (CommTAPIRef *)HeapAlloc( GetProcessHeap(), 0, 0x19C );
	if ( comm == 0 )
		return 0;

	memset( comm, 0, 0x19C );
	comm->m_ops[ 0 ] = (void *)CommTAPIConstruct;
	comm->m_ops[ 1 ] = (void *)Rva008139A0;
	comm->m_ops[ 2 ] = (void *)Rva00813A50;
	comm->m_ops[ 3 ] = (void *)CommTAPIUnresolve;
	comm->m_ops[ 4 ] = (void *)Rva00813D00;
	comm->m_ops[ 5 ] = (void *)Rva00813E30;
	comm->m_ops[ 6 ] = (void *)Rva00813E50;
	comm->m_ops[ 7 ] = (void *)Rva00813F20;
	comm->m_ops[ 8 ] = (void *)CommTAPICallback;
	comm->m_ops[ 9 ] = (void *)Rva00813F90;
	comm->m_ops[ 10 ] = (void *)CommTAPITick;
	comm->m_ops[ 11 ] = (void *)Rva00814040;
	comm->m_ops[ 12 ] = (void *)Rva00814070;
	comm->m_ops[ 13 ] = (void *)Rva008140A0;
	_mbscpy( (unsigned char *)comm->m_name, (const unsigned char *)"TAPI" );
	comm->m_state = 0;
	threadHandle = CreateThread(
		0, 0, (LPTHREAD_START_ROUTINE)Rva00812FD0, comm, 0, &comm->m_workerId );
	CloseHandle( threadHandle );
	while ( comm->m_state == 0 )
		Sleep( 0 );

	if ( comm->m_state == 1 )
	{
		HeapFree( GetProcessHeap(), 0, comm );
		return 0;
	}

	comm->m_transport = CommSerialConstruct( first, second, third );
	comm->m_lineHandle = -1;
	comm->m_callHandle = -1;
	comm->m_state = 2;
	return comm;
}

/* The three op-table stubs retail holds at 0x0067FBF0 and 0x0067F940 (5B,
 * empty frames) and 0x0067FF20 (17B, tick read). BFME1 names all three as
 * op callees without giving bodies; the shapes are forced. The lowercase
 * pair keeps BFME1's plain-scope (C++) linkage, matching their pins. */
void CommTAPIUnresolve( void )
{
}

void CommTAPICallback( void )
{
}

void CommTAPITick( void )
{
	Rva007FEA00();
}
