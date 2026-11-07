// stlport
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// Native [41FD3D,41FDDE), cdecl parser. Owned MeshInstancingManager ctor
// puts its table at +10 and stores the singleton at E03134. Retail uppercases
// the token, parses the one Instances field into the mapped int, and inserts
// a const-key copy. Original parser name remains unknown.
#include "ascii_string.h"
#include <utility>
class INI;
#include "../../../Include/Common/INI/FieldParse.h"
#include "../../../Include/Common/INI/INI.h"
static const FieldParse fields[]={ {"Instances",INI::parseInt,0,0},{0,0,0,0} };
struct InsertRet0041FA92 {void *node;void *owner;unsigned char found;};
class Rva000427195 { public: InsertRet0041FA92 rva0041FC77(const void*); __forceinline void insertOne(const void *value) { rva0041FC77(value); } };
class Rva0041FB13;extern Rva0041FB13 *TheMeshInstancingManager;
struct Rva0041FD3DManagerView {char prefix[16];Rva000427195 table;};
struct NoCaseTreeValue4 {char body[4];};
// Retail inlines the pair default ctor and has no out-of-line copy; another
// unit's copy is first in link order, so dllimport keeps this one inline-only.
namespace _STL { template <> __declspec(dllimport) __forceinline pair<const AsciiString,NoCaseTreeValue4>::pair() : first(AsciiString()), second(NoCaseTreeValue4()) {} }
void parseMeshNameMatchesDefinition(INI *ini)
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

// INI block registration (LINK-236). Each unit links its own 12-byte BlockParse nodes onto
// theBlockParseList from a file-scope object whose inline constructor does the link; MSVC 7.1
// builds token and parse in .data, so the node's .text$yc initializer is only the 21-byte link
// (retail .CRT$XCU 0x007B01FD, node 0x00DC8430). It is the last entry before its run's pool-init marker 0x007B0212,
// so it is the marker unit's own node, not a marker-less INI wrapper's; this file defines its
// callback.
typedef void (*INIBlockParse)( INI *ini );
extern struct BlockParse *theBlockParseList;
struct BlockParse
{
	BlockParse *next;
	const char *token;
	INIBlockParse parse;

	BlockParse( const char *token, INIBlockParse parse ) : next(theBlockParseList), token(token), parse(parse)
	{
		theBlockParseList = this;
	}
};

BlockParse theMeshNameMatchesBlockParse( "MeshNameMatches", parseMeshNameMatchesDefinition );
