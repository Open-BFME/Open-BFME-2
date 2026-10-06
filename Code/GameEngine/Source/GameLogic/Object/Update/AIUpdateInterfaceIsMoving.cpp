// cl: /O1 /DNDEBUG /MD
//
// ?isMoving@AIUpdateInterface@@QBE_NXZ
// retail 0x00264688, 97 bytes (Ghidra FUN_00664688), pinned from
// privateFollowPathAppend where the Open-BFME-1 donor asks isMoving().
//
// Body (layout from the banked attempt and its evidence): an object whose
// template has kind bit +0x108 & 4 never moves; an object contained by
// another (+0x274) that has an AI (+0x258) and whose template lacks bit
// +0x115 & 0x20 moves as its container does; otherwise the +0x3B7 flag, the
// virtual at byte offset 0x1B8 and the goal word at +0x1FC decide. The
// container case is written as the tail call it was: MSVC turns it into
// retail's backward jump, which the loop forms of earlier attempts rotated.

typedef bool Bool;

struct ThingTemplate
{
	unsigned char m_pad000[0x108];
	unsigned char m_kindof108;
	unsigned char m_pad109[0x115 - 0x109];
	unsigned char m_kindof115;
};

class AIUpdateInterface;

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Object *getContainedBy() const { return m_containedBy; }
private:
	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_pad008[0x258 - 0x008];
	AIUpdateInterface *m_ai;
	unsigned char m_pad25C[0x274 - 0x25C];
	Object *m_containedBy;
};

class AIUpdateInterface
{
public:
	// Slots before byte offset 0x1B8; not needed here.
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual void vslot050();
	virtual void vslot051();
	virtual void vslot052();
	virtual void vslot053();
	virtual void vslot054();
	virtual void vslot055();
	virtual void vslot056();
	virtual void vslot057();
	virtual void vslot058();
	virtual void vslot059();
	virtual void vslot060();
	virtual void vslot061();
	virtual void vslot062();
	virtual void vslot063();
	virtual void vslot064();
	virtual void vslot065();
	virtual void vslot066();
	virtual void vslot067();
	virtual void vslot068();
	virtual void vslot069();
	virtual void vslot070();
	virtual void vslot071();
	virtual void vslot072();
	virtual void vslot073();
	virtual void vslot074();
	virtual void vslot075();
	virtual void vslot076();
	virtual void vslot077();
	virtual void vslot078();
	virtual void vslot079();
	virtual void vslot080();
	virtual void vslot081();
	virtual void vslot082();
	virtual void vslot083();
	virtual void vslot084();
	virtual void vslot085();
	virtual void vslot086();
	virtual void vslot087();
	virtual void vslot088();
	virtual void vslot089();
	virtual void vslot090();
	virtual void vslot091();
	virtual void vslot092();
	virtual void vslot093();
	virtual void vslot094();
	virtual void vslot095();
	virtual void vslot096();
	virtual void vslot097();
	virtual void vslot098();
	virtual void vslot099();
	virtual void vslot100();
	virtual void vslot101();
	virtual void vslot102();
	virtual void vslot103();
	virtual void vslot104();
	virtual void vslot105();
	virtual void vslot106();
	virtual void vslot107();
	virtual void vslot108();
	virtual void vslot109();
	virtual Bool vslot110() const;

	Bool isMoving() const;
private:
	Object *getObject() const { return m_object; }

	unsigned char m_pad004[0x008 - 0x004];
	Object *m_object;
	unsigned char m_pad00C[0x1FC - 0x00C];
	void *m_goal;
	unsigned char m_pad200[0x3B7 - 0x200];
	Bool m_flag3B7;
};

Bool AIUpdateInterface::isMoving() const
{
	Object *obj = getObject();
	if (obj->getTemplate()->m_kindof108 & 4)
		return false;

	Object *container = obj->getContainedBy();
	if (container && container->getAI() && !(container->getTemplate()->m_kindof115 & 0x20))
		return container->getAI()->isMoving();

	if (m_flag3B7)
		return true;
	if (vslot110())
		return false;
	else
		return m_goal != 0 ? true : false;
}
