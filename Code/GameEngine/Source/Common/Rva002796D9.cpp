// cl: /O1 /MD
class Drawable
{
public:
	void rva00273755();
};
class Rva0027601BHost
{
public:
	void rva0027601B();
};
class Rva00277C42Host
{
public:
	void rva00277C42();
};
class Rva002779CEHost
{
public:
	void rva002779CE();
};
class Rva00273F74Host
{
public:
	void rva00273F74();
};
class Rva00275F3FHost
{
public:
	void rva00275F3F();
};
class Rva00273808Host
{
public:
	void rva00273808();
};
class Rva00277669Host
{
public:
	void rva00277669();
};
class Rva00279074Host
{
public:
	void rva00279074();
};
class Rva00273C47Host
{
public:
	void rva00273C47();
};
void __cdecl rva002778E1();
class Rva002796D9Host
{
public:
	void rva002796D9(int v);
};
// ?rva002796D9@Rva002796D9Host@@QAEXH@Z
void Rva002796D9Host::rva002796D9(int v)
{
	switch (v)
	{
	case 0:
		((Rva0027601BHost *)this)->rva0027601B();
		((Drawable *)this)->rva00273755();
		((Rva00277C42Host *)this)->rva00277C42();
		((Rva002779CEHost *)this)->rva002779CE();
		break;
	case 1:
		((Rva00273F74Host *)this)->rva00273F74();
		((Rva00275F3FHost *)this)->rva00275F3F();
		((Rva00273808Host *)this)->rva00273808();
		((Rva00277669Host *)this)->rva00277669();
		break;
	case 2:
		((Rva00279074Host *)this)->rva00279074();
		break;
	case 3:
		((Rva00273C47Host *)this)->rva00273C47();
		break;
	case 4:
		return;
	case 5:
		rva002778E1();
		break;
	default:
		break;
	}
}
