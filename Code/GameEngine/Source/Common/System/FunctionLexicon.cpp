// cl: /O1 /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/System/FunctionLexicon.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1):
// FunctionLexicon::keyToFunc 0x002D2235 (42B), FunctionLexicon::findFunction
// 0x002D225F (77B) and FunctionLexicon::winLayoutInitFunc 0x002D23A1 (48B).
// The unit carries its own BFME2 view of the class instead of Zero Hour's
// header: the table array sits at +0x0C (BFME2's 0xC-byte SubsystemInterface
// base) and findFunction's TABLE_ANY loop runs over 12 tables (cmp edi, 0xc),
// both read off retail's findFunction; winLayoutInitFunc searches slots 8 then
// 7. keyToFunc must stay in this unit ahead of findFunction: retail keeps
// `this` in edx across its calls, which cl does only for a callee it has
// already compiled here.
enum NameKeyType { NAMEKEY_INVALID = 0 };

class WindowLayout;
typedef void (*WindowLayoutInitFunc)(WindowLayout *layout, void *userData);

class FunctionLexicon
{
public:
	struct TableEntry
	{
		NameKeyType key;
		const char *name;
		void *func;
	};

	enum TableIndex
	{
		TABLE_ANY = -1,
		TABLE_WIN_LAYOUT_INIT = 7,		// BFME2 slots, from winLayoutInitFunc
		TABLE_WIN_LAYOUT_DEVICEINIT = 8,
		MAX_FUNCTION_TABLES = 12		// BFME2: findFunction's loop bound
	};

	WindowLayoutInitFunc winLayoutInitFunc(NameKeyType key, TableIndex index = TABLE_ANY);

protected:
	void *keyToFunc(NameKeyType key, TableEntry *table);
	void *findFunction(NameKeyType key, TableIndex index);

private:
	unsigned char m_subsystem[0xC];			// SubsystemInterface base (BFME2 size)
	TableEntry *m_tables[MAX_FUNCTION_TABLES];	// +0x0C
};

void *FunctionLexicon::keyToFunc(NameKeyType key, TableEntry *table)
{
	if (key == NAMEKEY_INVALID)
		return 0;

	TableEntry *entry = table;
	while (entry && entry->key != NAMEKEY_INVALID)
	{
		if (entry->key == key)
			return entry->func;
		entry++;
	}

	return 0;
}

void *FunctionLexicon::findFunction(NameKeyType key, TableIndex index)
{
	void *func = 0;

	if (key == NAMEKEY_INVALID)
		return 0;

	if (index == TABLE_ANY)
	{
		int i;
		for (i = 0; i < MAX_FUNCTION_TABLES; i++)
		{
			func = keyToFunc(key, m_tables[i]);
			if (func)
				break;
		}
	}
	else
	{
		func = keyToFunc(key, m_tables[index]);
	}

	return func;
}

WindowLayoutInitFunc FunctionLexicon::winLayoutInitFunc(NameKeyType key, TableIndex index)
{
	if (index == TABLE_ANY)
	{
		WindowLayoutInitFunc func;

		func = (WindowLayoutInitFunc)findFunction(key, TABLE_WIN_LAYOUT_DEVICEINIT);
		if (func == 0)
			func = (WindowLayoutInitFunc)findFunction(key, TABLE_WIN_LAYOUT_INIT);
		return func;
	}
	return (WindowLayoutInitFunc)findFunction(key, index);
}
