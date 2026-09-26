// cl: /O1 /MD
// ??_GEmotionTrackerUpdateModuleData@@UAEPAXI@Z @0x004B15AE, 28 bytes.
// Scalar deleting destructor: calls the rowed 0x004B1285 destructor and
// frees through operator delete. Same-shape sibling of ??_GVersion via
// the family deleting-dtor pattern (local class so the deleting
// destructor is emitted; the complete-destructor call resolves through
// the destructor's own row).

class EmotionTrackerUpdateModuleData
{
public:
	__declspec(noinline) virtual ~EmotionTrackerUpdateModuleData();

private:
	int m_famgen;
};

EmotionTrackerUpdateModuleData::~EmotionTrackerUpdateModuleData()
{
	m_famgen = 0;
}

void EmotionTrackerDelete(EmotionTrackerUpdateModuleData *p)
{
	delete p;
}
