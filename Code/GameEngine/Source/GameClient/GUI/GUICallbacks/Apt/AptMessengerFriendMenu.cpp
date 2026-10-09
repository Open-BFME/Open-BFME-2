// cl: /O1 /arch:SSE /G7 /EHs /EHc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva005AEBD3@AptMessenger@@QAEXXZ, retail 0x005AEBD3..0x005AED3C (361 bytes)
// thiscall RET 0.
//
// Friend-list context menu refresh of the AptMessenger screen (same receiver
// and file family as the rowed AptMessenger members 0x005AE7C6..0x005AEA3E;
// reached through the 0x005AF117 dispatcher on g_Va00E046BC == 0). It resets
// the two entries of the menu vector at +0x28C to "APT:RemoveFriend" /
// "APT:InviteToPlay" (rowed StringBase<char>::set 0x000055F5) and clears
// their enable bytes and the +0x2A0 flag; reads the selection through the
// rowed AptMessenger::GetSelectedPlayers 0x00511C19 into a vector<int>
// (rowed _Vector_base ctor 0x00211E58); with exactly one selected player it
// snapshots the buddy list (rowed MyBuddyList_ ctor 0x005AEB2C -- the WB
// name) and looks the player up (rowed 0x005AE7A5), counting hits, online
// entries and entries whose record status (+0x10) is neither 0 nor 2. Hits
// enable "remove"; pending entries enable "invite" only offline and when the
// g_Va00E063EC query (rowed 0x0059EF33) holds; online entries turn the second
// entry into an enabled "APT:AcceptFriend" and set +0x2A0. WB twin 0x01515780
// (unnamed) has the same strings and order. The method name is
// address-derived; entry/field names are inferred.
#include "ascii_string.h"
#include <vector>

typedef int Int;

// MyBuddyList_ (WorldBuilder name of the rowed 0x005AEB2C constructor): a
// snapshot vector of 8-byte buddy entries.
struct BfmeE8
{
	void *p;
	unsigned char flag;
	char pad[3];
};

class Rva005AEB2C
{
public:
	Rva005AEB2C();
	_STL::vector<BfmeE8> m_vec;
};

// The rowed lookup 0x005AE7A5 on the list's begin/end pair.
struct Rva005AE7A5Class
{
	int m_0;
	int m_4;
	int rva005AE7A5(int a1);
};

struct BuddyRecordView
{
	char m_pad00[0x10];
	Int m_status;						// +0x10
};

class Rva0059ECAD
{
public:
	unsigned char rva0059EF33() const;
};

extern int g_Va00E046BC;
extern int g_Va00E063EC;

struct AptMenuItem
{
	AsciiString label;
	bool enabled;
};

class AptMessenger
{
public:
	void GetSelectedPlayers(Int listIndex, Int a, Int b);
	void rva005AEBD3();

private:
	unsigned char m_pad000[0x28C];
	_STL::vector<AptMenuItem> m_menuItems;	// +0x28C
	unsigned char m_pad298[0x2A0 - 0x298];
	bool m_acceptFriend;				// +0x2A0
};

void AptMessenger::rva005AEBD3()
{
	m_menuItems[0].label = "APT:RemoveFriend";
	m_menuItems[1].label = "APT:InviteToPlay";
	m_menuItems[0].enabled = false;
	m_menuItems[1].enabled = false;
	m_acceptFriend = false;
	_STL::vector<int> selected;
	GetSelectedPlayers(g_Va00E046BC, (int)&selected, 0);
	if (selected.size() != 1)
		return;
	Rva005AEB2C buddies;
	Int found = 0;
	Int online = 0;
	Int pending = 0;
	for (_STL::vector<int>::iterator it = selected.begin(); it != selected.end(); ++it)
	{
		BfmeE8 *entry = (BfmeE8 *)((Rva005AE7A5Class *)&buddies)->rva005AE7A5(*it);
		if (entry)
		{
			++found;
			if (entry->flag)
			{
				++online;
			}
			else
			{
				Int status = ((BuddyRecordView *)entry->p)->m_status;
				if (status != 0 && status != 2)
					++pending;
			}
		}
	}
	if (found)
		m_menuItems[0].enabled = true;
	if (pending)
	{
		if (!online && g_Va00E063EC && ((Rva0059ECAD *)g_Va00E063EC)->rva0059EF33())
			m_menuItems[1].enabled = true;
	}
	else if (online)
	{
		m_menuItems[1].enabled = true;
		m_menuItems[1].label = "APT:AcceptFriend";
		m_acceptFriend = true;
	}
}
