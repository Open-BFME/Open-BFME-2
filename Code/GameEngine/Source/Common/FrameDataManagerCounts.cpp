// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// Adapted from Open-BFME-1 FrameDataManager.cpp (EA GPL-3.0-or-later).
// BFME2 callers and retail bodies verify the ring global, 20-byte stride,
// count accessors and quit-state offsets independently of BFME1.
class NetCommandList {
public:
 void reset();
};
enum FrameDataReturnType { FRAMEDATA_NOTREADY, FRAMEDATA_RESEND, FRAMEDATA_READY };
class FrameData {
public:
 FrameDataReturnType allCommandsReady(bool debugSpewage);
 unsigned int getAckCommandCount();
 __declspec(noinline) unsigned int getFrameCommandCount();
 unsigned int getCommandCount();
 NetCommandList *getCommandList();
 void init();
 __declspec(noinline) void setFrameCommandCount(unsigned int count);
 __declspec(noinline) void zeroFrame();
 __declspec(noinline) void destroyGameMessages();
private:
 unsigned int m_frameCommandCount;
 unsigned int m_commandCount;
 NetCommandList *m_commandList;
 char storage[8];
};
// FRAME_DATA_LENGTH: VA 0x00DD2DB8 (.data); retail initial value is 258.
// Target callers use it to size/index the frame-data ring; Open-BFME-1's
// NetworkUtil.cpp defines the same runtime global at its BFME1 address.
int FRAME_DATA_LENGTH = 258;

void FrameData::zeroFrame() {
 m_commandCount &= 0;
 m_frameCommandCount &= 0;
}
void FrameData::destroyGameMessages() {
 if (m_commandList == 0)
  return;
 m_commandList->reset();
 m_commandCount &= 0;
}
unsigned int FrameData::getFrameCommandCount() {
 return m_frameCommandCount;
}
__declspec(noinline) void FrameData::setFrameCommandCount(unsigned int count) {
 m_frameCommandCount = count;
}

class FrameDataManager {
public:
 FrameDataReturnType allCommandsReady(unsigned int frame, bool debugSpewage);
 int rva00670890(unsigned int frame, int mark);
 unsigned int getAckCommandCount(unsigned int frame);
 void destroyGameMessages();
 unsigned int getCommandCount(unsigned int frame);
 NetCommandList *getFrameCommandList(unsigned int frame);
 unsigned int getFrameCommandCount(unsigned int frame);
 void setFrameCommandCount(unsigned int frame, unsigned int count);
 void resetFrame(unsigned int frame, bool isAdvancing);
 void setQuitFrame(unsigned int frame);
 bool getIsQuitting();
private:
 void *vtable;
 FrameData *m_frameData;
 bool m_isLocal;
 bool m_isQuitting;
 unsigned int m_quitFrame;
};
void FrameDataManager::destroyGameMessages() {
 int frame = 0;
 unsigned int offset = 0;
 while (frame < FRAME_DATA_LENGTH) {
  ((FrameData *)((char *)m_frameData + offset))->destroyGameMessages();
  ++frame;
  offset += 0x14;
 }
}
// Both accessors fold the logic frame onto the ring, whose length BFME
// keeps in the global at 0x00DD2DB8 rather than a constant, and ask that slot.
unsigned int FrameDataManager::getCommandCount(unsigned int frame) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].getCommandCount();
}
NetCommandList *FrameDataManager::getFrameCommandList(unsigned int frame) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].getCommandList();
}
unsigned int FrameDataManager::getFrameCommandCount(unsigned int frame) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].getFrameCommandCount();
}
void FrameDataManager::setFrameCommandCount(unsigned int frame, unsigned int count) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 m_frameData[frameindex].setFrameCommandCount(count);
}
void FrameDataManager::resetFrame(unsigned int frame, bool isAdvancing) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 m_frameData[frameindex].init();
 if (m_isLocal) {
  m_frameData[frameindex].setFrameCommandCount((unsigned int)-1);
 }
}
void FrameDataManager::setQuitFrame(unsigned int frame) {
 m_isQuitting = true;
 m_quitFrame = frame;
}
bool FrameDataManager::getIsQuitting() { return m_isQuitting; }

// Open-BFME-1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 FrameDataManager.cpp;
// BFME2 verifies the same ring global and 20-byte element stride. Each callee
// has a matched BFME2 provider. The count-by-mark helper keeps its donor name;
// its original type and method name remain unknown.
FrameDataReturnType FrameDataManager::allCommandsReady(unsigned int frame, bool debugSpewage) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].allCommandsReady(debugSpewage);
}
class BfmeThingYN {
public:
 int bfmeCountYN(int mark) const;
};
int FrameDataManager::rva00670890(unsigned int frame, int mark) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return ((const BfmeThingYN *)&m_frameData[frameindex])->bfmeCountYN(mark);
}
unsigned int FrameDataManager::getAckCommandCount(unsigned int frame) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].getAckCommandCount();
}
