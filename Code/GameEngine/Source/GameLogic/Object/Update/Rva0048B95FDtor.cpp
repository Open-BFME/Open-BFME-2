// cl: /O1 /DNDEBUG /MD /GX-
//
// ??1Rva0048B95F@@QAE@XZ, retail 0x0048B95F, 27 bytes. Watchlist-value dtor:
// releases the tracked pointer at +0 through its slot0 virtual with 0,
// frees the return via operator delete, then zeroes the slot. Called with
// value-this from the FireWeaponUpdate behavior dtor (rowed 0x48BD11 via
// the Rva0048B95FHelper pin) and from the value deleting-dtor 0x48B9B4.
// Rva-addressed honest name (twin Rva003A4CAE precedent); do-not-name the
// value class without an element-type ID. Zero new pins (all callees rowed).

struct Rva0048B95FTracked
{
	virtual void *deleteInstance(int flags);
};

class Rva0048B95F
{
public:
	~Rva0048B95F();
private:
	Rva0048B95FTracked *m_tracked;	// +0
};

// ??1Rva0048B95F@@QAE@XZ @0x0048B95F
Rva0048B95F::~Rva0048B95F()
{
	if (m_tracked != 0) {
		::operator delete(m_tracked->deleteInstance(0));
	}
	m_tracked = 0;
}
