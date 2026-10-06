// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF4BD@Rva005FF4BD@@QAEXH@Z @ 0x005FF4BD 8B
// Forwarder: this+4 holds Rva005FF267 object; tail-jmps to its SetState.
// Evidence: chain via 0x005FF267 row; callers 0x005FF124 push 0 lea ecx esi+8 and 0x006004EF; layout +4 ptr.
class Rva005FF267
{
public:
	void rva005FF267(int state);
};

class Rva005FF4BD
{
public:
	void rva005FF4BD(int state);
private:
	char m_pad0[4];
	Rva005FF267 *m_obj;
};

void Rva005FF4BD::rva005FF4BD(int state)
{
	m_obj->rva005FF267(state);
}
