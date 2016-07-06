#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "CPSock.h"
#include "Basedef.h"

int ConnectPort = 0;

unsigned char pKeyWord[512] = { // 7.xx keys
	41, 179, 238, 84, 119, 230, 48, 148, 38, 80, 117, 205, 167, 63, 55, 237, 201, 4, 1, 102,
	133, 126, 92, 153, 38, 190, 149, 174, 160, 83, 113, 136, 39, 108, 91, 100, 13, 137, 17, 242,
	1, 189, 80, 107, 147, 92, 155, 91, 59, 10, 147, 212, 150, 245, 225, 159, 87, 89, 97, 16,
	124, 241, 92, 64, 34, 134, 150, 52, 214, 42, 14, 183, 142, 125, 240, 110, 20, 113, 9, 246,
	71, 177, 208, 142, 214, 156, 140, 10, 215, 146, 180, 181, 242, 147, 203, 202, 116, 50, 69, 31,
	7, 127, 67, 194, 98, 24, 7, 20, 177, 34, 195, 43, 0, 22, 174, 241, 107, 79, 17, 2,
	110, 82, 17, 94, 3, 129, 33, 80, 221, 114, 172, 134, 177, 134, 250, 128, 119, 219, 227, 161,
	217, 95, 67, 223, 213, 19, 205, 106, 91, 46, 72, 54, 74, 76, 157, 212, 138, 79, 220, 131,
	138, 9, 192, 217, 212, 133, 163, 231, 46, 220, 131, 102, 230, 98, 24, 145, 170, 85, 110, 100,
	153, 162, 53, 221, 2, 252, 42, 232, 93, 213, 172, 161, 10, 131, 27, 135, 86, 13, 207, 116,
	85, 250, 139, 179, 26, 169, 9, 60, 192, 77, 128, 86, 2, 97, 3, 190, 147, 165, 45, 119,
	43, 63, 104, 105, 82, 54, 250, 14, 6, 238, 66, 41, 31, 224, 69, 233, 152, 0, 250, 100,
	196, 49, 156, 193, 84, 95, 3, 28, 106, 81, 200, 94, 142, 243, 8, 40, 200, 60, 79, 239,
	151, 76, 222, 146, 37, 248, 162, 109, 115, 111, 1, 28, 206, 5, 249, 44, 60, 224, 175, 199,
	81, 210, 193, 137, 15, 167, 176, 171, 52, 125, 164, 184, 169, 135, 180, 198, 105, 122, 67, 171,
	164, 87, 82, 244, 89, 141, 132, 39, 75, 114, 173, 26, 128, 197, 137, 231, 23, 88, 177, 83,
	197, 165, 54, 249, 193, 81, 249, 96, 92, 103, 104, 26, 9, 80, 80, 17, 74, 97, 198, 71,
	249, 225, 197, 241, 150, 140, 54, 117, 249, 70, 127, 0, 24, 42, 227, 80, 82, 156, 17, 129,
	201, 130, 251, 52, 106, 69, 130, 23, 235, 212, 246, 46, 173, 75, 232, 185, 156, 82, 136, 48,
	245, 253, 178, 25, 42, 69, 61, 96, 170, 170, 124, 220, 242, 93, 149, 130, 121, 103, 152, 49,
	247, 12, 239, 128, 174, 15, 54, 98, 3, 7, 230, 35, 47, 85, 19, 146, 101, 0, 107, 211,
	15, 0, 233, 161, 119, 77, 110, 142, 204, 44, 110, 26, 137, 232, 61, 240, 46, 214, 235, 99,
	153, 106, 100, 95, 173, 104, 140, 232, 155, 34, 79, 93, 160, 104, 52, 140, 99, 114, 106, 241,
	229, 84, 2, 16, 37, 38, 6, 53, 72, 148, 120, 185, 166, 249, 178, 1, 105, 152, 52, 29,
	8, 68, 101, 185, 113, 250, 85, 227, 41, 178, 23, 72, 44, 230, 123, 212, 181, 53, 35, 13,
	248, 132, 106, 242, 204, 6, 55, 37, 61, 147, 71, 184
};
/*
unsigned char pKeyWord[512] = { // 6.13 keys

	235,125,  235,124,  235,125,  235,125,  215,125,  235,125,  135,125,  235,122,  235,125,  235,125, 
	115,125,   35, 55,  235,145,  215,125,  225,125,  235,125,   35,125,  235,123,  135,125,  135,229, 
	125,125,  115, 47,  135,105,   35,125,  235,125,  235,125,   35,125,  235,125,   32,212,  235,120, 
	135,225,  215,144,   35,195,   35,125,  145,125,   35,125,  135,125,  135,132,   27,125,  235,128, 
	135,120,  145,124,  235,187,  235,125,  255,125,  235,105,  235,121,  235,121,  235,25,     5, 47, 
	195, 95,   25, 65,  235,145,  113,125,  167,125,  235,125,  164,125,  135, 25,   33,124,   135,22, 
	235,112,  235,125,   35,125,  235,125,  235,123,   35,128,  225,123,  235,125,  135,125,  235,123, 
	139,195,  235,122,  135,125,  235,125,  209,221,  235,125,  246,126,  135,125,  136, 25,  135,245, 
	135,125,  215,225,  155,135,  135,125,  205,123,   35,138,  131,127,  235, 20,  235,125,   31,125, 
	235,125,  233, 15,   35, 22,  235,125,  245,155,  241,155,  163,125,  232,125,  231,122,  235,125,

	233,125,  235,125,  231,125,  235,125,  235,125,  235,123,  235,125,  235,125,  235,125,  235,125, 
	132,125,  235,125,  235,125,  235,125,  135,124,  235,152,  245,122,  235,128,  235, 26,  235,225, 
	232,111,  209,121,  135,125,  225,133,  235,123,  235,121,  225,121,  235,127,  135,125,  235,124, 
	 45,125,  215,221,  233,125,  235,134,   15,121,  235,121,    5,125,  215,125,  235,225,  135,225, 
	215,143,    5,125,  235,122,  231,165,  235,155,  235,135,  233,124,  235,125,  235,128,  235,121, 
	132,135,   55,215,  234,121,  145,145,   15,115,   75, 25,  235,125,  145,125,  135,129,  235,124, 
	 35,225,   75,131,  163,122,  245,121,   35,125,  230,125,  225,126,  174,124,   15,225,  135,126, 
	231,121,  155,125,    2,125,  235,123,   135,113,   221,45, 135,121,  231,121,  235,124,   35,218, 
	 35,125,  235,125,  175,121,   55,124,  195,121,  205,125,  235,122,   33,125,  235, 25,  235,149, 
	135,125,  225,125,  235,125,  135,125,  205,125,   35,125,  135,124,  221,145,  235,122,  235,175, 

	135, 35,  235, 16,  215,223,  135,134,  135,165,  135,124,  115,126,  237,125,  215,125,  235,125, 
	235,125,  215,125,  225,122,  134,125,  234,126,  235,152,  235,121,  245,125,  225,122,  235, 35, 
	235,111,   35,125,  135,123,  235,125,  125,128,  231,183,  235,122,   35,125,  135,126,  235,165, 
	135,125,  235,125,  134,125,  235,125,  135,156,  225,221,  235,125,  115,125,    5,125,  235,131, 
	135,125,   35,125,  233,125,  115,125,  225,122,  135,121,  235,125 , 235,125,  235,122,  235,55, 
	235,125,  235,125,  231,127,  235,125,  164,145,  235,125

};
*/
//Server.cpp
extern HWND			hWndMain;
extern unsigned int CurrentTime;
extern unsigned int LastSendTime;
void   Log (char *String1, char *String2 , unsigned int ip);


