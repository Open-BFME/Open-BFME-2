// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva00203FA8@ScriptEngine@@QAEXH@Z at retail 0x00203FA8 (39B).
// Clears the flag word of the first 8-byte record in the +0x1A120 range
// whose +0x04 word equals the argument, then stops. Same
// ecx-plus-stack-arg callee-cleanup member shape as the rowed neighbour
// setSequentialTimer at 0x00203FCF (ends ret 8); this one takes one stack
// argument and ends ret 4. Member naming follows that neighbour; the record
// payload is otherwise unrecovered, so the address-derived name stays.
class ScriptEngine003FA8Record
{
public:
	void *m_00;
	int m_flag04;
};

class ScriptEngine
{
public:
	void rva00203FA8(int needle);

private:
	char m_pre[0x1A120];
	ScriptEngine003FA8Record *m_begin; // +0x1A120
	ScriptEngine003FA8Record *m_end; // +0x1A124
};

void ScriptEngine::rva00203FA8(int needle)
{
	ScriptEngine003FA8Record *rec = m_begin;
	ScriptEngine003FA8Record *end = m_end;
	for (; rec != end; ++rec) {
		if (needle == rec->m_flag04) {
			rec->m_flag04 = 0;
			break;
		}
	}
}
