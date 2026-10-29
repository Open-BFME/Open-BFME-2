// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport46
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);
#include "ascii_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t);
template <> void vector<AsciiString, allocator<AsciiString> >::push_back(const AsciiString&);
template <> AsciiString *vector<AsciiString, allocator<AsciiString> >::erase(AsciiString*, AsciiString*);
template <> void vector<AsciiString, allocator<AsciiString> >::_M_insert_overflow(AsciiString*, const AsciiString&, const __false_type&, size_t, bool);
}

// WorldBuilder10802C0 names SplitString/CreateAHeroHero.cpp1243;
// target40952C169 has vectorAsciiString output and AsciiString input.
static int SplitString(_STL::vector<AsciiString> &out, const AsciiString &text, const char *delimiters)
{
 char *buffer=(char *)_alloca(text.getLength()+1);
 out.erase(out.begin(),out.end());
 _mbscpy((unsigned char *)buffer,(const unsigned char *)text.str());
 char *token=strtok(buffer,delimiters);
 while(token) {
  out.push_back(AsciiString(token));
  token=strtok(0,delimiters);
 }
 return out.size();
}

// Native4095D5 and WB10800C0 locate an executable in semicolon-delimited PATH.
bool Rva004095D5(AsciiString &path, const AsciiString &exeName)
{
 _STL::vector<AsciiString> directories;
 AsciiString environment(getenv("PATH"));
 SplitString(directories,environment,";");
 for (_STL::vector<AsciiString>::iterator it=directories.begin();it!=directories.end();++it) {
  AsciiString candidate=*it;
  char last=0;
  if (!candidate.isEmpty()) last=candidate.str()[candidate.getLength()-1];
  if (last!='\\' && last!='/') candidate+="\\";
  candidate+=exeName;
  if (_access(candidate.str(),0)==0) { path=candidate; return true; }
 }
 return false;
}

bool ExecuteCommand(const AsciiString &exePath, const AsciiString &arguments);

bool Rva004096E6(const AsciiString &fileName)
{
	AsciiString exeName("p4.exe");
	AsciiString arguments("edit ");
	AsciiString exePath;
	arguments += fileName;

	if (!Rva004095D5(exePath, exeName))
		return false;
	if (!ExecuteCommand(exePath, arguments))
		return false;

	arguments = "add ";
	arguments += fileName;
	if (!ExecuteCommand(exePath, arguments))
		return false;

	return true;
}
