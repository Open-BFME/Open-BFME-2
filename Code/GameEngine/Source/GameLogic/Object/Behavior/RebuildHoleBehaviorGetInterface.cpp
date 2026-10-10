// cl: /O1 /DNDEBUG /MD
//
// ?getRebuildHoleBehaviorInterface@RebuildHoleBehavior@@UAEPAVRebuildHoleBehaviorInterface@@XZ
// retail 0x00483322, 12 bytes: slot 13 of the RebuildHoleBehavior behavior-
// module vtable (0x00849AA8 entry). Zero Hour's RebuildHoleBehavior.h
// defines it inline as { return this; }: the conversion to the
// RebuildHoleBehaviorInterface base, which sits at +0x24 here as in the
// rowed getRebuildHoleBehaviorInterfaceFromObject 0x004831CB (module+0x24),
// null-checked by the compiler. Only the bases' sizes are modelled.

class RebuildHoleBehaviorInterface
{
public:
	virtual void s00();
};

class RebuildHoleBehaviorPrimaryView
{
public:
	virtual void p00();
private:
	char m_pad04[0x24 - 4];
};

class RebuildHoleBehavior : public RebuildHoleBehaviorPrimaryView, public RebuildHoleBehaviorInterface
{
public:
	virtual RebuildHoleBehaviorInterface *getRebuildHoleBehaviorInterface();
};

RebuildHoleBehaviorInterface *RebuildHoleBehavior::getRebuildHoleBehaviorInterface()
{
	return this;
}
