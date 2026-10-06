// cl: /DNDEBUG /MD /EHsc
// ?isInside@Object@@QAE_NPAVPolygonTrigger@@@Z, retail 0x0028B411, 52 bytes.
// Object::isInside scans the triggerInfo array at +0x3C0 (stride 8, isInside
// at +6) for the given trigger, bounded by the signed count at +0x43A.
// Evidence: caller Team::didAllExit at 0x0039E38D calls didExit then this body
// exactly where BFME1 Team::didAllExit calls didExit then isInside; BFME1 donor
// Object.cpp:3027 same loop with entered/exited/isInside bytes; sibling
// didEnter 0x0028D718 (+4) and didExit 0x0028D757 (+5) stashes prove +0x3C0
// stride-8 layout and +0x43A signed count; BFME2 non-const signature matches
// sibling QAE_NPAV didEnter/didExit pins.
typedef bool Bool;

class PolygonTrigger;

struct TriggerInfo
{
	PolygonTrigger *m_trigger; // +0
	unsigned char m_entered; // +4
	unsigned char m_exited; // +5
	unsigned char m_isInside; // +6
	unsigned char m_padding; // +7
};

class Object
{
public:
	Bool isInside(PolygonTrigger *pTrigger);

private:
	char m_pad00[0x3C0];
	TriggerInfo m_triggerInfo[5];
	char m_pad3E8[0x43A - 0x3C0 - 5 * 8];
	char m_numTriggerAreasActive;
};

Bool Object::isInside(PolygonTrigger *pTrigger)
{
	for (int i = 0; i < m_numTriggerAreasActive; ++i)
	{
		if (m_triggerInfo[i].m_isInside && m_triggerInfo[i].m_trigger == pTrigger)
			return true;
	}
	return false;
}
