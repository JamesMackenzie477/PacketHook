#include "Hook.h"

// Stores the send buffered function.
_SendBuffered __SendBuffered;
// Stores the send buffered hook object.
Hook* pSendBuffered;

// Our hook for the send buffered function.
void __fastcall SendBufferedHook(RakPeer* peer, void * trash, const char * data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, ConnectMode connectionMode, uint32_t receipt, char a22)
{
	// MessageBoxW(NULL, L"hi", L"hi", NULL);
	// Detatches the hook.
	pSendBuffered->Detatch();
	// Calls the original function.
	__SendBuffered(peer, data, numberOfBitsToSend, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
	// Reattaches the hook.
	pSendBuffered->Attach();
	// Checks the packet identifier.
	/*switch (PACKET_IDENTIFIER(data))
	{
	case ID_ROBLOX_START_AUTH_THREAD:
	case ID_ROBLOX_AUTH:
		// Forwards the packet.
		// peer->SendBuffered(data, numberOfBitsToSend, priority, reliability, orderingChannel, systemIdentifier, broadcast, connectionMode, receipt);
		// break;
	default:
		// Invalid packet.
		break;
	}*/
}

// Adds the process hooks.
DWORD WINAPI AttachHooks(_In_ LPVOID hinstDLL)
{
	// Gets the send buffered address.
	__SendBuffered = reinterpret_cast<_SendBuffered>(reinterpret_cast<char *>(GetModuleHandleW(L"RobloxPlayerBeta.exe")) + SEND_BUFFERED_OFFSET);
	// Hooks the send buffered function.
	pSendBuffered = new Hook(__SendBuffered, SendBufferedHook);
	// Attaches the hook.
	if (!pSendBuffered->Attach()) return FALSE;
	// Function succeeded.
	return true;
}

// The main entry point of the library.
BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	// Checks the reason for the entry call.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Adds the process hooks.
		CreateThread(NULL, NULL, AttachHooks, hinstDLL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		// Removes the process hooks.
		break;
	}
	// Function success.
	return true;
}

// Calls the internal send buffered function.
void RakPeer::SendBuffered(const char * data, BitSize_t numberOfBitsToSend, PacketPriority priority, PacketReliability reliability, int a6, int a7, int a8, __int16 a9, int a10, char a11, int a12, int a13, int a14, int a15, int a16, int a17, int a18, bool broadcast, ConnectMode connectionMode, uint32_t receipt, char a22)
{
	__SendBuffered(this, data, numberOfBitsToSend, priority, reliability, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, broadcast, connectionMode, receipt, a22);
}