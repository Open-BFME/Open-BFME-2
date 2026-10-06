// ?PushDynamicSetStack@FXShaderParameterBinder@@QAEXPBD@Z
// partial score=0.9 date=2026-09-29
// cl: /DNDEBUG /MD /EHsc
// stlport
// ?PushDynamicSetStack@FXShaderParameterBinder@@QAEXPBD@Z @0x001535FF 101B evidence: same class FXShaderParameterBinder +0x10; COM slots 0x4C 0x6C; string WW3DDynamicSet; ScienceType cur
// Best probe 103B vs 101B 3 regions: first-call pushes scheduled late (retail pushes string+name at +0x14 before mov [ebp-4]); second-call scratch uses eax/ecx not edi/eax. Tried out-temp and self-temp levers per shape guide scratch-rotate; self-temp worsened to 105B.

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{

template <class T>
class allocator
{
};

template <class T, class A = allocator<T> >
class vector
{
public:
	void push_back(const T &x);
};

}

struct Rva0015354EStore
{
	unsigned char m_pad00[4];
	_STL::vector<ScienceType> m_sciences04; // +4
};

class FXShaderParameterBinder
{
public:
	void PushDynamicSetStack(ScienceType value);
	void PushDynamicSetStack(const char *name);

private:
	unsigned char m_pad00[0x10];
	Rva0015354EStore *m_store10; // +0x10
};

struct Com19
{
	virtual void * __stdcall slot00(); virtual void * __stdcall slot04(); virtual void * __stdcall slot08(); virtual void * __stdcall slot0C();
	virtual void * __stdcall slot10(); virtual void * __stdcall slot14(); virtual void * __stdcall slot18(); virtual void * __stdcall slot1C();
	virtual void * __stdcall slot20(); virtual void * __stdcall slot24(); virtual void * __stdcall slot28(); virtual void * __stdcall slot2C();
	virtual void * __stdcall slot30(); virtual void * __stdcall slot34(); virtual void * __stdcall slot38(); virtual void * __stdcall slot3C();
	virtual void * __stdcall slot40(); virtual void * __stdcall slot44(); virtual void * __stdcall slot48();
	virtual void * __stdcall slot4C(const char *name, const char *type);
};

struct Com6C
{
	virtual void * __stdcall slot00(); virtual void * __stdcall slot04(); virtual void * __stdcall slot08(); virtual void * __stdcall slot0C();
	virtual void * __stdcall slot10(); virtual void * __stdcall slot14(); virtual void * __stdcall slot18(); virtual void * __stdcall slot1C();
	virtual void * __stdcall slot20(); virtual void * __stdcall slot24(); virtual void * __stdcall slot28(); virtual void * __stdcall slot2C();
	virtual void * __stdcall slot30(); virtual void * __stdcall slot34(); virtual void * __stdcall slot38(); virtual void * __stdcall slot3C();
	virtual void * __stdcall slot40(); virtual void * __stdcall slot44(); virtual void * __stdcall slot48(); virtual void * __stdcall slot4C();
	virtual void * __stdcall slot50(); virtual void * __stdcall slot54(); virtual void * __stdcall slot58(); virtual void * __stdcall slot5C();
	virtual void * __stdcall slot60(); virtual void * __stdcall slot64(); virtual void * __stdcall slot68();
	virtual int __stdcall slot6C(void *a, ScienceType *out);
};

void FXShaderParameterBinder::PushDynamicSetStack(const char *name)
{
	Rva0015354EStore *store = m_store10;
	ScienceType cur;
	ScienceType *out = &cur;
	if (store == 0)
		return;
	ScienceType *finish = *(ScienceType **)((char *)store + 8);
	cur = *(finish - 1);
	Com19 *c19 = *(Com19 **)this;
	void *found = c19->slot4C(name, "WW3DDynamicSet");
	if (found == 0)
		goto add;
	Com6C *c6c = *(Com6C **)this;
	int r = c6c->slot6C(found, out);
	if (r < 0)
		goto reload;
	if (cur < 0)
		goto reload;
	if (cur < 6)
		goto add;
reload:
	{
		Rva0015354EStore *s2 = m_store10;
		ScienceType *f2 = *(ScienceType **)((char *)s2 + 8);
		cur = *(f2 - 1);
	}
add:
	PushDynamicSetStack(cur);
}
