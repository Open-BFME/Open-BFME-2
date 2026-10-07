// cl: /O1 /DNDEBUG /MD
// Reconstruction of the 58B dense-wheel copier at 0x00319831: when the
// Drawable wheel info is present and dense, run the pinned 0x538ED1
// worker on the second fetch, then mirror +0x44/+0x48 into +0x3C/+0x40;
// then run the rowed listener forEach on the +0x08 list and tail-jump
// the rowed 0x3195C9 gate. The 0x538ED1 worker reads its second word
// from the stale stack slot holding pushed-esi (the owner), so it is
// declared here taking only this (no pushes emitted); the bytes and the
// runtime owner both match. The second getWheelInfo call reuses stale
// ecx with no reload, which MSVC does not emit for an opaque thiscall,
// so it is pinned as a callee-cleanup free function (same bytes).
struct TWheelInfo
{
	int m_begin;
	int m_end;
};

class Drawable
{
public:
	const TWheelInfo *getWheelInfo() const;
};

const TWheelInfo *__stdcall rva00318B83Free(void *arg);

class Rva00538ED1
{
public:
	void rva00538ED1();
};

class Rva003197EEListener
{
public:
	virtual void notify(void *);
};

class Rva003197EEList
{
public:
	void forEach(void (Rva003197EEListener::*notify)(void *), void *arg);
};

class Rva003195C9Owner : public Drawable
{
public:
	void rva00319831(void *arg);
private:
	unsigned char m_pad[0x3c];
	int m_3c;
	int m_40;
	int m_44;
	int m_48;
};

void Rva003195C9Owner::rva00319831(void *arg)
{
	const TWheelInfo *info = getWheelInfo();
	if (info != 0)
	{
		const TWheelInfo *info2 = rva00318B83Free(arg);
		((Rva00538ED1 *)info2)->rva00538ED1();
	}
	m_3c = m_44;
	m_40 = m_48;
	union {
		int addr;
		void (Rva003197EEListener::*notify)(void *);
	} u;
	u.addr = 0x9cb26a;
	((Rva003197EEList *)(((char *)this) + 8))->forEach(u.notify, this);
}
