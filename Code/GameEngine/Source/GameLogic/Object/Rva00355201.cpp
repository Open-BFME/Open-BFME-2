// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// ?Rva00355201Apply@@YGXHPAX0@Z @0x00355201 86B
// Evidence: chain from 0x005481F9; range at +4/+8 step 4; armor lookup 0x0035516C row; flags from kind 1/2; ObjectID at +0x10
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum ObjectID { INVALID_ID = 0 };

class ArmorTemplate;
class Rva0035516C
{
public:
	const ArmorTemplate *rva0035516C(NameKeyType key) const;
};
// Bind the native VA 0x00E01E18 slot to its existing subsystem owner;
// casts below retain this unit's independently verified local view.
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;

class Rva00548117
{
public:
	void rva005481F9(ObjectID v, int flags);
};

struct KeyRange00355201
{
	int m_pad;
	NameKeyType *m_begin;
	NameKeyType *m_end;
};

struct Arg200355201
{
	char m_pad[0x10];
	ObjectID m_id;
};

void __stdcall Rva00355201Apply(int kind, void *a2, void *a3)
{
	if (kind == 0)
		return;
	Arg200355201 *arg2 = (Arg200355201 *)a2;
	KeyRange00355201 *range = (KeyRange00355201 *)a3;
	NameKeyType *cur = range->m_begin;
	NameKeyType *end = range->m_end;
	for (; cur != end; ++cur) {
		const ArmorTemplate *armor = reinterpret_cast<Rva0035516C *>(TheAiOrdersManager)->rva0035516C(*cur);
		if (!armor)
			continue;
		int flags = 0;
		if (kind == 1)
			flags = 1;
		else if (kind == 2)
			flags = 2;
		((Rva00548117 *)armor)->rva005481F9(arg2->m_id, flags);
	}
}
