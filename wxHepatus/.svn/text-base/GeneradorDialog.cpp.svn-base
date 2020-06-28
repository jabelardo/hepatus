#include <wxHepatus/GeneradorDialog.h>
#include <wxHepatus/Utils.h>
#include <wxHepatus/Criptografia.h>

#include <wx/statline.h>
#include <wx/msgdlg.h>

#include <stdexcept>

namespace wxHepatus
{

char const * const KEY_FILE_NAME = "lotix.key";

BEGIN_EVENT_TABLE(GeneradorDialog, wxDialog)
	EVT_TEXT_ENTER(ID_seedTextCtrl, GeneradorDialog::onSeedTextEnter)
	EVT_BUTTON(ID_cancelButton, GeneradorDialog::onCancelButton)
	EVT_BUTTON(ID_okButton, GeneradorDialog::onOkButton)
END_EVENT_TABLE()

GeneradorDialog::GeneradorDialog(Database& database)
	: wxDialog(0, -1, wxT("wxHepatus"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
	, database(database)
{    
	wxStaticText* label1 = new wxStaticText(this, -1, wxT("Semilla de autentificación:"));
    seedTextCtrl = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);    
    wxStaticLine* staticLine = new wxStaticLine(this, -1);
    cancelButton = new wxButton(this, -1, wxT("Cerrar"));
    okButton = new wxButton(this, -1, wxT("Generar"));

    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 2, 3, 6);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL, 0);
    gridSizer->Add(seedTextCtrl, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    gridSizer->AddGrowableCol(1);
    sizer1->Add(gridSizer, 1, wxALL|wxEXPAND, 12);
    sizer1->Add(staticLine, 0, wxLEFT|wxRIGHT|wxBOTTOM|wxEXPAND, 6);
    sizer2->Add(cancelButton, 0, wxLEFT|wxRIGHT|wxADJUST_MINSIZE, 6);
    sizer2->Add(okButton, 0, wxRIGHT|wxALIGN_CENTER_HORIZONTAL|wxADJUST_MINSIZE, 6);
    sizer1->Add(sizer2, 0, wxBOTTOM|wxALIGN_RIGHT, 6);
    SetAutoLayout(true);
    SetSizer(sizer1);
    sizer1->Fit(this);
    sizer1->SetSizeHints(this);
    Layout();
    
    seedTextCtrl->SetId(ID_seedTextCtrl);
    cancelButton->SetId(ID_cancelButton);
    okButton->SetId(ID_okButton);
}

GeneradorDialog::~GeneradorDialog()
{
}

void 
GeneradorDialog::onSeedTextEnter(wxCommandEvent&)
{
	okButton->SetFocus();
}

void 
GeneradorDialog::onCancelButton(wxCommandEvent&)
{
	Close();
}

void 
GeneradorDialog::onOkButton(wxCommandEvent&)
{
	if (isEmptyTextCtrlWithAlert(*this, *seedTextCtrl, "Escriba la semilla")) {
		return;
	}
	std::string const seed(seedTextCtrl->GetValue().mb_str(*wxConvCurrent));
	try {
		generarKeyFile(KEY_FILE_NAME, seed);
		wxDialog* dlg = new wxMessageDialog(this, 
		                                    wxT("Archivo generado"), 
			           	 			        wxT("Aviso"), 
							 	            wxOK | wxICON_EXCLAMATION);			 
		dlg->ShowModal();
		dlg->Destroy();
				
	} catch (std::runtime_error const& e) {
		wxDialog* dlg = new wxMessageDialog(this, 
		                                    wxString(e.what(), *wxConvCurrent),
			            	 			    wxT("Aviso"), 
							 	            wxOK | wxICON_EXCLAMATION);			 
		dlg->ShowModal();
		dlg->Destroy();
	}
}

}

#if 0
#include <vcl.h>
#include <time.h>
#include <errno.h>
#include <sys\stat.h>
#include <stdlib.h>

#pragma hdrstop

#include "unitInfo.h"
#include <string>
#include "unitCatalogo.h"
#include "unitData.h"
#include "unitLogin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

extern bool master;
char keysource [20] = "", keydest [20] = "";
char tecnico[] = {'-','A','B','C','D','E','F'};
char nivel[] = {'0','5','3','3','3','3','5'};
int idAgente;
int TipoAgente = 0;
AnsiString NombreAgente = "";

TfrmClaves *frmClaves;

//---------------------------------------------------------------------------
void MensajeError(char * mensaje);
void MensajeOk(char * mensaje);
void MensajeWarning(char * mensaje);

