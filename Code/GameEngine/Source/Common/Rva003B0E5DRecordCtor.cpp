// cl: /O1 /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP=
#include "ascii_string.h"
struct Rva003B0E5DRecord {Rva003B0E5DRecord();AsciiString text;int a,b,c;};
Rva003B0E5DRecord::Rva003B0E5DRecord():a(0),b(60),c(100){}
// Native ctor [3B0E5D,3B0E75) through RET; record at PlayerTemplate+154.
// String member then integers0/60/100; names remain unproven.
