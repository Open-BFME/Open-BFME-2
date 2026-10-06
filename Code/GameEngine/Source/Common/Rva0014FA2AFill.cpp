// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014FA2AFill@@YAXPAVRva0014F699@@0ABV1@@Z @0x0014FA2A 29B range fill assigning same value via rowed 0x0014F699.
// Retail: push esi / mov esi [esp+8] / jmp cmp / push [esp+0x10] / mov ecx esi / call 0x14F699 / add esi 0x4c / cmp esi [esp+c] / jne / pop esi / ret.
// Target facts: __cdecl void (first last value); stride 0x4C from sizeof Rva0014F699; callees rowed ??4Rva0014F699@@QAEAAV0@ABV0@@Z; callers 0x001509E0 0x00150A20 push 3 args caller-cleans.
// Callers: 0x001509E0 0x00150A20 in 0x00150959; callees: 0x0014F699.
// Not established: owning class identity; names are address-derived.
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

class Rva0014F699
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	RefCountPtr<TextureClass> m_48;
public:
	Rva0014F699 &operator=(const Rva0014F699 &other);
};

void __cdecl Rva0014FA2AFill(Rva0014F699 *first, Rva0014F699 *last, const Rva0014F699 &value)
{
	for (; first != last; ++first)
		*first = value;
}
