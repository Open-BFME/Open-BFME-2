// cl: /DNDEBUG /MD /EHsc
// ?createMessageStream@GameEngine@@MAEPAVMessageStream@@XZ @0x00225F12 50B vslot 30
// (Zero Hour's protected virtual GameEngine::createMessageStream factory)
// factory returning new MessageStream via rowed operator new 0x0002FDA0 plus
// rowed ctor 0x0030F697 with EH prolog. Evidence: vslot 30 of GameEngine and
// Win32GameEngine vtables; no callers; same this forwarded.

void *__cdecl operator new(unsigned int size);

class MessageStream
{
public:
	MessageStream();

private:
	char m_pad00[0x20];
};

class GameEngine
{
public:
protected:
	virtual MessageStream *createMessageStream(void);
};

MessageStream *GameEngine::createMessageStream(void)
{
	return new MessageStream;
}
