// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0044E633@Rva0044E633@@QAEPAXXZ @0x0044E633 15B
// Filtered-find forward through Object::getSpecialPowerModule. Retail is mov eax [ecx+4]
// push [eax+0x38] mov ecx [ecx+8] call rowed Object::getSpecialPowerModule ret.
// Evidence: unlock lane; callers at 0x0045021D 0x00450FE9 0x004510C6
// 0x00492BD0 0x00494E30 0x004CD6E1 0x004CDA6E; unblocks five functions;
// flags /O1 from rowed callee TU BfmeSubBECFilteredFind.cpp while prev
// and next TUs use defaults that reorder the loads. Owner unproven so
// the name stays address-derived.

struct Rva0044E633Holder
{
	char m_pad[0x38];
	void *m_arg38;
};

class SpecialPowerTemplate;
class SpecialPowerModuleInterface;

class Object
{
public:
	SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};

class Rva0044E633
{
public:
	char m_pad0[4];
	Rva0044E633Holder *m_ptr04;
	Object *m_bec08;
	void *rva0044E633();
};

void *Rva0044E633::rva0044E633()
{
	return m_bec08->getSpecialPowerModule(reinterpret_cast<const SpecialPowerTemplate *>(m_ptr04->m_arg38));
}
