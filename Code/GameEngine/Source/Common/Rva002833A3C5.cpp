// cl: /DNDEBUG /MD /EHsc /O1 /G7 /Oy-
//
// The adjacent 34-byte bodies at 0x002833A3 and 0x002833C5 each read a map
// pointer at +0x40 or +0x3C, respectively, and call the same 78-byte helper
// at 0x00283033 with an output slot and pointer key. A returned non-null
// handle is released through the rowed 0x0007DEEF fastcall. The owner and
// method names are address-derived; no target class identity is inferred.

struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva00283033
{
public:
	void rva00283033(void *out, void *key);
};

class Rva002833A3C5Owner
{
public:
	void rva002833A3(void *unused, void *key);
	void rva002833C5(void *unused, void *key);

private:
	char m_pad00[0x3c];
	Rva00283033 *m_map3c;
	Rva00283033 *m_map40;
};

void Rva002833A3C5Owner::rva002833A3(void *, void *key)
{
	m_map40->rva00283033(&key, key);
	if (key)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)key);
}

void Rva002833A3C5Owner::rva002833C5(void *, void *key)
{
	m_map3c->rva00283033(&key, key);
	if (key)
		ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)key);
}
