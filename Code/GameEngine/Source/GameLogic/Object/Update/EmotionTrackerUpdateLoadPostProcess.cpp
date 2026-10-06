// cl: /DNDEBUG /MD
//
// ?loadPostProcess@EmotionTrackerUpdate@@MAEXXZ, retail 0x004B0FB9, 50 bytes:
// slot 1 of EmotionTrackerUpdate's primary vtable 0x00C5667C (ctors 0x004B1333,
// 0x004B21EF), the slot UpdateModule::loadPostProcess 0x0058B03E fills for
// modules that do not override it. Re-derives the pointer at +0x9C from the
// index at +0xC4 into the pointer vector at +0x90 (begin/end at +0x90/+0x94),
// null when the index is out of range.
class ModuleData;
class Object;

struct EmotionTrackerUpdatePtrVector
{
	unsigned int size() const { return (unsigned int)(m_end - m_begin); }
	void *const &operator[](int i) const { return m_begin[i]; }
	void **m_begin; // +0x00
	void **m_end; // +0x04
	void **m_capacity; // +0x08
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
protected:
	virtual void loadPostProcess();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class EmotionTrackerUpdate : public UpdateModule
{
protected:
	virtual void loadPostProcess();
private:
	unsigned char m_pad0C[0x90 - 0x0C];
	EmotionTrackerUpdatePtrVector m_90; // +0x90
	void *m_9C; // +0x9C
	unsigned char m_padA0[0xC4 - 0xA0];
	int m_C4; // +0xC4
};

void EmotionTrackerUpdate::loadPostProcess()
{
	if (m_C4 >= 0 && m_C4 < m_90.size())
		m_9C = m_90[m_C4];
	else
		m_9C = 0;
}
