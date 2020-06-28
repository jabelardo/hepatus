#ifndef WXHEPATUS_CLAVESDIALOG_H_
#define WXHEPATUS_CLAVESDIALOG_H_

#include <wx/wx.h>
#include <wxHepatus/Database.h>

namespace wxHepatus
{

class GeneradorDialog : public wxDialog
{
public:
	GeneradorDialog(Database& database);
	virtual ~GeneradorDialog();
	
private:
	DECLARE_EVENT_TABLE()
	
   	enum 
	{ 
		  ID_seedTextCtrl
		, ID_cancelButton
		, ID_okButton
	};	
	
    wxTextCtrl* seedTextCtrl;
    wxButton* cancelButton;
    wxButton* okButton;    
    Database& database;
    
    void onSeedTextEnter(wxCommandEvent& event);
    void onOkButton(wxCommandEvent& event);
    void onCancelButton(wxCommandEvent& event);
};

}

#if 0
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <ADODB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TfrmClaves : public TForm
{
__published:	// IDE-managed Components
        TLabel *lblRecogedor;
        TLabel *lblAgente;
        TLabel *lblLlave;
        TLabel *lblTecnico;
        TEdit *txtIdRec;
        TEdit *txtRecogedor;
        TEdit *txtIdAge;
        TEdit *txtAgente;
        TEdit *txtLlave;
        TComboBox *cmbTecnicos;
        TButton *btnAceptar;
        TButton *btnBuscarRec;
        TButton *btnBuscarAgente;
        TComboBox *cmbTipo;
        TLabel *lblTipo;
        TEdit *txtDato;
        TRichEdit *txtGenerado;
        TButton *btnCifrado;
        TBitBtn *btnInstalar;
        TButton *btnLlave;
        TBitBtn *btnAleatorio;
        void __fastcall btnAceptarClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btnBuscarRecClick(TObject *Sender);
        void __fastcall btnBuscarAgenteClick(TObject *Sender);
        void __fastcall txtIdRecExit(TObject *Sender);
        void __fastcall txtIdAgeExit(TObject *Sender);
        void __fastcall btnCifradoClick(TObject *Sender);
        void __fastcall btnInstalarClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnLlaveClick(TObject *Sender);
        void __fastcall btnAleatorioClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmClaves(TComponent* Owner);
         void calcularkey();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmClaves *frmClaves;
//---------------------------------------------------------------------------
#endif

#endif /*WXHEPATUS_CLAVESDIALOG_H_*/
