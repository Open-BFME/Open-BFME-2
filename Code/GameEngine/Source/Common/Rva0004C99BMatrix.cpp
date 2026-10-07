// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// ?rva0004C99B@Rva0004C99B@@QAEXXZ @0x0004C99B 102B
// Matrix setup: initializes a 12-float buffer (identity-ish, 1.0 at
// 0/5/10) then runs the 0x00713290 matrix method on a second buffer and
// the same-this 0x0023A1BB helper.
class Rva000713290
{
public:
	void rva000713290(void *buf);
};
class Rva0004C99B
{
public:
	void rva0004C99B();
	void rva00023A1BB();
private:
	char m_pad[0];
};
void Rva0004C99B::rva0004C99B()
{
	float buf1[12];
	float buf2[12];
	buf1[0] = 1.0f;
	buf1[1] = 0.0f;
	buf1[2] = 0.0f;
	buf1[3] = 0.0f;
	buf1[4] = 0.0f;
	buf1[5] = 1.0f;
	buf1[6] = 0.0f;
	buf1[7] = 0.0f;
	buf1[8] = 0.0f;
	buf1[9] = 0.0f;
	buf1[10] = 1.0f;
	buf1[11] = 0.0f;
	((Rva000713290 *)buf2)->rva000713290(buf1);
	rva00023A1BB();
}
