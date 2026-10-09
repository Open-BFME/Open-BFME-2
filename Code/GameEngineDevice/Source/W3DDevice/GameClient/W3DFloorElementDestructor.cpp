// cl: /MD /EHs /Ireference/shims/bfme2_ascii
// Complete floor-element cleanup at 0x000E5033 (104 bytes through RET).
// Semantic guide: Open-BFME-1 6c1e0b51, BaseHeightMapFloorElementDestructor.cpp.
// Native and WB 0x881140 prove the two texture handles at +20/+24, strings
// at +8C/+90, and the leading call to the shared E4567 resource cleanup.
// BFME 1's member offsets differ; retain the target's existing unwind-pin
// name rather than asserting its virtual class identity. The target constructor
// starts with sphere floats, and this nonvirtual destructor writes no vptr.
// The four EH states and their cleanup actions are verified independently.
#include "W3DFloorElement.h"

FloorMatrixRow::FloorMatrixRow() {}
Gen_uw_000e5033::~Gen_uw_000e5033() { reinterpret_cast<Rva000E4567 *>(this)->rva000E4567(); }

typedef char FloorRowStride[(sizeof(FloorMatrixRow)==16)?1:-1];
typedef char FloorElementExtent[(sizeof(Gen_uw_000e5033)==0xa0)?1:-1];
Gen_uw_000e5033::Gen_uw_000e5033() : m_render28(0), m_drawable2c(0), m_3c(0),m_40(0),m_44(0),m_48(0),m_id4c(0), m_active80(false),m_flag81(false),m_flag82(false),m_opacity84(1),m_speed88(0),m_94(0),m_state98(0),m_flag9c(false),m_flag9d(false)
{
}

