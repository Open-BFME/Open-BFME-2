// cl: /O1 /arch:SSE /G7 /MD
// ?rva0059AEFF@Rva0059AEFF@@QAEHXZ @0x0059AEFF 49B.
// Leaf that forwards a truncated float through a sink struct to the pinned
// 0x0037DF8D and returns the sink's middle field. The float comes from
// +0x10 of the object at +0x24, the receiver from +0x08, the sink's head
// points at g_00C70E5C and its tail holds the truncated int. Evidence:
// caller 0x004F9BAB, pin callee 0x0037DF8D, extern g_00C70E5C, no donor.
class Rva0037DCA5;
class Rva002206F9Sink
{
public:
	int *m_00;
	int m_04;
	int m_08;
};
extern int g_00C70E5C;
class Rva0037DCA5
{
public:
	void rva0037DF8D(Rva002206F9Sink *sink);
};
struct Rva0059AEFF24
{
	char m_pad00[0x10];
	float m_10;
};
class Rva0059AEFF
{
public:
	int rva0059AEFF();
private:
	char m_pad00[8];
	Rva0037DCA5 *m_08;
	char m_pad0C[0x24 - 0x0C];
	Rva0059AEFF24 *m_24;
};
int Rva0059AEFF::rva0059AEFF()
{
	float f = m_24->m_10;
	Rva0037DCA5 *obj = m_08;
	Rva002206F9Sink sink;
	sink.m_00 = &g_00C70E5C;
	sink.m_04 = 0;
	sink.m_08 = (int)f;
	obj->rva0037DF8D(&sink);
	return sink.m_04;
}
