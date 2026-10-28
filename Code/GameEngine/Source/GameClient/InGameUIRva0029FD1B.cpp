// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include
// ?rva0029FD1B@InGameUI@@QAEXHPAVMaterialPassClass@@PAVOverridable@@H@Z, retail 0x0029FD1B, 387 bytes.
// Lever: the m_890 decal call is an equal-arm conditional on the member (m_890 ? call : call), which makes cl
// compute the colour before the null test like retail.
// @0x0029FD1B 387B, retail-guided InGameUI radius decal.
class Object;
class Player;
class MaterialPassClass;
class Overridable;
class RadiusDecalTemplate;
class Shadow;

class PlayerList
{
public:
	char m_pad00[0x10];
	Player *m_localPlayer; // +0x10
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	Object *findNaturalCommandCenter();
	Object *rva002AC629();
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

class Shadow
{
public:
	void setColor(int color);
};

#include "Lib/Coord3D.h"

class TextureClass;
class MaterialPassClass
{
public:
	TextureClass *Peek_Texture(int arg) const;
};
class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
};
class RadiusDecal {};
class RadiusDecalTemplate
{
public:
	void createRadiusDecal(const Coord3D &pos, float radius, const Player *player, RadiusDecal &decal) const;
private:
	char m_pad[0x10];
};

struct Rva0029FD1BNode
{
	char m_pad00[8];
	RadiusDecalTemplate m_template; // +0x08 (embedded: retail passes node+8)
};


class InGameUI
{
public:
	void rva0029FD1B(int id, MaterialPassClass *mp, Overridable *ov, int isValid);
protected:
	void handleRadiusCursor();
public:
#define BFME_V8(a,b,c,d,e,f,g,h) virtual void v##a(); virtual void v##b(); virtual void v##c(); virtual void v##d(); virtual void v##e(); virtual void v##f(); virtual void v##g(); virtual void v##h();
	BFME_V8(00,01,02,03,04,05,06,07) BFME_V8(08,09,10,11,12,13,14,15)
	BFME_V8(16,17,18,19,20,21,22,23) BFME_V8(24,25,26,27,28,29,30,31)
	BFME_V8(32,33,34,35,36,37,38,39) BFME_V8(40,41,42,43,44,45,46,47)
	BFME_V8(48,49,50,51,52,53,54,55) BFME_V8(56,57,58,59,60,61,62,63)
	virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
	virtual void v68(); virtual void v69();
	virtual void *v70();
	virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74();
	virtual void *v75();
	virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79(); virtual void v80();
	virtual void v81();
#undef BFME_V8
private:
	char m_pad000[0x234];
	void *m_238; // +0x238
	char m_pad23C[0x874 - 0x23C];
	char m_hashtable[0x888 - 0x874]; // +0x874
	int m_888;   // +0x888
	RadiusDecal m_curRadiusCursor; // +0x88C
	Shadow *m_890; // +0x890
	int m_894;
	int m_898;
	int m_89C; // +0x89C
};

namespace _STL
{
template <class T1, class T2> struct pair {};
template <class T> struct hash {};
template <class T> struct equal_to {};
template <class P> struct _Select1st {};
template <class T> class allocator {};
template <class V> struct _Hashtable_node {};
template <class V, class K, class HF, class Ex, class Eq, class A>
struct hashtable
{
private:
	template <class K2> _Hashtable_node<V> *_M_find(const K2 &key) const;
	struct iterator
	{
		iterator(_Hashtable_node<V> *cur, hashtable *ht) : _M_cur(cur), _M_ht(ht) {}
		_Hashtable_node<V> *_M_cur;
		hashtable *_M_ht;
	};
	iterator find(const K &key) { return iterator(_M_find(key), this); }
	friend class InGameUI;
};
}

typedef _STL::hashtable<_STL::pair<const unsigned, void *>, unsigned, _STL::hash<unsigned>,
	_STL::_Select1st<_STL::pair<const unsigned, void *> >, _STL::equal_to<unsigned>,
	_STL::allocator<_STL::pair<const unsigned, void *> > > Rva0029FD1BHashtable;
void *rva002888D4(void *table, int *key);


void InGameUI::rva0029FD1B(int id, MaterialPassClass *mp, Overridable *ov, int isValid)
{
	if (m_888 != (id ? id : id))
	{
		v81();
		Rva0029FD1BHashtable::iterator it = ((Rva0029FD1BHashtable *)m_hashtable)->find(*(const unsigned *)&id);
		if (it._M_cur == 0)
			return;
		Rva0029FD1BNode *node = (Rva0029FD1BNode *)it._M_cur;

		Object *obj = 0;
		if (m_238)
		{
			int commandType = *(int *)((char *)m_238 + 0x14);
			if (commandType == 0x20)
			{
				if (ThePlayerList && ThePlayerList->m_localPlayer)
					obj = ThePlayerList->m_localPlayer->findNaturalCommandCenter();
			}
			else if (commandType == 0x26)
			{
				if (ThePlayerList && ThePlayerList->m_localPlayer)
					obj = ThePlayerList->m_localPlayer->rva002AC629();
			}
		}
		if (!obj)
		{
			if (!v70())
				return;
			void *v = v75();
			if (!v)
				return;
			obj = *(Object **)((char *)v + 0xFC);
			if (!obj)
				return;
		}
		{
		Player *pl = obj->getControllingPlayer();
		if (!pl)
			return;

		float radius;
		if (id == m_89C)
		{
			TextureClass *tex = ((MaterialPassClass *)((char *)obj + 0x330))->Peek_Texture((int)ov);
			if (tex)
			{
				float *f = *(float **)((char *)tex + 4);
				radius = f[0x38 / 4] + f[0x34 / 4];
			}
			else
				radius = 0.0f;
		}
		else
		{
			if (!mp)
				return;
			const Overridable *fo = ((Overridable *)mp)->friend_getFinalOverride();
			radius = *(float *)((char *)fo + 0x54);
		}
		if (radius <= 0.0f)
			return;

		Coord3D pos;
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		node->m_template.createRadiusDecal(pos, radius, pl, m_curRadiusCursor);
		}
		m_888 = id;
		this->handleRadiusCursor();
	}

	int color = (unsigned char)isValid ? -1 : (int)0xFFFF1414;
	if (m_890)
		(m_890) ? (m_890->setColor(color)) : (m_890->setColor(color));
}
