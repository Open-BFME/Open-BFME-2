// cl: /Oy- /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?EraseRange@Rva004BA399Vector@@QAEPAVRva004BA1C8@@PAV2@0@Z, retail 0x004BA399 51B: range-erase via CopyRange plus DestroyRange.
// Evidence: same 51B shape as rowed ?EraseRange@Rva002983DAVector at 0x002983DA; callees rowed CopyRange 0x004BA324 plus DestroyRange 0x004BA341; callers at 0x004BA4CD plus 0x004BA6D1; prev/next rows in Rva004BA1C8Record.cpp.
class Rva004BA1C8;
Rva004BA1C8 *Rva004BA324CopyRange(Rva004BA1C8 *first, Rva004BA1C8 *last, Rva004BA1C8 *result, int dummy);
void Rva004BA341DestroyRange(Rva004BA1C8 *first, Rva004BA1C8 *last);
class Rva004BA399Vector {
public:
	Rva004BA1C8 *EraseRange(Rva004BA1C8 *first, Rva004BA1C8 *last);
private:
	int m_00;
	Rva004BA1C8 *m_finish;
	int m_08;
};
Rva004BA1C8 *Rva004BA399Vector::EraseRange(Rva004BA1C8 *first, Rva004BA1C8 *last)
{
	Rva004BA1C8 *newFinish = Rva004BA324CopyRange(last, m_finish, first, (int)((char *)&first + 3));
	Rva004BA341DestroyRange(newFinish, m_finish);
	m_finish = newFinish;
	return first;
}
