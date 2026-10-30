// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva004DCEC4@Emotion@@QAE_NXZ retail 0x004DCEC4..0x004DD018 (340 bytes,
// RET): the per-frame step of one emotion an object's EmotionTrackerUpdate
// keeps (its only caller is EmotionTrackerUpdate::update at 0x004B1633,
// WorldBuilder twin 0x01230DD0 in EmotionTrackerUpdate.cpp; this body's own
// twin is 0x010EA740). Ghidra split it after the EH prolog (0x004DCEC4, 10
// bytes) and called the rest 0x004DCECE.
//
// The emotion is the record whose constructor is rowed at 0x004DD206
// (Rva004DD206TwoTreeConstructor.cpp): the object at +0x00, its nugget
// template at +0x04, a source object id at +0x08, the start frame at +0x2C and
// the frame it began at +0x30. Once the end frame passes the emotion is done.
// On the template's start delay (+0x40) frame it adds the template's
// attribute modifier (name read by the rowed 0x004DC8E7, strength +0x48
// unless +0x44 is set) to the object; after the +0x50 delay it pokes the
// object's AI (0x00263298); a template FX list (+0x34) plays on the object, or
// on what the object's 0x0029439D relation reports through its slot 19,
// against the source object while that still exists; a type-3 template ends
// with its source object or once that object's +0x438 bit 0 is set.
// Returns true while the emotion keeps running.
//
// Target facts: boundary, caller, callees, member offsets and branch order
// are from retail. Member and method names are address-derived.
//
// The modifier-name temporary is live across the out-of-line
// StringBase<char>::isEmpty call (0x00001E2F) with no EH state of its own and
// only the zeroed destroy flag at [ebp-0x18] left behind, which a throw()
// isEmpty declaration (string_base.h) reproduces. The frame test reads the
// template delay through an inline getter, as the WorldBuilder twin's
// separate temporary for it shows; that gives retail's load order.
#include "ascii_string.h"

#include "../../../Common/GameLogicObjectLookupView.h"

class GameLogic;
extern GameLogic *TheGameLogic;

class EmotionNugget;
class Object;
class AIUpdateInterface {
    friend class EmotionNugget;
protected:
    virtual void SetEmotionState(int, Object *);
public:
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual void v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual void v90();
    virtual bool v91();
    virtual void v92();
    virtual void v93();
    virtual void v94();
    virtual void v95();
    virtual void v96();
    virtual void v97();
    virtual void v98();
    virtual void v99();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void v103();
    virtual void v104();
    virtual void v105();
    virtual void v106();
    virtual void v107();
    virtual void v108();
    virtual void v109();
    virtual bool v110();
    int getCurrentStateID() const;
    void rva00263298();
    void rva002632E1();
    char pad04[0x3c5-4]; unsigned char allow04;
};

// What Object::rva0029439D reports; its slot 19 names the FX target.
class Rva0029439DResult
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18();
	virtual Object *v19();
};

class ThingTemplate;
enum ObjectStatusTypes { STATUS_46 = 0x46 };
struct ModelConditionFlags {
 unsigned int words[19];
 // Returns the masked word (WB's BitFlags::test compares it with zero).
 unsigned int test(size_t bit) const { return words[bit/32] & (1UL << (bit%32)); }
 void set(int bit) { words[bit>>5] |= 1U << (bit & 0x1f); }
 void clear(int bit) { words[bit >> 5] &= ~(1 << (bit & 0x1f)); }
};
class Object {
public:
    void *rva0029439D();
    void clearAndSetModelConditionFlagsForHorde(const int *, const int *);
    void rva0028CFB2(const int *, const int *);
    void rva0028AE6D();
    bool isSignificantlyAboveTerrain() const;
    ObjectID getID() const { return id; }
    const ThingTemplate *getTemplate() const { return thingTemplate; }
    bool addAttributeModifierToPool(const AsciiString &name, int strength);
    AIUpdateInterface *getAI() const { return ai; }
    bool testStatus438() const { return (m_status438 & 1) != 0; }
    bool testStatus(ObjectStatusTypes status) const;
    bool rva0028AFBB() const;
    void *rva0028C197() const;
    bool rva0028C149(int attribute, float *value, int arg);
    char pad00[4]; ThingTemplate *thingTemplate;
    char pad08[0x74-8]; ObjectID id;
    char pad78[0x10c-0x78]; ModelConditionFlags modelConditions;
    char pad158[0x258-0x158]; AIUpdateInterface *ai; // +0x258
    char pad25C[0x438 - 0x25C];
    unsigned char m_status438; // +0x438
};

