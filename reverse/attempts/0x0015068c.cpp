// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z
// partial score=0.98 date=2026-10-05
// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z
// partial score=0.98 date=2026-09-29
// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z
// partial score=0.98 date=2026-09-29
// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z
// partial score=0.98 date=2026-09-29
// cl: /O1
//
// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z @0x0015068C 51B
// Vector-like reassign: copies [first, m_04) into result through the rowed
// 3-arg ?Rva00150265Copy (called with an extra tag arg the callee ignores,
// whose leaked inner-copy return is the new end), destroys [newEnd, m_04)
// via rowed ?Rva0014F8AEDestroy, stores the new end, returns result.
// Evidence: chain lane (callee landed this session), caller at 0x00150BBB.
// Owning class unproven, hence honest Rva names.

class Rva0014F699;
class Rva0014F3E7;

void __cdecl Rva00150265Copy(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result);
void __cdecl Rva0014F8AEDestroy(Rva0014F3E7 *first, Rva0014F3E7 *last);

class Rva0015068C
{
public:
	Rva0014F699 *rva0015068C(Rva0014F699 *result, Rva0014F699 *first);

private:
	int m_00;
	Rva0014F3E7 *m_04;
};

typedef Rva0014F699 *(__cdecl *Copy4Fn)(Rva0014F699 *first, Rva0014F699 *last, Rva0014F699 *result, void *tag);

// ?rva0015068C@Rva0015068C@@QAEPAVRva0014F699@@PAV2@0@Z present-unmatched
Rva0014F699 *Rva0015068C::rva0015068C(Rva0014F699 *result, Rva0014F699 *first)
{
	bool tag;
	Rva0014F3E7 *newEnd = (Rva0014F3E7 *)((Copy4Fn)Rva00150265Copy)(first, (Rva0014F699 *)m_04, result, &tag);
	Rva0014F8AEDestroy(newEnd, m_04);
	m_04 = newEnd;
	return result;
}
