// cl: /DNDEBUG /MD
//
// Small bodies with no ledger owner, batch AA: vtable slots together with
// the unrowed callees they need (Ghidra-listed, never rowed). As in
// VslotSmallBodiesA-Z, each class and method is address-derived unless the
// ledger already names it, and models only what its body touches. Meanings
// are not recovered.

typedef int Int;

class AsciiString;

// 0x001D9083: whether the armor template the store at VA 0x00DFDBC4 finds
// under this name (the rowed 0x001D901B) has a positive +0x74; reached
// from 0x004BF8AC, the slot that applies it to the +0xF8 name (eleven
// module tables).
class ArmorTemplate
{
public:
	char m_pad00[0x74];
	Int m_74;
};
class Rva001D901B
{
public:
	const ArmorTemplate *rva001D901B(const AsciiString &name) const;
};
extern class ArmorStore *TheArmorStore;
class Rva001D9083
{
public:
	Int rva001D9083();
};
Int Rva001D9083::rva001D9083()
{
	const ArmorTemplate *armor = (*(Rva001D901B **)&TheArmorStore)->rva001D901B(*(const AsciiString *)this);
	if (armor)
	{
		bool positive = armor->m_74 > 0;
		return positive;
	}
	return 0;
}
class Rva004BF8AC
{
public:
	Int rva004BF8AC();
private:
	char m_pad00[0xF8];
	Rva001D9083 m_F8;
};
Int Rva004BF8AC::rva004BF8AC()
{
	return m_F8.rva001D9083();
}

// 0x0060038E (three tables): virtual slot 4 of the +0x08 object.
class Rva0060038ETarget
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
};
class Rva0060038E
{
public:
	void rva0060038E();
private:
	Int m_00;
	Int m_04;
	Rva0060038ETarget *m_08;
};
void Rva0060038E::rva0060038E()
{
	m_08->v04();
}

// 0x001F9343 (three callers): the pinned
// ParticleSystemManager::findTemplate for the name (the second argument is
// unused); 0x001E0C77 is a slot that asks the manager at VA 0x00DFDD04 for
// its +0x148 name with its first argument.
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	__declspec(noinline) ParticleSystemTemplate *rva001F9343(const AsciiString &name, Int unused) const;
};
ParticleSystemTemplate *ParticleSystemManager::rva001F9343(const AsciiString &name, Int) const
{
	return findTemplate(name);
}
extern class ParticleSystemManager *TheParticleSystemManager;
class Rva001E0C77
{
public:
	ParticleSystemTemplate *rva001E0C77(Int a, Int unused);
private:
	char m_pad00[0x148];
	void *m_148; // AsciiString
};
ParticleSystemTemplate *Rva001E0C77::rva001E0C77(Int a, Int)
{
	return TheParticleSystemManager->rva001F9343(*(const AsciiString *)&m_148, a);
}

// 0x0042c0ae: installed-vtable scalar store. Only the native memory
// write and stack-word ABI are known; owner and field meaning remain unknown.
class Rva0042C0AEScalarStore {public: void rva0042C0AE(Int unused); private: char m_prefix[0x28]; Int m_value;};
void Rva0042C0AEScalarStore::rva0042C0AE(Int unused) {m_value=0;}

// 0x0042c0b5: installed-vtable scalar store. Only the native memory
// write and stack-word ABI are known; owner and field meaning remain unknown.
class Rva0042C0B5ScalarStore {public: void rva0042C0B5(Int unused,Int value); private: char m_prefix[0x24]; Int m_value;};
void Rva0042C0B5ScalarStore::rva0042C0B5(Int unused,Int value) {m_value=value;}

// 0x0056a9ed: installed-vtable scalar store. Only the native memory
// write and stack-word ABI are known; owner and field meaning remain unknown.
class Rva0056A9EDScalarStore {public: void rva0056A9ED(Int unused); private: char m_prefix[0x9]; unsigned char m_value;};
void Rva0056A9EDScalarStore::rva0056A9ED(Int unused) {m_value=0;}

// 0x005cc958: installed-vtable scalar store. Only the native memory
// write and stack-word ABI are known; owner and field meaning remain unknown.
class Rva005CC958ByteStore {public: void rva005CC958(Int unused);void rva005CC95F(Int unused); private: char m_prefix[0x23]; unsigned char m_value;};
void Rva005CC958ByteStore::rva005CC958(Int unused) {m_value=1;}
void Rva005CC958ByteStore::rva005CC95F(Int unused) {m_value=0;}

// 0x005e39d9: installed-vtable scalar store. Only the native memory
// write and stack-word ABI are known; owner and field meaning remain unknown.
class Rva005E39D9ScalarStore {public: void rva005E39D9(Int unused,Int value); private: char m_prefix[0x29]; unsigned char m_value;};
void Rva005E39D9ScalarStore::rva005E39D9(Int unused,Int value) {m_value=1;}
