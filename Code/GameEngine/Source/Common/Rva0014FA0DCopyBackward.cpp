// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014FA0DCopyBackward@@YAXPAVRva0014F699@@00@Z @0x0014FA0D 29B wrapper forwarding to rowed 5-arg 0x0014F746.
// Retail: push ebp / mov ebp esp / push ecx / push 0 / lea eax [ebp-1] / push eax / push [ebp+0x10] / push [ebp+c] / push [ebp+8] / call 0x14F746 / add esp 0x14 / leave / ret.
// Target facts: __cdecl void (first last result); creates 1-byte tag at [ebp-1]; forwards (first last result tag 0) to rowed ?Rva0014F746CopyBackward@@YAPAVRva0014F699@@PAV1@00PAXH@Z; ignores return; caller 0x001509D3 pushes 3 caller-cleans.
// Callers: 0x001509D3 in 0x00150959; callees: 0x0014F746.
// Precedent: Rva0039BA4BCopyBackward 29B same shape to 5-arg 0x0039B92D.
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

Rva0014F699 *__cdecl Rva0014F746CopyBackward(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *dest, void *tag, int extra);

void __cdecl Rva0014FA0DCopyBackward(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result)
{
	char tag;
	Rva0014F746CopyBackward(first, last, result, &tag, 0);
}
