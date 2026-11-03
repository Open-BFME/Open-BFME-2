// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

struct Rva00160A00Node
{
	char pad[0x0C];
	Rva00160A00Node *m_0C;
	Rva00160A00Node *m_10;
};

class AIPlayer
{
	char pad[8];
	Rva00160A00Node *m_08;

public:
	void flip();
};

void AIPlayer::flip()
{
	Rva00160A00Node *currentNode = m_08;
	Rva00160A00Node *lastNode = 0;
	if (currentNode)
	{
		do
		{
			Rva00160A00Node *firstLink = currentNode->m_0C;
			Rva00160A00Node *secondLink = currentNode->m_10;
			currentNode->m_10 = firstLink;
			currentNode->m_0C = secondLink;
			lastNode = currentNode;
			currentNode = secondLink;
		} while (currentNode);
	}
	m_08 = lastNode;
}
