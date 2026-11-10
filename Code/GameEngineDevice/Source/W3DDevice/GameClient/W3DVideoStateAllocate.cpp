// cl: /O1 /Ob2 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// BF1 f98983a7d W3DVideoBufferAllocateBfme.cpp identifies the embedded
// 20B state and its six inputs. Native725BC..726B0 independently proves
// the separate surface and texture allocation branches and all call ABIs.
class W3DRadarResetSurface {
public:
 W3DRadarResetSurface(unsigned,unsigned,unsigned,unsigned);
 ~W3DRadarResetSurface();
 W3DRadarResetSurface &operator=(const W3DRadarResetSurface &);
 void *surface;
};
class CursorTextureSlot {
public:
 W3DRadarResetSurface Get_Surface_Level();
 void *texture;
};
class Rva00131DFC {
public: void rva00131DFC(void *,void *,void *,void *,int,int);
};
class Rva00739C70 { public: void cleanup(); };
#include "../../../../GameEngine/Include/Common/Rva000724AE.h"
bool Rva000724AE::rva000725BC(unsigned tw,unsigned th,unsigned w,unsigned h,unsigned format,bool onlySurface) {
 bool result=false;
 m_00=w;
 m_04=h;
 if(onlySurface) {
  m_flags=4;
  *reinterpret_cast<W3DRadarResetSurface *>(&m_0c)=W3DRadarResetSurface(tw,th,format,0);
  int pitch;
  if(rva000724D7(&pitch)) {
   reinterpret_cast<Rva00739C70 *>(this)->cleanup();
   result=true;
  } else rva000724AE();
 } else {
  m_flags=0;
  reinterpret_cast<Rva00131DFC *>(&m_08)->rva00131DFC(
   reinterpret_cast<void *>(tw),reinterpret_cast<void *>(th),reinterpret_cast<void *>(format),reinterpret_cast<void *>(1),1,0);
  if(m_08) {
   *reinterpret_cast<W3DRadarResetSurface *>(&m_0c)=reinterpret_cast<CursorTextureSlot *>(&m_08)->Get_Surface_Level();
   int pitch;
   if(rva000724D7(&pitch)) {
    reinterpret_cast<Rva00739C70 *>(this)->cleanup();
    result=true;
   } else rva000724AE();
  }
 }
 return result;
}
