// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
#include <malloc.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>
extern "C" unsigned char *__cdecl _mbscpy(unsigned char *,const unsigned char *);
#include "ascii_string.h"

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

bool Rva00407AF9Run(const AsciiString &exePath, const AsciiString &arguments);

bool Rva004096E6(const AsciiString &fileName)
{
	AsciiString exeName("p4.exe");
	AsciiString arguments("edit ");
	AsciiString exePath;
	arguments += fileName;

	if (!Rva004095D5(exePath, exeName))
		return false;
	if (!Rva00407AF9Run(exePath, arguments))
		return false;

	arguments = "add ";
	arguments += fileName;
	if (!Rva00407AF9Run(exePath, arguments))
		return false;

	return true;
}
