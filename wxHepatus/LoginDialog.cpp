#include <wxHepatus/LoginDialog.h>
#include <wxHepatus/Utils.h>
#include <wxHepatus/GeneradorDialog.h>

#include <wx/statline.h>
#include <wx/msgdlg.h>

namespace wxHepatus
{

BEGIN_EVENT_TABLE(LoginDialog, wxDialog)
	EVT_TEXT_ENTER(ID_userTextCtrl, LoginDialog::onUserTextEnter)
	EVT_TEXT_ENTER(ID_passwdTextCtrl, LoginDialog::onPasswdTextEnter)
	EVT_BUTTON(ID_cancelButton, LoginDialog::onCancelButton)
	EVT_BUTTON(ID_okButton, LoginDialog::onOkButton)
END_EVENT_TABLE()
	
LoginDialog::LoginDialog(Database& database)
    : wxDialog(0, -1, wxT("Inicio de sesión"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
    , database(database)
{
    wxStaticText* label1 = new wxStaticText(this, -1, wxT("Usuario:"));
    userTextCtrl = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
    wxStaticText* label2 = new wxStaticText(this, -1, wxT("Clave:"));
    passwdTextCtrl = new wxTextCtrl(this, -1, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_PASSWORD);
    wxStaticLine* staticLine = new wxStaticLine(this, -1);
    cancelButton = new wxButton(this, -1, wxT("Cancelar"));
    okButton = new wxButton(this, -1, wxT("Iniciar Sesión"));

    wxBoxSizer* sizer1 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* gridSizer = new wxFlexGridSizer(2, 2, 3, 6);
    gridSizer->Add(label1, 0, wxALIGN_CENTER_VERTICAL, 0);
    gridSizer->Add(userTextCtrl, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
    gridSizer->Add(label2, 0, wxALIGN_CENTER_VERTICAL, 0);
    gridSizer->Add(passwdTextCtrl, 1, wxEXPAND|wxALIGN_CENTER_VERTICAL, 0);
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
    
    userTextCtrl->SetId(ID_userTextCtrl);    
    passwdTextCtrl->SetId(ID_passwdTextCtrl);
    cancelButton->SetId(ID_cancelButton);
    okButton->SetId(ID_okButton);
}

void 
LoginDialog::onUserTextEnter(wxCommandEvent&)
{
	passwdTextCtrl->SetFocus();
}

void 
LoginDialog::onPasswdTextEnter(wxCommandEvent&)
{
	okButton->SetFocus();
}

LoginDialog::~LoginDialog()
{
}

void 
LoginDialog::onOkButton(wxCommandEvent&)
{
	if (isEmptyTextCtrlWithAlert(*this, *userTextCtrl, "Escriba un usuario")) {
		return;
	}	
	if (isEmptyTextCtrlWithAlert(*this, *passwdTextCtrl, "Escriba la clave")) {
		return;	
	}
	std::string const usuario(userTextCtrl->GetValue().mb_str(*wxConvCurrent));
	std::string const clave(passwdTextCtrl->GetValue().mb_str(*wxConvCurrent));
	if (!database.validarUsuario(usuario, clave)) { 		
		wxDialog* dlg = new wxMessageDialog(this, 
		                                    wxT("Usuario y/o clave incorrectos..."),
			            	 			    wxT("Aviso"),
							 	            wxOK | wxICON_EXCLAMATION);			 
		dlg->ShowModal();
		dlg->Destroy();
		return;
	}
	GeneradorDialog* dlg = new GeneradorDialog(database);
	dlg->ShowModal();
	Close();
}

void 
LoginDialog::onCancelButton(wxCommandEvent&)
{
	Close();
}
	
}
