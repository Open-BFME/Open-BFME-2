// _bfmeReload1221
// partial score=0.9832391138273492 date=2026-10-09
// cl: /MD /EHsc
extern int g_bfmeIndexFA;
extern int g_bfmeStateFA[625];
extern unsigned int *g_bfmeNext1221;
void __cdecl bfmeSeed(int);
#define MIX(a,b) (((a)&0x80000000U)|((b)&0x7fffffffU))
#define MAGIC(b) (((b)&1U)?0x9908b0dfU:0U)
extern "C" unsigned int bfmeReload1221(){
 unsigned *p0=(unsigned*)g_bfmeStateFA,*p2=(unsigned*)g_bfmeStateFA+2,*pM=(unsigned*)g_bfmeStateFA+397;
 unsigned s0,s1;
 if(g_bfmeIndexFA < -1)bfmeSeed(4357);
 s0=g_bfmeStateFA[0];s1=g_bfmeStateFA[1];
 g_bfmeIndexFA=623;g_bfmeNext1221=(unsigned*)g_bfmeStateFA+1;
 int j;
 for(j=228;--j;s0=s1,s1=*p2++)*p0++=*pM++^(MIX(s0,s1)>>1)^MAGIC(s1);
 for(pM=(unsigned*)g_bfmeStateFA,j=397;--j;s0=s1,s1=*p2++)*p0++=*pM++^(MIX(s0,s1)>>1)^MAGIC(s1);
 s1=g_bfmeStateFA[0];*p0=*pM^(MIX(s0,s1)>>1)^MAGIC(s1);
 s1^=s1>>11;s1^=(s1<<7)&0x9d2c5680U;s1^=(s1<<15)&0xefc60000U;return s1^(s1>>18);
}
