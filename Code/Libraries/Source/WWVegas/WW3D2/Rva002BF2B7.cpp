// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
// ?rva002BF2B7@Rva002BF4F3@@QAE_NHPAVVector3@@@Z, retail 0x002BF2B7 129B.
// Zero out then best RenderObj via slot42 then re-setup and cast. Evidence:
// unlock lane, caller 0x0009ADB1, callees rva002BEA10 rva002BEF4B Cast rowed,
// slots 42 and 13, out Vector3 proven by Cast, bool return. Finish stash
// 0x002bf2b7 score 0.98 missing mov ecx esi reload.
class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class RenderObjClass;

class Rva00DFEF18Host
{
public:
	bool Cast(RenderObjClass *obj, const Vector3 &start, const Vector3 &dir, Vector3 *out, int collisionType, bool checkHidden);
};

class Rva002BF4F3 : public Rva00DFEF18Host
{
public:
	virtual void ownerSlot0();
	virtual void ownerSlot1();
	virtual void ownerSlot2();
	virtual void ownerSlot3();
	virtual void ownerSlot4();
	virtual void ownerSlot5();
	virtual void ownerSlot6();
	virtual void ownerSlot7();
	virtual void ownerSlot8();
	virtual void ownerSlot9();
	virtual void ownerSlot10();
	virtual void ownerSlot11();
	virtual void ownerSlot12();
	virtual void ownerSlot13(int, const Vector3 &, const Vector3 &);
	virtual void ownerSlot14();
	virtual void ownerSlot15();
	virtual void ownerSlot16();
	virtual void ownerSlot17();
	virtual void ownerSlot18();
	virtual void ownerSlot19();
	virtual void ownerSlot20();
	virtual void ownerSlot21();
	virtual void ownerSlot22();
	virtual void ownerSlot23();
	virtual void ownerSlot24();
	virtual void ownerSlot25();
	virtual void ownerSlot26();
	virtual void ownerSlot27();
	virtual void ownerSlot28();
	virtual void ownerSlot29();
	virtual void ownerSlot30();
	virtual void ownerSlot31();
	virtual void ownerSlot32();
	virtual void ownerSlot33();
	virtual void ownerSlot34();
	virtual void ownerSlot35();
	virtual void ownerSlot36();
	virtual void ownerSlot37();
	virtual void ownerSlot38();
	virtual void ownerSlot39();
	virtual void ownerSlot40();
	virtual void ownerSlot41();
	virtual RenderObjClass *ownerSlot42();

	void rva002BEA10(RenderObjClass *, bool);
	void rva002BEF4B(RenderObjClass *);
	bool rva002BF2B7(int, Vector3 *);
};

bool Rva002BF4F3::rva002BF2B7(int a1, Vector3 *out)
{
	out->X = 0.0f;
	out->Y = 0.0f;
	out->Z = 0.0f;
	RenderObjClass *obj = ownerSlot42();
	if (!obj)
		return false;
	rva002BEA10(obj, false);
	rva002BEF4B(obj);
	Vector3 vec1;
	Vector3 vec2;
	ownerSlot13(a1, vec1, vec2);
	bool hit = reinterpret_cast<Rva00DFEF18Host *>(this)->Cast(obj, vec1, vec2, out, 1, false);
	rva002BEA10(obj, true);
	return hit;
}
