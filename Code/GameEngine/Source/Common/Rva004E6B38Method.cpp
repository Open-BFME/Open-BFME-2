// cl: /MD /EHsc
// InGameNotificationBoxMovieClip::CloseImmediately (WorldBuilder name, InGameNotificationBoxMovieClip.cpp line 230: unless state 0/1, clear, Hide, state 1, then clear both held pointers).
// was ?rva004E6B38@Rva004E6B38@@QAEXXZ @ 0x004E6B38 (69B): flag-guarded Hide callback via Rva0043DB23 then two OwnedPointerResets clears. Callers at 0x004E6B8E and 0x004E724B and jmp at 0x004E7019. Callees rowed 0x00524021 0x0043DB23 0x004E6A1D. Global TheRva00222A8BTarget and string Hide.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
void __cdecl Rva0043DB23(Rva00222A8BTarget *target, void *owner, const char *name);
class Rva00524021
{
public:
	void rva00524021();
private:
	void *m_begin;
	void *m_end;
};
class Rva004E6935
{
public:
	~Rva004E6935();
};
class Rva004E6A1D
{
public:
	Rva004E6935 *m_ptr;
	void clear();
};
class InGameNotificationBoxMovieClip
{
public:
	void CloseImmediately();
	unsigned char m_pad00[4];
	void *m_owner;
	int m_state;
	unsigned char m_pad0C[0x30 - 0x0C];
	Rva00524021 m_vec;
	unsigned char m_pad38[0x40 - 0x38];
	Rva004E6A1D m_hold40;
	Rva004E6A1D m_hold44;
};
void InGameNotificationBoxMovieClip::CloseImmediately()
{
	if (m_state != 0 && m_state != 1)
	{
		m_vec.rva00524021();
		Rva0043DB23(TheRva00222A8BTarget, m_owner, "Hide");
		m_state = 1;
	}
	m_hold40.clear();
	m_hold44.clear();
}
