// cl: /O1 /DNDEBUG /MD
// ?rva00356FAF@ScriptEngine@@QAEXH@Z @0x00356FAF 45B via unlock callee evidence
// Evidence: calls rowed ScriptEngine::rva00203FA8 0x00203FA8; prev ScriptEngine TU; clears +0x1A114/+0x1A11C.
class ScriptEngine
{
public:
	void rva00203FA8(int needle);
	void rva00356FAF(int arg);

private:
	char m_pad[0x1A114];
	int m_1A114;
	int m_1A118;
	int m_1A11C;
};

void ScriptEngine::rva00356FAF(int arg)
{
	rva00203FA8(arg);
	if (m_1A11C == arg)
		m_1A11C = 0;
	if (m_1A114 == arg)
		m_1A114 = 0;
}
