// cl: /MD /EHsc
//
// ??1Rva005FFB89@@QAE@XZ @ 0x005FFB89 (61B).
// Dtor of 8-byte record with two hint-ref holders at +0 and +4.
// Evidence: release row 0x0007DEEF; callers 0x005FFBFC;
// precedent Rva005F918DDtor holder with forceinline Release dtor.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva005FFB89Holder
{
	TargetRef00217D4C *m_ptr;
	__forceinline ~Rva005FFB89Holder() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};

class Rva005FFB89
{
public:
	~Rva005FFB89();
private:
	Rva005FFB89Holder m_h0;
	Rva005FFB89Holder m_h4;
};

Rva005FFB89::~Rva005FFB89() {}
