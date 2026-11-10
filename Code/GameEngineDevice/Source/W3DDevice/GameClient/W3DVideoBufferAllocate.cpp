// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// W3DVideoBuffer::allocate, retail 0x00072760..0x0007280A (170 B, RET 0xC), vtable
// 0x007C64D8 slot 2. WorldBuilder 0x0099C010 (callgraph score 1.0) carries the same body:
// the ZH allocate spine (free, size copies, texture size validation, format
// lookup) under a DX8 thread lock, plus a BFME bool stored at +0x49 and passed to the
// format mapper, then one state allocation per buffered state (rowed 0x000725BC).
void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();

#include "../../../Include/W3DDevice/GameClient/BFMEDX8DeviceLock.h"

// retail 0x0011E670: BFME's DXWrapper::AdjustTextureSize (Zero Hour's donor text calls
// TextureLoader::Validate_Texture_Size here).
#include "../../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

int Rva0007240CGet(int kind, bool flag);

#include "../../../../GameEngine/Include/Common/Rva000724AE.h"

class W3DVideoBuffer
{
public:
	virtual ~W3DVideoBuffer();
	virtual void slot1();
	virtual bool allocate(unsigned int width, unsigned int height, bool flag);
	virtual void free();

private:
	unsigned int m_x_pos;
	unsigned int m_y_pos;
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_texture_width;
	unsigned int m_texture_height;
	unsigned int m_pitch;
	float m_value_20;
	int m_format;
	bool m_flag_28;
	Rva000724AE m_states[1];
	Rva000724AE *m_state_40;
	Rva000724AE *m_state_44;
	bool m_flag_48;
	bool m_flag_49;
	bool m_flag_4a;
};

bool W3DVideoBuffer::allocate(unsigned int width, unsigned int height, bool flag)
{
	BFMEDX8DeviceLock guard;
	free();
	m_width = width;
	m_height = height;
	m_texture_width = width;
	m_texture_height = height;
	DX8Wrapper::AdjustTextureSize(m_texture_width, m_texture_height);
	m_flag_49 = flag;
	int format = Rva0007240CGet(m_format, flag);
	if (format == 0)
		return false;
	for (int i = 0; i < 1; i++) {
		if (!m_states[i].rva000725BC(m_texture_width, m_texture_height, m_width, m_height, format, false))
			return false;
	}
	return true;
}
