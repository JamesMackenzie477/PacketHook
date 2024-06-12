#pragma once
#include <PacketPriority.h>
#include "Hooker.h"

// Defines various Roblox packet identifiers.
#define ID_ROBLOX_SCHEMA_VERSION (char)0x90
#define ID_ROBLOX_START_AUTH_THREAD (char)0x92
#define ID_ROBLOX_AUTH (char)0x8A
#define ID_ROBLOX_INITIAL_SPAWN_NAME (char)0x8F

// Allows for extraction of a packet identifier.
#define PACKET_IDENTIFIER(I) ((unsigned char)I[0])

// Stores the Send Buffered method offset.
#define SEND_BUFFERED_OFFSET 0x951060

typedef unsigned int uint32_t;
typedef uint32_t BitSize_t;

enum ConnectMode
{
	NO_ACTION,
	DISCONNECT_ASAP,
	DISCONNECT_ASAP_SILENTLY,
	DISCONNECT_ON_NO_ACK,
	REQUESTED_CONNECTION,
	HANDLING_CONNECTION_REQUEST,
	UNVERIFIED_SENDER,
	CONNECTED
};

class RakPeer
{
public:
	void SendBuffered(const char * data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, ConnectMode connectionMode, uint32_t receipt, char a22);
};

// Defines the send buffered function.
typedef void(__thiscall * _SendBuffered)(RakPeer * peer, const char * data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, ConnectMode connectionMode, uint32_t receipt, char a22);