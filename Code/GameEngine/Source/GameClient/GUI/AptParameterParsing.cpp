// cl: /O1 /Ob0 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <ctype.h>
#include <string.h>
// Native whole helper00412689..004126A6: initial jump over loop,
// signed char isspace IAT predicate and increment through cursor pointer.
// All three caller sites use ESI; static C++ naturally selects that private ABI.
static void Rva00412689SkipSpaces(const char **p)
{
 while (**p && isspace(**p)) ++*p;
}
// Native57B [004126D4,0041270D): prefix comparison, then whitespace,
// then '=' delimiter. Caller argument and call site establish the ABI;
// no WorldBuilder name is available for this helper.
bool Rva004126D4(const char *input, const char *key, int keyLen)
{
 if (strncmp(input,key,keyLen)==0) {
  input += keyLen;
  Rva00412689SkipSpaces(&input);
  if (*input == '=') return true;
 }
 return false;
}
