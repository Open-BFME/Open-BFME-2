// cl: /DNDEBUG /MD
// ?rva002AD826@Player@@QAE_NW4ScienceType@@@Z @0x002AD826 56B
// Player purchase path: capable check then ScienceStore cost then bank withdraw via slot 2 then private addScience. Evidence: calls rowed isCapable 0x002ABE86 plus getCost 0x001FF3DC plus pin addScience 0x002AD661, TheScienceStore global, virtual [edx+8] on +8 member, callers 0x003BC775 plus 0x004F32E9, neighbours Rva002AD5ED plus grantScience PlayerO1Shard.
typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ScienceStore
{
public:
	int getSciencePurchaseCost(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

class Bank
{
public:
	virtual void f0();
	virtual void f1();
	virtual void withdraw(int amount);
};

class Player
{
public:
	bool isCapableOfPurchasingScience(ScienceType science) const;
	bool rva002AD826(ScienceType science);
private:
	bool addScience(ScienceType science);
	char m_pad00[8];
	Bank m_bank;
};

bool Player::rva002AD826(ScienceType science)
{
	if (!isCapableOfPurchasingScience(science))
		return false;
	int cost = TheScienceStore->getSciencePurchaseCost(science);
	m_bank.withdraw(-cost);
	addScience(science);
	return true;
}
