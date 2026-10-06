// cl: /O1 /MD /EHsc
// ??1NetGameCommandMsg@@UAE@XZ retail 0x004D5609 84B
// Zero Hour NetGameCommandMsg::~NetGameCommandMsg shape: unlink and delete
// each GameMessageArgument from the list head at +0x28 (next at +4); retail
// deletes (deleteInstance) through the slot-0 deleting dtor with flag 0 followed by the global
// ??3@YAXPAX@Z (a global-scope delete). Own vptr C601E4; the inline base dtor
// restores C60130. The delete sits in a forced-inline helper so its null test
// survives as in retail. Helper class names are local.

class NetGameCommandMsgArg
{
public:
	virtual ~NetGameCommandMsgArg();

	NetGameCommandMsgArg *m_next; // +0x04
};

__forceinline void deleteInstance(NetGameCommandMsgArg *arg)
{
	::delete arg;
}

class NetGameCommandMsgBase
{
public:
	virtual ~NetGameCommandMsgBase() {}

private:
	unsigned char m_pad04[0x28 - 4];
};

class NetGameCommandMsg : public NetGameCommandMsgBase
{
public:
	virtual ~NetGameCommandMsg();

private:
	NetGameCommandMsgArg *m_argList; // +0x28
};

NetGameCommandMsg::~NetGameCommandMsg()
{
	NetGameCommandMsgArg *arg = m_argList;
	while (arg != 0)
	{
		m_argList = m_argList->m_next;
		deleteInstance(arg);
		arg = m_argList;
	}
}




