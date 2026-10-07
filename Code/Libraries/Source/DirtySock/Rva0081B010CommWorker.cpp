// cl: /Od /GZ /GS /MD /DNDEBUG

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

struct Rva0081B010Dcb
{
	unsigned int m_length;
	unsigned int m_baudRate;
	unsigned int m_flags;
	unsigned short m_reserved;
	unsigned short m_xonLimit;
	unsigned short m_xoffLimit;
	unsigned char m_byteSize;
	unsigned char m_parity;
	unsigned char m_stopBits;
	char m_xonChar;
	char m_xoffChar;
	char m_errorChar;
	char m_eofChar;
	char m_evtChar;
	unsigned short m_reserved1;
};

struct Rva0081B010Timeouts
{
	unsigned int m_readInterval;
	unsigned int m_readMultiplier;
	unsigned int m_readConstant;
	unsigned int m_writeMultiplier;
	unsigned int m_writeConstant;
};

/* Retail calls the serial API through import thunks this repo names
 * Rva01358* (see the pin log); the import verifier maps each slot to its
 * real kernel32 entry, so the declarations below use the real names.
 * Rva01358CCC=CloseHandle Rva01358CE8=CreateFileA Rva01358D54=GetCommConfig
 * Rva01358D58=GetCommState Rva01358F28=SetupComm Rva01358ED8=SetCommConfig
 * Rva01358EDC=SetCommMask Rva01358EE0=SetCommState Rva01358EE4=SetCommTimeouts
 * Rva01358EB0=PurgeComm Rva01358F0C=SetEvent. */
extern "C" {
__declspec(dllimport) int __stdcall CloseHandle( void *handle );
__declspec(dllimport) void *__stdcall CreateFileA( const char *name,
	unsigned int desiredAccess, unsigned int shareMode, void *security,
	unsigned int creation, unsigned int flags, void *templateHandle );
__declspec(dllimport) int __stdcall GetCommConfig( void *handle, void *config,
	unsigned int *size );
__declspec(dllimport) int __stdcall GetCommState( void *handle,
	struct Rva0081B010Dcb *dcb );
__declspec(dllimport) int __stdcall SetupComm( void *handle,
	unsigned int inQueue, unsigned int outQueue );
__declspec(dllimport) int __stdcall SetCommConfig( void *handle, void *config,
	unsigned int size );
__declspec(dllimport) int __stdcall SetCommMask( void *handle,
	unsigned int mask );
__declspec(dllimport) int __stdcall SetCommState( void *handle,
	struct Rva0081B010Dcb *dcb );
__declspec(dllimport) int __stdcall SetCommTimeouts( void *handle,
	struct Rva0081B010Timeouts *timeouts );
__declspec(dllimport) int __stdcall PurgeComm( void *handle,
	unsigned int flags );
__declspec(dllimport) int __stdcall SetEvent( void *eventHandle );

char *__cdecl strncpy( char *destination, const char *source,
	unsigned int count );
char *__cdecl strchr( const char *string, int character );
int __cdecl strncmp( const char *left, const char *right,
	unsigned int count );
}

// g_00E0ABA4: VA 0x00E0ABA4 (.data(bss)); retail initial byte is zero.
char g_00E0ABA4 = 0;

struct Rva0081BD40Comm;
extern "C" void __cdecl Rva0081B700( struct Rva0081BD40Comm *comm );

extern "C" int Rva0081B010( struct Rva0081B010Comm *comm, char *argument )
{
	int baud;
	char device[ 0x20 ];
	struct Rva0081B010Timeouts timeouts;
	char config[ 0x1000 ];
	struct Rva0081B010Dcb *dcb;
	char *parse;
	unsigned int len;

	baud = 0;
	timeouts.m_readInterval = 0xffffffff;
	timeouts.m_readMultiplier = 0;
	timeouts.m_readConstant = 0;
	timeouts.m_writeMultiplier = 0;
	timeouts.m_writeConstant = 0;
	dcb = (struct Rva0081B010Dcb *)( config + 8 );

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
		GetCommConfig( comm->m_handle, config, &len );
		dcb->m_evtChar = 0x0a;
		dcb->m_flags = dcb->m_flags | 1;
		dcb->m_flags = dcb->m_flags & 0xfffff7ff;
		dcb->m_flags = dcb->m_flags & 0xfffffeff;
		dcb->m_flags = dcb->m_flags & 0xfffffdff;
		dcb->m_flags = dcb->m_flags & 0xffffbfff;
		SetCommConfig( comm->m_handle, config, len );
		goto finish;
	}

	dcb->m_length = 0x1c;
	GetCommState( comm->m_handle, dcb );
	dcb->m_evtChar = 0x0a;
	dcb->m_flags = dcb->m_flags | 1;
	dcb->m_flags = dcb->m_flags & 0xfffff7ff;
	dcb->m_flags = dcb->m_flags & 0xfffffeff;
	dcb->m_flags = dcb->m_flags & 0xfffffdff;
	dcb->m_flags = dcb->m_flags & 0xffffbfff;
	dcb->m_byteSize = 8;
	dcb->m_flags = dcb->m_flags | 2;
	dcb->m_stopBits = 0;
	dcb->m_flags = dcb->m_flags & 0xffffffbf;
	dcb->m_flags = dcb->m_flags & 0xfffffff7;
	dcb->m_flags = ( dcb->m_flags & 0xffffffcf ) | 0x10;

	while ( argument != 0 && *argument != 0 )
	{
		if ( *argument == ',' )
			argument++;

		if ( strncmp( argument, "+RTS", 4 ) == 0 )
			dcb->m_flags = ( dcb->m_flags & 0xffffcfff ) | 0x2000;
		if ( strncmp( argument, "-RTS", 4 ) == 0 )
			dcb->m_flags = ( dcb->m_flags & 0xffffcfff ) | 0x1000;
		if ( strncmp( argument, "+CTS", 4 ) == 0 )
			dcb->m_flags = dcb->m_flags | 4;
		if ( strncmp( argument, "-CTS", 4 ) == 0 )
			dcb->m_flags = dcb->m_flags & 0xfffffffb;

		if ( *argument >= '0' && *argument <= '9' )
		{
			dcb->m_baudRate = 0;
			while ( *argument >= '0' && *argument <= '9' )
			{
				dcb->m_baudRate = dcb->m_baudRate * 10
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
