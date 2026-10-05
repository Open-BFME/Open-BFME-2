// cl: /O1 /DNDEBUG /MD
//
// ?rva0049C5D9@Rva0049C5D9@@QAEXHH@Z @0x0049C5D9 27B.
// Clears the id at +0x40, then forwards both stack args to 0x4502CE.

class Rva0049C592
{
public:
	void rva0049C592();
};

class Rva004502CE
{
public:
	void rva004502CE(int a, int b);
};

class Rva0049C5D9
{
public:
	void rva0049C5D9(int a, int b);
};

void Rva0049C5D9::rva0049C5D9(int a, int b)
{
	((Rva0049C592 *)this)->rva0049C592();
	((Rva004502CE *)this)->rva004502CE(a, b);
}
