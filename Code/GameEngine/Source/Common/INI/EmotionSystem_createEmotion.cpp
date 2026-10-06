// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/INI/EmotionSystem_createEmotion.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// EmotionSystem::createEmotion 0x0042632F (73B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.

class Object;
class EmotionTrackerUpdateEntry;

class Emotion
{
public:
	Emotion(Object *object, EmotionTrackerUpdateEntry *entry);

private:
	unsigned char m_unknown00[0x34];
};

class EmotionSystem
{
public:
	Emotion *createEmotion(EmotionTrackerUpdateEntry *entry, Object *object);
};

// ?createEmotion@EmotionSystem@@QAEPAVEmotion@@PAVEmotionTrackerUpdateEntry@@PAVObject@@@Z
Emotion *EmotionSystem::createEmotion(EmotionTrackerUpdateEntry *entry, Object *object)
{
	if (entry == 0 || object == 0)
		return 0;

	return new Emotion(object, entry);
}
