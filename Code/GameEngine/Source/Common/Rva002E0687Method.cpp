// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002E0687@Rva002E0687@@QBE_NXZ @0x002E0687 18B.
// Self-identity test via global logic holder: return g_009FEF10->m_98 == this.
// Evidence: mov edx [0x00DFEF10] plus cmp [edx+0x98] ecx plus sete al;
// global g_009FEF10 mangled ?g_009FEF10@@3PAVRva002BA8F1Logic@@A used by 2 TUs;
// 7 callers incl 0x002B2A95 0x002B4E83; neighbours share /O1.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
class Rva002BA8F1Logic;

struct Rva002E0687Holder
{
	char m_pad[0x98];
	void *m_98;
};
class Rva002E0687
{
public:
	bool rva002E0687() const;
};
bool Rva002E0687::rva002E0687() const
{
	return ((Rva002E0687Holder *)(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))->m_98 == this;
}
