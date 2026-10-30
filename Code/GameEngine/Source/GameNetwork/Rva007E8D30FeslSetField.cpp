// cl: /GS
// 0x007E8D30: the FESL message TU's private copy of the escaped string-field
// writer (compare the DirtySock copy Rva007ECE60 at 0x007ECE60).  It is a
// file-static helper whose only caller, 0x007E8EF0, hands it the field name in
// ECX and the value in EAX: MSVC's private register convention for a static
// function, reproduced here by compiling it with that caller.

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate( int size, int flags );
	virtual void release( void *block, int flags );
};

class GenAlloc; GenAlloc *Gen007EFFC0();

// 0x007EC030: deletes the named field from the record.
int Rva007EC030( char *text, const char *tag );

// Retail 0x00655B90: replaces or appends a record field. The placeholder
// spelling is inherited from the independently matched DirtySock donor.
int Rva007E8B00( unsigned char *buffer, int size, const char *field );

// g_Rva011293A0HexFirst: matched references place it at VA 0xce0c10; retail contents, sized to the
// 0x108-byte gap before the next known global there.
char g_Rva011293A0HexFirst[264] = {
	48, 48, 48, 48, 48, 48, 48, 48,
	48, 48, 48, 48, 48, 48, 48, 48,
	49, 49, 49, 49, 49, 49, 49, 49,
	49, 49, 49, 49, 49, 49, 49, 49,
	50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50,
	51, 51, 51, 51, 51, 51, 51, 51,
	51, 51, 51, 51, 51, 51, 51, 51,
	52, 52, 52, 52, 52, 52, 52, 52,
	52, 52, 52, 52, 52, 52, 52, 52,
	53, 53, 53, 53, 53, 53, 53, 53,
	53, 53, 53, 53, 53, 53, 53, 53,
	54, 54, 54, 54, 54, 54, 54, 54,
	54, 54, 54, 54, 54, 54, 54, 54,
	55, 55, 55, 55, 55, 55, 55, 55,
	55, 55, 55, 55, 55, 55, 55, 55,
	56, 56, 56, 56, 56, 56, 56, 56,
	56, 56, 56, 56, 56, 56, 56, 56,
	57, 57, 57, 57, 57, 57, 57, 57,
	57, 57, 57, 57, 57, 57, 57, 57,
	97, 97, 97, 97, 97, 97, 97, 97,
	97, 97, 97, 97, 97, 97, 97, 97,
	98, 98, 98, 98, 98, 98, 98, 98,
	98, 98, 98, 98, 98, 98, 98, 98,
	99, 99, 99, 99, 99, 99, 99, 99,
	99, 99, 99, 99, 99, 99, 99, 99,
	100, 100, 100, 100, 100, 100, 100, 100,
	100, 100, 100, 100, 100, 100, 100, 100,
	101, 101, 101, 101, 101, 101, 101, 101,
	101, 101, 101, 101, 101, 101, 101, 101,
	102, 102, 102, 102, 102, 102, 102, 102,
	102, 102, 102, 102, 102, 102, 102, 102,
	0, 0, 0, 0, 0, 0, 0, 0,
};
// g_Rva011294A8HexSecond: matched references place it at VA 0xce0d18 (.rdata); retail bytes.
char g_Rva011294A8HexSecond[256] = {
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66,
};


// g_bfmeFeslFieldClassTable: FESL record-field name class table, retail VA
// 0xce0e20 (256 bytes, .rdata) directly after g_Rva011294A8HexSecond. Every
// consumer is the FESL record-field replacer Rva007E8B00 (0x00655b90): it
// compares record and field characters by table class (0 = invalid/end, 1 =
// field separator ':' or '=', >=2 = the upper-cased character value, so
// 'a'-'z' fold to 'A'-'Z' and digits/underscore stay). Values read from
// retail; the BFME 1 copy names it Rva007E8B00ClassTable (no EA identifier
// recovered), so this is a neutral descriptive name.
extern const unsigned char g_feslFieldClassTable[256] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
	0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x5f,
	0x00, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

