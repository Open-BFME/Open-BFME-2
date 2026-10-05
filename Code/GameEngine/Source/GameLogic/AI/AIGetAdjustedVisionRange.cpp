// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// AI::getAdjustedVisionRangeForObject, retail 0x002FDD0A (138 bytes), ported
// from Zero Hour's GameEngine/Source/GameLogic/AI/AI.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference). Callers include
// AIGuardMachine::getStdGuardRange and AIGuardOuterState::onEnter.
// BFME 2 deltas (target evidence): the float at Object +0xB8 is added to the
// vision range once the object is known to have an AI (Object +0x258); Zero
// Hour's AI_VISIONFACTOR_OWNERTYPE guard modifiers and the contained-by
// largest-weapon-range override are absent, so only the mood factor
// remains: sleep gives 0, alert and aggressive scale by the TAiData floats at
// +0x4C and +0x50. getMoodMatrixValue is the pinned 0x00264F5E.
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

enum
{
	AI_VISIONFACTOR_OWNERTYPE = 0x01,
	AI_VISIONFACTOR_MOOD = 0x02,
	AI_VISIONFACTOR_GUARDINNER = 0x04
};

enum MoodMatrixParameters
{
	MM_Controller_Player = 0x00000001,
	MM_Controller_AI = 0x00000002,
	MM_Mood_Sleep = 0x00000100,
	MM_Mood_Passive = 0x00000200,
	MM_Mood_Normal = 0x00000400,
	MM_Mood_Alert = 0x00000800,
	MM_Mood_Aggressive = 0x00001000,
	MM_Mood_Bitmask = (MM_Mood_Sleep | MM_Mood_Passive | MM_Mood_Normal | MM_Mood_Alert | MM_Mood_Aggressive)
};

class AIUpdateInterface
{
public:
	UnsignedInt getMoodMatrixValue(void) const;
};

class Object
{
public:
	Real getVisionRange() const;
	Real getBfmeVisionBonus() const { return m_bfmeVisionBonusB8; }
	// The AI is read directly: an inline getAI here would be one more COMDAT
	// copy beside the Zero Hour header views' (ZH offset).
	unsigned char m_pad00[0xB8];
	Real m_bfmeVisionBonusB8; // +0xB8
	unsigned char m_padBC[0x258 - 0xBC];
	AIUpdateInterface *m_ai; // +0x258
};

struct TAiData
{
	unsigned char m_pad00[0x4C];
	Real m_alertRangeModifier; // +0x4C
	Real m_aggressiveRangeModifier; // +0x50
};

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, Int factorsToConsider);
	const TAiData *getAiData() const { return m_aiData; }
private:
	unsigned char m_pad00[0x18];
	TAiData *m_aiData; // +0x18
};
extern AI *TheAI;

//-------------------------------------------------------------------------------------------------
Real AI::getAdjustedVisionRangeForObject(const Object *object, Int factorsToConsider)
{
	Real originalRange = object->getVisionRange();
	const AIUpdateInterface *ai = object->m_ai;

	if (!ai)
	{
		return 0.0f;
	}

	originalRange += object->getBfmeVisionBonus();

	UnsignedInt moodMatrixVal = ai->getMoodMatrixValue();

	if ((factorsToConsider & AI_VISIONFACTOR_MOOD) && ((moodMatrixVal & MM_Controller_Player) == 0) )
	{
		switch(moodMatrixVal & MM_Mood_Bitmask)
		{
			case MM_Mood_Sleep:
				return 0.0f;

			case MM_Mood_Passive:
			case MM_Mood_Normal:
				break;

			case MM_Mood_Alert:
				originalRange *= TheAI->getAiData()->m_alertRangeModifier;
				break;

			case MM_Mood_Aggressive:
				originalRange *= TheAI->getAiData()->m_aggressiveRangeModifier;
				break;
		}
	}

	return originalRange;
}
