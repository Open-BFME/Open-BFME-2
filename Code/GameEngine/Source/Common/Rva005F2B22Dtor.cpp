// cl: /DNDEBUG /MD /EHsc
// ??1Rva005F2B22@@QAE@XZ retail 0x005F2B22 84B
// Non-virtual dtor of a polymorphic class: own vptr C79218; under EH state 1,
// when the holder at +0x20 is empty and the Apt window manager global
// g_bfmeAptWindowManager (VA 0x00DFE4CC) is set, the rowed
// ?rva005F2792@Rva005F2792@@QAEXXZ 0x005F2792 runs on this object; then the
// holder's inline dtor runs the rowed ?clear@Rva000AD6F4@@QAEXXZ 0x000AD6F4
// and the base's inline dtor restores C4EF80. Names address-derived.

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva005F2792
{
public:
	void rva005F2792();
};

class Rva000AD6F4
{
public:
	~Rva000AD6F4();
	void clear();

	void *m_ptr;
};

class Rva005F2B22Base
{
public:
	~Rva005F2B22Base() {}
	virtual void Rva005F2B22Slot0();
};

class Rva005F2B22 : public Rva005F2B22Base
{
public:
	~Rva005F2B22();

private:
	char m_pad04[0x20 - 4];
	Rva000AD6F4 m_holder; // +0x20
};

Rva005F2B22::~Rva005F2B22()
{
	if (m_holder.m_ptr == 0 && g_bfmeAptWindowManager)
		reinterpret_cast<Rva005F2792 *>(this)->rva005F2792();
}
