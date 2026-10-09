// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva003B46C7Destroy@@YAXPAUPrereqUnitRec@ProductionPrerequisite@@0@Z @0x003B46C7 25B destroy range over 0x14-byte PrereqUnitRec via rowed dtor 0x00577998 callers 0x003B6846 0x003B7057
class AsciiString
{
public:
	~AsciiString();
private:
	char *m_data;
	char m_pad[8];
};
class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned int m_first;
		unsigned int m_second;
		AsciiString m_name;
		~PrereqUnitRec();
	};
};
void Rva003B46C7Destroy(ProductionPrerequisite::PrereqUnitRec *first, ProductionPrerequisite::PrereqUnitRec *last)
{
	for (; first != last; ++first)
		first->~PrereqUnitRec();
}

extern "C" void __cdecl free(void *block);

class Rva003B6846Vec
{
public:
	void rva003B6846();
private:
	ProductionPrerequisite::PrereqUnitRec *m_start;
	ProductionPrerequisite::PrereqUnitRec *m_finish;
};

// ?rva003B6846@Rva003B6846Vec@@QAEXXZ @0x003B6846 30B chain via 0x003B46C7 destroy plus _free callers 0x003B68A8 0x003B72F5
void Rva003B6846Vec::rva003B6846()
{
	Rva003B46C7Destroy(m_start, m_finish);
	if (m_start)
		free(m_start);
}

// Native3B57D9..3B57E5 is bounded by priorRET4 at3B57D6 and the next
// independently rowed entry3B57E5. It subtracts20 from word4, reloads that
// pointer intoECX, then tail-calls the existing577998 +8 AsciiString teardown.
// BF1 f989 Common/Gen20VectorDestructor.cpp and
// Containers/Rva0013C2D0VectorDestructor.cpp underO1/SSE2/G6 provide whole-TU
// pop_back operation guides. Their element/vector names are not target facts.
// Original owner and element identity remain unknown. The existing destructor
// declaration is only the verified shared+8 string cleanup contract; this does
// not identify the payload as ProductionPrerequisite::PrereqUnitRec. This home
// already has a native20B destroy loop calling that same actual cleanup.
struct Rva003B57D9
{
    unsigned int word0;
    unsigned char *finish;
    void removeLastStringTail();
};

void Rva003B57D9::removeLastStringTail()
{
    finish -= 20;
    reinterpret_cast<ProductionPrerequisite::PrereqUnitRec *>(finish)->~PrereqUnitRec();
}
