// ?findServer@PeerThreadClass@@QAEHPAU_SBServer@@@Z
// partial score=0.55 date=2026-10-07
// ?findServer@PeerThreadClass@@ present-unmatched
Int PeerThreadClass::findServer( SBServer server )
{
	char tmp[10] = "";
	const char *newName = SBServerGetStringValue(server, "gamename", tmp);
	UnsignedInt newPrivateIP = SBServerGetPrivateInetAddress(server);
	UnsignedShort newPrivatePort = SBServerGetPrivateQueryPort(server);
	UnsignedInt newPublicIP = SBServerGetPublicInetAddress(server);

	SBServer serverToRemove = NULL;

	for (std::map<Int, SBServer>::iterator it = m_stagingServers.begin(); it != m_stagingServers.end(); ++it)
	{
		if (it->second == server)
		{
			return it->first;
		}
		else
		{
			const char *oldName = SBServerGetStringValue(it->second, "gamename", tmp);
			UnsignedInt oldPrivateIP = SBServerGetPrivateInetAddress(it->second);
			UnsignedShort oldPrivatePort = SBServerGetPrivateQueryPort(it->second);
			UnsignedInt oldPublicIP = SBServerGetPublicInetAddress(it->second);
			if (!strcmp(oldName, newName) &&
				oldPrivateIP == newPrivateIP &&
				oldPublicIP == newPublicIP &&
				oldPrivatePort == newPrivatePort)
			{
				serverToRemove = it->second;
			}
		}
	}

	if (serverToRemove)
	{
		// this is the same as another game - it has just migrated to another port.  Remove the old and replace it.
		PeerResponse resp;
		resp.peerResponseType = PeerResponse::PEERRESPONSE_STAGINGROOM;
		resp.stagingRoom.id = removeServerFromMap( serverToRemove );
		resp.stagingRoom.action = PEER_REMOVE;
		resp.stagingRoom.isStaging = TRUE;
		resp.stagingRoom.percentComplete = -1;
		TheGameSpyPeerMessageQueue->addResponse(resp);
	}

	return addServerToMap(server);
}