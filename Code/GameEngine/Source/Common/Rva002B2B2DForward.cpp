// cl: /O1 /MD
//
// ?rva002B2B2D@Rva002BA8F1Logic@@QAEPAURva002B3740Item@@XZ retail 0x002B2B2D 18 bytes.
// Leaf forwarder: push this+0xB8 int, ecx = this+0xB0 view, call rowed
// Rva0020EAF6View::rva0020EAF6. Identity via pin plus callers 0x002B35F7
// 0x002B3669 0x002B3740 in Rva002BA8F1Logic methods; prev/next share /O1.
class Rva0020E89C;

#include "../../Include/GameLogic/Rva0020EAF6View.h"

struct Rva002B3740Item;

#include "../../Include/GameLogic/Rva002BA8F1Logic.h"

Rva002B3740Item *Rva002BA8F1Logic::rva002B2B2D()
{
	return (Rva002B3740Item *)((Rva0020EAF6View *)m_B0)->rva0020EAF6(fieldB8);
}
