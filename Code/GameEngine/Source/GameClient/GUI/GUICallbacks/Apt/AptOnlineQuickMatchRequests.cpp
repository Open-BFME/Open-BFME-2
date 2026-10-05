// cl: /O1 /GX /MD
//
// BFME2's online quick match screen Apt callbacks
// "AptOnline::OnlineQuickMatch::WidenSearch" (0x005BAA2B) and "::Cancel"
// (0x005BAAA3), bound by those names as member pointers by the screen's
// registration; that binding is their only reference. Each posts a peer
// thread request (Rva0059FF9DDo.cpp's record and queue views).

struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();

	int unknown_00;
	unsigned char m_rest[0x1EC - 0x04];
};

struct Global003EF728V6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6(BfmeOpaqueOwnedRecord492 *rec);
};

extern Global003EF728V6 *g_00A02340;

// The online shell owning the screen (+0x58); its unrowed 0x00516F08 is
// pinned by address.
class Rva00516F08
{
public:
	void rva00516F08();
};

namespace AptOnline
{
class OnlineQuickMatch
{
public:
	void WidenSearch(const char *unused);
	void Cancel(const char *unused);

private:
	unsigned char m_pad00[0x58];
	Rva00516F08 *m_owner; // +0x58
	unsigned char m_pad5c[0x60 - 0x5C];
	int m_state; // +0x60
};
}

// Retail 0x005BAA2B, 88 bytes: "AptOnline::OnlineQuickMatch::WidenSearch"
// posts request 0x11.
void AptOnline::OnlineQuickMatch::WidenSearch(const char *unused)
{
	BfmeOpaqueOwnedRecord492 request;
	request.unknown_00 = 0x11;
	g_00A02340->f6(&request);
}

// Retail 0x005BAAA3, 104 bytes: "AptOnline::OnlineQuickMatch::Cancel" posts
// request 0x12, resets the state and tells the owner.
void AptOnline::OnlineQuickMatch::Cancel(const char *unused)
{
	BfmeOpaqueOwnedRecord492 request;
	request.unknown_00 = 0x12;
	g_00A02340->f6(&request);
	m_state = 0;
	m_owner->rva00516F08();
}
