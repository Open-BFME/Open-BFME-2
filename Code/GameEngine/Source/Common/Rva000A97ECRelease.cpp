// cl: /O1 /MD /EHsc /DNDEBUG
// ?rva000A97EC@Rva000A97EC@@QAE_N_N@Z @0x000A97EC 26B: zero-and-release.
// Clears +0x0, frees this through the rowed operator delete when the flag
// bit is set, and returns this. Honest address-derived names; boundary
// verified (push esi at 0xA97EC, pop + ret 4 at end).
void operator delete(void *p);
class Rva000A97EC {
public:
	Rva000A97EC *rva000A97EC(bool b);
private:
	int m_0;
};
Rva000A97EC *Rva000A97EC::rva000A97EC(bool b)
{
	m_0 = 0;
	if (b & 1)
		::operator delete(this);
	return this;
}
