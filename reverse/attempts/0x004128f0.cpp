// ?Rva004128F0GetParam@@YA_NPBD0AAVAsciiString@@@Z
// partial score=0.6 date=2026-10-08
// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <ctype.h>
#include <string.h>
static void skipSpaces(const char **p)
{
 while (**p && isspace(**p)) ++*p;
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
     (after=entry+keyLen, skipSpaces(&after), *after=='='))
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
 skipSpaces(&params);
 if (match) {
  const char *start = params;
  const char *end = start;
  while (*end && *end != '&') ++end;
  if (end == start) value.clear();
  else ((StringBase<char> *)&value)->set(start,end-start);
  return true;
 }
 while (*params) {
  char c = *params;
  ++params;
  if (c == '&') break;
 }
next:
 skipSpaces(&params);
 entry = params;
 if (*entry) goto compare;
 return false;
}
