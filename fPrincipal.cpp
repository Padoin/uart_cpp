// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "fPrincipal.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmPrincipal *frmPrincipal;

// ---------------------------------------------------------------------------
__fastcall TfrmPrincipal::TfrmPrincipal(TComponent* Owner) : TForm(Owner) {
}
// ---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnListarPortasClick(TObject *Sender) {
	ListarPortas();
}
// ---------------------------------------------------------------------------

bool __fastcall TfrmPrincipal::conexaoEstabelecida(){
	return objPorta != NULL && objPorta->GetAberta();
}
// ---------------------------------------------------------------------------

void TfrmPrincipal::ListarPortas() {
	TRegistry *registro = new TRegistry;
	TStringList *lista = new TStringList;

	registro->RootKey = HKEY_LOCAL_MACHINE;
	registro->OpenKey("HARDWARE\\DEVICEMAP\\SERIALCOMM", false);
	registro->GetValueNames(lista);
	cmbPorta->Items->Clear();

	for (int i = 0; i < lista->Count; i++) {
		cmbPorta->Items->Add(registro->ReadString(lista->Strings[i]));
	}

	if (cmbPorta->Items->Count > 0) {
		cmbPorta->ItemIndex = 0;
	}

	registro->CloseKey();

	delete(registro, lista);
};

bool TfrmPrincipal::ConfigurarPorta() {
	if (objPorta->LerConfigPorta()) {

		/* configurar baudrate
		 opcoes no combobox:
		 4800
		 9600
		 19200
		 38400
		 57600
		 115200
		 128000
		 */
		switch (cmbVelocidade->ItemIndex) {
		case 0:
			objPorta->config.BaudRate = CBR_4800;
			break;
		case 1:
			objPorta->config.BaudRate = CBR_9600;
			break;
		case 2:
			objPorta->config.BaudRate = CBR_19200;
			break;
		case 3:
			objPorta->config.BaudRate = CBR_38400;
			break;
		case 4:
			objPorta->config.BaudRate = CBR_57600;
			break;
		case 5:
			objPorta->config.BaudRate = CBR_115200;
			break;
		case 6:
			objPorta->config.BaudRate = CBR_128000;
			break;

		default:
			break;
		}

		/* paridade
		 None
		 Even
		 Odd
		 Mark
		 */
		switch (cmbParidade->ItemIndex) {
		case 0:
			objPorta->config.Parity = NOPARITY;
			break;
		case 1:
			objPorta->config.Parity = EVENPARITY;
			break;
		case 2:
			objPorta->config.Parity = ODDPARITY;
			break;
		case 3:
			objPorta->config.Parity = MARKPARITY;
			break;
		default:
			break;

		}

		/* stopbit
		 1
		 2
		 */
		switch (cmbBitParada->ItemIndex) {
		case 0:
			objPorta->config.StopBits = ONESTOPBIT;
			break;
		case 1:
			objPorta->config.StopBits = TWOSTOPBITS;
			break;
		default:
			break;
		}

		/* byte size */
		switch (cmbBitsDados->ItemIndex) {
		case 0:
			objPorta->config.ByteSize = 8;
			break;
		case 1:
			objPorta->config.ByteSize = 9;
			break;
		default:
			break;
		}

		return objPorta->SetConfigPorta();

	}

	else
		ShowMessage("Erro em ler config. da porta");

	return false;

}
// ---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnAbrirPortaClick(TObject *Sender)
{

	if(!conexaoEstabelecida()){
		ShowMessage("porta ja esta aberta");
		return;
	}

	char *porta = (char *) cmbPorta->Text.c_str();
	objPorta = new CPortaSerial(porta);
	ConfigurarPorta();

}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnEnviarClick(TObject *Sender)
{
	if(!conexaoEstabelecida())
		return;

	char textoEnviar = (char)edtTx->Text.c_str();
	objPorta->TransmitirByte(textoEnviar);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::threadOnRun(TIdThreadComponent *Sender)
{
    Sleep(1000);

	if(!conexaoEstabelecida())
		return;

	// char textoRecebido = objPorta->ReceberByte();
	char textoRecebido = 'c';
	mmoRx->Lines->Add(textoRecebido);
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnLimparRxClick(TObject *Sender)
{
	mmoRx->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TfrmPrincipal::btnFecharPortaClick(TObject *Sender)
{
    delete objPorta;
}
//---------------------------------------------------------------------------

