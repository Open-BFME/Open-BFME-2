// cl: /DNDEBUG /MD /EHsc
// ??0Rva0039B893@@QAE@XZ @0x0039B7FB 34B default ctor zeroing 2 ints plus 3 words with same vtable.
// Evidence: stores vtable 0x0081AD6C like rowed copy ctor 0x0039B893; stride 0x14 with int at +0x04
// float at +0x08 via movss and words at +0x0C +0x0E +0x10; callers 0x0039C5A3 0x0039D1DE.

typedef int Int;
typedef short Short;

class Rva0039B893
{
public:
	Rva0039B893();
	Rva0039B893(const Rva0039B893 &other);
	Rva0039B893 &operator=(const Rva0039B893 &other);
	virtual ~Rva0039B893();

	Int m_field04;
	float m_field08;
	Short m_field0C;
	Short m_field0E;
	Short m_field10;
};

Rva0039B893::Rva0039B893()
	: m_field04(0)
	, m_field08(0.0f)
	, m_field0C(0)
	, m_field0E(0)
	, m_field10(0)
{
}
