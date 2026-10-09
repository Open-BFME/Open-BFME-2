// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX- /Oy-
// Native285FA9 parses an indexed24B terrain-material entry at instance+10.
// The named INI token/table/exception providers and retail Color/Name/Fuel/
// MaxBurnRate/Decay/Resistance descriptors establish field-parser purpose.
// A normal local static aggregate owns its compiler-generated lazy guard.
class INI;
typedef void (*INIFieldParseProc)(INI *,void *,void *,const void *);
struct FieldParse {
 const char *token;
 INIFieldParseProc parser;
 const void *userData;
 int offset;
};
class INI {
public:
 const char *getNextToken(const char *);
 void initFromINI(void *,const FieldParse *);
 static void parseColorInt(INI *,void *,void *,const void *);
 static void parseAsciiString(INI *,void *,void *,const void *);
 static void parseUnsignedInt(INI *,void *,void *,const void *);
};
class INIException {
public:
 INIException(int,const char *,...);
 INIException(const INIException &);
 ~INIException();
 char *message;
 int errorCode;
};
extern "C" __declspec(dllimport) int __cdecl atoi(const char *);
static inline const void *materialMask(unsigned mask) { return reinterpret_cast<const void *>(mask); }
void Rva00285FA9Parse(INI *ini,void *,void *store,const void *) {
 const char *token=ini->getNextToken(0);
 if(!token) throw INIException(3,"TerrainCellType index expected.");
 int index=atoi(token);
 if(index<0 || index>=4) throw INIException(3,"TerrainCellType index out of valid range.");
 static const FieldParse fields[]={
  {"Color",INI::parseColorInt,0,0},
  {"Name",INI::parseAsciiString,0,4},
  {"Fuel",INI::parseUnsignedInt,materialMask(0xffff),8},
  {"MaxBurnRate",INI::parseUnsignedInt,materialMask(0xfff),12},
  {"Decay",INI::parseUnsignedInt,materialMask(0x3ff),16},
  {"Resistance",INI::parseUnsignedInt,materialMask(0xff),20},
  {0,0,0,0}
 };
 ini->initFromINI((char *)store+0x10+index*24,fields);
}
