// cl: /O1 /G7 /DNDEBUG /MD /EHsc /arch:SSE
// Native wrapper93 initializes16-byte listener storage at4 before the derived
// vptr and allocates the verified40-byte implementation. A nonpolymorphic
// storage base models that initialization order; original inheritance is
// structural inference. Target tableC75AAC has dtor4E06 and float callback4C48.
// Callback sends owner and float via the established two-word listener walker;
// its native unconditional collection address is owner+4. The legacy int word
// of that walker carries the32-bit owner pointer here. Both table entries have
// actual typed providers; no new pins or definition markers are introduced.
// ??1Rva005D4C61@@UAE@XZ retail 0x005D4C61 90B dtor stores vtable 0x00875AAC plus list forEach and holder clear with list free

class Rva005D4C01Listener;
class Rva00330757Member { public: Rva00330757Member();
 Rva005D4C01Listener **m_begin,**m_end,**m_capacity; unsigned int m_index;
};

class Rva005D4C01Listener
{
public:
	virtual void notify(void *);
};

void __cdecl free(void *);

class Rva005D4C01List
{
public:
	void forEach(void (Rva005D4C01Listener::*notify)(void *), void *arg);
// ??1Rva005D4C01List@@QAE@XZ present-unmatched
	~Rva005D4C01List()
	{
		void *p = storage.m_begin;
		if (p)
			free(p);
	}
	Rva00330757Member storage;
};

class DummyCb1
{
public:
	void cb(void *);
};

class Rva005D4913
{
public:
	Rva005D4913(void *,int,const class AsciiString &);
 ~Rva005D4913();
 char storage[0x28];
};

class Rva005D4BE7
{
	Rva005D4913 *m_ptr;
public:
	Rva005D4BE7(Rva005D4913 *p):m_ptr(p) {}
 void rva005D4BE7();
// ??1Rva005D4BE7@@QAE@XZ present-unmatched
	~Rva005D4BE7()
	{
		rva005D4BE7();
	}
};

class Rva005D4C61 : public Rva005D4C01List
{
public:
	Rva005D4C61(int,const AsciiString &);
 virtual ~Rva005D4C61();
 virtual void rva005D4C48(float);
private:
	Rva005D4BE7 m_14;
};

Rva005D4C61::~Rva005D4C61()
{
	typedef void (Rva005D4C01Listener::*Notify_t)(void *);
	forEach((Notify_t)&DummyCb1::cb, this);
}

Rva005D4C61::Rva005D4C61(int level,const AsciiString &name):m_14(new Rva005D4913(this,level,name)) {}
class ScrollBarListenerSlots { public: virtual void slot00(); virtual void slot04(Rva005D4C61 *,float); };
class Rva005D48DBElem { public: void Method(int,float); };
typedef void (Rva005D48DBElem::*Rva005D48DBFn)(int,float);
class Rva005D4C1FList { public: void forEach(Rva005D48DBFn,int,float); };
void Rva005D4C61::rva005D4C48(float position) {
 reinterpret_cast<Rva005D4C1FList *>(reinterpret_cast<Rva005D4C01List *>(reinterpret_cast<char *>(this)+4))->forEach(reinterpret_cast<Rva005D48DBFn>(&ScrollBarListenerSlots::slot04),reinterpret_cast<int>(this),position);
}
