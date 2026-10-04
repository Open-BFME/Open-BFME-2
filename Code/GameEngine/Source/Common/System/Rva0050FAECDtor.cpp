// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ??1Rva0050FAEC@@UAE@XZ retail 0x0050FAEC 11B
// Trivial dtor: stores vtable 0x00865518 then tail-jmps to pinned base dtor
// 0x005248D0. Evidence: 11B mov-plus-jmp shape, no EH prolog, caller 0x0050E7C8,
// unwind funclets at 0x007948B2/0x00794921/0x00794956 reference it.
class Rva005248D0
{
public:
	virtual ~Rva005248D0();
};

class Rva0050FAEC : public Rva005248D0
{
public:
	virtual ~Rva0050FAEC();
};

Rva0050FAEC::~Rva0050FAEC()
{
}
