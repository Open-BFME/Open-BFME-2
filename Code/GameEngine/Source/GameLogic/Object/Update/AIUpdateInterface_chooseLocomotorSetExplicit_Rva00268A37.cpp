// cl: /O1 /MD /DNDEBUG
//
// ?chooseLocomotorSetExplicit@AIUpdateInterface@@QAE_NH@Z
// retail 0x00268A37, 115 bytes (Ghidra FUN_00668a37).
//
// Donor: GeneralsMD AIUpdate.cpp chooseLocomotorSetExplicit, unchanged in
// shape. BFME 2 looks the locomotor template vector up on the object's
// template (+4 of the object at +8) through the rowed lookup 0x0033C288,
// clears the locomotor set at +0x1CC (0x001E7E25), nulls the current
// locomotor (+0x1F0), adds each non-null template (0x001E88CE, with a
// second argument of 0) and records the set type at +0x1F4. The set's
// valid-surface word at +0x1DC (+0x10 in it) matches getMoodMatrixValue.

typedef int Int;
typedef bool Bool;

class LocomotorTemplate;

struct LocomotorTemplateVector
{
	unsigned int size() const { return m_finish - m_start; }
	const LocomotorTemplate *at(unsigned int i) const { return m_start[i]; }

	const LocomotorTemplate **m_start;
	const LocomotorTemplate **m_finish;
};

class ModuleInfo
{
public:
	const int *rva0033C288(int which) const;	// locomotor vector lookup, 0x0033C288
};

class Object
{
public:
	const ModuleInfo *getTemplate() const { return m_template; }
private:
	void *m_vtable;
	const ModuleInfo *m_template;
};

class LocomotorSet
{
public:
	void clear();
	void addLocomotor(const LocomotorTemplate *lt, Bool flag);
private:
	char m_pad00[0x24];
};

class Locomotor;

class AIUpdateInterface
{
public:
	Bool chooseLocomotorSetExplicit(Int wst);
private:
	Object *getObject() const { return m_object; }

	void *m_vtable;
	char m_pad04[0x08 - 0x04];
	Object *m_object;
	char m_pad0C[0x1CC - 0x0C];
	LocomotorSet m_locomotorSet;
	Locomotor *m_curLocomotor;
	Int m_curLocomotorSet;
};

Bool AIUpdateInterface::chooseLocomotorSetExplicit(Int wst)
{
	const LocomotorTemplateVector *set = (const LocomotorTemplateVector *)getObject()->getTemplate()->rva0033C288(wst);
	if (set)
	{
		m_locomotorSet.clear();
		m_curLocomotor = 0;
		for (Int i = 0; i < set->size(); ++i)
		{
			const LocomotorTemplate *lt = set->at(i);
			if (lt)
				m_locomotorSet.addLocomotor(lt, false);
		}
		m_curLocomotorSet = wst;
		return true;
	}
	return false;
}