class FXList
{
public:
	static void doFXObj(const FXList *, const Object *, const Object *);
	void doFXObj(const Object *primary, const Object *secondary) const;
};

// The template's attribute modifier name, read through the rowed getter.
class Rva004DC8E7AsciiField
{
public:
	AsciiString get() const;
	int getDelay() const { return m_40; }
	char m_pad00[0x10];
	int m_10; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	char m_pad1C[0x1C];
	const FXList *m_fx38; // +0x38
	AsciiString m_str3C; // +0x3C
	int m_40; // +0x40
	unsigned char m_flag44; // +0x44
	char m_pad45[0x3];
	int m_48; // +0x48
	int m_4C; // +0x4C
	char m_pad50[0x50];
	int m_a0; // +0xA0
	char m_padA4[0x94];
	int m_138; // +0x138
	char m_pad13C[0x48];
	unsigned char m_184; // +0x184
	char m_pad185[0x3];
};

class EmotionTrackerUpdateEntry
{
public:
	char pad00[4];
	int m_type; // +0x04
	char pad08[0x34 - 8];
	const FXList *m_fx; // +0x34
	char pad38[0x40 - 0x38];
	unsigned int getModifierDelay() const { return m_modifierDelay; }
	unsigned int m_modifierDelay; // +0x40
	bool m_noStrength; // +0x44
	char pad45[0x48 - 0x45];
	int m_strength; // +0x48
	char pad4C[0x50 - 0x4C];
	unsigned int m_aiDelay; // +0x50
};

class Emotion
{
public:
	bool rva004DCEC4();

	Object *word00;
	EmotionTrackerUpdateEntry *word04;
	ObjectID word08;
	char pad0C[0x2C - 0x0C];
	unsigned int word2C; // +0x2C, end frame
	unsigned int word30; // +0x30, frame the emotion began
};

bool Emotion::rva004DCEC4()
{
	bool done = false;
	if (word2C && TheGameLogic->getFrame() >= word2C)
		done = true;

	bool apply = !((const StringBase<char> *)&((Rva004DC8E7AsciiField *)word04)->get())->isEmpty()
		&& TheGameLogic->getFrame() == word30 + word04->getModifierDelay();
	if (apply) {
		int strength = 0;
		if (!word04->m_noStrength)
			strength = word04->m_strength;
		word00->addAttributeModifierToPool(((Rva004DC8E7AsciiField *)word04)->get(), strength);
	}

	unsigned int aiDelay = word04->m_aiDelay;
	if (aiDelay && TheGameLogic->getFrame() >= word30 + aiDelay) {
		AIUpdateInterface *ai = word00->getAI();
		if (ai)
			ai->rva00263298();
	}

	if (word04->m_fx) {
		Object *target = word00;
		Rva0029439DResult *related = (Rva0029439DResult *)word00->rva0029439D();
		if (related)
			target = related->v19();
		ObjectID sourceID = word08;
		Object *source = TheGameLogic->findObjectByID(sourceID);
		if (source || sourceID == INVALID_OBJECT_ID) {
			FXList::doFXObj(word04->m_fx, target ? target : word00, source);
		}
	}

	if (word04->m_type == 3) {
		Object *source = TheGameLogic->findObjectByID(word08);
		if (!source || source->testStatus438())
			done = true;
	}
	return !done;
}
