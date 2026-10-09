// ?createGaussianVector@W3DShaderManager@@SAXPAXPAUBfmeGaussianParams@@@Z
// partial score=0.0 date=2026-10-09
// cl: /O1 /arch:SSE /DNDEBUG /MD /EHsc
// Native000780BC..00078246 full394B; WB007D3920 createGaussianVector.
// Semantic guide WB W3DShaderManager.cpp1529 plus retail float constants/loops.
// Signature already pinned from verified ScreenHilightFilter/Rva007D85C0 callers.
// Uncompiled: current pinned reference versus immutable checkout blocks compiler.
// Two coefficient/amplitude pairs at params8/C and10/14; components0 and taps4.
// Kernel contains raw12B (offset,zero,weight) samples, padded to a multiple of4.
// Existing Gen_p12pod erase2A133B and PrereqUnitRec push_back2DF89B independently
// prove the retained helper bodies are only12B POD operations; no new aliases.
#include <math.h>
struct Gen_p12pod { char opaque[12]; };
struct PrereqUnitRec;
namespace _STL {
 template<class T> class allocator {};
 template<class T,class A=allocator<T> > class vector;
 template<> class vector<Gen_p12pod,allocator<Gen_p12pod> > {
 public: Gen_p12pod *erase(Gen_p12pod *,Gen_p12pod *);
 };
 template<> class vector<PrereqUnitRec,allocator<PrereqUnitRec> > {
 public: void push_back(const PrereqUnitRec &);
 };
}
struct GaussianSample {float x,y,z;};
struct GaussianKernelView {
 GaussianSample *begin,*end,*capacity;
 __forceinline void clear() {
  reinterpret_cast<_STL::vector<Gen_p12pod> *>(this)->erase(reinterpret_cast<Gen_p12pod *>(begin),reinterpret_cast<Gen_p12pod *>(end));
 }
 __forceinline void append(const GaussianSample &sample) {
  reinterpret_cast<_STL::vector<PrereqUnitRec> *>(this)->push_back(reinterpret_cast<const PrereqUnitRec &>(sample));
 }
 unsigned size() const {return end-begin;}
};
struct BfmeGaussianParams {
 int components,taps; float coefficient0,amplitude0,coefficient1,amplitude1;
};
class W3DShaderManager {
public: static void createGaussianVector(void *,BfmeGaussianParams *);
};
void W3DShaderManager::createGaussianVector(void *kernel,BfmeGaussianParams *params)
{
 BfmeGaussianParams p=*params;
 int taps=p.taps,components=p.components;
 float scale=15.0f/(float)taps;
 if(scale>1.0f) scale=(1.0f-scale)*0.5f+scale;
 struct Pair {float coefficient,amplitude;} pair[2]={
  {p.coefficient0,scale*p.amplitude0},{p.coefficient1,scale*p.amplitude1}};
 float center=((float)taps-1.0f)*0.5f;
 GaussianKernelView *out=static_cast<GaussianKernelView *>(kernel);
 out->clear();
 for(int i=0;i<taps;++i) {
  GaussianSample sample={(float)i-center-0.1f,0.0f,0.0f};
  float norm=sample.x*sample.x/(center*center);
  for(int j=0;j<components;++j)
   sample.z=(float)(sample.z+pair[j].amplitude*(1.0/exp((double)norm*pair[j].coefficient)));
  if(sample.z>0.01f) out->append(sample);
 }
 GaussianSample zero={0.0f,0.0f,0.0f};
 int padding=(int)(4-out->size()%4)%4;
 for(int n=0;n<padding;++n) out->append(zero);
}
