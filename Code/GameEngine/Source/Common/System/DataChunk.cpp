// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 DataChunkInput version getter, transferred from the exact BFME1
// reconstruction (Code/GameEngine/Source/Common/System/DataChunk.cpp).
// Retail BFME2 keeps the same shape: null chunk stack reads zero, otherwise
// the version word at chunk+0xC with the stack head at this+0x1C.

struct InputChunk
{
	unsigned char m_pre[0x0C];
	unsigned short m_version;	// +0x0C
};

class DataChunkInput
{
public:
	unsigned short getChunkVersion();

private:
	unsigned char m_pre[0x1C];
	InputChunk *m_chunkStack;	// +0x1C
};

// ?getChunkVersion@DataChunkInput@@QAEGXZ
unsigned short DataChunkInput::getChunkVersion()
{
	if (m_chunkStack == 0)
		return 0;

	return m_chunkStack->m_version;
}
