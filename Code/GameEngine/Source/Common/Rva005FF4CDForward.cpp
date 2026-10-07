// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FF4CD@Rva005FF4CD@@QAEX_N@Z @ 0x005FF4CD 8B
// Forwarder: this+4 holds Rva005FF328 object; tail-jmps to its rva005FF328.
// Evidence: callers 0x005FAE2A 0x005FAE4B 0x005FA8C8; prev 0x005FF4BD same +4 forwarder precedent; callee rowed 0x005FF328.
class Rva005FF328
{
public:
	void rva005FF328(bool flag);
};

class Rva005FF4CD
{
public:
	void rva005FF4CD(bool flag);
private:
	char m_pad0[4];
	Rva005FF328 *m_obj;
};

void Rva005FF4CD::rva005FF4CD(bool flag)
{
	m_obj->rva005FF328(flag);
}
