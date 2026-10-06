// cl: /DNDEBUG /MD /EHsc
// ?changeWantOpenCount@GateOpenAndCloseBehavior@@QAEXH@Z @0x00498831 30B
// GateOpenAndCloseBehavior delta clamp-add at +0x40. Evidence: gap between
// Disp8ByteFieldGetters and GateOpenAndCloseBehaviorPoolKey; offset 0x40
// matches m_40 in GateOpenAndCloseBehaviorCtorShard; caller 0x003A23A5.
class GateOpenAndCloseBehavior
{
	char m_pad[0x40];
	int m_40;
public:
	void changeWantOpenCount(int delta);
};

void GateOpenAndCloseBehavior::changeWantOpenCount(int delta)
{
	if (delta == -1 || delta == 1) {
		if (m_40 < 0)
			m_40 = 0;
		m_40 += delta;
	}
}
