// ?rva0028ABFC@Object@@QAEXM@Z
// partial score=0.99 date=2026-10-05
// cl: /O1 /DNDEBUG /MD
// ?rva0028ABFC@Object@@QAEXM@Z
// recovered from packet 0x0028ABFC 56B lane=unlock
// Evidence: rowed init 0x007584C0 and 0x002710EC; row 0x006BEB00 bfmeOneCNG takes void* but retail passes float via fld/fstp so declared float here (row types wrong); callers 0x004BE924 etc; prev/next Object TUs /O1 /DNDEBUG /MD; abuts next 0x0028AC34.
// ?rva0028ABFC@Object@@QAEXM@Z present-unmatched
class BfmeSubCNG
{
public:
	void bfmeOneCNG(float v);
};

class Rva009A2350
{
public:
	void init();
};

class Rva002710EC
{
public:
	void rva002710EC();
};

class Object
{
public:
	void rva0028ABFC(float f);
private:
	char _00[0x84];
	Rva002710EC *m_84;
	char _88[0x20];
	BfmeSubCNG m_a8;
	char _ac[0x420];
	Rva009A2350 *m_4cc;
};

void Object::rva0028ABFC(float f)
{
	((BfmeSubCNG *)((char *)this + 0xA8))->bfmeOneCNG(f);
	Rva009A2350 *p = m_4cc;
	if (p != 0) {
		p->init();
	}
	Rva002710EC *q = m_84;
	if (q != 0) {
		q->rva002710EC();
	}
}
