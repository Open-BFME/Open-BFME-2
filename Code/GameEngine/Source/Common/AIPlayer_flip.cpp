// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "../../Include/GameLogic/AIPlayerClass.h"
#include "../GameLogic/AI/TeamInQueue.h"

void AIPlayer::flip()
{
	TeamInQueue *currentNode = m_teamReadyQueue;
	TeamInQueue *lastNode = 0;
	if (currentNode)
	{
		do
		{
			TeamInQueue *previousLink = currentNode->m_prevReady;
			TeamInQueue *nextLink = currentNode->m_nextReady;
			currentNode->m_nextReady = previousLink;
			currentNode->m_prevReady = nextLink;
			lastNode = currentNode;
			currentNode = nextLink;
		} while (currentNode);
	}
	m_teamReadyQueue = lastNode;
}
