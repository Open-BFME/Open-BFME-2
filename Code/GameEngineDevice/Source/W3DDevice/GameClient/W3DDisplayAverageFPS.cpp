// cl: /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// Complete 221-byte boundary 0x000437A1..0x0004387E. The target setter
// at +0x180 and the two rowed 64-bit timer helpers independently establish
// the receiver field and call ABI; the names of function-local samples
// retain Zero Hour source provenance.
class W3DDisplay
{
public:
 void updateAverageFPS(void);
private:
 unsigned char m_unmodelled[0x180];
 float m_averageFPS;
};
// ZH W3DDisplay::updateAverageFPS is the semantic/source guide. Retail
// 437A1..4387E has the same 30-sample counter/frequency moving average,
// omits the debug-only cumulative timer, and stores the average at +180.
// Donor source 575ba2b04743f190f069805fbdc59936123c45da, WB 966AF0.
__int64 Rva00043024Get();
__int64 Rva0004300DGet();
void W3DDisplay::updateAverageFPS()
{
 const float MaximumFrameTimeCutoff=0.5f;
 const int FPS_HISTORY_SIZE=30;
 static __int64 lastUpdateTime64=0;
 static int historyOffset=0;
 static int numSamples=0;
 static double fpsHistory[FPS_HISTORY_SIZE];
 __int64 freq64=Rva00043024Get();
 __int64 time64=Rva0004300DGet();
 __int64 timeDiff=time64-lastUpdateTime64;
 double elapsedSeconds=(double)timeDiff/(double)freq64;
 if(elapsedSeconds<=MaximumFrameTimeCutoff){
  if(historyOffset>=FPS_HISTORY_SIZE)historyOffset=0;
  double currentFPS=1.0/elapsedSeconds;
  fpsHistory[historyOffset++]=currentFPS;
  numSamples++;
  if(numSamples>FPS_HISTORY_SIZE)numSamples=FPS_HISTORY_SIZE;
 }
 if(numSamples){
  float average=0;
  for(int i=0,j=historyOffset-1;i<numSamples;i++,j--){
   if(j<0)j=FPS_HISTORY_SIZE-1;
   average+=fpsHistory[j];
  }
  m_averageFPS=average/(float)numSamples;
 }
 lastUpdateTime64=time64;
}
