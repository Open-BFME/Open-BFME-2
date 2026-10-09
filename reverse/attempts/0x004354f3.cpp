// ?PromptAddFriend@AptSaveLoad@@SA_NXZ
// partial score=0.99 date=2026-10-09
// WB12AD250 PromptAddFriend and native4354F3..43566A establish static bool ABI.
// Complete375B, only key home -10 vs native -14 differs at two displacement bytes.
// Both branches bind named AddFriendConfirmationHandler; native53B Rva holder copy
// has its proven +4 reference lifetime. Four-byte one-member callback view restores
// stack-save order. EHs preserves C-linkage prompt cleanup states4/7.
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs
// Retail boundary 0x004354F3..0x0043566A is 375 bytes and ends in RET.
// Its caller at 0x00435CCC tests AL and falls through to the saved-game
// handler only when this routine declines to show the add-friend prompt.
// stlport
#include <map>
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

struct AptSaveLoadSlot
{
 const UnicodeString &getName() const { return m_name; }
	unsigned char m_pad000[0x30];
	UnicodeString m_name;
	unsigned char m_pad034[0x1AC - 0x34];
	int m_profileID;
};

class GameSpyGameSlot;


class RvaFriendProfileMap : public _STL::map<int, int>
{
};

class GameSpyInfoInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3c() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4c() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5c() = 0;
	virtual RvaFriendProfileMap *getFriendProfiles() = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;
extern int g_Va00E032E0;

class AptSaveLoad
{
public:
	static GameSpyGameSlot *GetOpponentSlotData();
	static void AddFriendConfirmationHandler(int);
	static bool PromptAddFriend();
	unsigned char m_pad000[0x27C];
	int m_state;
};

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva0023E8D8
{
public:
	Rva0023E8D8() : m_impl(0) {}
	~Rva0023E8D8() { if(m_impl)ReleaseTreeHintRef00217D4C((TargetRef00217D4C*)m_impl); }
	Rva0023E8D8(void *function);
	Rva0023E8D8(const Rva0023E8D8 &r) : m_impl(r.m_impl) {if(m_impl)++((int*)m_impl)[1];}
	void *m_impl;
};


struct CallbackStorage;
extern "C" void __cdecl Rva00437F61(int type,
	const UnicodeString &message, const UnicodeString &title,
	CallbackStorage callback);
extern "C" void __cdecl Rva0043802B(int type,
	const UnicodeString &message, const UnicodeString &title,
	CallbackStorage callback);

struct CallbackStorage {
 Rva0023E8D8 holder;
 CallbackStorage(void*p):holder(p){}
 CallbackStorage(const CallbackStorage&r):holder(r.holder){}
};
bool AptSaveLoad::PromptAddFriend()
{
	AptSaveLoadSlot *slot;
	RvaFriendProfileMap *profiles;
	if (!TheGameSpyInfo)
		goto declined;

	slot = (AptSaveLoadSlot *)AptSaveLoad::GetOpponentSlotData();
	if (!slot)
		goto declined;

	profiles = TheGameSpyInfo->getFriendProfiles();
	if (!profiles)
		goto declined;
	int profile = slot->m_profileID;
	if (profiles->find(profile) != profiles->end())
		goto declined;
	goto show_prompt;

declined:
	return false;

show_prompt:
	{
		UnicodeString message;
	{
			message.format(TheGameText->fetch("APT:AddFriendOnSaveDescription",0).str(), slot->getName().str());
		}

		if (g_Va00E032E0)
		{
			void (__cdecl *callback)(int) = AptSaveLoad::AddFriendConfirmationHandler;
			Rva0043802B(2, TheGameText->fetch("APT:AddFriendOnSaveTitle", 0),
				message,
				CallbackStorage(&callback));
			((AptSaveLoad *)g_Va00E032E0)->m_state = 0x0C;
		}
		else
		{
			void (__cdecl *callback)(int) = AptSaveLoad::AddFriendConfirmationHandler;
			Rva00437F61(2, TheGameText->fetch("APT:AddFriendOnSaveTitle", 0),
				message,
				CallbackStorage(&callback));
		}
	}
	return true;
}
