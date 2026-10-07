// Sibling of the AptValue conversion helper in Rva006F1F50Cluster.cpp: the
// same "isXml() -> checked cast -> +0x20 sub-object -> build an Apt integer"
// shape, but it invokes the sub-object's vtable slot 0x74 instead of 0x70.
// A __cdecl free function; identity is not recovered, so the name is
// address-derived. No // cl: line: the default /O2 frameless shape matches.

class AptValue;

class Rva006F1F90Sub
{
public:
	virtual void vf00();
	virtual void vf04();
	virtual void vf08();
	virtual void vf0c();
	virtual void vf10();
	virtual void vf14();
	virtual void vf18();
	virtual void vf1c();
	virtual void vf20();
	virtual void vf24();
	virtual void vf28();
	virtual void vf2c();
	virtual void vf30();
	virtual void vf34();
	virtual void vf38();
	virtual void vf3c();
	virtual void vf40();
	virtual void vf44();
	virtual void vf48();
	virtual void vf4c();
	virtual void vf50();
	virtual void vf54();
	virtual void vf58();
	virtual void vf5c();
	virtual void vf60();
	virtual void vf64();
	virtual void vf68();
	virtual void vf6c();
	virtual int vf70();
	virtual int vf74();
};

class BfmeAptValue006DCD20
{
public:
	int isXml() const;
	BfmeAptValue006DCD20 *rva006DD260();

	char m_pad00[0x20];
	Rva006F1F90Sub *m_sub20;
};

// The native call targets the verified type-7 pooled factory at
// 0x006D8520 in AptIntegerCreateBFME2.cpp. Only its static interface is
// used here; neither a scalar layout nor these callers' identity is inferred.
class AptInteger
{
public:
	static AptValue *Create(int value);
};

void rva006F1F90(BfmeAptValue006DCD20 *value)
{
	int result = 0;

	if (static_cast<unsigned char>(value->isXml()))
	{
		BfmeAptValue006DCD20 *child = value->rva006DD260();

		if (child->m_sub20 != 0)
			result = child->m_sub20->vf74();
	}

	AptInteger::Create(result);
}
