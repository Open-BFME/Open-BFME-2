// cl: /O1 /G7 /MD /EHsc /Ireference/shims/bfme2_ascii
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24:
// game/GameEngine/Source/GameLogic/LivingWorld/ParseEnableRegion.cpp.
// Target4E1579/129 has the same null guards, exception text and registration
// purpose. Its FieldParse callback entry is named EnableRegion; the record
// table at VA C61A50 is Region / INI::parseAsciiString / null / offset4.
// The local eight-byte record has a vptr at0 and owned AsciiString at4.
// C61A20 is the already-defined Rva004E156B vtable: its only entry routes
// through rowed scalar deleter4E1BC4 and string-record destructor4E156B.
// This novtable view restores that proven table explicitly and owns cleanup
// through the verified canonical releaseBuffer provider; no new vtable or type identity is
// asserted. The address-named cleanup view is only its one-pointer call ABI.
// It avoids emitting an AsciiString deleting COMDAT that native bytes refute.
// The member is opaque storage to preserve the native constructor
// and destructor store order. Inline helper copies claim no recovery bytes.
// Native4E15B8 calls the rowed8B helper566527 with this record by reference;
// that helper adds8 to the owner and tails to rowed vector append56225E.
// The append ABI alias binds precisely that observed call. FXList is the
// existing provider's spelling; this parser does not assert an FXList identity
// for its Region record. Owner/type names retain their target addresses.
// Ghidra confirms129B; next byte is int3 padding before start4E15FB. MSVC's
// emitted130th byte is that same padding, not extra function code.
class Rva004E1579StringCleanup { void *data; public: void release(); };
#pragma comment(linker, "/alternatename:?release@Rva004E1579StringCleanup@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
class INI;
typedef void (__cdecl *ParseFunc)(INI *, void *, void *, const void *);
struct FieldParse { const char *token; ParseFunc parse; const void *data; int offset; };
class INI { public: void initFromINI(void *, const FieldParse *); static void parseAsciiString(INI *, void *, void *, const void *); };
class INIException { public: char *mFailureMessage; int m_argCount; INIException(int, const char *, ...); INIException(const INIException &); ~INIException(); };
extern "C" const void *const vtbl_00C61A20[];
#pragma comment(linker, "/alternatename:_vtbl_00C61A20=??_7Rva004E156B@@6B@")
class __declspec(novtable) Rva004E1579RegionRecord {
public:
 // ??0Rva004E1579RegionRecord@@QAE@XZ present-unmatched
 Rva004E1579RegionRecord() { *(const void *const **)this=vtbl_00C61A20; regionData=0; }
 // ??1Rva004E1579RegionRecord@@UAE@XZ present-unmatched
 virtual ~Rva004E1579RegionRecord() { *(const void *const **)this=vtbl_00C61A20; ((Rva004E1579StringCleanup *)&regionData)->release(); }
private: void *regionData;
};
static const FieldParse regionFields[]={{"Region", INI::parseAsciiString,0,4},{0,0,0,0}};
class Rva004E1579RegionOwner { public: void append(const Rva004E1579RegionRecord &); };
#pragma comment(linker, "/alternatename:?append@Rva004E1579RegionOwner@@QAEXABVRva004E1579RegionRecord@@@Z=?rva00566527@Rva00566527@@QAEXABVFXList@@@Z")
void Rva004E1579ParseEnableRegion(INI *ini, void *instance, void *, const void *)
{
 if(ini && instance) {
  Rva004E1579RegionRecord record;
  ini->initFromINI(&record,regionFields);
  ((Rva004E1579RegionOwner *)instance)->append(record);
 } else throw INIException(3,"ParseEnableRegion::Invalid data passed in.");
}
