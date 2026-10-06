// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005FFA4E@Rva005FFA4E@@QAEXH@Z @ 0x005FFA4E 8B
// Forwarder: this+4 holds Rva005FF450 object; tail-jmps to its 0x005FF9D8 SetUnitIconCount.
// Evidence: chain via 0x005FF9D8 row; caller 0x005FF061 push int mov ecx ebx esi+8; layout +4 ptr.
class Rva005FF450
{
public:
	void rva005FF9D8(int count);
};

class Rva005FFA4E
{
public:
	void rva005FFA4E(int count);
private:
	char m_pad0[4];
	Rva005FF450 *m_obj;
};

void Rva005FFA4E::rva005FFA4E(int count)
{
	m_obj->rva005FF9D8(count);
}
