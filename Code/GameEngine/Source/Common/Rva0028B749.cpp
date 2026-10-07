// cl: /O1 /MD
class Player;
class Object
{
public:
	Player *getControllingPlayer() const;
};
class Rva002AA5E1Host
{
public:
	void rva002AA5E1(void *a, int b, float c);
};
class Rva0028B749Host
{
public:
	void rva0028B749(int a, float b);
};
// ?rva0028B749@Rva0028B749Host@@QAEXHM@Z
void Rva0028B749Host::rva0028B749(int a, float b)
{
	Player *p = ((const Object *)this)->getControllingPlayer();
	if (p != 0)
		((Rva002AA5E1Host *)p)->rva002AA5E1(this, a, b);
}
