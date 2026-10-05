// ?rva0028CECF@Object@@QAE_NXZ
// partial score=0.93 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ?rva0028CECF@Object@@QAE_NXZ @0x0028CECF (104B). Identity: Object predicate
// climbing the +0x274 containedBy chain while the container template flag
// byte 0x115 has bit 0x20, then gating on the +0x258 entry and comparing the
// template float at +0x50c against the rowed Object float 0x0028AC7D and the
// rowed Rva002627E8 float 0x002627E8. Evidence: 11 callers, callees rowed,
// neighbours Object methods with +0x274/+0x250 per Rva0028CC7CFinish and
// +0x258 holder per ObjectRva0028AC4EAccessors; flags from SSE sibling
// ObjectRva0028B141. Honest address name on the proven Object class.

class Rva002627E8
{
public:
	float rva002627E8() const;
};

struct Rva0028CECFTemplate
{
	char m_pad00[0x115];
	unsigned char m_flag115;
	char m_pad116[0x50C - 0x116];
	float m_f50C;
};

class Object
{
public:
	bool rva0028CECF();
	float rva0028AC7D() const;

private:
	char m_pad00[4];
	Rva0028CECFTemplate *m_template004;
	char m_pad08[0x258 - 8];
	Rva002627E8 *m_entry258;
	char m_pad25C[0x274 - 0x25C];
	Object *m_contained274;
};

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ?rva0028CECF@Object@@QAE_NXZ present-unmatched
bool Object::rva0028CECF()
{
	Object *obj = this;
	for (;;) {
		Object *cont = obj->m_contained274;
		if (cont == 0)
			break;
		Rva0028CECFTemplate *tmpl = cont->m_template004;
		_ReadWriteBarrier();
		if ((tmpl->m_flag115 & 0x20) == 0)
			break;
		obj = cont;
	}
	Rva002627E8 *holder = obj->m_entry258;
	if (holder == 0)
		goto ret_false;
	float f = obj->m_template004->m_f50C;
	if (f <= 0.0f)
		goto ret_true;
	float f1 = obj->rva0028AC7D();
	float f2 = holder->rva002627E8() * f;
	if (f2 > f1)
		goto ret_false;
	goto ret_true;
ret_false:
	return false;
ret_true:
	return true;
}
