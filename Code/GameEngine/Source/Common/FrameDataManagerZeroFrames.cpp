// ?zeroFrames@FrameDataManager@@QAEXII@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// FrameDataManager::zeroFrames, retail 0x0058B7AF, 62 bytes. BFME1
// FrameDataManager.cpp shape verbatim (EA GPL-3.0-or-later): fold the start
// frame onto the ring, then zero that many entries wrapping with modulo.
//
// Dedicated TU (callee-visibility split, getPlanar/worker precedent): the
// family TU defines zeroFrame, which lets MSVC prove edx survives the call
// and keep the frame index in edx; retail homes it to esi, so this TU sees
// only the opaque decl (resolves via the matched row) while the def stays
// in FrameDataManagerCounts.cpp. The m_frameData[frameIndex] subscript under
// /G7 emits the retail mov+imul+add sequence (twin-accessor precedent).
class NetCommandList {
public:
 void reset();
};
class FrameData {
public:
 __declspec(noinline) void zeroFrame();
private:
 unsigned int m_frameCommandCount;
 unsigned int m_commandCount;
 NetCommandList *m_commandList;
 char storage[8];
};
extern int FRAME_DATA_LENGTH;
class FrameDataManager {
public:
 void zeroFrames(unsigned int startingFrame, unsigned int numFrames);
private:
 void *vtable;
 FrameData *m_frameData;
 bool m_isLocal;
 bool m_isQuitting;
 unsigned int m_quitFrame;
};
// ?zeroFrames@FrameDataManager@@QAEXII@Z
void FrameDataManager::zeroFrames(unsigned int startingFrame, unsigned int numFrames) {
 unsigned int frameIndex = startingFrame % FRAME_DATA_LENGTH;
 for (unsigned int i = 0; i < numFrames; ++i) {
  m_frameData[frameIndex].zeroFrame();
  ++frameIndex;
  frameIndex = frameIndex % FRAME_DATA_LENGTH;
 }
}
