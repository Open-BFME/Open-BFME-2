// cl: /Oy- /DNDEBUG /MD
// ?rva003F35B0@ConnectionVec@@QAEPAVLivingWorldRegionConnection@@PAV2@0@Z @0x003F35B0 51B
// Copy-destroy tail over LivingWorldRegionConnection ranges: rowed copy
// 0x003F325A with a 4-arg cast and dead-arg-slot dummy [ebp+0xb], then rowed
// DestroyRange 0x003F0CA1 over [mid m_finish), update m_finish, return first
// arg. Same shape as Rva003F3159Finish. Evidence: retail 4+2 pushes with
// add esp,0x18, ret 8, all callees rowed.
class LivingWorldRegionConnection;
class Rva003F2A11;
Rva003F2A11 *Rva003F325ACopy(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *);
typedef Rva003F2A11 *(__cdecl *Rva003F325A4Fn)(Rva003F2A11 *, Rva003F2A11 *, Rva003F2A11 *, void *);
void Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *, LivingWorldRegionConnection *);
struct ConnectionVec
{
	LivingWorldRegionConnection *rva003F35B0(LivingWorldRegionConnection *a, LivingWorldRegionConnection *b);
	LivingWorldRegionConnection *m_start;
	LivingWorldRegionConnection *m_finish;
	LivingWorldRegionConnection *m_end;
};
LivingWorldRegionConnection *ConnectionVec::rva003F35B0(LivingWorldRegionConnection *a, LivingWorldRegionConnection *b)
{
	Rva003F2A11 *mid = ((Rva003F325A4Fn)&Rva003F325ACopy)((Rva003F2A11 *)(void *)b, (Rva003F2A11 *)(void *)m_finish, (Rva003F2A11 *)(void *)a, (char *)&a + 3);
	Rva003F0CA1_DestroyRange((LivingWorldRegionConnection *)(void *)mid, m_finish);
	m_finish = (LivingWorldRegionConnection *)(void *)mid;
	return a;
}
