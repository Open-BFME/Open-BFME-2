// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/bfme2_ascii
#include "ascii_string.h"
#include <ctype.h>
#include <string.h>
#include "../../../../Libraries/Include/Lib/Coord2D.h"
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
static void Rva00412689SkipSpaces(const char **queryCursor)
{
 while (**queryCursor && isspace(**queryCursor)) ++*queryCursor;
}

// Native 004126A6..004126BD (EAX = cursor address): advance past the next
// '=' or to the terminator. Inlined into GetParam after the key.
static inline void skipPastEquals(const char **queryCursor)
{
 while (**queryCursor) {
  if (**queryCursor == '=') { ++*queryCursor; return; }
  ++*queryCursor;
 }
}

// Native 004126BD..004126D4 (EAX = cursor address): advance past the next
// '&' or to the terminator. Inlined into GetParam to skip a parameter.
static inline void skipPastAmpersand(const char **queryCursor)
{
 while (**queryCursor) {
  if (**queryCursor == '&') { ++*queryCursor; return; }
  ++*queryCursor;
 }
}

// Native57B [004126D4,0041270D): prefix comparison, then whitespace,
// then '=' delimiter. Caller argument and call site establish the ABI;
// no WorldBuilder name is available for this helper. GetParam inlines it.
__forceinline bool matchParamKey(const char *input, const char *key, int keyLen)
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
  bool match = matchParamKey(params, key, keyLen);
  skipPastEquals(&params);
  Rva00412689SkipSpaces(&params);
  if (match) {
   const char *start = params;
   while (*params && *params != '&') ++params;
   if (params == start) value.clear();
   else ((StringBase<char> *)&value)->set(start,params-start);
   return true;
  }
  skipPastAmpersand(&params);
 }
}

// Native 004129DF..00412A3C (93B cdecl ret): the "RenderImageDisabled"
// custom-render callback the global registration 0x00412F14 binds by address.
// Same image lookup (0x00223AC4) and W3DDisplay draw (0x0004D6B3) as the rowed
// sibling Rva00412B94, with the draw mode fixed at 1 instead of parsed from the
// parameters; the mode's meaning is not established.
class Image;
#include "../../../../Libraries/Source/Apt/AptPlayerClass.h"
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Display;
extern Display *TheDisplay;
#include "../../../../GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplayClass.h"

// ?Rva004129DF@@YAXPBVCoord2D@@0PBD1@Z
void Rva004129DF(const Coord2D *origin, const Coord2D *size,
                 const char *path, const char *parameters)
{
 const Image *image = reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager)->FindRenderImage(path, parameters);
 if (image)
 {
  reinterpret_cast<W3DDisplay *>(TheDisplay)->rva0004D6B3(
      const_cast<Image *>(image), origin->x, origin->y, size->x + origin->x,
      size->y + origin->y, -1, 1);
 }
}
