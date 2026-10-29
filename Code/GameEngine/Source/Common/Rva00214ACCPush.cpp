// cl: /DNDEBUG /MD
// stlport
// ?rva00214ACC@Rva00214ACC@@QAEXURva004DFCB0Element@@@Z @0x00214ACC 16B
// Vector push_back wrapper: lea eax,[esp+4] push eax add ecx,0xC call rowed
// push_back 0x004DFCB0 ret 4. Evidence: rowed push_back 0x004DFCB0; caller
// 0x00214CFF in unclaimed 0x00214C4E; abuts prev 0x00214AC7 and next 0x00214ADC;
// container offset 0xC. Honest address-derived holder.
// This wrapper carries an untyped four-byte slot. The common append uses the
// established donor ModuleData-pointer spelling; that spelling does not establish
// the application type of this holder or its argument. Preserve the raw bits.
class ModuleData;

struct Rva004DFCB0Element
{
	unsigned word0;
};

#include <vector>

namespace _STL
{
// Bind push_back to the rowed 0x004DFCB0 worker.
template <> void vector<const ModuleData *, allocator<const ModuleData *> >::push_back(const ModuleData *const &value);
}

class Rva00214ACC
{
public:
	void rva00214ACC(Rva004DFCB0Element value);
private:
	char m_pad[0x0C];
	_STL::vector<const ModuleData *> m_vec;
};

void Rva00214ACC::rva00214ACC(Rva004DFCB0Element value)
{
	m_vec.push_back(reinterpret_cast<const ModuleData *const &>(value.word0));
}
