// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP= /G7
//
// ?Rva00595C79FormatAddress@@YA?AVAsciiString@@PBURva00595C79Address@@@Z, retail 0x00595c79, 34 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

struct Rva00595C79Address
{
	UnsignedInt m_ip;
	UnsignedShort m_port;
};

AsciiString Rva00595C04FormatIPPort( UnsignedInt ip, UnsignedShort port )
{
	AsciiString str;
	str.format( "%d.%d.%d.%d:%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff, port );
	return str;
}

AsciiString Rva00595C79FormatAddress( const Rva00595C79Address *address )
{
	return Rva00595C04FormatIPPort( address->m_ip, address->m_port );
}

AsciiString Rva00595C9BFormatIP( UnsignedInt ip )
{
	AsciiString str;
	str.format( "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff );
	return str;
}
