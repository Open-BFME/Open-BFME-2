// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ??0FrameData@@QAE@XZ, retail 0x005DA4C8, 20 bytes.
//
// Identity (target evidence): FrameDataManager's constructor 0x0058B567 builds
// its FRAME_DATA_LENGTH array of 0x14-byte entries through the eh vector
// constructor iterator with this body as the element constructor and
// 0x005DA4DC as the element destructor, as Zero Hour's
// `m_frameData = NEW FrameData[FRAME_DATA_LENGTH]` does. The fields agree with
// the matched FrameData rows: frame command count at +0 (getFrameCommandCount),
// command count at +4 (getCommandCount), command list at +8 (getCommandList,
// init, the destructor).
//
// Source order (donor): Zero Hour's FrameData::FrameData without m_frame, which
// BFME 2's 0x14-byte FrameData does not have. MSVC 7.1 emits the stores in that
// order, +8 then +4 then +0 then +0x0C and +0x10; only the -1 store is
// scheduled first. Body first placed from the BFME 1 donor
// game/GameEngine/Source/Common/R2ZeroingConstructors.cpp (reference/open-bfme-1
// @ 6d943426), where it is the address-named Rva00670130.

class NetCommandList;

class FrameData
{
public:
	FrameData();

private:
	unsigned int m_frameCommandCount;
	unsigned int m_commandCount;
	NetCommandList *m_commandList;
	unsigned int m_lastFailedCC;
	unsigned int m_lastFailedFrameCC;
};

FrameData::FrameData()
{
	m_commandList = 0;
	m_commandCount = 0;
	m_frameCommandCount = -1;
	m_lastFailedCC = 0;
	m_lastFailedFrameCC = 0;
}
