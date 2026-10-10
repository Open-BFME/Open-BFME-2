// cl: /EHsc /MD /Ireference/shims/bfme2_ascii
//
// ?rva005C3D5F@Rva005C3D5F@@QAEXPBD@Z, retail 0x005c3d5f, 130 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Target 5C3D5F/130 reads index parameter, checks signed 0<=index<3,
// clears two distinct pointer holders in a 12-byte record at this+20+index*12.
// Original receiver, record and parser names remain unknown.
#include "ascii_string.h"
#include <stdlib.h>
bool __cdecl Rva004128F0GetParam(const char *,const char *,AsciiString &);
class Rva002BED91 { public: void clear(); void *held; };
class Rva000AD6F4 { public: void clear(); void *held; };
struct Rva005C3D5FRecord { unsigned char unknown[4]; Rva000AD6F4 first; Rva002BED91 second; };
class Rva005C3D5F { public: void rva005C3D5F(const char *); unsigned char unknown[0x20]; Rva005C3D5FRecord records[3]; };
void Rva005C3D5F::rva005C3D5F(const char *args) {
 AsciiString index;
 if(Rva004128F0GetParam(args,"index",index)) {
  int i=atoi(index.str());
  if(i>=0 && i<3) {
   Rva005C3D5FRecord *record=&records[i];
   record->second.clear();
   record->first.clear();
  }
 }
}
