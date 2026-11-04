// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Donor: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d
// game/GameEngine/Source/GameLogic/Object/WeaponStore_reset.cpp.
// Native BFME 2 table C02114 slot 9 and WB BB4430 establish WeaponStore::reset.
// WB BB43D0 indexes the active vector at +0x0C and calls the empty
// WeaponTemplate::reset. Preserve the real STLport operations: their visible
// definitions retain the 28-byte counted loop that a hand-written empty loop
// loses. The target's template successor is +0x04, as in the donor.

#define _STLP_NO_EXCEPTIONS 1

#include <vector>

typedef int Int;

#include "../../../Include/GameLogic/WeaponTemplate.h"

// The header declares no reset/override helpers; these TU-local inlines keep
// the donor's empty WeaponTemplate::reset and the +0x04 successor accessors.
static __forceinline void weaponTemplateReset(WeaponTemplate *) { }
static __forceinline bool weaponTemplateIsOverride(WeaponTemplate *wt) { return wt->m_nextTemplate != 0; }
static __forceinline WeaponTemplate *weaponTemplateClearNext(WeaponTemplate *wt)
{
	WeaponTemplate *ret = wt->m_nextTemplate;
	wt->m_nextTemplate = 0;
	return ret;
}

typedef _STL::vector<WeaponTemplate *> WeaponTemplateVector;

class WeaponStore
{
public:
	virtual void reset();

protected:
	void resetWeaponTemplates( void )
	{
		for (Int i = 0; i < m_weaponTemplateVector.size(); i++)
		{
			WeaponTemplate* wt = m_weaponTemplateVector[i];
			weaponTemplateReset(wt);
		}
	}

private:
	unsigned char m_unmodelled004[0x8];
	WeaponTemplateVector m_weaponTemplateVector;			///< this+0x0C
};

void WeaponStore::reset()
{
	// clean up any overriddes.
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		WeaponTemplate *wt = *it;
		if (weaponTemplateIsOverride(wt))
		{
			WeaponTemplate *override = wt;
			wt = weaponTemplateClearNext(wt);
			// Native dispatch uses destructor flag 0 then global delete.
			::delete override;
			*it = wt;
		}
	}

	resetWeaponTemplates();
}
