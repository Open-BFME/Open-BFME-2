// cl: /DNDEBUG /MD
//
// ?rva0028AE6D@Object@@QAEXXZ @0x0028AE6D 46B
// The notifier every model-condition setter calls after a bit changes in the
// +0x10C word array (509 call sites). Two independent guarded calls: the
// Drawable at +0x84 is handed the condition words with (0, 0), then the AI at
// +0x258 is woken by a direct tail jump to the rowed
// AIUpdateInterface::wakeUpNow (0x00262871).
//
// Donor: BFME 1 Object::notifyModelConditionChanged
// (game/GameEngine/Source/GameLogic/Object/ObjectModelConditions.cpp) has this
// exact shape, with the Drawable call being replaceModelConditionState(flags,
// false, 0). That is donor naming, not target fact, so the row and the
// Drawable callee (0x002791E7, unrowed) keep address-derived names.

class ModelConditionFlags
{
	unsigned int m_words[10];
};

class Drawable
{
public:
	void rva002791E7(const ModelConditionFlags &flags, unsigned int a, unsigned int b);
};

class Object;

class AIUpdateInterface
{
	friend class Object;
protected:
	void wakeUpNow();
};

class Object
{
public:
	void rva0028AE6D();

private:
	unsigned char m_pad000[0x84];
	Drawable *m_drawable; // +0x84
	unsigned char m_pad088[0x10C - 0x88];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad134[0x258 - 0x134];
	AIUpdateInterface *m_ai; // +0x258
};

void Object::rva0028AE6D()
{
	if (m_drawable)
		m_drawable->rva002791E7(m_modelConditionFlags, 0, 0);

	if (m_ai)
		m_ai->wakeUpNow();
}
