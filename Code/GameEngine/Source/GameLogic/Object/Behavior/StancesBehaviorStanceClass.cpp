// cl: /O1 /DNDEBUG /MD
//
// ?rva0045ED4B@StancesBehavior@@QBEHXZ, retail 0x0045ED4B, 27 bytes, just
// before the rowed StancesBehaviorModuleData::buildFieldParse (0x0045ED8C)
// and StancesBehavior::xfer (0x0045ED9D). Classifies the +0x30 stance:
// 2 stays 2, 3..5 give 3, anything else 1. Nine callers, among them the
// slot 0x005D7305 that reaches it through Object::findModule with the
// rowed StancesBehavior name key. Ghidra-listed, previously unrowed;
// address-derived method name.

typedef int Int;

class StancesBehavior
{
public:
	Int rva0045ED4B() const;
private:
	char m_pad00[0x30];
	Int m_stance30;
};

Int StancesBehavior::rva0045ED4B() const
{
	switch (m_stance30)
	{
	case 2:
		return 2;
	case 3:
	case 4:
	case 5:
		return 3;
	}
	return 1;
}
