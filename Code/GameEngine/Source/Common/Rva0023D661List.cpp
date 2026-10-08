// cl: /MD
// ?rva0023D661@Rva0023D661@@QAEXH@Z @ 0x0023D661 45B: calls Object::rva0028B31A on each node from +0xAC head via +0x8C next then tails to TheAudio slot 0x180
// Evidence: chain from just-landed 0x0028B31A; global 0x009FE6E8 is TheAudio per GameLogicSetGamePaused and ScriptActions siblings; slot 0x180 follows audioSlot178 convention.
class Object
{
public:
	void rva0028B31A(int val);
	char m_pad0[0x8C];
	Object *m_next;
};

class BfmeAudio
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
	virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
	virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
	virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
	virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
	virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31();
	virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35();
	virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39();
	virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43();
	virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47();
	virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51();
	virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55();
	virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59();
	virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63();
	virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67();
	virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71();
	virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75();
	virtual void a76(); virtual void a77(); virtual void a78(); virtual void a79();
	virtual void a80(); virtual void a81(); virtual void a82(); virtual void a83();
	virtual void a84(); virtual void a85(); virtual void a86(); virtual void a87();
	virtual void a88(); virtual void a89(); virtual void a90(); virtual void a91();
	virtual void a92(); virtual void a93(); virtual void a94(); virtual void a95();
	virtual void audioSlot180(int val);
};

extern class AudioManager *TheAudio;

class Rva0023D661
{
public:
	void rva0023D661(int val);
private:
	char m_pad[0xAC];
	Object *m_head;
};

void Rva0023D661::rva0023D661(int val)
{
	Object *obj = m_head;
	while (obj != 0) {
		obj->rva0028B31A(val);
		obj = obj->m_next;
	}
	return (*(BfmeAudio **)&TheAudio)->audioSlot180(val);
}
