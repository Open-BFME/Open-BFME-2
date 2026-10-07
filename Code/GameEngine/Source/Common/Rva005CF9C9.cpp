// cl: /MD /EHsc
// StrategicInGameUI::BattleResolver::Impl::PromptStateHandler::SendResolutionMethodMessage (WorldBuilder name, lines 553..556: message 0x6A7 with the method and the battle id).
// was ?rva005CF9C9@Rva005CF9C9@@QAEXH@Z @0x005CF9C9 54B
// Emits GameMessage type 0x6a7 via MessageStreamSubsystem slot 0x48 then appends arg and [this+4]+0x14+0x30.
// Evidence: unlock lane; callees rowed 0x0030F936 appendIntegerArgument; global MessageStreamSubsystem at VA 0x00A00950; callers 0x005D0DBB 0x005D0E10 pass this-8 and one int (ret 4).
#include <new>

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
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

extern MessageStream *MessageStreamSubsystem;

struct Rva005CF9C9Inner
{
	char _00[0x30];
	int m_30;
};

struct Rva005CF9C9Mid
{
	char _00[0x14];
	Rva005CF9C9Inner *m_14;
};

class Rva00575674Sub
{
public:
	void rva00575674(void *state);
};

// A partial owner view: both callbacks address the state slot at +0x1C.
struct Rva005D0DBBOwner
{
	char _00[0x1C];
	Rva00575674Sub m_state;
};

// Native constructor boundary 0x005D0AD5..0x005D0B5E: RET8, EAX=this.
// Both callbacks independently allocate 0x1C bytes and pass owner, method.
// The original state class name and the rest of its fields are unresolved.
class Rva005D0AD5
{
public:
	Rva005D0AD5(Rva005CF9C9Mid *owner, int method);
private:
	char _00[0x1C];
};

// The 20-byte alternative state has an existing verified constructor at
// 0x005D0C31. These are its provider's two base declarations and layout.
class Rva005CF8A1
{
public:
	Rva005CF8A1(void *owner);
	virtual ~Rva005CF8A1();
private:
	char _04[0x0C];
};

class Rva005D0C31Second
{
public:
	virtual ~Rva005D0C31Second();
};

class Rva005D0C31 : public Rva005CF8A1, public Rva005D0C31Second
{
public:
	Rva005D0C31(void *owner);
	virtual ~Rva005D0C31();
};

namespace StrategicInGameUI
{
class BattleResolver
{
public:
	class Impl;
};
class BattleResolver::Impl
{
public:
	class PromptStateHandler;
};
}
class StrategicInGameUI::BattleResolver::Impl::PromptStateHandler
{
public:
	void SendResolutionMethodMessage(int arg);
private:
	char _00[4];
	Rva005CF9C9Mid *m_04;
};

void StrategicInGameUI::BattleResolver::Impl::PromptStateHandler::SendResolutionMethodMessage(int arg)
{
	GameMessage *msg = MessageStreamSubsystem->CreateMessage(0x6a7);
	msg->appendIntegerArgument(arg);
	msg->appendIntegerArgument(m_04->m_14->m_30);
}

// Function-pointer entries at VA 0x00C752B8 and 0x00C752BC independently
// establish these callbacks. Their receiver adjustment (-8), owner field
// (-4), message values (1 and 3), allocation size and constructor ABI all
// come from the respective 85-byte retail boundaries. Address-derived names
// preserve the uncertainty about the original callback class and methods.
class Rva005D0DBBCallback
{
public:
	virtual void rva005D0DBB();
	virtual void rva005D0E10();
	virtual void rva005D0E65();
private:
	Rva005CF9C9Mid *owner() const
	{
		return *reinterpret_cast<Rva005CF9C9Mid *const *>(
			reinterpret_cast<const char *>(this) - 4);
	}
};

void Rva005D0DBBCallback::rva005D0DBB()
{
	reinterpret_cast<StrategicInGameUI::BattleResolver::Impl::PromptStateHandler *>(
		reinterpret_cast<char *>(this) - 8)->SendResolutionMethodMessage(1);
	Rva005D0AD5 *state = new Rva005D0AD5(
		*reinterpret_cast<Rva005CF9C9Mid **>(reinterpret_cast<char *>(this) - 4), 1);
	reinterpret_cast<Rva005D0DBBOwner *>(owner())->m_state.rva00575674(state);
}

void Rva005D0DBBCallback::rva005D0E10()
{
	reinterpret_cast<StrategicInGameUI::BattleResolver::Impl::PromptStateHandler *>(
		reinterpret_cast<char *>(this) - 8)->SendResolutionMethodMessage(3);
	Rva005D0AD5 *state = new Rva005D0AD5(
		*reinterpret_cast<Rva005CF9C9Mid **>(reinterpret_cast<char *>(this) - 4), 3);
	reinterpret_cast<Rva005D0DBBOwner *>(owner())->m_state.rva00575674(state);
}

// VA 0x00C752C0 points here. Retail independently supplies message value 2,
// a 0x14-byte allocation and the one-argument constructor 0x005D0C31.
void Rva005D0DBBCallback::rva005D0E65()
{
	reinterpret_cast<StrategicInGameUI::BattleResolver::Impl::PromptStateHandler *>(
		reinterpret_cast<char *>(this) - 8)->SendResolutionMethodMessage(2);
	Rva005D0C31 *state = new Rva005D0C31(
		*reinterpret_cast<Rva005CF9C9Mid **>(reinterpret_cast<char *>(this) - 4));
	reinterpret_cast<Rva005D0DBBOwner *>(owner())->m_state.rva00575674(state);
}
