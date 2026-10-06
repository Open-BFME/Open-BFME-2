// cl: /MD
//
// ?Rva004ADBF2@Rva004AD9B0@@MAEX_N0@Z, retail 0x004ADBF2, 70 bytes. Virtual
// slot 13 (offset 0x34) of vtable 0x008551C0 (class of rowed dtor
// ??1Rva004AD9B0@@UAE@XZ in ModuleUpdateDtors.cpp, same primary; gap
// between 0x004ADB1B/188 and 0x004ADC38/80). Body forwards two bools to
// pinned SpecialAbilityUpdate::onExit 0x004502CE after BuildListInfo
// gatherer check via rowed 0x005508E2 (twice, second stores 1.0f at
// +0xb0) and Object::setStatus 0x0023DB0E with 0x4a/false. Identity is
// slot 13 plus the onExit-forward shape; flags copy the neighbour
// ModuleUpdateDtors.cpp (/O1 /MD) plus /arch:SSE for retail movss.
// Honest address-derived name: class proven by vtable/dtor, method
// unmapped so Rva address used; protected virtual per Module precedent.

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

enum ObjectStatusTypes
{
	ST_4A = 0x4a
};

class Object
{
public:
	void setStatus(ObjectStatusTypes status, bool flag);
};

class Rva004AD9B0;

class SpecialAbilityUpdate
{
private:
	void onExit(bool a, bool b);
	friend class Rva004AD9B0;
};

class Rva004AD9B0
{
protected:
	virtual void Rva004ADBF2(bool a, bool b);
private:
	char m_pad04[4];
	void *m_08;
};

void Rva004AD9B0::Rva004ADBF2(bool a, bool b)
{
	int v = ((BuildListInfo *)m_08)->getDesiredGatherers();
	if (v != 0)
	{
		int v2 = ((BuildListInfo *)m_08)->getDesiredGatherers();
		float one = 1.0f;
		*(float *)(v2 + 0xb0) = one;
	}
	((Object *)m_08)->setStatus((ObjectStatusTypes)0x4a, false);
	((SpecialAbilityUpdate *)this)->onExit(a, b);
}
