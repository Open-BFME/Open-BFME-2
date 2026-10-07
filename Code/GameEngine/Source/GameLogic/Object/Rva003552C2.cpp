// cl: /Ireference/shims/bfme2_ascii /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// ?rva003552C2@Rva00355B61@@QAE_NW4NameKeyType@@@Z @0x003552C2 77B
// Evidence: this is Rva00355B61 via this->rva00355155; global g_00E01E18 via Rva0035516C find; ArmorTemplate check 0x355290 row types int but retail tests al so byte-truncated use; second find then virtual slot 0x10; caller 0x36B700
enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
struct ArmorListNode
{
	ArmorListNode *m_next;
	int m_4;
	int m_8;
};
class ArmorTemplate
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void vslot10(NameKeyType key);
	int rva00355290();
	ArmorListNode *m_head;
	int m_check;
};
class Rva0035516C
{
public:
	const ArmorTemplate *rva0035516C(NameKeyType key) const;
};
// Bind the native VA 0x00E01E18 slot to its existing subsystem owner;
// casts below retain this unit's independently verified local view.
class AiOrdersManager;
extern AiOrdersManager *TheAiOrdersManager;
class Rva00355B61
{
public:
	const ArmorTemplate *rva00355155(NameKeyType key) const;
	bool rva003552C2(NameKeyType key);
};
bool Rva00355B61::rva003552C2(NameKeyType key)
{
	const ArmorTemplate *t1 = reinterpret_cast<Rva0035516C *>(TheAiOrdersManager)->rva0035516C(key);
	if (!t1)
		return false;
	if (((unsigned char)((ArmorTemplate *)t1)->rva00355290()) == 0)
		return false;
	ArmorListNode *head = ((ArmorTemplate *)t1)->m_head;
	ArmorListNode *first = head->m_next;
	const ArmorTemplate *t2 = rva00355155((NameKeyType)first->m_8);
	if (t2) {
		((ArmorTemplate *)t2)->vslot10(key);
		return true;
	}
	return false;
}
