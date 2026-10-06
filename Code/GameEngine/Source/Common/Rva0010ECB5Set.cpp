// cl: /MD
// ?rva0010ECB5@Rva0010ECB5@@QAE_NXZ at 0x0010ECB5 (8B).
// This-adjusting thunk to ?set@Rva0040F9D@@QAE_NXZ at 0x00040F9D: add ecx,0x4C then tail-jmp.
// Evidence: retail bytes add ecx,0x4C; jmp 0x00040F9D; rowed callee in Rva0040F9DEvent.cpp;
// callers at 0x000A835A 0x000A83F5 0x000A860B; sibling 0x0010EC4D calls same set at +0x44.
class Rva0040F9D
{
public:
	virtual ~Rva0040F9D();
	bool set();
private:
	void *m_handle;
};

class Rva0010ECB5
{
public:
	bool rva0010ECB5();
private:
	char m_pad[0x4C];
	Rva0040F9D m_evt;
};

bool Rva0010ECB5::rva0010ECB5()
{
	return m_evt.set();
}