// g_bfmeFeslFieldSeparator: the '\n' appended after a replaced field by the
// same FESL record-field replacer (retail .data byte 0x00dd7f45 = 0x0A,
// between the "or@@" literal run and the 0x009d7f48 pointer table); BFME 1's
// bank calls the same byte Rva007E8B00Separator and compares it with '\n'.
char g_feslFieldSeparator = '\n';

#include <string.h>

// Complete 549-byte FESL copy of the DirtySock Y4TextToValue.c donor.
// Keep the final equivalent clear paths and the volatile separator read;
// see reverse/attempt_support/fesl-655b90-recovery-20261022/readme.md.
int Rva007E8B00( unsigned char *buffer, int size, const char *field )
{
	int i;
	int iDelta;
	unsigned char *recordCursor;
	unsigned char *pValue;
	unsigned char *pTail;
	unsigned char cClassBuffer;
	unsigned char cClassField;
	unsigned char *pBuffer;

	pBuffer = buffer;

	if ( pBuffer == 0 )
	{
		return -1;
	}

	if ( field == 0 || (unsigned int)*field <= ' ' )
	{
		return -1;
	}

	if ( *field == '~' )
	{
		for ( recordCursor = pBuffer; *recordCursor != 0; recordCursor++ )
		{
		}

		if ( recordCursor != pBuffer && recordCursor[ -1 ] >= ' '
			&& recordCursor[ -1 ] != g_feslFieldSeparator
			&& recordCursor < pBuffer + size - 1 )
		{
			*recordCursor = g_feslFieldSeparator;
			recordCursor++;
			*recordCursor = 0;
		}

		pTail = recordCursor;
		pValue = pTail;
	}
	else
	{
		recordCursor = pBuffer;

		for ( ;; )
		{
			if ( *recordCursor == 0 )
			{
				if ( recordCursor != pBuffer && recordCursor[ -1 ] >= ' '
					&& recordCursor[ -1 ] != g_feslFieldSeparator
					&& recordCursor < pBuffer + size - 1 )
				{
					*recordCursor = g_feslFieldSeparator;
					recordCursor++;
					*recordCursor = 0;
				}

				pTail = recordCursor;
				pValue = pTail;
				break;
			}

			if ( *recordCursor <= ' ' )
			{
				recordCursor++;
				continue;
			}

			if ( g_feslFieldClassTable[ *recordCursor ] == 1 )
			{
				pTail = recordCursor;
				pValue = pTail;
				break;
			}

			for ( i = 0; ; i++ )
			{
				cClassBuffer = g_feslFieldClassTable[ recordCursor[ i ] ];
				cClassField = g_feslFieldClassTable[ (unsigned char)field[ i ] ];

				if ( cClassBuffer != cClassField || cClassBuffer < 2 )
				{
					break;
				}
			}

			if ( cClassBuffer + cClassField == 2 )
			{
				pTail = recordCursor;
				pValue = pTail;

				for ( ; *pTail >= ' '; pTail++ )
				{
				}

				if ( *pTail > 0 )
				{
					pTail++;
				}

				break;
			}

			do
			{
				recordCursor++;
			}
			while ( *recordCursor >= ' ' );
		}
	}

	for ( i = 0; (unsigned int)field[ i ] >= ' '; i++ )
	{
	}
	i++;

	iDelta = i - ( pTail - pValue );

	for ( recordCursor = pTail; *recordCursor != 0; recordCursor++ )
	{
	}

	recordCursor++;

	if ( iDelta > 0 && pBuffer + size - recordCursor < iDelta )
	{
		return -1;
	}

	if ( iDelta == 0 && memcmp( pValue, field, i ) == 0 )
	{
		return 0;
	}

	if ( iDelta > 0 )
	{
		memmove( pTail + iDelta, pTail, recordCursor - pTail );
	}

	if ( iDelta < 0 )
	{
		memmove( pValue, pValue - iDelta, recordCursor - ( pValue - iDelta ) );
	}

	memcpy( pValue, field, i );

	if ( pValue[ i ] == 0 && g_feslFieldSeparator != '\n' )
	{
		// Equivalent paths retain the allocation weights needed by VC7.1.
		// Their merged store gives retail's late EBP save and EBX value pointer.
		if ( i > 0 )
			goto clearPositive;
		pValue[ i - 1 ] = 0;
		goto clearDone;
clearPositive:
		pValue[ i - 1 ] = 0;
clearDone:
		;
	}
	else
	{
		pValue[ i - 1 ] = *(volatile char *)&g_feslFieldSeparator;
	}

	return i - 1;
}

