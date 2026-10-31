#pragma once
// Target VA C1C780: one __purecall entry (RVA0003B810), no bases/data/dtor.
// Native typed overrides include Announce onDie4851C7; ZH is donor evidence only.
class DamageInfo;
class DieModuleInterface
{
public:
	virtual void onDie( const DamageInfo *damageInfo ) = 0;
};
