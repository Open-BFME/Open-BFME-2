// ?Rva004128F0GetParam@@YA_NPBD0AAVAsciiString@@@Z
// partial score=0.9465732888819278 date=2026-10-09
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

bool __cdecl Rva004128F0GetParam(const char *input, const char *key, AsciiString &value)
{
 if (!input || !*input || !key || !*key) return false;
 int keyLen = strlen(key);
 const char *params = input;
 const char *entry;
 const char *after;
 bool match;
 goto next;
compare:
 if (strncmp(entry,key,keyLen)==0 &&
     (after=entry+keyLen, Rva00412689SkipSpaces(&after), *after=='='))
  match=true;
 else
  match=false;
equals:
 while (*entry) {
  char c = *entry;
  ++entry;
  params = entry;
  if (c == '=') break;
 }
 Rva00412689SkipSpaces(&params);
 if (match) {
  const char *start = params;
  while (*params && *params != '&') ++params;
  if (params == start) value.clear();
  else ((StringBase<char> *)&value)->set(start,params-start);
  return true;
 }
 while (*params) {
  char c = *params;
  ++*reinterpret_cast<const char *volatile *>(&params);
  if (c == '&') break;
 }
next:
 Rva00412689SkipSpaces(&params);
 entry = params;
 if (*entry) goto compare;
 return false;
}
