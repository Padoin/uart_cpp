// ---------------------------------------------------------------------------

#pragma hdrstop

#include "CPortaSerial.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)

CPortaSerial::CPortaSerial(char *tPorta)
{
   hPorta = CreateFileA(tPorta,
                        GENERIC_READ | GENERIC_WRITE,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        0,
                        NULL
                        );

   if(hPorta == INVALID_HANDLE_VALUE)
		aberta = false;

   else
   {
	   if(GetCommTimeouts(hPorta, &CommTimeouts) == 0)
		aberta = false;

        else
        {
            CommTimeouts.ReadIntervalTimeout = 10;
            CommTimeouts.ReadTotalTimeoutMultiplier = 5;
            CommTimeouts.ReadTotalTimeoutConstant = 100;

            CommTimeouts.WriteTotalTimeoutMultiplier = 5;
            CommTimeouts.WriteTotalTimeoutConstant = 100;
        }

         if(SetCommTimeouts(hPorta, &CommTimeouts) == 0)
		  aberta = false;

		  else aberta = true;
   }
}

CPortaSerial::~CPortaSerial() {
	CloseHandle(hPorta);
	aberta = false;
}

unsigned char _fastcall CPortaSerial::ReceberByte() {
	DWORD nBytesRead;
	DWORD dwCommEvent;
	char byte = 0x00;

	ReadFile(hPorta, &byte, 1, &nBytesRead, NULL);

	return byte;
};

bool _fastcall CPortaSerial::TransmitirByte(unsigned char dado) {

	DWORD nBytesWrite;

	return WriteFile(hPorta, &dado, 1, &nBytesWrite, NULL);
};

bool _fastcall CPortaSerial::GetAberta() {
	return aberta;
};

HANDLE _fastcall CPortaSerial::getHandle() {
	return hPorta;
};

bool _fastcall CPortaSerial::LerConfigPorta() {
	return GetCommState(hPorta, &config);
};

bool _fastcall CPortaSerial::SetConfigPorta() {
	if (!SetCommState(hPorta, &config))
		return false;

	return true;
};
