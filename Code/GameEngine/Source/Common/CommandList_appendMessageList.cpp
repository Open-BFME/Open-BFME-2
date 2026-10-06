// cl: /DNDEBUG /MD /EHsc
// ?appendMessageList@CommandList@@QAEXPAVGameMessage@@@Z
// retail 0x0030F880, 34 bytes. Dedicated TU.
//
// ZH MessageStream.cpp shape verbatim (null-guarded walk calling virtual
// appendMessage per node, next() inline at +4). Retail calls appendMessage
// through primary-vtable slot 14 (0x38), eight slots later than the Zero
// Hour hierarchy used by MessageStream.cpp, so this TU carries a local
// replica with pad virtuals to hold the slot; the pad names are placeholders,
// only the count matters to the bytes. No /G7: it emits a loop-align nop
// retail does not have.

class GameMessage
{
public:
	GameMessage *next(void) { return m_next; }

private:
	void *vptr;
	GameMessage *m_next;
};

class CommandListReplica
{
public:
	virtual void pad00(void);
	virtual void pad01(void);
	virtual void pad02(void);
	virtual void pad03(void);
	virtual void pad04(void);
	virtual void pad05(void);
	virtual void pad06(void);
	virtual void pad07(void);
	virtual void pad08(void);
	virtual void pad09(void);
	virtual void pad10(void);
	virtual void pad11(void);
	virtual void pad12(void);
	virtual void pad13(void);
	virtual void appendMessage(GameMessage *msg);
};

class CommandList : public CommandListReplica
{
public:
	void appendMessageList(GameMessage *list);
};

// ?appendMessageList@CommandList@@QAEXPAVGameMessage@@@Z
void CommandList::appendMessageList(GameMessage *list)
{
	GameMessage *msg, *next;

	for (msg = list; msg; msg = next) {
		next = msg->next();
		appendMessage(msg);
	}
}
