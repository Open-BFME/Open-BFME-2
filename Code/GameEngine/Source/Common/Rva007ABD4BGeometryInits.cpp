// cl: /O1 /MD
// Dynamic initializers of two file-scope GeometryInfo objects, each a small
// sphere of one radius, registered for destruction with atexit. Target
// evidence: game.dat's __xc_a table points at 0x007ABD4B and 0x007ABD79; each
// loads one float constant (30.0f at 0x00BC4EB4, 5.0f at 0x00BC4EB8), stores
// it into all three float arguments, pushes isSmall 1 and type 0, calls the
// rowed ??0GeometryInfo@@QAE@W4GeometryType@@_NMMM@Z (0x00050B74) on
// 0x00DE1D00 / 0x00DE1D60 and registers the matched atexit thunk that runs
// GeometryInfo's destructor on the same global. GEOMETRY_SPHERE as type 0
// follows the donor enum. The owning TU and the globals' names are not
// established; the RVA names stand in for them.
extern "C" int __cdecl atexit( void ( __cdecl * )( void ) );

enum GeometryType
{
	GEOMETRY_SPHERE = 0
};

class GeometryInfo
{
public:
	GeometryInfo( GeometryType type, bool isSmall, float height, float majorRadius, float minorRadius );
};

void __cdecl rva007B6B19();
void __cdecl rva007B6B23();

extern unsigned g_Va00DE1D00;
extern unsigned g_Va00DE1D60;

struct Rva007ABD4BGeometryInits
{
	static void __cdecl rva007ABD4B();
	static void __cdecl rva007ABD79();
};

void __cdecl Rva007ABD4BGeometryInits::rva007ABD4B()
{
	( (GeometryInfo *)&g_Va00DE1D00 )->GeometryInfo::GeometryInfo( GEOMETRY_SPHERE, true, 30.0f, 30.0f, 30.0f );
	atexit( rva007B6B19 );
}

void __cdecl Rva007ABD4BGeometryInits::rva007ABD79()
{
	( (GeometryInfo *)&g_Va00DE1D60 )->GeometryInfo::GeometryInfo( GEOMETRY_SPHERE, true, 5.0f, 5.0f, 5.0f );
	atexit( rva007B6B23 );
}
