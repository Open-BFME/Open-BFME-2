// cl: /DNDEBUG /MD /GX-
//
// ?rva0056612F@Rva0056612FVec@@QAEXXZ retail 0x0056612F 30B
// Evidence: unlock lane; callee Rva0052CEDDClear 0x0052CEDD plus _free 0x00030830; caller 0x0056644E; prev ScrapStorage and next 0x0056614D same shape same flags; members start finish end.
extern "C" void __cdecl free(void *block);
class Rva004E1A04
{
public:
	~Rva004E1A04();
private:
	char m_pad[16];
};
void __cdecl Rva0052CEDDClear(Rva004E1A04 *first, Rva004E1A04 *last);
struct Rva0056612FVec
{
	void rva0056612F();
	Rva004E1A04 *m_start;
	Rva004E1A04 *m_finish;
	Rva004E1A04 *m_end;
};
void Rva0056612FVec::rva0056612F()
{
	Rva0052CEDDClear(m_start, m_finish);
	Rva004E1A04 *start = m_start;
	if (start != 0)
		free(start);
}
