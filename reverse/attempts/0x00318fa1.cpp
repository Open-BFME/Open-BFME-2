// ?rva00318FA1@Rva00318FA1@@QAEPAVRva0020E89C@@XZ
// partial score=0.93 date=2026-10-06
// cl: /O1 /DNDEBUG /MD
// ?rva00318FA1@Rva00318FA1@@QAEPAVRva0020E89C@@XZ @0x00318FA1 29B: return wheel lookup or null.
// Evidence: calls rowed ?getWheelInfo@Drawable@@QBEPBUTWheelInfo@@XZ 0x00318B83 then tail-jmps rowed ?rva00538CEF@Rva00538CEF@@QAEPAVRva0020E89C@@XZ 0x00538CEF; null and empty-vector guards; callers 0x0009C86A 0x002B3CB3 0x002BCED6 0x003195D2 0x0056AAD7 0x0056AAFA; neighbours Rva00318F64/Rva00318FBEGet give TU and flags.
class Rva0020E89C;

struct TWheelElem
{
	char m_pad[16];
};

struct TWheelInfo
{
	TWheelElem *m_start;
	TWheelElem *m_finish;
};

class Drawable
{
public:
	const TWheelInfo *getWheelInfo() const;
};

class Rva00538CEF
{
public:
	Rva0020E89C *rva00538CEF();
};

class Rva00318FA1
{
public:
	Rva0020E89C *rva00318FA1();
};

Rva0020E89C *Rva00318FA1::rva00318FA1()
{
	const TWheelInfo *wheel = ((Drawable *)this)->getWheelInfo();
	if (wheel) {
		if ((((char *)wheel->m_finish - (char *)wheel->m_start) >> 4) != 0)
			return ((Rva00538CEF *)wheel)->rva00538CEF();
	}
	return 0;
}
