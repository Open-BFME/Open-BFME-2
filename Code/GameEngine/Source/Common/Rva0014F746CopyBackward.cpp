// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014F746CopyBackward@@YAPAVRva0014F699@@PAV1@00PAXH@Z @0x0014F746 50B copy_backward via rowed 0x0014F699 with dummy trailing args.
// Retail: push ebp / mov ebp esp / mov eax [ebp+c] / sub eax [ebp+8] / push 0x4c / cdq / pop ecx / idiv ecx / test eax eax / jle / push esi / mov esi eax / sub [ebp+c] 0x4c / sub [ebp+0x10] 0x4c / push [ebp+c] / mov ecx [ebp+0x10] / call 0x14F699 / dec esi / jne / pop esi / mov eax [ebp+0x10] / pop ebp / ret.
// Target facts: __cdecl (first last dest tag extra) -> dest; count=(last-first) via idiv 0x4C from sizeof; loop --last --dest *dest=*last via rowed assign; tag/extra ride dead above frame for 5-arg callers with add esp 0x14; caller 0x0014FA20 pushes 5.
// Callers: 0x0014FA20 in 0x0014FA0D pushes 5 (first last result tag null); callees: 0x0014F699.
// Precedent: Rva002195B7CopyBackward 47B same shape with sar 3 plus dummy tag args and 29B forwarder.
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

Rva0014F699 *__cdecl Rva0014F746CopyBackward(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n <= 0)
		return dest;
	for (int i = n; i != 0; --i) {
		--last;
		--dest;
		*dest = *last;
	}
	return dest;
}
