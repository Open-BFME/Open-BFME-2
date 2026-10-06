// Target PushButtonData cleanup called by GadgetPushButtonSystem at 0x328639.
// Target boundary 0x327E50/13 releases its opaque owner at +0x1C.
// cl: /DNDEBUG /MD /EHsc
class OpaqueRefCounted
{
public:
	void Release_Ref(void);
};

class PushButtonData
{
public:
	char m_prefix[0x1C];
	OpaqueRefCounted *m_audioEvent;
	~PushButtonData(void);
};

PushButtonData::~PushButtonData(void)
{
	if (m_audioEvent)
		m_audioEvent->Release_Ref();
}
