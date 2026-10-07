// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Five pre-increment-then-two-call members (36B each): push esi,
// mov esi, ecx, mov eax, [esi+0x10], inc eax, push eax, call <note>,
// push [esp+0x0C], mov ecx, esi, push [esp+0x0C], call <run>,
// mov eax, [esp+8], pop esi, ret 8. Each passes m_count+1 (loaded, not
// stored) to its note helper, then (a, b) to its run helper, and returns
// a. /O1 keeps the argument reads on the stack slots.
// 0x00057B27 (note 0x00056BFE, run 0x00054BC3),
// 0x00057D38 (note 0x0053F1EC-opaque-alias of the rowed Armor hashtable
//   resize, run 0x000556AB),
// 0x000E0536 (note 0x000E0322, run 0x000E0298),
// 0x003EF34A (note 0x00212858, run 0x003EF264),
// 0x0052B7F8 (note 0x00212858, run 0x0052B737).
// Helper identities unproven (opaque pins); owner names address-derived.
// One ledger row per member.

class Rva00056BFESub
{
public:
	void note(int value);
};

class Rva00054BC3Sub
{
public:
	void run(int a, int b);
};

class Rva0053F1ECSub
{
public:
	void note(int value);
};

class Rva000556ABSub
{
public:
	void run(int a, int b);
};

class Rva000E0322Sub
{
public:
	void note(int value);
};

class Rva000E0298Sub
{
public:
	void run(int a, int b);
};

class Rva00212858Sub
{
public:
	void note(int value);
};

class Rva003EF264Sub
{
public:
	void run(int a, int b);
};

class Rva0052B737Sub
{
public:
	void run(int a, int b);
};

class Rva00057B27Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva00057D38Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva000E0536Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva003EF34AOwner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

class Rva0052B7F8Owner
{
public:
	int fwd(int a, int b);

private:
	char m_pad[0x10];
	int m_count;
};

int Rva00057B27Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00056BFESub *)this)->note(next);
	((Rva00054BC3Sub *)this)->run(a, b);
	return a;
}

int Rva00057D38Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva0053F1ECSub *)this)->note(next);
	((Rva000556ABSub *)this)->run(a, b);
	return a;
}

int Rva000E0536Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva000E0322Sub *)this)->note(next);
	((Rva000E0298Sub *)this)->run(a, b);
	return a;
}

int Rva003EF34AOwner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00212858Sub *)this)->note(next);
	((Rva003EF264Sub *)this)->run(a, b);
	return a;
}

int Rva0052B7F8Owner::fwd(int a, int b)
{
	int next = m_count + 1;
	((Rva00212858Sub *)this)->note(next);
	((Rva0052B737Sub *)this)->run(a, b);
	return a;
}

// cl: /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// Native Ghidra 0x0052B894..0x0052B8ED: 89B RET4 constructor.
// It writes the base vptr, copies the input AsciiString into an 8B
// (name, this) entry, inserts it through the registry, then destroys the
// temporary. Result storage is the observed 12B iterator/result area.
// The owner and registry identities remain unknown; names describe their
// measured addresses and operations. The base vtable is already provided
// as vtbl_00C686BC by Disp0DwordImmSettersAddr.cpp's canonical alias.
#include "ascii_string.h"
extern "C" const void *const vtbl_00C686BC[];
extern Rva0052B7F8Owner *rva0052B84F();
class Rva0052B894Registration
{
public:
    Rva0052B894Registration(const AsciiString &name);
private:
    const void *const *m_vtable;
};
struct Rva0052B894Entry
{
    AsciiString name;
    Rva0052B894Registration *registration;
    Rva0052B894Entry(const AsciiString &key, Rva0052B894Registration *value)
        : name(key), registration(value) {}
};
Rva0052B894Registration::Rva0052B894Registration(const AsciiString &name)
{
    m_vtable = vtbl_00C686BC;
    Rva0052B894Entry entry(name, this);
    int result[3];
    Rva0052B7F8Owner *registry = rva0052B84F();
    registry->fwd((int)result, (int)&entry);
}

// stlport
#include <hash_map>
// The native getter at 0x0052B84F..0x0052B894 constructs one 20B local
// static registry through the existing hash_map constructor at 0x0052B81C.
// Its atexit thunk at 0x007B9298 destroys the registry through 0x0052B7B3.
// Reuse the rowed constructor's ABI view; its int key and element type are
// donor inferences, not established identities of the registration table.
// STLport 4.5.3 comes from the unchanged vendor subtree at BFME 1 revision
// 7dff0a4a9e937818d2731f9861ade1815663b9db.
struct Rva0052B81CElement
{
    char bytes[1];
    bool operator<(const Rva0052B81CElement &) const;
    bool operator==(const Rva0052B81CElement &) const;
};
namespace _STL
{
    template<> struct hash<Rva0052B81CElement>
    {
        unsigned operator()(const Rva0052B81CElement &) const;
    };
}
typedef _STL::hash_map<int, Rva0052B81CElement> Rva0052B84FRegistry;
class Rva0052B7B3Dtor
{
public:
    ~Rva0052B7B3Dtor();
};
namespace _STL
{
    // Leave construction to the independently rowed 31B provider. The
    // measured destructor thunk also avoids instantiating inferred element
    // operations when destroying this opaque registry.
    template<> Rva0052B84FRegistry::hash_map();
    template<> inline Rva0052B84FRegistry::~hash_map()
    {
        reinterpret_cast<Rva0052B7B3Dtor *>(this)->~Rva0052B7B3Dtor();
    }
}
Rva0052B7F8Owner *rva0052B84F()
{
    static Rva0052B84FRegistry registry;
    return reinterpret_cast<Rva0052B7F8Owner *>(&registry);
}
