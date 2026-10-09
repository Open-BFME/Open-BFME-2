// ?slot38@Rva004771EB@@UAE_NPAVObject@@HH@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /MD /DNDEBUG /Oy-
// partial score=0.85 date=2026-10-05
// ?rva004771EB@Rva004771EB@@QAE_NPAVObject@@HH@Z
// partial score=0.85 date=2026-10-05
// ?rva004771EB@Rva004771EB@@QAE_NPAVObject@@HH@Z, retail 0x004771EB, 147 bytes.
// Evidence: slot38-shape sibling in the 0x0047CA4D chain (STATUS_38 refusal is
// ObjectStatus 0x26 here): base slot38-shape body 0x00462977 refusal first, then
// a siege-engine lookup through the pinned ?rva00588BF3 member (this+0xfd box
// over this-0x20, non-null return passes), then a capacity gate reusing the a2
// home as the accumulator over two same-object virtuals (slots 0xCC and 0x114,
// gap-template layout after the slot53 TU idiom) plus the pinned 0x0028FBBE
// helper against the limit at tab+0x98 (tab base this-0x1c). /O1 with y-off ebp
// frame. Honest address name; the owning class is unproven.

enum ObjectStatusTypes
{
	STATUS_38 = 0x26
};
class Player;
class Rva00588E44Contain;
class Object
{
public:
	bool testStatus(ObjectStatusTypes s) const;
	Player *getControllingPlayer() const;
	int rva0028FBBE();
};
class OpenContain
{
public:
	virtual bool isValidContainerFor(Object *obj, bool a, bool b);
};
class Rva0047A040Base9E0
{
public:
	Rva00588E44Contain *rva00588BF3(void *a, Object *b);
};
class Rva0028FBBE
{
public:
	int rva0028FBBE();
};

template <int N> class Rva004771EBSlots : public Rva004771EBSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004771EBSlots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class Rva004771EBLow : public Rva004771EBSlots<51>
{
public:
	virtual int slotCC() = 0; // vtable slot 51 (0xCC)
};

template <int N> class Rva004771EBMid : public Rva004771EBMid<N - 1>
{
public:
	virtual void mid(char (*)[N]) = 0;
};
template <> class Rva004771EBMid<1> : public Rva004771EBLow
{
public:
	virtual void mid(char (*)[1]) = 0;
};

class Rva004771EB : public Rva004771EBMid<17>
{
public:
	virtual int slot114(int x) = 0; // vtable slot 69 (0x114)
	virtual bool slot38(Object *obj, int a2, int a3);
    __forceinline const char *moduleData() const { return *reinterpret_cast<const char *const *>(reinterpret_cast<const char *>(this)-0x1c); }
};

#pragma optimize("y", off)
bool Rva004771EB::slot38(Object *obj, int a2, int a3)
{
	if (!((OpenContain *)this)->OpenContain::isValidContainerFor(obj, *reinterpret_cast<bool *>(const_cast<int *>(&a2)), *reinterpret_cast<bool *>(&a3)))
		goto failed;
	if (*(int *)((char *)obj + 0x250) == 0 && obj->testStatus(STATUS_38)) {
		void *inner = (void *)((char *)this - 0x20);
		Rva0047A040Base9E0 *box = (Rva0047A040Base9E0 *)((char *)this + 0xfd);
		return (bool)box->rva00588BF3(inner, obj);
	}
	if ((unsigned char)a2 != 1)
		goto pass;
    const char *module=moduleData();
    volatile unsigned used=static_cast<unsigned>(slot114(0));
    used+=static_cast<unsigned>(slotCC());
    unsigned total=used+static_cast<unsigned>(obj->rva0028FBBE());
	if (static_cast<unsigned>(total) <= *reinterpret_cast<const unsigned *>(module+0x98))
		goto pass;
failed:
	return false;
 pass:
	return true;
}
#pragma optimize("", on)



