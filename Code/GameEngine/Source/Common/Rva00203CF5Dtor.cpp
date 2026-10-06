// cl: /O1
// ??1Rva00203CF5@@QAE@XZ @0x00203CF5 15B. Dtor stores string literal then links.
// Evidence: mov eax,[ecx+8]; mov [ecx],")=`"; mov ecx,[ecx+4]; mov [eax],ecx; no calls.
class Rva00203CF5
{
public:
	~Rva00203CF5();
	void *m00;
	void *m04;
	void *m08;
};
Rva00203CF5::~Rva00203CF5()
{
	void *next = m08;
	m00 = (void *)")=`";
	*(void **)next = m04;
}
