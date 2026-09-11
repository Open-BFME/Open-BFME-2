// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7 /GX
// Adapted from Open-BFME-1 FrameDataManager.cpp (EA GPL-3.0-or-later).
// BFME2 callers and retail bodies verify the ring global, 20-byte stride,
// count accessors and quit-state offsets independently of BFME1.
class NetCommandList {
public:
 void reset();
};
class FrameData {
public:
 __declspec(noinline) unsigned int getFrameCommandCount();
 unsigned int getCommandCount();
 void setFrameCommandCount(unsigned int count);
 __declspec(noinline) void zeroFrame();
 __declspec(noinline) void destroyGameMessages();
private:
 unsigned int m_frameCommandCount;
 unsigned int m_commandCount;
 NetCommandList *m_commandList;
 char storage[8];
};
#define FRAME_DATA_LENGTH (*(const int *)0x00DD2DB8)

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
void FrameData::setFrameCommandCount(unsigned int count) {
 m_frameCommandCount = count;
}

class FrameDataManager {
public:
 void destroyGameMessages();
 unsigned int getCommandCount(unsigned int frame);
 unsigned int getFrameCommandCount(unsigned int frame);
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
unsigned int FrameDataManager::getFrameCommandCount(unsigned int frame) {
 unsigned int frameindex = frame % FRAME_DATA_LENGTH;
 return m_frameData[frameindex].getFrameCommandCount();
}
void FrameDataManager::setQuitFrame(unsigned int frame) {
 m_isQuitting = true;
 m_quitFrame = frame;
}
bool FrameDataManager::getIsQuitting() { return m_isQuitting; }
