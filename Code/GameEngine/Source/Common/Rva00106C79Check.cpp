// cl: /O1 /DNDEBUG /MD
//
// ?rva00106C79@Rva00106C79Holder@@QAE_NHH@Z @0x00106C79 37B bool.
// Retail (this=esi Holder, 2 int args, ret 8): if (m_08!=6) return false;
// ((Rva007E3410Object*)this)->invokeForMode() via rowed 0x00106A06;
// return this->rva00106970(a1,a2) via pin 0x00106970.
// Names opaque (callee class view minimal for rowed call); pin proves nothing.
class Rva007E3410Object
{
public:
	void invokeForMode(void);
};

class Rva00106C79Holder
{
public:
	bool rva00106C79(int a1, int a2);
	bool rva00106970(int a1, int a2);
private:
	char m_pad00[8];
	int m_08; // +0x08 cmp 6
};

bool Rva00106C79Holder::rva00106C79(int a1, int a2)
{
	if (m_08 == 6) {
		((Rva007E3410Object *)this)->invokeForMode();
		return rva00106970(a1, a2);
	}
	return false;
}