//------------------------------------------------------------------------
__fastcall TfrmClaves::TfrmClaves(TComponent* Owner)
        : TForm(Owner)
{
}
//------------------------------------------------------------------------
string TimeToStr(time_t t, const char *formato)
{
   if (t == 0)
   t = time(NULL);
   struct tm *TM = localtime(&t);
   char hora[15];
   sprintf(hora,formato,TM->tm_hour, TM->tm_min,TM->tm_sec);
   return string(hora);
}
//------------------------------------------------------------------------
string DateToStr(time_t t)
{
   if (t == 0)
   t = time(NULL);
   struct tm *TM = localtime(&t);
   char fecha[15];
   sprintf(fecha,"%d%02d%02d",TM->tm_year + 1900,TM->tm_mon + 1,TM->tm_mday );
   return string(fecha);
}
//-----------------------------------------------------------------------------

//------------------------------------------------------------------------
string
HEX(const char * cnumero, bool modo)
{
   int numero;
   int i;
   char aHex [] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

   if (!modo)
   {
      for (i = 0; i < sizeof(aHex); i++)
      {
         if ( cnumero[0] == aHex[i] )
         {
            numero = i * 16;
            break;
         }
      }
      for (i = 0; i < sizeof(aHex); i++)
      {
         if ( cnumero[1] == aHex[i] )
         {
            numero += i;
            break;
         }
      }
      char cHex[10];
      sprintf(cHex,"%d",numero);
      return string(cHex);
   }
   else
   {
      string cHex = "";
      unsigned char num = cnumero[0];
      numero = num;
      if (numero < 16)
      cHex = "0";
      else
      {
         cHex = aHex[numero / 16];
         numero = numero % 16;
      }
      cHex = cHex + aHex[numero];
      return cHex;
   }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
string
DecryptStr(string tira, const char *clave)
{
   string aux = "";
   for( unsigned int i = 0; i < tira.length(); i += 2)
   {
      string e1;
      e1 = tira.substr(i,2);
      string e2;
      e2 = HEX(e1.c_str(), false);
      unsigned char num;
      char x[4];
      strcpy(x, e2.c_str());
      num = atoi(x);
      int num2 = abs(num - 255);
      char c = num2;
      aux += c;
   }
   char texto[255];
   strcpy(texto,aux.c_str());
   crypto(texto,strlen(texto),clave,strlen(clave));
   return string(texto);
}
//-----------------------------------------------------------------------------
bool
BuscarRec(AnsiString Agente)
{
   if (Agente == "")
      return false;
   datModulo->adoQuery->Close();
   datModulo->adoQuery->SQL->Text = "SELECT * FROM Agentes WHERE Id = " + Agente + " AND IdTipoAgente IN (2,3)";
   datModulo->adoQuery->Open();
   if (datModulo->adoQuery->RecordCount <= 0)
      return false;
   return true;
}
//-----------------------------------------------------------------------------
bool
BuscarAge(AnsiString Recogedor, AnsiString Agente)
{
   if (Agente == "" || Recogedor == "")
      return false;
   datModulo->adoQuery->Close();
   datModulo->adoQuery->SQL->Text = "SELECT * FROM Agentes WHERE Id = " + Agente + " AND IdRecogedor = " + Recogedor + " AND IdTipoAgente = 1";
   datModulo->adoQuery->Open();
   if (datModulo->adoQuery->RecordCount <= 0)
      return false;
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmClaves::btnAceptarClick(TObject *Sender)
{
time_t hora = time(NULL);
char fechahora[11];
string recogedor = "";
string agente = "";
char tipoclave[] = {'-','E','V','C','I','D','B'};
string emergencia = "";
string clave = "";

   if (!BuscarRec(txtIdRec->Text))
   {
      ShowMessage("El codigo del recogedor no existe...");
      txtIdRec->SetFocus();
      return;
   }

   if (!BuscarAge(txtIdRec->Text,txtIdAge->Text))
   {
      ShowMessage("El codigo del agente no existe...");
      txtIdAge->SetFocus();
      return;
   }

   if (txtLlave->Text.Length() != 8)
   {
      ShowMessage("La llave es invalida...");
      txtLlave->SetFocus();
      return;
   }

   if (cmbTecnicos->ItemIndex == 0)
   {
      ShowMessage("Debe seleccionar un tecnico, por favor...");
      cmbTecnicos->SetFocus();
      return;
   }

   sprintf(fechahora,"%X",hora);
   clave = txtLlave->Text.c_str();
   switch (cmbTipo->ItemIndex)
   {
     case 0:
        ShowMessage("Debe seleccionar una clave, por favor...");
        cmbTipo->SetFocus();
        return;
     case 1:
        emergencia += fechahora;
     break;
     case 2:
        hora += 86400 * 8;
        sprintf(fechahora,"%X",hora);
        emergencia += fechahora;
     break;
     case 3:
        emergencia += fechahora;
     break;
     case 4:
        emergencia += tecnico[cmbTecnicos->ItemIndex];
        emergencia += txtIdRec->Text.c_str();
        emergencia += ":";
        emergencia += txtIdAge->Text.c_str();
        emergencia += ":";
     break;
     case 5:
        emergencia += fechahora;
     break;
     case 6:
        emergencia += fechahora;
     break;
     default:
        return;
   }
   int lentext = txtIdAge->Text.Length();
   if ( lentext > 1 )
   {
      agente = txtIdAge->Text.SubString(lentext - 1, 2).c_str();
   }
   else
   {
      agente += '0';
      agente += txtIdAge->Text.c_str();
   }
   emergencia += agente;
   emergencia += tipoclave[cmbTipo->ItemIndex];
   txtDato->Text = emergencia.c_str();
   txtGenerado->Text = EncryptStr(emergencia,clave.c_str()).c_str();
}
//---------------------------------------------------------------------------
void __fastcall TfrmClaves::FormCreate(TObject *Sender)
{
   cmbTipo->ItemIndex = 0;
   cmbTecnicos->ItemIndex = 0;
   calcularkey();
   //ShowMessage(keysource);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::btnBuscarRecClick(TObject *Sender)
{
   idAgente = 0;
   TipoAgente = 2;
   frmCatalogo->ShowModal();
   if ( idAgente != 0)
   {
      txtIdRec->Text = IntToStr(idAgente);
      txtRecogedor->Text = NombreAgente;
   }
   txtIdAge->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::btnBuscarAgenteClick(TObject *Sender)
{
   if (!BuscarRec(txtIdRec->Text))
   {
      ShowMessage("El codigo del recogedor no existe...");
      return;
   }
   idAgente = 0;
   TipoAgente = 1;
   frmCatalogo->ShowModal();
   if ( idAgente != 0)
   {
      txtIdAge->Text = IntToStr(idAgente);
      txtAgente->Text = NombreAgente;
   }
   cmbTipo->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::txtIdRecExit(TObject *Sender)
{
   if ( BuscarRec(txtIdRec->Text) )
      txtRecogedor->Text = datModulo->adoQuery->FieldValues["Nombre"];
   else
      txtRecogedor->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::txtIdAgeExit(TObject *Sender)
{
   if ( BuscarAge(txtIdRec->Text, txtIdAge->Text) )
      txtAgente->Text = datModulo->adoQuery->FieldValues["Nombre"];
   else
      txtAgente->Text = "";
}
//---------------------------------------------------------------------------

void MensajeError(char * mensaje)
{
    Application->MessageBox(mensaje,"Error",MB_OK | MB_ICONERROR );
}

//---------------------------------------------------------------------------
void MensajeOk(char * mensaje)
{
    Application->MessageBox(mensaje,"Informaci�n",MB_OK | MB_ICONINFORMATION );
}

//---------------------------------------------------------------------------
void MensajeWarning(char * mensaje)
{
    Application->MessageBox(mensaje,"Advertencia",MB_OK | MB_ICONWARNING );
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TfrmClaves::calcularkey()
{
   struct stat sStat;
   char clave [13];
   char llave [41];
   string resultado;
   FILE *cifrado = fopen("infox000.cfg","r");
   if ( stat( "infox000.cfg",&sStat ) != -1 )
   {
      time_t hora = sStat.st_mtime;
      struct tm *TM = localtime(&hora);
      char fechahora [13];
      sprintf(fechahora,"%d%02d%02d%02d%02d",TM->tm_year+1900,TM->tm_mon+1,TM->tm_mday,TM->tm_hour,TM->tm_min);
      strcpy(clave,fechahora);
      fread(llave,sizeof(llave),1,cifrado);
      crypto(llave,strlen(llave),clave,strlen(clave));
      resultado = DecryptStr(llave,clave).c_str();
      strcpy(keysource,resultado.c_str());
   }
   else
   {
      MensajeError("Error abriendo el archivo de cifrado!");
      Application->Terminate();
   }
   fclose(cifrado);
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TfrmClaves::FormShow(TObject *Sender)
{
   if (master)
   {
      btnInstalar->Visible = true;
      btnLlave->Visible = true;
      btnAleatorio->Visible = true;
   }
   else
   {
      btnInstalar->Visible = false;
      btnLlave->Visible = false;
      btnAleatorio->Visible = false;
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::btnLlaveClick(TObject *Sender)
{
   ShowMessage(keysource);
}
//---------------------------------------------------------------------------

void __fastcall TfrmClaves::btnAleatorioClick(TObject *Sender)
{
   char caracteres [] = "abcdefghijklmnopqrstuvwxyz1234567890.,/*-+:!?ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   int unsigned longitud = 12;
   char aleatorio[12] = "";
   for( unsigned int i = 0; i < longitud; i ++)
   {
      aleatorio[i] = caracteres[random(strlen(caracteres)-1)];
   }
   aleatorio[12] = '\0';
   txtGenerado->Text = aleatorio;
}
//---------------------------------------------------------------------------
#endif