//////////////////////////////////////////////////////////////////////////
//
//             CPSock,  ~CPSock
//
// Receive buffer and transmit buffer is allocated.
// Send and receive buffer pointer is reset Bubba
//////////////////////////////////////////////////////////////////////////

CPSock::CPSock()
{	
	Sock = 0;
	Init = 0;
	pSendBuffer      = (char *)malloc(SEND_BUFFER_SIZE);
	pRecvBuffer      = (char *)malloc(RECV_BUFFER_SIZE);

	nSendPosition    = 0;
	nSentPosition    = 0;
	nRecvPosition    = 0;
	nProcPosition    = 0;	
}

CPSock::~CPSock()
{   
	if (pSendBuffer	!= NULL)    
		free(pSendBuffer);

    if (pRecvBuffer != NULL)   
		free(pRecvBuffer);
}

BOOL CPSock::CloseSocket()
{	
	nSendPosition    = 0;
	nSentPosition    = 0;
	nRecvPosition    = 0;
	nProcPosition    = 0;
	Init             = 0;

    if (Sock != 0) 
		closesocket(Sock);

	Sock = 0;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//
//                       WSAInitialize   
//
// WSA initialization
// Server, all clients are executed once the first
/////////////////////////////////////////////////////////////////////////


BOOL CPSock::WSAInitialize()
{    
	WSADATA WSAData;

     if (WSAStartup(MAKEWORD(1,1), &WSAData) != 0) 
		 return FALSE;

 	 return TRUE;
}

/////////////////////////////////////////////////////////////////////////
//
//							StartListen
//
// Listening socket (LSock) Listen to begin with.
// Connection should be connected to the WSA_ACCEPT.
// If successful LSock, a failure FALSE (0) is returned.
/////////////////////////////////////////////////////////////////////////

SOCKET CPSock::StartListen(HWND hWnd, int ip, int port, int WSA)
{      
	   
	SOCKADDR_IN	local_sin;
	char		Temp[256];
	SOCKET		tSock = socket(AF_INET, SOCK_STREAM, 0);

	if(tSock == INVALID_SOCKET) 
	{	
		MessageBox(hWnd, "Initialize socket fail", "ERROR", MB_OK);

		return FALSE;
	}
    
	gethostname(Temp, 256);
	local_sin.sin_family		= AF_INET;
	local_sin.sin_addr.s_addr	= ip;		//INADDR_ANY;
	local_sin.sin_port			= htons((unsigned short int)port);       

	if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
	{	
		MessageBox(hWnd, "Binding fail", "ERROR", MB_OK);
		closesocket(tSock);

		return FALSE;
	}

	if(listen(tSock, MAX_PENDING_CONNECTS) < 0)
	{	
		MessageBox(hWnd, "Listen fail", "ERROR", MB_OK);
		closesocket(tSock);

		return FALSE;
	}

	if(WSAAsyncSelect(tSock, hWnd, WSA, FD_ACCEPT) > 0)
	{	
		MessageBox (hWnd, "WSAAsyncSelect fail", "ERROR", MB_OK);
		closesocket(tSock);

		return FALSE;
	}

	Sock = tSock;

	return tSock;
}

SOCKET CPSock::ConnectServer(char *HostAddr, int Port, int ip, int WSA)
{      
	SOCKADDR_IN InAddr;	//Connect
	SOCKADDR_IN local_sin; // Bind local IP

	memset(&InAddr, 0, sizeof(InAddr));
	memset(&local_sin,	0,	sizeof(local_sin));

	nSendPosition = 0;
	nSentPosition = 0;
	nRecvPosition = 0;
	nProcPosition = 0;

	if(Sock != 0) 
		CloseSocket();

	InAddr.sin_addr.s_addr	= inet_addr(HostAddr);
  	InAddr.sin_family		= AF_INET;
	InAddr.sin_port			= htons((unsigned short)Port);

	SOCKET tSock = socket(AF_INET, SOCK_STREAM, 0);

	if(tSock == INVALID_SOCKET) 
    {	
		MessageBox(NULL, "Initialize socket fail", "ERROR", MB_OK);
		return 0;
	}
	
    local_sin.sin_family		= AF_INET;
    local_sin.sin_addr.s_addr	= ip;
  	local_sin.sin_port			= 0;      

	if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
    {	
		ConnectPort += 10;
		local_sin.sin_port = htons((unsigned short int)(ConnectPort + 5000));

		if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
		{	
			ConnectPort += 10;
			local_sin.sin_port = htons((unsigned short int)(ConnectPort + 5000));

			if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
			{	
				MessageBox(NULL, "Binding fail", "ERROR", MB_OK);
				closesocket(tSock);

				return 0;
			}
		}
	}

	if(tSock == INVALID_SOCKET)	
		return 0;

	if(connect(tSock, (PSOCKADDR)&InAddr, sizeof(InAddr)) < 0)       
	{	
		closesocket(tSock);
		Sock = 0;

		return 0;
	}

	if(WSAAsyncSelect(tSock, hWndMain, WSA, FD_READ | FD_CLOSE) > 0) 
	{	
		closesocket(tSock);
		Sock = 0;

		return 0;
	}

	Sock = tSock;

	unsigned int InitCode = INITCODE;
	send(tSock, (char*)&InitCode, 4, 0);

	Init = 1;

	return tSock;
}

SOCKET CPSock::ConnectBillServer(char *HostAddr, int Port, int ip, int WSA)
{
	char msg[256];	

	SOCKADDR_IN remote_sin;
	SOCKADDR_IN local_sin;
	SOCKET      tSock;

	nRecvPosition = 0;
	nSendPosition = 0;
	nProcPosition = 0;

    if(Sock != 0) 
		CloseSocket();
	
	tSock = socket(AF_INET, SOCK_STREAM, 0);

	if(tSock == INVALID_SOCKET) 
		return 0;

	local_sin.sin_family		= AF_INET;
	local_sin.sin_addr.s_addr	= ip;
	local_sin.sin_port			= 0;    

	if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
	{	
		local_sin.sin_port = htons((unsigned short int)(ConnectPort + 6000));

		if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
		{	
			ConnectPort += 10;
			local_sin.sin_port = htons((unsigned short int)(ConnectPort + 6000));

			if(bind(tSock, (struct sockaddr FAR *)&local_sin, sizeof(local_sin)) == SOCKET_ERROR)
			{	
				MessageBox (NULL, "Binding fail", "ERROR", MB_OK);	
				closesocket(tSock);

				return 0;
			}
		}
	}

	sprintf(msg, "sock:%d ip:%d.%d.%d.%d port:%d-%d", tSock, local_sin.sin_addr.S_un.S_un_b.s_b1, local_sin.sin_addr.S_un.S_un_b.s_b2, 
		local_sin.sin_addr.S_un.S_un_b.s_b3, local_sin.sin_addr.S_un.S_un_b.s_b4, local_sin.sin_port, ConnectPort); 

	ConnectPort++;

	remote_sin.sin_addr.s_addr	 = inet_addr(HostAddr);
	remote_sin.sin_family		 = AF_INET;
	remote_sin.sin_port			 = htons((unsigned short)Port);  

	if(connect(tSock, (PSOCKADDR)&remote_sin, sizeof(remote_sin)) < 0)       
	{	
		sprintf(msg, "sock:%d ip:%d.%d.%d.%d port:%d-%d", tSock, remote_sin.sin_addr.S_un.S_un_b.s_b1, remote_sin.sin_addr.S_un.S_un_b.s_b2, 
			remote_sin.sin_addr.S_un.S_un_b.s_b3, remote_sin.sin_addr.S_un.S_un_b.s_b4, remote_sin.sin_port, Port); 

		closesocket(tSock);
		Sock = 0;

		return 0;
	}

	sprintf(msg, "sock:%d ip:%d.%d.%d.%d port:%d-%d", tSock, remote_sin.sin_addr.S_un.S_un_b.s_b1, remote_sin.sin_addr.S_un.S_un_b.s_b2, 
		remote_sin.sin_addr.S_un.S_un_b.s_b3, remote_sin.sin_addr.S_un.S_un_b.s_b4, remote_sin.sin_port, Port);

    if(WSAAsyncSelect(tSock, hWndMain, WSA, FD_READ|FD_CLOSE) > 0) 
	{	
		closesocket(tSock);
		Sock = 0;

		return 0;
	}

	Sock = tSock;

	return tSock;
}

BOOL CPSock::Receive()
{
	int Rest = RECV_BUFFER_SIZE - nRecvPosition;
	int tReceiveSize = recv(Sock, (char*)(pRecvBuffer + nRecvPosition), Rest, 0);

	if(tReceiveSize == SOCKET_ERROR || tReceiveSize == Rest)
		return FALSE;

	nRecvPosition = nRecvPosition + tReceiveSize;

	return TRUE;				  
}

/*
	 nRecvPosition = Final do ultimo pacote
	 nProcPosition = Começo do ultimo pacote
*/
char* CPSock::ReadMessage(int *ErrorCode, int *ErrorType)
{
	*ErrorCode = 0;

	if(nProcPosition >= nRecvPosition)
	{	
		nRecvPosition = 0;
		nProcPosition = 0;

		return 0;
	}

	//  Init packet authentication
	if(Init == 0)
	{	
		if(nRecvPosition - nProcPosition < 4) 
			return 0;

		int InitCode = *((unsigned int *)(pRecvBuffer + nProcPosition));

		if(InitCode != INITCODE)
		{	
			*ErrorCode = 2;
			*ErrorType = InitCode;

			return 0;
		}

		Init = 1;
		nProcPosition += 4;
	}

	//	Check received message is larger than HEADER
	if	(nRecvPosition - nProcPosition < sizeof(HEADER)) 
		return 0;

	//	Check full message arrived
	unsigned short	Size		= *((unsigned short *) (pRecvBuffer + nProcPosition)); 
	unsigned char	iKeyWord	= *((unsigned char  *) (pRecvBuffer + nProcPosition + 2));
	unsigned char	KeyWord		= pKeyWord[iKeyWord * 2];
	unsigned char	CheckSum	= *((unsigned char  *) (pRecvBuffer + nProcPosition + 3));
	unsigned int	SockType	= *((unsigned int	*) (pRecvBuffer + nProcPosition + 4));
	unsigned int	SockID		= *((unsigned int	*) (pRecvBuffer + nProcPosition + 6));

	if(Size > MAX_MESSAGE_SIZE || Size < sizeof(HEADER)) 
	{	
		nRecvPosition=	0;
		nProcPosition=	0;

		*ErrorCode   =	2;
		*ErrorType   =	Size;

		return 0;
	}

	unsigned int	Rest = nRecvPosition - nProcPosition;

	if (Size > Rest) 
		return 0;

	//	Get message
	char *pMsg = &(pRecvBuffer[nProcPosition]);

	nProcPosition = nProcPosition + Size;

	if(nRecvPosition <= nProcPosition) 
	{	
		nRecvPosition = 0;
		nProcPosition = 0;
	}

	// Compare check_sum in packet
	unsigned char Sum1 = 0;
	unsigned char Sum2 = 0;

	int	pos = KeyWord;

	for	(int i = 4; i < Size; i++, pos++)
	{	
		int rst = pos%256;

		Sum2 += pMsg[i];

		unsigned char Trans = pKeyWord[rst * 2 + 1];

		int mod = i&0x3;

		if  (mod == 0) 
			pMsg[i] = pMsg[i] - (Trans << 1);

		if  (mod == 1) 
			pMsg[i] = pMsg[i] + (Trans >> 3);

		if  (mod == 2) 
			pMsg[i] = pMsg[i] - (Trans << 2);

		if  (mod == 3) 
			pMsg[i] = pMsg[i] + (Trans >> 5);

		Sum1 += pMsg[i];
	}

	unsigned char Sum = Sum2 - Sum1;

	// return packet, even check_sum not match
	if	(Sum != CheckSum)
	{	
		*ErrorCode	= 1;
		*ErrorType  = Size;

		return pMsg;
	} 

	return pMsg;
}

char* CPSock::ReadBillMessage(int *ErrorCode, int *ErrorType)
{     
	 *ErrorCode = 0;
	 *ErrorType = 0; 

	 if (nProcPosition >= nRecvPosition)
	 { 
		 nRecvPosition = 0;
	     nProcPosition = 0;

		 return 0;
	 }
	 
	 if (nRecvPosition - nProcPosition < g_cGame) // 196
		 return 0;

	 char *pMsg = &(pRecvBuffer[nProcPosition]);

	 nProcPosition = nProcPosition + g_cGame;

	 if(nRecvPosition <= nProcPosition) 
	 {  
		 nRecvPosition = 0;
		 nProcPosition = 0;
	 }

	 return pMsg;
}

BOOL CPSock::SendBillMessage(char *Msg)
{ 
	if (nSendPosition + g_cGame >= SEND_BUFFER_SIZE ) 
		return FALSE;

	for (int i = 0; i < g_cGame; i++)
		pSendBuffer[nSendPosition + i] = Msg[i];

	 nSendPosition = nSendPosition + g_cGame;

	 BOOL Err = SendMessage();

     return Err;
}

BOOL CPSock::AddMessage(char *pMsg, int Size)
{
	char temp[256];
	HEADER *pSMsg = (HEADER *)pMsg;

	if(nSendPosition + Size >= SEND_BUFFER_SIZE)	
	{	
		sprintf(temp, "err,add buffer full %d %d %d %d", nSendPosition, Size, pSMsg->Type, Sock);
		Log(temp, "-system", 0);

		return FALSE;
	}

	// check socket valid
	if	(Sock <= 0)
	{
		sprintf(temp, "err,add buffer invalid %d %d %d %d", nSendPosition, Size, pSMsg->Type, Sock);
		Log(temp, "-system", 0);

		return FALSE;
	}
	
	unsigned char iKeyWord  =	rand()%256;
	unsigned char KeyWord	=	pKeyWord[iKeyWord * 2];
	unsigned char CheckSum	=	0;
	pSMsg->Size				=	Size;
	pSMsg->KeyWord			=	iKeyWord;
	pSMsg->CheckSum			=	CheckSum;
	pSMsg->ClientTick		=	CurrentTime;
	LastSendTime			=	CurrentTime;

#ifdef _PACKET_DEBUG
	MSG_STANDARD *debug = (MSG_STANDARD*)pMsg;

	if(BASE_CheckPacket(debug))
	{
		sprintf(temp, "**PACKET_DEBUG** Type:%d Size:%d", debug->Type, debug->Size);
        Log(temp, "-system", 0);
	}
#endif 

	unsigned char Sum1 = 0;
	unsigned char Sum2 = 0;
 	int			  pos  = KeyWord;

	for (int i = 4; i < Size; i++, pos++)
	{	
		Sum1 += pMsg[i];

		int rst = pos%256;

		unsigned char Trans = pKeyWord[rst * 2 + 1];

		int mod = i&0x3;

		if  (mod == 0) 
			pSendBuffer[nSendPosition + i] = pMsg[i] + (Trans << 1); 

		if  (mod == 1) 
			pSendBuffer[nSendPosition + i] = pMsg[i] - (Trans >> 3);

		if  (mod == 2)
			pSendBuffer[nSendPosition + i] = pMsg[i] + (Trans << 2);

		if  (mod == 3) 
			pSendBuffer[nSendPosition + i] = pMsg[i] - (Trans >> 5);

		Sum2 += pSendBuffer[nSendPosition + i];
	}
	
	CheckSum = Sum2 - Sum1;
	pSMsg->CheckSum = CheckSum;

	memcpy(pSendBuffer + nSendPosition, pMsg, 4);
	
	nSendPosition = nSendPosition + Size;
	
	return TRUE;
}

void CPSock::RefreshRecvBuffer()
{	
	int left = nRecvPosition - nProcPosition;
	if(left <= 0) 
		return;

	memcpy(pRecvBuffer, pRecvBuffer + nProcPosition, left);

	nProcPosition = 0;
	nRecvPosition -= left;
}

void CPSock::RefreshSendBuffer()
{	
	int left = nSendPosition - nSentPosition;
	if	(left <= 0) 
		return;

	memcpy(pSendBuffer, pSendBuffer + nSentPosition, left);

	nSentPosition = 0;
	nSendPosition -= left;
}

BOOL CPSock::SendMessageA()
{
	char temp[256];

	if (Sock <= 0)
	{
		nSendPosition = 0;
		nSentPosition = 0;

		return FALSE;
	}

	if	(nSentPosition > 0) 
		RefreshSendBuffer();

    if(nSendPosition > SEND_BUFFER_SIZE || nSendPosition < 0 || Sock < 0)
    {	
		#ifdef  _PACKET_DEBUG
		sprintf(temp, "err send1 %d %d %d", nSendPosition, nSentPosition, Sock);
		Log(temp, "-system", 0);
		#endif

		nSendPosition = 0;
		nSentPosition = 0;

		return FALSE;
	}

	if(nSentPosition > nSendPosition || nSentPosition >= SEND_BUFFER_SIZE || nSentPosition < 0)
	{	
		#ifdef  _PACKET_DEBUG
		sprintf(temp, "err send2 %d %d %d", nSendPosition, nSentPosition, Sock);
		Log(temp, "-system", 0);
		#endif

		nSendPosition = 0;
		nSentPosition = 0;
	}

	for(int i = 0; i < 1; i++)
	{
		int err = 0;
		int	Left = nSendPosition - nSentPosition;
		int tSend = send(Sock, pSendBuffer + nSentPosition, Left, 0);

		if	(tSend != SOCKET_ERROR)	
			nSentPosition = nSentPosition + tSend;	// Bytes transmitted
		else
			err = WSAGetLastError();	

		if(nSentPosition < nSendPosition || tSend == SOCKET_ERROR)
			continue;
		else
		{	
			nSendPosition = 0;
			nSentPosition = 0;

			return TRUE;
		}
	}

	if(nSendPosition > SEND_BUFFER_SIZE)
		return FALSE;

	return TRUE; 
}

BOOL CPSock::SendOneMessage(char* Msg, int Size)
{	
	AddMessage(Msg, Size);

	BOOL Err = SendMessageA();

	return Err;
}