// cl: /Oy- /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?EraseRange@Rva00566B81Vector@@QAEPAVRva00566695@@PAV2@0@Z @0x00566B81 51B.
// Range-erase via rowed CopyRange 0x00566A9A plus rowed DestroyRange 0x003F0CA1.
// Evidence: chain lane; callers at 0x00566BF0 plus 0x00566D46; same 51B shape
// as rowed EraseRange at 0x004BA399. Element type is Rva00566695 (stride 0x18)
// for CopyRange; DestroyRange is rowed under LivingWorldRegionConnection
// (same 0x18 stride same vector finish at +4) so the range is forwarded
// through a pointer cast. No new pins.
class Rva00566695;
Rva00566695 *Rva00566A9ACopyRange(Rva00566695 *first, Rva00566695 *last, Rva00566695 *result, int dummy);
class LivingWorldRegionConnection;
void Rva003F0CA1_DestroyRange(LivingWorldRegionConnection *first, LivingWorldRegionConnection *last);
class Rva00566B81Vector {
public:
	Rva00566695 *EraseRange(Rva00566695 *first, Rva00566695 *last);
private:
	int m_00;
	Rva00566695 *m_finish;
	int m_08;
};
Rva00566695 *Rva00566B81Vector::EraseRange(Rva00566695 *first, Rva00566695 *last)
{
	Rva00566695 *newFinish = Rva00566A9ACopyRange(last, m_finish, first, (int)((char *)&first + 3));
	Rva003F0CA1_DestroyRange((LivingWorldRegionConnection *)newFinish, (LivingWorldRegionConnection *)m_finish);
	m_finish = newFinish;
	return first;
}
