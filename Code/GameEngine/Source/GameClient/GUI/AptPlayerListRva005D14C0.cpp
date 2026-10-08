// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
// ?rva005D14C0@Rva005D14C0@@QAEXXZ @ 0x005D14C0, 86 bytes.
// Target evidence: the body begins at 0x005D14C0 and returns at 0x005D1515.
// It invokes the row-view fade/dispatch helper at 0x005D13C2, reads the
// selected row through the rowed 0x005C792C getter, then emits message 0x6B7
// with the host index and selected entry's +0x14 value. The MessageStream
// vtable call and both GameMessage appends are rowed. Pointer fields and the
// meaning of the message remain structural inferences; class identity is
// unknown and the method name is address-derived.

class GameMessage
{
public:
	void appendIntegerArgument(int value);
};

class MessageStream
{
public:
	virtual ~MessageStream();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *CreateMessage(int type);
};
extern class MessageStream *TheMessageStream;

class Rva000B3FD0NullTarget
{
public:
	void rva000B3FD0();
};

class Rva005ED976
{
public:
	void rva005ED5EB();
};

class Rva005D13C2DispatchTarget
{
public:
	virtual void v0();
	virtual void dispatch();
};

class Rva005D13C2
{
public:
	void rva005D13C2();
	Rva005D13C2DispatchTarget *m_dispatch;
	char m_pad04[4];
	void *m_messageHost;
	Rva005ED976 *m_view;
	char **m_entries;
};

class Rva00005C792CPtrChaseField
{
public:
	int get() const;
};

struct Rva005D14C0MessageHost
{
	char m_pad00[4];
	int m_value04;
};

struct Rva005D14C0Entry
{
	char m_pad00[0x14];
	int m_value14;
};

class Rva005D14C0
{
public:
	void rva005D14C0();

private:
	char m_pad00[8];
	Rva005D13C2 *m_data;
};

void Rva005D14C0::rva005D14C0()
{
	reinterpret_cast<Rva000B3FD0NullTarget *>(this)->rva000B3FD0();
	m_data->rva005D13C2();

	int index = reinterpret_cast<Rva00005C792CPtrChaseField *>(m_data->m_view)->get();
	Rva005D14C0Entry *entry = (Rva005D14C0Entry *)m_data->m_entries[index];
	GameMessage *message = TheMessageStream->CreateMessage(0x6B7);
	message->appendIntegerArgument(((Rva005D14C0MessageHost *)m_data->m_messageHost)->m_value04);
	message->appendIntegerArgument(entry->m_value14);
}
