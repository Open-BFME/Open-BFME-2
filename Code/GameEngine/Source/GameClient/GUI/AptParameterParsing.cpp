// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <ctype.h>
#include <string.h>
// Apt query-string parameter parsing ("key=value&key=value").
// Native helpers in retail order: 00412689 SkipSpaces (29B) 004126A6
// SkipPastEquals (23B) 004126BD SkipPastAmpersand (23B) 004126D4 key-prefix
// match (57B) then 004128F0 GetParam (239B).
// The three cursor helpers are statics with a private register ABI (ESI or
// EAX carries the cursor address). Only SkipSpaces keeps call sites; the two
// skip-past helpers and the key matcher are inlined into GetParam while
// their out-of-line copies stay in the image uncalled (no direct callers of
// 004126A6 004126BD or 004126D4) which is what an inline helper whose body
// is still emitted looks like. Inlining needs /Ob1 so this unit no longer
// carries /Ob0.

// Native whole helper 00412689..004126A6: initial jump over loop
// signed char isspace IAT predicate and increment through cursor pointer.
// All three caller sites use ESI; static C++ naturally selects that private ABI.
static void Rva00412689SkipSpaces(const char **p)
{
 while (**p && isspace(**p)) ++*p;
}

// Native 004126A6..004126BD (EAX = cursor address): advance past the next
// '=' or to the terminator. Inlined into GetParam after the key.
static inline void Rva004126A6SkipPastEquals(const char **p)
{
 while (**p) {
  if (**p == '=') { ++*p; return; }
  ++*p;
 }
}

// Native 004126BD..004126D4 (EAX = cursor address): advance past the next
// '&' or to the terminator. Inlined into GetParam to skip a parameter.
static inline void Rva004126BDSkipPastAmpersand(const char **p)
{
 while (**p) {
  if (**p == '&') { ++*p; return; }
  ++*p;
 }
}

// Native57B [004126D4,0041270D): prefix comparison, then whitespace,
// then '=' delimiter. Caller argument and call site establish the ABI;
// no WorldBuilder name is available for this helper. GetParam inlines it.
__forceinline bool Rva004126D4(const char *input, const char *key, int keyLen)
{
 if (strncmp(input,key,keyLen)==0) {
  input += keyLen;
  Rva00412689SkipSpaces(&input);
  if (*input == '=') return true;
 }
 return false;
}

// Native 004128F0..004129DF (239B plain ret): looks key up in an Apt query
// string and copies its value (up to the next '&') into value; an empty value
// clears it. Returns whether the key was present. 20+ callers across the Apt
// callbacks (e.g. 0x004108BB 0x004115F5 0x0050EFA4). AsciiString clear
// 0x00036410 and set 0x00036780.
bool __cdecl Rva004128F0GetParam(const char *input, const char *key, AsciiString &value)
{
 if (!input || !*input || !key || !*key) return false;
 int keyLen = strlen(key);
 const char *params = input;
 for (;;) {
  Rva00412689SkipSpaces(&params);
  if (!*params) return false;
  bool match = Rva004126D4(params, key, keyLen);
  Rva004126A6SkipPastEquals(&params);
  Rva00412689SkipSpaces(&params);
  if (match) {
   const char *start = params;
   while (*params && *params != '&') ++params;
   if (params == start) value.clear();
   else ((StringBase<char> *)&value)->set(start,params-start);
   return true;
  }
  Rva004126BDSkipPastAmpersand(&params);
 }
}
