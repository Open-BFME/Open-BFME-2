// cl: /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil
// ?Reset_Line@Rva00743060Class@@QAEXXZ @0x00743060 22B.
// Recovered from the ?Reset_Line@SegLineRendererClass@@QAEXXZ recipe at
// 0x00191260. Same operand-masked shape: stamp the sync time from the global at
// 0x00DEC3CC, then zero the two-float UV offset with the shared Vector2::Set.
// Only the member offsets differ: this class keeps LastUsedSyncTime at +0x2C and
// CurrentUVOffset at +0x30 (the template uses +0x30/+0x34). No calls, so the
// offsets are the whole difference. Identity unknown; address-derived class.
#include "vector2.h"

class Rva00743060Class;

// The sync time at 0x00DEC3CC is WW3D's private static (defined in ww3d.cpp).
#include "WW3DClass.h"

class Rva00743060Class
{
public:
	void Reset_Line();

private:
	char m_prefix[0x2c];
	unsigned m_lastUsedSyncTime;	// +0x2c
	Vector2 m_currentUVOffset;	// +0x30
};

void Rva00743060Class::Reset_Line()
{
	m_lastUsedSyncTime = WW3D::SyncTime;
	m_currentUVOffset.Set(0.0f, 0.0f);
}
