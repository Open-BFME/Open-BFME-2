// cl: /DNDEBUG /MD
//
// Player::isCapableOfPurchasingScience, retail 0x002ABE86 (67B): Zero
// Hour's body - no invalid or already-owned science, the prerequisites
// (0x002A9EAC, Zero Hour's hasPrereqsForScience, pinned from this call)
// met, and a nonzero cost no greater than the +0x24 purchase points.
typedef bool Bool;
typedef int Int;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

class ScienceStore
{
public:
	Int getSciencePurchaseCost(ScienceType science) const;
};
extern ScienceStore *TheScienceStore;

class Player
{
public:
	Bool hasScience(ScienceType t) const;
	Bool hasPrereqsForScience(ScienceType t) const;
	Bool isCapableOfPurchasingScience(ScienceType science) const;
private:
	unsigned char m_pad00[0x24];
	Int m_sciencePurchasePoints; // +0x24
};

Bool Player::isCapableOfPurchasingScience(ScienceType science) const
{
	if (science == SCIENCE_INVALID)
		return false;

	if (hasScience(science))
		return false;

	if (!hasPrereqsForScience(science))
		return false;

	Int cost = TheScienceStore->getSciencePurchaseCost(science);
	if (cost == 0 || cost > m_sciencePurchasePoints)
		return false;

	return true;
}
