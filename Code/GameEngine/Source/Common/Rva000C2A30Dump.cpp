// cl: /DNDEBUG /MD
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva000C2A30Dump.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva000C2A30Owner::dump 0x00200A01 (100B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Retail RVA 0x000C2A30. Formats the owner's name and each string in the
// vector at +8 into a stack buffer with "%s %s\n" and hands the buffer to the
// imported reporting call. Nothing names the owner, so it is address-derived.

extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA( void *text );

extern "C" __declspec(dllimport) int __cdecl sprintf( char *, const char *, ... );

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// class-gate: allow AsciiString the donor's own view; the placed bodies are byte-exact under it
class AsciiString
{
public:
	const char *str() const
	{
		return m_bfmeData ? m_bfmeData->m_bfmeChars : "";
	}

	struct Header
	{
		int m_bfmeRefCount;
		unsigned short m_bfmeLength;
		unsigned short m_bfmeCapacity;
		char m_bfmeChars[ 1 ];
	};

	Header *m_bfmeData;
};

class Rva000C2A30Owner
{
public:
	void dump();

	AsciiString m_bfmeName;
	unsigned char m_bfmePad004[ 4 ];
	AsciiString *m_bfmeFirst;
	AsciiString *m_bfmeLast;
};

void Rva000C2A30Owner::dump()
{
	for( AsciiString *entry = m_bfmeFirst; entry != m_bfmeLast; ++entry )
	{
		char buffer[ 0x100 ];

		sprintf( buffer, "%s %s\n", m_bfmeName.str(), entry->str() );
		OutputDebugStringA( buffer );
	}
}
