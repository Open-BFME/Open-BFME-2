// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmePoolHolder88
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder88 *m_target;

	__declspec(noinline) BfmePoolRef10 &operator=(const BfmePoolRef10 &rhs);
	__forceinline ~BfmePoolRef10()
	{
		if (m_target)
			m_target->m_ref.Release_Ref();
	}
};

__declspec(noinline) BfmePoolRef10 &BfmePoolRef10::operator=(const BfmePoolRef10 &rhs)
{
	if (this != &rhs)
	{
		m_target = rhs.m_target;
	}
	return *this;
}

class LargeGroupAudioGridCell
{
public:
	void setOverlappedLocking(bool flag);
};

class TargetObj005C8DBF : public LargeGroupAudioGridCell
{
public:
	void method_005C8D6B();
};

class HostClass005C8E0A : public TargetObj005C8DBF
{
public:
	char pad00[8];
	BfmePoolRef10 m_ref08;
	char pad18[0x3a];
	unsigned char m_flag46;

	void rva005C8F17();
	void method_005C9069();

	void method_005C908B(BfmePoolRef10 holder, unsigned char flag);
};

void HostClass005C8E0A::method_005C908B(BfmePoolRef10 holder, unsigned char flag)
{
	rva005C8F17();
	if (!holder.m_target)
		return;
	m_ref08 = holder;
	m_flag46 = flag;
	method_005C8D6B();
	setOverlappedLocking(true);
	method_005C9069();
}
