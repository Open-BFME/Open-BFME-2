// cl: /MD
// stlport
//
// ??0Rva0022CD65@@QAE@XZ @0x0022CD65 19B: opaque map-holder ctor with int flag.
// Calls the rowed map<int,void*> default ctor at 0x0033C432 (row in
// stlport_map_int_ptr_o1.cpp) then stores 1 at +0xC and returns this.
// No vtable store, no EH prologue. Used as the ??_L element initializer
// by the outer ctor at 0x0022CD78 (push 0x62CD65). Owner identity unproven,
// honest Rva name. Prev 0x0022C55B (SaveMapPreviewCopy.cpp) and next
// 0x0022CE19 (SaveGameInfoCopyBFME2.cpp) carry /EHsc which retail lacks,
// so new file beside them uses /O1 /MD like Rva004E35A3Ctor.cpp.
#include <map>

class Rva0022CD65
{
public:
	Rva0022CD65();

private:
	_STL::map<int, void *> m_map;
	int m_val;
};

Rva0022CD65::Rva0022CD65() : m_val(1)
{
}
