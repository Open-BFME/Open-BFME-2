// cl: /Ireference/shims/bfme2_ascii /O1 /GX /MD /D_CRTIMP=
//
// Two BFME 2-only dotted-address formatters with address names (no ZH or
// BFME 1 counterpart, no direct callers found): 0x00595C04 (117B) returns
// "%d.%d.%d.%d:%d" of an address and a 16-bit port, 0x00595C9B (112B)
// "%d.%d.%d.%d" of an address. Target evidence: by-value AsciiString return
// through the rowed format 0x00038150 and copy ctor 0x000365F0, octets
// pushed low to high from shr 0x18 / byte 2 / ah / and 0xff, port by
// movzx word; the ":%d" literal sits at 0x00C70A30, right after the
// FirewallHelperClass vftable 0x00C70A2C, so these belong to that unit.
// The 34-byte wrapper 0x00595C79 that feeds 0x00595C04 from an {ip, port}
// record is banked (it pushes the port without zero-extension).
#include "ascii_string.h"

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;

AsciiString Rva00595C04FormatIPPort( UnsignedInt ip, UnsignedShort port )
{
	AsciiString str;
	str.format( "%d.%d.%d.%d:%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff, port );
	return str;
}

AsciiString Rva00595C9BFormatIP( UnsignedInt ip )
{
	AsciiString str;
	str.format( "%d.%d.%d.%d", ip >> 24, (ip >> 16) & 0xff, (ip >> 8) & 0xff, ip & 0xff );
	return str;
}
