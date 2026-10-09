// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?slot00@Rva0035986C@@UAEXHH@Z, retail 0x0035A994..0x0035A9C1 (45
// bytes, RET8): the sole slot of the derived visitor table8153D8.
// Native and WB prove a two-argument cell callback, not a destructor. It counts the attempt (+0x10), runs the +0x04 object's 0x0035A4A3
// (not yet rowed; pinned) with both arguments, the +0x08 value, 0, the +0x18
// flag and the +0x0C value, and counts a success (+0x14). WorldBuilder's twin
// (0x00E5F9D0) is unnamed.

class Rva0035A4A3
{
public:
	bool rva0035A4A3(int a, int b, int c, int zero, bool flag, int d);
};

#include "../GameLogic/System/TerrainResourceVisitorView.h"

void Rva0035986C::slot00(int a, int b)
{
	++m_10;
	if (reinterpret_cast<Rva0035A4A3 *>(m_04)->rva0035A4A3(a, b, m_08, 0, m_18, m_0C))
		++m_14;
}
