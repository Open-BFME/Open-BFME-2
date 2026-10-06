// cl: /DNDEBUG /MD /EHsc
// ??4Payload@DeliverPayloadNugget@@QAEAAU01@ABU01@@Z @0x0027F589 29B
// Payload copy-assign: plain-copy scalar at +0 then TreeHintRef assign at +4 then return this.
// Evidence: pinned name; callee TreeHintRef assign 0x002174A4 rowed; caller STL copy in ObjectCreationList.cpp; prev/next Map TUs share flags.
struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};

class DeliverPayloadNugget
{
public:
	struct Payload
	{
		int m_first;
		TreeHintRef00217D4C m_second;
		Payload &operator=(const Payload &other);
	};
};

DeliverPayloadNugget::Payload &DeliverPayloadNugget::Payload::operator=(const Payload &other)
{
	m_first = other.m_first;
	m_second = other.m_second;
	return *this;
}
