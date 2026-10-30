// cl: /Od /GZ /GS /DNDEBUG
// platformsdk
#include <windows.h>
#include <string.h>

struct Rva0081B010Comm
{
	char m_head[ 0x7c ];
	void *m_handle;
	char m_gap80[ 0x10 ];
	void *m_event0;
	char m_gap94[ 0x10 ];
	void *m_event1;
	char m_gapA8[ 0x10 ];
	void *m_event2;
	char m_gapBC[ 0x10 ];
	int m_state;
};

/* Retail calls the serial API through import thunks this repo names
 * Rva01358* (see the pin log); the import verifier maps each slot to its
 * real kernel32 entry.
 * Rva01358CCC=CloseHandle Rva01358CE8=CreateFileA Rva01358D54=GetCommConfig
 * Rva01358D58=GetCommState Rva01358F28=SetupComm Rva01358ED8=SetCommConfig
 * Rva01358EDC=SetCommMask Rva01358EE0=SetCommState Rva01358EE4=SetCommTimeouts
 * Rva01358EB0=PurgeComm Rva01358F0C=SetEvent.  strncpy, strchr and strncmp
 * go through msvcrt's import stubs with a direct e8, so the unit is built
 * without /MD, as a library compiled against the static CRT headers is. */

// g_00E0ABA4: VA 0x00E0ABA4 (.data(bss)); retail initial byte is zero.
char g_00E0ABA4 = 0;

struct Rva0081BD40Comm;
extern "C" void __cdecl Rva0081B700( struct Rva0081BD40Comm *comm );

extern "C" int Rva0081B010( struct Rva0081B010Comm *comm, char *argument )
{
	int baud;
	char device[ 0x20 ];
	COMMTIMEOUTS timeouts;
	char config[ 0x1000 ];
	DCB *dcb;
	char *parse;
	DWORD len;

	baud = 0;
	timeouts.ReadIntervalTimeout = 0xffffffff;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;
	timeouts.WriteTotalTimeoutMultiplier = 0;
	timeouts.WriteTotalTimeoutConstant = 0;
	dcb = (DCB *)( config + 8 );

	if ( argument == 0 && comm->m_state == 4 )
	{
		comm->m_state = 5;
		SetCommMask( comm->m_handle, 2 );
		PurgeComm( comm->m_handle, 0x0f );
		CloseHandle( comm->m_handle );
		comm->m_handle = (void *)-1;
		return 0;
	}

	if ( comm->m_state != 1 && comm->m_state != 5 )
		return -8;

	if ( comm->m_state == 1 )
		Rva0081B700( reinterpret_cast< struct Rva0081BD40Comm * >( comm ) );

	strncpy( device, argument, 0x20 );
	if ( strchr( device, ':' ) != 0 )
	{
		*( strchr( device, ':' ) ) = 0;
		argument = strchr( argument, ':' ) + 1;
	}
	else
	{
		/* Retail's default serial pointer is image-specific: BFME1 has
		 * 0x0130B18C in this slot, BFME2 0x00E0ABA4. Both address their
		 * own image's .data (here LUT-like binary bytes, not a config
		 * string -- no textual default exists in this image), so the
		 * no-colon path parses whatever the link placed there. The BFME2
		 * zero-filled byte is named so it follows the linked image. */
		argument = &g_00E0ABA4;
	}

	if ( strncmp( device, "TAPI", 4 ) == 0 )
	{
		parse = device + 4;
		baud = 0;
		for ( ; *parse >= '0' && *parse <= '9';
			parse++ )
		{
			baud = baud * 10 + ( *parse & 0x0f );
		}
		comm->m_handle = (void *)baud;
	}
	else
	{
		comm->m_handle = CreateFileA( device, 0xc0000000, 0, 0,
			3, 0x40000080, 0 );
		if ( comm->m_handle == (void *)-1 )
			return -4;
	}

	SetupComm( comm->m_handle, 0x2000, 0x1000 );
	SetCommTimeouts( comm->m_handle, &timeouts );
	SetCommMask( comm->m_handle, 2 );

	if ( baud != 0 )
	{
		len = 0x1000;
		GetCommConfig( comm->m_handle, (COMMCONFIG *)config, &len );
		dcb->EvtChar = 0x0a;
		dcb->fBinary = 1;
		dcb->fNull = 0;
		dcb->fOutX = 0;
		dcb->fInX = 0;
		dcb->fAbortOnError = 0;
		SetCommConfig( comm->m_handle, (COMMCONFIG *)config, len );
		goto finish;
	}

	dcb->DCBlength = 0x1c;
	GetCommState( comm->m_handle, dcb );
	dcb->EvtChar = 0x0a;
	dcb->fBinary = 1;
	dcb->fNull = 0;
	dcb->fOutX = 0;
	dcb->fInX = 0;
	dcb->fAbortOnError = 0;
	dcb->ByteSize = 8;
	dcb->fParity = 1;
	dcb->StopBits = ONESTOPBIT;
	dcb->fDsrSensitivity = 0;
	dcb->fOutxDsrFlow = 0;
	dcb->fDtrControl = DTR_CONTROL_ENABLE;

	while ( argument != 0 && *argument != 0 )
	{
		if ( *argument == ',' )
			argument++;

		if ( strncmp( argument, "+RTS", 4 ) == 0 )
			dcb->fRtsControl = RTS_CONTROL_HANDSHAKE;
		if ( strncmp( argument, "-RTS", 4 ) == 0 )
			dcb->fRtsControl = RTS_CONTROL_ENABLE;
		if ( strncmp( argument, "+CTS", 4 ) == 0 )
			dcb->fOutxCtsFlow = 1;
		if ( strncmp( argument, "-CTS", 4 ) == 0 )
			dcb->fOutxCtsFlow = 0;

		if ( *argument >= '0' && *argument <= '9' )
		{
			dcb->BaudRate = 0;
			while ( *argument >= '0' && *argument <= '9' )
			{
				dcb->BaudRate = dcb->BaudRate * 10
					+ ( *argument & 0x0f );
				argument++;
			}
		}

		while ( *argument != ',' && *argument != 0 )
			argument++;
	}

	SetCommState( comm->m_handle, dcb );

finish:
	PurgeComm( comm->m_handle, 0x0c );
	SetEvent( comm->m_event0 );
	SetEvent( comm->m_event1 );
	SetEvent( comm->m_event2 );
	comm->m_state = ( comm->m_state != 5 ) + 4;
	return 0;
}
