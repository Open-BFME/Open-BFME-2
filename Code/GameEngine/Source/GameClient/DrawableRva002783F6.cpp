// cl: /O1 /DNDEBUG /MD
//
// ?rva002783F6@Rva002783F6Host@@QAEXH@Z, retail 0x002783F6, 74B: a Drawable
// member (this goes straight to the rowed Drawable::stopAmbientSound), rowed
// under the host name its 5 matched callers use. Target evidence: when the
// three flag bytes +0x447/+0x448/+0x44A are all set, it runs 0x002743D7,
// asks the owning Object (+0xFC) for its +0x254 module's slot-8 answer (0
// without an object) and passes that and the argument to 0x00278341.
// Names past that are placeholders.
template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <> class BfmeVirtualSlots<0> {};

class Rva002783F6Module : public BfmeVirtualSlots<8>
{
public:
	virtual int rva002783F6Query();		// slot 8 (+0x20)
};

class Object
{
public:
	unsigned char m_pad0[0x254];
	Rva002783F6Module *m_x254;		// +0x254
};

class Drawable
{
public:
	void stopAmbientSound();			// 0x002743D7
};

class Rva002783F6Host
{
public:
	void rva002783F6(int v);
	void rva00278341(int query, int v); // 0x00278341
	char m_pad00[0xFC];
private:
	Object *m_object; // +0xFC
	char m_pad100[0x347];
	unsigned char m_x447; // +0x447
	unsigned char m_x448; // +0x448
	char m_pad449[0x1];
	unsigned char m_x44A; // +0x44A
	char m_pad44B[0x1];
};
class Rva00278341Host
{
public:
	void rva00278341(int query, int v);	// 0x00278341
};

void Rva002783F6Host::rva002783F6(int v)
{
	if (m_x447 && m_x448 && m_x44A)
	{
		((Drawable *)this)->stopAmbientSound();
		Object *obj = m_object;
		int query = 0;
		if (obj)
			query = obj->m_x254->rva002783F6Query();
		((Rva00278341Host *)this)->rva00278341(query, v);
	}
}
