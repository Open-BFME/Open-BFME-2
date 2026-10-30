// cl: /Od /GZ /GS /DNDEBUG
// platformsdk
// Retail 0x00819630: DirtySock TAPI transport allocation called by
// Rva00812DD0.  The address-derived entry keeps the raw cdecl ABI proved by
// that caller; the object view is local because no shared layout is justified.
// Built without /MD: retail calls the msvcrt _mbscpy import stub with a direct
// e8, as a library compiled against the static CRT headers does.
#include <windows.h>
#include <string.h>
#include <mbstring.h>

struct CommSerialRef
{
	void *m_ops[ 14 ];
	char m_gap38[ 0x14 ];
	char m_name[ 0x2c ];
	void *m_transport;
	int m_handle;
	char m_gap80[ 8 ];
	int m_field88;
	int m_field8c;
	void *m_event0;
	char m_gap94[ 0x10 ];
	void *m_event1;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	char m_gapBC[ 0x0c ];
	int m_threadId;
	int m_state;
	int m_pendingValue;
	int m_recvRecordSize;
	int m_recvBufferSize;
	int m_recvWriteOffset;
	int m_recvReadOffset;
	void *m_recvBuffer;
	int m_recvSequence;
	int m_sendRecordSize;
	int m_sendBufferSize;
	int m_sendWriteOffset;
	int m_sendReadOffset;
	int m_sendAckOffset;
	void *m_sendBuffer;
	unsigned int m_sendSequence;
	char m_gap108[ 0x800 ];
	int m_field908;
	char m_gap90c[ 0x1000 ];
	int m_streamCapacity;
	int m_streamLength;
	int m_streamSlot;
	char m_gap1918[ 8 ];
	char m_lock[ 0x18 ];
	int m_depth;
	int m_flags;
	char m_tail[ 4 ];
};

extern "C"
{
	void Rva0081ACD0( void *comm );
	int Rva0081B790( void *comm, void *argument );
	int Rva0081B830( void *comm );
	int Rva0081B910( void *comm, void *argument );
	int Rva0081BA60( void *comm, const void *payload, int length );
	int Rva0081BC80( void *comm, void *buffer, int size, unsigned int *when );
	int Rva0081BD40( void *comm, void *buffer, int size, unsigned int *when );
}

// Retail installs this typed five-argument cdecl callback in operation-table
// slot 2 and returns a status in EAX.  Its upstream spelling is unavailable,
// so the address-derived name is retained.
typedef int ( __cdecl *Rva0081AE20Proc )( void *comm, const char *name,
	char *output, int outputSize, int flags );
extern void CommSerialUnresolve( void );
extern void CommSerialCallback( void );
extern void Rva0081BA40( void );
extern "C" void Rva0081B9B0( void *comm );

extern "C" int Rva0081B9D0( void *comm );
// The generated row keeps the exact retail COFF spelling/address. CreateThread
// consumes that address as a DWORD WINAPI(void *) thread entry.
extern void d_00819920( void );
typedef unsigned long ( __stdcall *Rva00819920ThreadProc )( void *parameter );
extern void *Rva007F0000Alloc( int size );

extern "C" int Rva0081AE20( void *comm, const char *name, char *output,
	int outputSize, int separator )
{
	int i;
	void *handle;
	const char *list[ 5 ] = { "COM1", "COM2", "COM3", "COM4", 0 };
	char *originalOutput;

	originalOutput = output;
	output[ 0 ] = '*';
	output[ 1 ] = 0;
	output[ 2 ] = 0;

	if ( name == 0 || *name == 0 )
		return -1;

	if ( outputSize < 0x40
		|| (unsigned int)outputSize < strlen( name ) + 2 )
		return -6;

	if ( strcmp( name, "localhost" ) != 0 )
	{
		wsprintfA( output, "%s%c", name, 0 );
		return 1;
	}

	for ( i = 0; list[ i ] != 0; i++ )
	{
		handle = CreateFileA( list[ i ], 0xc0000000, 0, 0, 3,
			0x40000080, 0 );

		if ( handle == (void *)-1 )
			continue;

		CloseHandle( handle );

		if ( output != originalOutput )
			*output++ = (char)separator;

		output += wsprintfA( output, "%s", list[ i ] );
	}

	*output++ = 0;
	*output++ = 0;
	return 1;
}

extern "C" void *CommSerialConstruct( int first, int second, int third )
{
	unsigned long pid;
	void *result;
	CommSerialRef *comm;

	comm = (CommSerialRef *)Rva007F0000Alloc( 0x1944 );
	if( comm == 0 )
		return 0;

	memset( comm, 0, 0x1944 );
	comm->m_ops[ 0 ] = (void *)CommSerialConstruct;
	comm->m_ops[ 1 ] = (void *)Rva0081ACD0;
	comm->m_ops[ 2 ] = (void *)(Rva0081AE20Proc)Rva0081AE20;
	comm->m_ops[ 3 ] = (void *)CommSerialUnresolve;
	comm->m_ops[ 4 ] = (void *)Rva0081B790;
	comm->m_ops[ 5 ] = (void *)Rva0081B830;
	comm->m_ops[ 6 ] = (void *)Rva0081B910;
	comm->m_ops[ 7 ] = (void *)Rva0081B9B0;
	comm->m_ops[ 8 ] = (void *)CommSerialCallback;
	comm->m_ops[ 9 ] = (void *)Rva0081B9D0;
	comm->m_ops[ 10 ] = (void *)Rva0081BA40;
	comm->m_ops[ 11 ] = (void *)Rva0081BA60;
	comm->m_ops[ 12 ] = (void *)Rva0081BC80;
	comm->m_ops[ 13 ] = (void *)Rva0081BD40;
	_mbscpy( (unsigned char *)comm->m_name, (const unsigned char *)"SERIAL" );
	InitializeCriticalSection( (CRITICAL_SECTION *)comm->m_lock );

	comm->m_recvRecordSize = first + 0x10;
	comm->m_recvBufferSize = comm->m_recvRecordSize * second;
	comm->m_recvBuffer = Rva007F0000Alloc(
		comm->m_recvBufferSize );
	comm->m_sendRecordSize = first + 0x10;
	comm->m_sendBufferSize = comm->m_sendRecordSize * third;
	comm->m_sendBuffer = Rva007F0000Alloc(
		comm->m_sendBufferSize );
	comm->m_field908 = 0;
	comm->m_streamSlot = 0;
	comm->m_streamLength = 0;
	comm->m_streamCapacity = 0x800;
	comm->m_state = 1;
	comm->m_pendingValue = 0;
	comm->m_threadId = GetCurrentThreadId();
	comm->m_handle = -1;
	comm->m_event0 = CreateEventA( 0, 1, 1, 0 );
	comm->m_event1 = CreateEventA( 0, 1, 1, 0 );
	comm->m_event2 = CreateEventA( 0, 1, 1, 0 );
	result = CreateThread( 0, 0, (Rva00819920ThreadProc)d_00819920,
		comm, 0, &pid );
	if( result == 0 )
		return 0;
	SetThreadPriority( result, 2 );
	CloseHandle( result );
	return comm;
}

void CommSerialUnresolve( void )
{
}

void CommSerialCallback( void )
{
}
