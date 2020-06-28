//---------------------------------------------------------------------------

#if 0
#include <vcl.h>
#include <string>
#pragma hdrstop

#include "unitCatalogo.h"
#include "unitInfo.h"
#include "unitData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

extern int idAgente;
extern int TipoAgente;
extern AnsiString NombreAgente;

TfrmCatalogo *frmCatalogo;
//---------------------------------------------------------------------------
__fastcall TfrmCatalogo::TfrmCatalogo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogo::txtAgenteChange(TObject *Sender)
{
   datModulo->adoQuery->DisableControls();
   datModulo->adoQuery->Close();
   datModulo->adoQuery->SQL->Clear();
   datModulo->adoQuery->SQL->Add("SELECT *");
   datModulo->adoQuery->SQL->Add("FROM Agentes");
   datModulo->adoQuery->SQL->Add("WHERE Nombre LIKE");
   datModulo->adoQuery->SQL->Add("'%" + txtAgente->Text + "%'");
   datModulo->adoQuery->SQL->Add("AND IdTipoAgente = " + IntToStr(TipoAgente));
   if (TipoAgente == 1)
      datModulo->adoQuery->SQL->Add("AND IdRecogedor = " + frmClaves->txtIdRec->Text);
   datModulo->adoQuery->Open();
   datModulo->adoQuery->EnableControls();
}
//---------------------------------------------------------------------------
void __fastcall TfrmCatalogo::btnAceptarClick(TObject *Sender)
{
   if (datModulo->adoQuery->RecordCount > 0)
   {
      idAgente = datModulo->adoQuery->FieldValues["Id"];
      NombreAgente = datModulo->adoQuery->FieldValues["Nombre"];
      Close();
   }
   else ShowMessage("No existe codigo seleccionado...");
}
//---------------------------------------------------------------------------

void __fastcall TfrmCatalogo::Button1Click(TObject *Sender)
{
   ShowMessage(datModulo->adoQuery->SQL->Text);
}
//---------------------------------------------------------------------------



void __fastcall TfrmCatalogo::FormShow(TObject *Sender)
{
   txtAgente->Text = "";
   datModulo->adoQuery->Close();
   if (TipoAgente == 2)
      datModulo->adoQuery->SQL->Text = "SELECT * FROM Agentes WHERE IdTipoAgente IN (2,3) ORDER BY Id";
   else
      datModulo->adoQuery->SQL->Text = "SELECT * FROM Agentes WHERE IdTipoAgente = " + IntToStr(TipoAgente) + " AND IdRecogedor = " + frmClaves->txtIdRec->Text + " ORDER BY Id";
   datModulo->adoQuery->Open();
}
//---------------------------------------------------------------------------
#endif




