// ?rva00214762@Rva002147D1@@QAE_NHPAXPAMPBV?$StringBase@D@@@Z
// partial score=0.95 date=2026-10-06
// ?rva00214762@Rva002147D1@@QAE_NHPAXPAMPBV?$StringBase@D@@@Z
// partial score=0.95 date=2026-10-03
// cl: /O1 /DNDEBUG /MD
// ?rva00214762@Rva002147D1@@QAE_NHPAXPAMPBV?$StringBase@D@@@Z retail 0x00214762 63B
// Guarded indexed forward through Rva004036B1::rva004036B1: bounds-check index
// against (m_end-m_begin)-1, null-check the slot, else forward key/out/filter.
// Evidence: same +0x0c +0x10 layout as siblings 0x002147D1/0x00214738; rowed
// callee 0x004036B1; callers at 0x004033E9 0x004034A6 0x004037DA.
template <typename T> class StringBase;
class Rva004036B1
{
public:
	bool rva004036B1(void *key, float *out, const StringBase<char> *filter);
};
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class Rva002147D1
{
public:
	bool rva00214762(int index, void *key, float *out, const StringBase<char> *filter);
private:
	char _pad[0x0C];
	int m_begin;
	int m_end;
};
// ?rva00214762@Rva002147D1@@QAE_NHPAXPAMPBV?$StringBase@D@@@Z present-unmatched
bool Rva002147D1::rva00214762(int index, void *key, float *out, const StringBase<char> *filter)
{
	if (index < 0)
		return false;
	if ((unsigned)index > (unsigned)((m_end - m_begin >> 2) - 1))
		return false;
	_ReadWriteBarrier();
	int base = m_begin;
	int off = index * 4;
	if (*(void **)(off + base) != 0)
	{
		_ReadWriteBarrier();
		return (*(Rva004036B1 **)(off + base))->rva004036B1(key, out, filter);
	}
	return false;
}
