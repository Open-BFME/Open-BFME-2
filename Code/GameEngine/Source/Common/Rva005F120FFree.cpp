// ?rva005F120F@Rva005F120F@@QAEXXZ @0x005F120F 30B.
// Buffer-owning clear without EH: range clear of (m_first, m_last) via rowed
// 0x005EF5EF, then frees the buffer when non-null. No guard and no try, so no
// EH frame unlike its 63B twins at 0x005EF8BB/0x005F11D0. The post-call reload
// matches a second m_first read after the call.
// Evidence: same Clear+free shape; callers at 0x005EFC14/0x005F1268/0x005F13B0.
// cl: /MD
struct Rva005F0647;
void __cdecl Rva005EF5EFClear(Rva005F0647 *first, Rva005F0647 *last);
extern "C" void __cdecl free(void *block);
class Rva005F120F
{
public:
	void rva005F120F();

	Rva005F0647 *m_first;
	Rva005F0647 *m_last;
};
void Rva005F120F::rva005F120F()
{
	Rva005EF5EFClear(m_first, m_last);
	if (m_first != 0)
		free(m_first);
}
