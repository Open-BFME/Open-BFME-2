// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ?rva005974CC@Rva0059734B@@UAEXPAVXfer@@PAX@Z @0x005974CC 244B: slot12 xfer override pruning via AsciiString and command buttons; vtable 0x00870BD0 caller 0x005972B3
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

enum ObjectID
{
	INVALID_ID = 0
};

class Object
{
public:
	const AsciiString *rva00290E67() const;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

struct BfmeWorldRV;
extern BfmeWorldRV *g_bfmeWorldRV;

class Rva0031D5F8
{
public:
	void *rva0031D5F8(const AsciiString *s);
};

class CommandButton
{
public:
	char m_pad00[0x10];
	AsciiString m_10;
};

class CommandSet
{
public:
	const CommandButton *getCommandButton(int i) const;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool IsLoading();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(void *p);
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27(AsciiString &s);
	virtual void v28();
	virtual void v29();
	virtual void v29b();
	virtual void v30(int &i);
	virtual void v31();
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
	virtual void Rva0055AED6(Xfer *x, void *p);
protected:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva0059734B : public Rva0055B0CC
{
public:
	virtual void rva005974CC(Xfer *x, void *p);
private:
	int m_2C;
	CommandButton *m_30;
};

struct TwoBytes
{
	bool a;
	bool b;
};

void Rva0059734B::rva005974CC(Xfer *x, void *p)
{
	TwoBytes t;
	t.a = true;
	t.b = true;
	x->v10(&t);
	Rva0055B0CC::Rva0055AED6(x, p);
	x->v30(m_2C);
	const AsciiString *src;
	if (m_30 != 0)
		src = &m_30->m_10;
	else
		src = &AsciiString::TheEmptyString;
	AsciiString tmp(*src);
	x->v27(tmp);
	if (!x->IsLoading())
		return;
	_ReadWriteBarrier();
	if (((const StringBase<char> *)&tmp)->compare(*(const StringBase<char> *)&AsciiString::TheEmptyString) == 0)
		return;
	Object *obj = TheGameLogic->findObjectByID(m_08);
	if (obj == 0)
		return;
	const AsciiString *name = obj->rva00290E67();
	void *world = ((Rva0031D5F8 *)g_bfmeWorldRV)->rva0031D5F8(name);
	for (int i = 0; i < 0x20; ++i)
	{
		if (m_30 != 0)
			break;
		const CommandButton *b = ((CommandSet *)world)->getCommandButton(i);
		if (b != 0)
		{
			if (((const StringBase<char> *)&b->m_10)->compare(*(const StringBase<char> *)&tmp) == 0)
			{
				m_30 = (CommandButton *)b;
			}
		}
	}
}
