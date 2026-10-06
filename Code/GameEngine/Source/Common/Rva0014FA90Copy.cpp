// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014FA90Copy@@YAPAVRva0014F699@@PAV1@00PAXH@Z @0x0014FA90 50B forward copy via rowed 0x0014F699 with dummy trailing args.
// Retail: push ebp / mov ebp esp / mov eax [ebp+c] / sub eax [ebp+8] / push 0x4c / cdq / pop ecx / idiv ecx / test eax eax / jle / push esi / mov esi eax / push [ebp+8] / mov ecx [ebp+0x10] / call 0x14F699 / add [ebp+8] 0x4c / add [ebp+0x10] 0x4c / dec esi / jne / pop esi / mov eax [ebp+0x10] / pop ebp / ret.
// Target facts: __cdecl (first last dest tag extra) -> dest; count=(last-first) via idiv 0x4C; loop *dest=*first via rowed assign ++first ++dest; tag/extra dead for 5-arg callers with add esp 0x14; caller 0x00150278 pushes 5.
// Callers: 0x00150278 in 0x00150265 pushes 5; callees: 0x0014F699 assign.
// Precedent: Rva000E1860Copy 47B same shape with 4B stride plus dummy-tag 5-arg form Rva002195B7.
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

Rva0014F699 *__cdecl Rva0014FA90Copy(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		*dest = *first;
		++first;
		++dest;
	}
	return dest;
}