// The record's "name=" prefix, as the DirtySock copy's Rva007EC730 writes it:
// a null name empties the record instead.
static char *Rva007E8D30Name( char *empty, char *dest, const char *src )
{
	if( src == 0 )
	{
		*empty = 0;
	}
	else
	{
		while( *src != 0 )
		{
			*dest = *src;
			dest++;
			src++;
		}

		*dest = '=';
		dest++;
	}

	return dest;
}

static int Rva007E8D30( const char *name, const char *value, char *record, int size )
{
	char *item;
	char *outputCursor;
	const unsigned char *pScan;
	const unsigned char *pSrc;
	unsigned int iLeft;
	int iResult;

	item = ( char * )( ( Rva007EFFC0Allocator * )((void *)Gen007EFFC0()) )->allocate( 0x32200, 2 );
	pSrc = ( const unsigned char * )value;

	if( pSrc == 0 )
	{
		Rva007EC030( record, name );
		return 0;
	}

	outputCursor = Rva007E8D30Name( record, item, name );

	// Retail starts the unsigned budget at 4 (add esi,4): sizeof the item
	// POINTER, so it wraps and never limits the 0x32200-byte block.
	iLeft = sizeof( item );
	iLeft -= outputCursor - item;

	for( pScan = pSrc; *pScan != 0 && *pScan != ' '; pScan++ )
	{
	}

	if( *pScan == ' ' )
	{
		*outputCursor = '"';
		outputCursor++;
		iLeft--;
	}

	for( ; *pSrc != 0 && iLeft > 0; pSrc++ )
	{
		if( *pSrc < ' ' || *pSrc == 0x7F || *pSrc == '=' || *pSrc == '"'
			|| *pSrc == ':' || *pSrc == '%' || *pSrc == '^' )
		{
			if( iLeft >= 3 )
			{
				*outputCursor = '%';
				outputCursor++;
				*outputCursor = g_Rva011293A0HexFirst[ *pSrc ];
				outputCursor++;
				*outputCursor = g_Rva011294A8HexSecond[ *pSrc ];
				outputCursor++;
			}

			iLeft -= 3;
		}
		else
		{
			*outputCursor = *pSrc;
			outputCursor++;
			iLeft--;
		}
	}

	if( iLeft <= 0 )
	{
		return -1;
	}

	if( *pScan == ' ' )
	{
		*outputCursor = '"';
		outputCursor++;
	}

	*outputCursor = 0;

	iResult = Rva007E8B00( (unsigned char *)record, size, item );
	( ( Rva007EFFC0Allocator * )((void *)Gen007EFFC0()) )->release( item, 0 );
	return iResult;
}

// 0x007E8EF0, the helper's only caller: stores the escaped field into the
// message record at +0x10 (size +0x14) and records -100 at +0x24 on failure.
class Rva007E8810Message
{
public:
	void rva007E8EF0( const char *key, const char *value );

private:
	char m_pad[0x10];
	char *m_10;
	int m_14;
	char m_pad18[0x0c];
	int m_24;
};

void Rva007E8810Message::rva007E8EF0( const char *key, const char *value )
{
	if( Rva007E8D30( key, value, m_10, m_14 ) < 0 )
		m_24 = -100;
}
