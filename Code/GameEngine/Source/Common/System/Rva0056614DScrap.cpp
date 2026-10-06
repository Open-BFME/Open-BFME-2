// cl: /DNDEBUG /MD /GX-
//
// ?rva0056614D@Rva0056614DVec@@QAEXXZ retail 0x0056614D 30B
// Evidence: chain lane; callee Rva0052CEF6Clear 0x0052CEF6 plus _free 0x00030830; caller 0x00566645; prev ScrapStorage same shape same flags; members start finish end.
extern "C" void __cdecl free(void *block);
class Rva004E366E
{
public:
	void rva004E366E();
private:
	char m_pad[12];
};
void __cdecl Rva0052CEF6Clear(Rva004E366E *first, Rva004E366E *last);
struct Rva0056614DVec
{
	void rva0056614D();
	Rva004E366E *m_start;
	Rva004E366E *m_finish;
	Rva004E366E *m_end;
};
void Rva0056614DVec::rva0056614D()
{
	Rva0052CEF6Clear(m_start, m_finish);
	Rva004E366E *start = m_start;
	if (start != 0)
		free(start);
}
