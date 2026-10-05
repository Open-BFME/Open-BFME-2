// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?makeStateMachine@AnimalAIUpdate@@MAEPAVAIStateMachine@@XZ, retail
// 0x0047EC69, 63 bytes: slot 150 of AnimalAIUpdate's primary vtable
// 0x00C47B98, the slot where the matched AIUpdateInterface::makeStateMachine
// 0x00262513 sits in the AIUpdate family. Same body with AnimalAIUpdate's own
// machine key 0xD7F450E0 (the base passes 0x4A9A0E38): a 0x68-byte
// AIStateMachine for the owner (pinned ctor 0x00351C48).
typedef unsigned int UnsignedInt;

class Object;

class AIStateMachine
{
public:
	AIStateMachine(Object *owner, UnsignedInt nameKey);
	unsigned char m_unmodelled_00[0x68];
};

class AIUpdateInterface
{
public:
	virtual ~AIUpdateInterface();
	Object *getObject() const { return m_object; }
protected:
	virtual AIStateMachine *makeStateMachine();
	const void *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class AnimalAIUpdate : public AIUpdateInterface
{
protected:
	virtual AIStateMachine *makeStateMachine();
};

AIStateMachine *AnimalAIUpdate::makeStateMachine()
{
	return new AIStateMachine(getObject(), 0xD7F450E0);
}
