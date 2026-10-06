// ?rva00346FA5@Rva00346FA5@@QBEPAXH@Z
// partial score=0.91 date=2026-09-28
// cl: /MD
//
// ?rva00346FA5@Rva00346FA5@@QBEPAXH@Z @0x00346FA5 43B
// Bounds-checked 12-byte element accessor. Evidence: __thiscall via ecx
// plus ret-4 single int arg; range from [ecx+0x3C] to [ecx+0x40] divided
// by 12 via cdq plus idiv; jl for arg<0 plus jae for arg>=count; imul-12
// plus add for slot; 26 callers; name stays address-derived.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;

private:
	char m_pad[0x3C];
	int m_begin3C;
	int m_end40;
};

void *Rva00346FA5::rva00346FA5(int index) const
{
	if (index >= 0)
	{
		int count = (m_end40 - m_begin3C) / 12;
		if ((unsigned)index < (unsigned)count)
		{
			_ReadWriteBarrier();
			return (void *)(m_begin3C + index * 12);
		}
	}
	return 0;
}
