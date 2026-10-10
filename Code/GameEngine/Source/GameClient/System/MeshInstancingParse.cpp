// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native [41FD3D,41FDDE), cdecl parser. Owned MeshInstancingManager ctor
// puts its table at +10 and stores the singleton at E03134. Retail uppercases
// the token, parses the one Instances field into the mapped int, and inserts
// a const-key copy. Original parser name remains unknown.
#include "ascii_string.h"
#include <utility>
class INI;
struct FieldParse {const char *name;void (*parse)(INI*,void*,void*,const void*);int offset;const void *data;};
class INI {public: const char *getNextToken(const char *seps=0);void initFromINI(void*,const FieldParse*);static void parseInt(INI*,void*,void*,const void*);};
static const FieldParse fields[]={ {"Instances",INI::parseInt,0,0},{0,0,0,0} };
struct InsertRet0041FA92 {void *node;void *owner;unsigned char found;};
class Rva000427195 { public: InsertRet0041FA92 rva0041FC77(const void*); __forceinline void insertOne(const void *value) { rva0041FC77(value); } };
class Rva0041FB13;extern Rva0041FB13 *TheMeshInstancingManager;
struct Rva0041FD3DManagerView {char prefix[16];Rva000427195 table;};
struct NoCaseTreeValue4 {char body[4];};
void Rva0041FD3DParse(INI *ini)
{
 if(TheMeshInstancingManager) {
  _STL::pair<const AsciiString,NoCaseTreeValue4> value;
  reinterpret_cast<StringBase<char> *>(&value)->set(ini->getNextToken());
  reinterpret_cast<StringBase<char> *>(&value)->toUpper();
  ini->initFromINI(&value.second,fields);
  _STL::pair<const AsciiString,NoCaseTreeValue4> key(value);
  reinterpret_cast<Rva0041FD3DManagerView *>(TheMeshInstancingManager)->table.insertOne(&key);
 }
}
