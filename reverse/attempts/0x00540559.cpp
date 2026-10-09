// ?rva00540559@Rva0054034A@@QAE?AVRva0053FDE6@@M@Z
// partial score=0.65 date=2026-10-09
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7 /arch:SSE
#include <math.h>
#include <new>
struct Rva0053FDE6Block16 { float m_10,m_14,m_18,m_1c; };
class Rva0053FE64 { public: static void *rva0053FE64(void*,float,void*,int,void*,int,void*,int,void*,int); };
class Rva0053FDE6 { public: __forceinline Rva0053FDE6(float t,void* a,int ta,void* b,int tb,void* c,int tc,void* d,int td) { Rva0053FE64::rva0053FE64(this,t,a,ta,b,tb,c,tc,d,td); } Rva0053FDE6(const Rva0053FDE6&); int m_00,m_04,m_08,m_0c; Rva0053FDE6Block16 m_block; float m_20; };
struct BfmePod40 { int m_00; Rva0053FDE6 frame; };

class Rva0054034A { public:
 bool rva0054034A(int);
 Rva0053FDE6 rva00540559(float frame);
 char m_pad00[16]; BfmePod40 *m_begin10,*m_end14; int m_pad18,m_hint1C;
};
Rva0053FDE6 Rva0054034A::rva00540559(float frame) {
 if(frame<0) { return m_begin10->frame; }
 rva0054034A((int)floor((double)frame));
 if((unsigned)m_hint1C >= (unsigned)(((char*)m_end14-(char*)m_begin10)/40)-1) {
  return m_begin10[m_hint1C].frame;
 }
 BfmePod40 *a=&m_begin10[m_hint1C];
 BfmePod40 *b=a+1;
 int ta=a->m_00,tb=b->m_00;
 if(ta==tb) { return a->frame; }
 frame=(frame-ta)/(tb-ta);
 BfmePod40 *p=m_hint1C>0?&m_begin10[m_hint1C-1]:a;
 BfmePod40 *n=(unsigned)(m_hint1C+2)<(unsigned)(((char*)m_end14-(char*)m_begin10)/40)?&m_begin10[m_hint1C+2]:b;
 return Rva0053FDE6(frame,&p->frame,p->m_00,&a->frame,a->m_00,&b->frame,tb,&n->frame,n->m_00);
}

