// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// Native 0x002ADCE1..0x002ADD31 (Ghidra FUN_006adce1, ret at 2ADD2E).
// Reference algorithm: STLport 4.5.3 stl/_hashtable.c erase(iterator),
// vendored by BFME1 6583b3c1ff21db4a561285717028fdafc780b7db.
// Target: ControlBar reset calls the by-value cursor wrapper at 3A37DC,
// which copies both cursor words locally and calls this worker by reference.
// The worker uses the first word as its node, hashes the key at node+4,
// unlinks it from buckets at this+4, releases it through rowed 1FD9EF,
// then decrements the count at this+10. The second cursor word is unused.
// Both calls reproduce the rowed implementations (223149 and 1FD9EF).
// Cursor/node labels describe observed use; original container instantiation
// and mapped payload types remain unknown. Retain address-derived names.
#include "ascii_string.h"
class Rva001FD9EF { public: void rva001FD9EF(void *); };
struct VideoNode { VideoNode *next; };
// Shared machine layout with ControlBarReset.cpp's captured cursor.
struct VideoPair {
 struct { void *first; void *second; } s;
 inline VideoPair(void *a,void *b) { s.first=a; s.second=b; }
 inline VideoPair(const VideoPair &other) { s.first=other.s.first; s.second=other.s.second; }
};
class Rva000427195 {
 char prefix[4];
 VideoNode **buckets;
 void *last;
 void *end;
 unsigned int count;
public:
 void rva003A37DC(VideoPair);
 void rva002ADCE1(const VideoPair &);
 int bucketIndex(const AsciiString *);
};
#pragma optimize("y", on)
void Rva000427195::rva002ADCE1(const VideoPair &it) {
 VideoNode *node=(VideoNode *)it.s.first;
 if(node) {
  unsigned int n=bucketIndex((const AsciiString *)(node+1));
  VideoNode *cur=buckets[n];
  if(cur==node) {
   buckets[n]=cur->next;
   ((Rva001FD9EF *)this)->rva001FD9EF(cur);
   --count;
  } else {
   VideoNode *next=cur->next;
   while(next) {
    if(next==node) {
     cur->next=next->next;
     ((Rva001FD9EF *)this)->rva001FD9EF(next);
     --count;
     break;
    }
    cur=next;
    next=cur->next;
   }
  }
 }
}
