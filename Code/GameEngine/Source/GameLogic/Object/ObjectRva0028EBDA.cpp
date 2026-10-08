// cl: /DNDEBUG /MD /EHsc
//
// ?rva0028EBDA@Object@@QAEX_N@Z, retail 0x0028EBDA 110B.
// Static NameKey for "EnragedBehavior" via TheNameKeyGenerator, then
// findModule; if module found, call rva004590C5 when flag true else
// rva004590E6. Chain via rowed 0x004590C5. Callers 0x0033593E 0x0048C97C.
enum NameKeyType
{
	NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Module
{
};

class Rva004590C5
{
public:
	void rva004590C5();
	void rva004590E6();
};

// The update at Object+0x24C (see EmotionTrackerUpdateRva004B0EBC.cpp for
// its per-emotion arrays: active flags at +0x24, frames at +0x30, source
// IDs at +0x60).
class EmotionTrackerUpdate
{
public:
	void rva004B0D4C(int index, void *source);
	void PulseEmotion(int index, void *source, int delay);
	void ForceEmotion(int index, float value, int arg);
};

// Rowed owner of the 12B indexed byte-clear at 0x004B0DA0
// (Code/GameEngine/Source/Common/Rva004B0DA0Setter.cpp): same this+index+0x24
// active-flag byte the rowed EmotionTrackerUpdate::PulseEmotion sets.
class Rva004B0DA0Holder
{
public:
	void rva004B0DA0(int index);
};

class Object
{
public:
	void rva0028EBDA(bool flag);
	void rva0028EC48(int index, void *source);
	void rva0028EC68(int index, void *source, int delay);
	void rva0028EC88(int index);
	void rva0028ECA8(int index, float value, int arg);
protected:
	Module *findModule(NameKeyType key) const;
private:
	unsigned char m_pad000[0x24C];
	EmotionTrackerUpdate *m_emotionTracker24C; // +0x24C
	unsigned char m_pad250[0x274 - 0x250];
	Object *m_containedBy274; // +0x274
};

void Object::rva0028EBDA(bool flag)
{
	static NameKeyType key_EnragedBehavior =
		TheNameKeyGenerator->nameToKey("EnragedBehavior");
	Rva004590C5 *m = (Rva004590C5 *)findModule(key_EnragedBehavior);
	if (m == 0)
		return;
	if (flag)
		m->rva004590C5();
	else
		m->rva004590E6();
}

// Four forwards to the Object+0x24C emotion tracker (retail 0x0028EC48,
// 0x0028EC68, 0x0028EC88: 32B each; 0x0028ECA8: 51B). The first three
// climb the +0x274 container chain to the outermost object and forward
// to its tracker, if any; the fourth forwards to the innermost object in
// that chain that has a tracker.
void Object::rva0028EC48(int index, void *source)
{
	Object *obj = this;
	while (obj->m_containedBy274)
		obj = obj->m_containedBy274;
	if (obj->m_emotionTracker24C)
		obj->m_emotionTracker24C->rva004B0D4C(index, source);
}

void Object::rva0028EC68(int index, void *source, int delay)
{
	Object *obj = this;
	while (obj->m_containedBy274)
		obj = obj->m_containedBy274;
	if (obj->m_emotionTracker24C)
		obj->m_emotionTracker24C->PulseEmotion(index, source, delay);
}

void Object::rva0028EC88(int index)
{
	Object *obj = this;
	while (obj->m_containedBy274)
		obj = obj->m_containedBy274;
	if (obj->m_emotionTracker24C)
		((Rva004B0DA0Holder *)obj->m_emotionTracker24C)->rva004B0DA0(index);
}

void Object::rva0028ECA8(int index, float value, int arg)
{
	Object *obj = this;
	while (!obj->m_emotionTracker24C)
	{
		obj = obj->m_containedBy274;
		if (!obj)
			return;
	}
	obj->m_emotionTracker24C->ForceEmotion(index, value, arg);
}
