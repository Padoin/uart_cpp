// ---------------------------------------------------------------------------

#ifndef CPortaSerialH
#define CPortaSerialH

#include<windows.h>
#include<Classes.hpp>

// ---------------------------------------------------------------------------
class CPortaSerial {

private:
	HANDLE hPorta;
	bool aberta;
	COMMTIMEOUTS commTimeouts;

	HANDLE _fastcall getHandle();

public:
	CPortaSerial(char *porta);
	~CPortaSerial();

	DCB config;

	unsigned char _fastcall ReceberByte();
	bool _fastcall TransmitirByte(unsigned char dado);
	bool _fastcall LerConfigPorta();
	bool _fastcall SetConfigPorta();
    bool _fastcall GetAberta();
	// __property bool xAberta = (read = GetAberta);

};

#endif
