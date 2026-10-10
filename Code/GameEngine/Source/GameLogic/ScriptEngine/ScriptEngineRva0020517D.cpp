// cl: /EHsc
// ?rva0020517D@ScriptEngine@@QAEXPAVObject@@@Z @0x0020517D 58B: remove sequential scripts for an object.
// Evidence: caller 0x003BC259 passes getUnitNamed Object*; loops m_sequentialScripts +0x10..+0x14 calling rowed cleanupSequentialScript 0x00204733 with (it,1,1) when slot empty or +8 matches Object+0x74; same shape as siblings 0x00205140 and 0x002051B7.
class Object;

class SequentialScript
{
public:
	char m_pad00[4];
	Object *m_04; // +0x04 match pointer
	int m_8; // +0x08 match key
	char m_padC[4]; // +0x0C..0x0F
	bool m_10; // +0x10 gate
	char m_pad11[3]; // +0x11..0x13
	SequentialScript *m_14; // +0x14 link
};

class Object
{
public:
	char m_pad[0x74];
	int m_74; // +0x74 match key
};

class ScriptEngine
{
protected:
	SequentialScript **cleanupSequentialScript(SequentialScript **it, bool cleanDanglers, bool removeEntry);
public:
	void rva0020517D(Object *obj);
	void rva00205140(SequentialScript *arg);
	void rva002051B7(Object *obj);
	void rva002064CB(class Team *team);
private:
	char m_pre[0x10];
	SequentialScript **m_begin; // +0x10
	SequentialScript **m_end; // +0x14
	char m_mid[0x1A110 - 0x18];
	Object *m_1A110; // +0x1A110
	char m_pad114[4];
	Object *m_1A118; // +0x1A118
};

void ScriptEngine::rva0020517D(Object *obj)
{
	if (!obj)
		return;
	int id = obj->m_74;
	SequentialScript **it = m_begin;
	while (it != m_end) {
		SequentialScript *s = *it;
		if (!s || s->m_8 == id)
			it = cleanupSequentialScript(it, true, true);
		else
			++it;
	}
}

void ScriptEngine::rva00205140(SequentialScript *arg)
{
	if (!arg)
		return;
	if (!arg->m_10)
		return;
	SequentialScript **it = m_begin;
	while (it != m_end) {
		SequentialScript *s = *it;
		if (s && s->m_14 == arg)
			it = cleanupSequentialScript(it, true, true);
		else
			++it;
	}
}

// ?rva002051B7@ScriptEngine@@QAEXPAVObject@@@Z @0x002051B7 81B
// Clear sequential-script slots whose +4 matches obj via rowed
// cleanupSequentialScript(it,1,0), then clear +0x1A110/+0x1A118 if obj.
// Evidence: same +0x10..+0x14 loop as siblings above, callee row 0x00204733,
// callers 0x003A3583 and thunk 0x002064CB.
void ScriptEngine::rva002051B7(Object *obj)
{
	if (!obj)
		return;
	for (SequentialScript **it = m_begin; it != m_end; ++it) {
		SequentialScript *s = *it;
		if (!s || s->m_04 == obj)
			cleanupSequentialScript(it, true, false);
	}
	if (m_1A110 == obj)
		m_1A110 = 0;
	if (m_1A118 == obj)
		m_1A118 = 0;
}

// ?rva002064CB@ScriptEngine@@QAEXPAVTeam@@@Z @0x002064CB 5B, pinned under this
// name: a tail jump into 0x002051B7 that keeps its Team* argument. Its one
// caller 0x003C0C3E has BFME 1's doTeamStopSequentialScript shape (getTeamNamed
// then removeAllSequentialScripts(Team*)), so the argument is a team pointer
// that 0x002051B7, typed Object* here, only compares against slot +4.
void ScriptEngine::rva002064CB(Team *team)
{
	rva002051B7((Object *)team);
}
