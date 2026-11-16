// cl: /MD /Oy-
// ??0Rva00331EAD@@QAE@HH@Z @0x00331EAD 36B
// 12-byte record ctor storing two ints then constructing the freelist member at +8
// through 0x29FB3B with an empty allocator temporary. Callers at
// 0x328ED and 0x32975 build a stack temp for vector search-insert.
#include "../../Include/GameLogic/Module/Rva0029FB3BMember.h"
#include "../../Include/GameLogic/Module/Rva0029FB3BAlloc.h"

class Rva00331EAD
{
	int m_00;
	int m_04;
	Rva0029FB3BMember m_08;

public:
	Rva00331EAD(int a, int b);
};

Rva00331EAD::Rva00331EAD(int a, int b) :
	m_00(a),
	m_04(b),
	m_08(Rva0029FB3BAlloc())
{
}
