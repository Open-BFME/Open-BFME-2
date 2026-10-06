// cl: /MD /EHsc
//
// ?rva005FFED5@Rva005FFED5@@QAEXH@Z @ 0x005FFED5 8B
// Forwarder: this+4 holds Rva005FFC26 object; tail-jmps to its SetState 0x005FFC26.
// Evidence: unlock via 0x005FFC26 row; callers 0x005FB054 0x005FB33B 0x005FB510; layout +4 ptr;
// precedent Rva005FF4BDForward 0x005FF4BD and Rva005FFA4EForward 0x005FFA4E.
class Rva005FFC26
{
public:
	void rva005FFC26(int state);
};

class Rva005FFED5
{
public:
	void rva005FFED5(int state);
private:
	char m_pad0[4];
	Rva005FFC26 *m_obj;
};

void Rva005FFED5::rva005FFED5(int state)
{
	m_obj->rva005FFC26(state);
}
