// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007AE680Name.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?setName@Rva007AE680Name@@QAEXPBD@Z 0x00108596 (30B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

extern "C" __declspec(dllimport) char *__cdecl strncpy( char *destination, const char *source,
	unsigned int count );

class Rva007AE680Name
{
public:
	void setName( const char *name );

private:
	unsigned char m_pad0[0x10];
	char m_name[32];
};

void Rva007AE680Name::setName( const char *name )
{
	strncpy( m_name, name, 31 );
	m_name[31] = 0;
}
