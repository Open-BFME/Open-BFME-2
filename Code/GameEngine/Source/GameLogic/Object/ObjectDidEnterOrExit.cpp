// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?didEnterOrExit@Object@@IBE_NXZ @0x0028D6EB (45B).
// Direct BFME1 transfer of Object::didEnterOrExit
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp:2970
// and ObjectFields.cpp:546): INERT kind gate then TheGameLogic frame compare
// against m_enteredOrExitedFrame for the current or previous frame. Callers
// are the pinned ?didEnter@Object@@QAE_NPAVPolygonTrigger@@@Z at 0x0028D718
// and ?didExit@Object@@QAE_NPAVPolygonTrigger@@@Z at 0x0028D757, both of which
// call this body first and return false when it returns false, exactly the
// donor didEnter/didExit shape. Landing this unblocks 0x0028D718 per the
// packet (unlock lane).
//
// Offsets (all retail-measured): template +0x04 (same slot Object.cpp and
// Object_isAbleToAttack.cpp document), kind byte +0x113 bit 0x02 is the INERT
// gate (same kind-byte area Object_isAbleToAttack.cpp models as
// m_kindByte10F etc.; base +0x108 holds STRUCTURE bit 0x80), entered-or-exited
// frame +0x3F8, GameLogic frame +0x40 (same +0x40 TurretStateMachineSetState.cpp
// documents for TheGameLogic at 0x00DFE78C). TheGameLogic bakes to its absolute
// (no ledger pin); testStatus/isKindOf need no rows here because the INERT
// check reads the kind byte directly.
//
// ?didEnter@Object@@QAE_NPAVPolygonTrigger@@@Z @0x0028D718 (63B) and
// ?didExit@Object@@QAE_NPAVPolygonTrigger@@@Z @0x0028D757 (63B): BFME1
// Object::didEnter/didExit (Object.cpp:2990), didEnterOrExit then a scan of
// the trigger info array (+0x3C0, stride 8, entered +4 / exited +5) over the
// active count byte at +0x43A. Retail keeps this in edx across the
// didEnterOrExit call, which cl only does when that callee was compiled
// earlier in the same TU, so they follow it here.

typedef bool Bool;
typedef unsigned int UnsignedInt;

class PolygonTrigger;

struct TriggerInfo
{
	PolygonTrigger *m_trigger;
	unsigned char m_entered;
	unsigned char m_exited;
	unsigned char m_pad[2];
};

struct ThingTemplate
{
	unsigned char m_pad[0x113];
	unsigned char m_byte113;
};

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }

private:
	unsigned char m_pad[0x40];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	Bool didEnter(PolygonTrigger *trig);
	Bool didExit(PolygonTrigger *trig);

protected:
	Bool didEnterOrExit() const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x3C0 - 0x08];
	TriggerInfo m_triggerInfo[5];
	char m_pad3E8[0x3F8 - 0x3E8];
	UnsignedInt m_enteredOrExitedFrame;
	char m_pad3FC[0x43A - 0x3FC];
	char m_numTriggerAreasActive;
};

Bool Object::didEnterOrExit() const
{
	if ((m_template->m_byte113 & 2) != 0)
		return false;
	UnsignedInt now = TheGameLogic->getFrame();
	return (m_enteredOrExitedFrame == now || m_enteredOrExitedFrame == now - 1);
}

Bool Object::didEnter(PolygonTrigger *trig)
{
	if (!didEnterOrExit())
		return false;
	for (int i = 0; i < m_numTriggerAreasActive; ++i)
	{
		if (m_triggerInfo[i].m_entered && m_triggerInfo[i].m_trigger == trig)
			return true;
	}
	return false;
}

Bool Object::didExit(PolygonTrigger *trig)
{
	if (!didEnterOrExit())
		return false;
	for (int i = 0; i < m_numTriggerAreasActive; ++i)
	{
		if (m_triggerInfo[i].m_exited && m_triggerInfo[i].m_trigger == trig)
			return true;
	}
	return false;
}
