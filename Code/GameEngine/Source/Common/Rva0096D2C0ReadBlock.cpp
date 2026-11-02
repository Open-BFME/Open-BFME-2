// cl: C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// The loader is WW3D's ChunkLoadClass: its Read (0x006151A0) is rowed in
// WWLib/chunkio.cpp. readBlock's own row keeps the BfmeChunkVFC parameter spelling.
class BfmeChunkVFC;
#include "../../../Libraries/Source/WWVegas/WWLib/ChunkLoadClass.h"

struct Rva0096D2C0Record
{
	char m_pad00[0x78];
	int m_value78;
	char m_tail7C[12];
};

class Rva0096D2C0Owner
{
public:
	bool readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record);

private:
	// BFME2 retail keeps the destination at +0x94 (BFME1 donor: +0x9C).
	char m_pad00[0x94];
	int *m_destination;
};

bool Rva0096D2C0Owner::readBlock(BfmeChunkVFC *loader, Rva0096D2C0Record *record)
{
	if (reinterpret_cast<ChunkLoadClass *>(loader)->Read(&record->m_value78, 16) != 16)
		return false;

	*m_destination = record->m_value78;
	return true;
}
