// cl: /O1 /G7 /arch:SSE /MD /EHsc
// WB8A5780 names W3DAptAux::PreDraw; nativeA8F98..A9071 RET0 supplies exact
// allocation/lifetime and throttled-clock behavior. BF1 renderer ctor453B
// and existing PostDraw supply E0 renderer and private sync static views.
// New observedElapsed name describes target role, not original spelling.
void Rva000A8F98();
class BfmeHub982;
class W3DAptAux {friend void Rva000A8F98();private:static BfmeHub982 *s_renderer;static unsigned s_syncTime0,s_syncTime1;};
class WW3D {friend void Rva000A8F98();public:static void Sync(unsigned);private:static unsigned SyncTime,PreviousSyncTime;};
class Rva00785FD0Renderer {public:Rva00785FD0Renderer();private:char nativeStorage[0xe0];};
class Rva00110FBF {public:void rva00110FBF();};
void Rva00118990();
extern float g_Va00DEC49C;
extern unsigned char g_00DB4CE0;
extern unsigned long g_00DE617C,g_00DE6180;
extern unsigned long AptObservedPreviousElapsed;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
void Rva000A8F98() {
 if(!W3DAptAux::s_renderer)W3DAptAux::s_renderer=(BfmeHub982*)new Rva00785FD0Renderer;
 if(W3DAptAux::s_renderer) {
  ((Rva00110FBF*)W3DAptAux::s_renderer)->rva00110FBF();Rva00118990();
  W3DAptAux::s_syncTime1=WW3D::SyncTime;g_Va00DEC49C=0.0f;W3DAptAux::s_syncTime0=WW3D::PreviousSyncTime;
  WW3D::Sync(AptObservedPreviousElapsed);
  unsigned long elapsed=g_00DE617C;
  if(g_00DB4CE0) {
   elapsed+=timeGetTime()-g_00DE6180;
   if(elapsed-AptObservedPreviousElapsed>100) {
    elapsed=AptObservedPreviousElapsed+100;g_00DE617C=elapsed;g_00DE6180=timeGetTime();
   }
  }
  WW3D::Sync(elapsed);AptObservedPreviousElapsed=elapsed;
 }
}
