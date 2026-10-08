// cl: /O1 /DNDEBUG /MD
//
// ?rva002D9FD9@Rva002D9FD9Owner@@QAEXPAVRva002D9FD9Arg@@@Z @0x002D9FD9 151B:
// extended guarded call sequence (thiscall, 1 arg, void). Same v03/v28
// pair preamble as landed 0x002D9F9F (pair filler at [ebp-4], flag byte
// in dead arg slot), plus v08-gated audio check (landed rva002D9608 via
// Rva002D9608 base), v90/v78 with stack temporaries, pinned 0x002D9D7C,
// then v04-gated TheAudio slot-0x74 refresh of m_0c. Owner derives from
// Rva002D9608 so the audio gate resolves; Arg vtable carries 145
// placeholder slots (placeholder-only vtables start at index 0).
// Views minimal; exact identities unproven.
class Xfer;
class AudioEventRTS
{
public:
 void internalXfer(Xfer *xfer, const void *version);
};

class Rva002D9608
{
public:
	bool rva002D9608();
	char m_pad[0xC];
	int m_0C;
};

class Rva002D9FD9Arg
{
public:
	virtual void v000(); virtual bool v001(); virtual bool v002();
	virtual bool v003();
	virtual void v004();
	virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010(void *p);
	virtual void v011(); virtual void v012(); virtual void v013(); virtual void v014();
	virtual void v015(); virtual void v016(); virtual void v017(); virtual void v018();
	virtual void v019(); virtual void v020(); virtual void v021(); virtual void v022();
	virtual void v023(); virtual void v024(); virtual void v025(); virtual void v026();
	virtual void v027(); virtual void v028(); virtual void v029(); virtual void v030(void *p);
	virtual void v031(); virtual void v032(); virtual void v033(); virtual void v034();
	virtual void v035(); virtual void v036(void *p); virtual void v037(); virtual void v038();
	virtual void v039(); virtual void v040(); virtual void v041(); virtual void v042();
	virtual void v043(); virtual void v044(); virtual void v045(); virtual void v046();
	virtual void v047(); virtual void v048(); virtual void v049(); virtual void v050();
	virtual void v051(); virtual void v052(); virtual void v053(); virtual void v054();
	virtual void v055(); virtual void v056(); virtual void v057(); virtual void v058();
	virtual void v059(); virtual void v060(); virtual void v061(); virtual void v062();
	virtual void v063(); virtual void v064(); virtual void v065(); virtual void v066();
	virtual void v067(); virtual void v068(); virtual void v069(); virtual void v070();
	virtual void v071(); virtual void v072(); virtual void v073(); virtual void v074();
	virtual void v075(); virtual void v076(); virtual void v077();
	virtual void v078();
	virtual void v079(); virtual void v080(); virtual void v081(); virtual void v082();
	virtual void v083(); virtual void v084(); virtual void v085(); virtual void v086();
	virtual void v087(); virtual void v088(); virtual void v089();
	virtual void v090();
	virtual void v091(); virtual void v092(); virtual void v093(); virtual void v094();
	virtual void v095(); virtual void v096(); virtual void v097(); virtual void v098();
	virtual void v099(); virtual void v100(); virtual void v101(); virtual void v102();
	virtual void v103(); virtual void v104(); virtual void v105(); virtual void v106();
	virtual void v107(); virtual void v108(); virtual void v109(); virtual void v110();
	virtual void v111(); virtual void v112(); virtual void v113(); virtual void v114();
	virtual void v115(); virtual void v116(); virtual void v117(); virtual void v118();
	virtual void v119(); virtual void v120(); virtual void v121(); virtual void v122();
	virtual void v123(); virtual void v124(); virtual void v125(); virtual void v126();
	virtual void v127(); virtual void v128(); virtual void v129(); virtual void v130();
	virtual void v131(); virtual void v132(); virtual void v133(); virtual void v134();
	virtual void v135(); virtual void v136(); virtual void v137(); virtual void v138();
	virtual void v139(); virtual void v140(); virtual void v141(); virtual void v142();
	virtual void v143(); virtual void v144();
};

class AudioManager
{
public:
	virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
	virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
	virtual void a08(); virtual void a09(); virtual void a10(); virtual void a11();
	virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15();
	virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19();
	virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23();
	virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27();
	virtual void a28();
	virtual int a29(void *o, int x);
};
extern AudioManager *TheAudio;

class Rva002D9FD9Owner : public Rva002D9608
{
public:
	void rva002D9FD9(Rva002D9FD9Arg *a);
};

// ?rva002D9FD9@Rva002D9FD9Owner@@QAEXPAVRva002D9FD9Arg@@@Z
void Rva002D9FD9Owner::rva002D9FD9(Rva002D9FD9Arg *a)
{
	if (a->v003())
		return;
	int t;
	((unsigned char *)&t)[0] = 1;
	((unsigned char *)&t)[1] = 6;
	a->v010(&t);
	unsigned char flag;
	int x;
	if (a->v002())
		flag = rva002D9608();
	a->v036(&flag);
	x = m_0C;
	a->v030(&x);
	((AudioEventRTS *)this)->internalXfer((Xfer *)a, &t);
	if (flag == 0)
		return;
	if (!a->v001())
		return;
	if (TheAudio == 0)
		return;
	m_0C = TheAudio->a29(this, x);
}
