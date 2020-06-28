#ifndef WXHEPATUS_LOGINDIALOG_H_
#define WXHEPATUS_LOGINDIALOG_H_

#include <wx/wx.h>
#include <wxHepatus/Database.h>

namespace wxHepatus
{

class LoginDialog : public wxDialog
{
public:
	LoginDialog(Database& database);
	virtual ~LoginDialog();
	
private:
	DECLARE_EVENT_TABLE()

	enum 
	{ 
		  ID_userTextCtrl
		, ID_passwdTextCtrl
		, ID_cancelButton
		, ID_okButton
	};	
    
    wxTextCtrl* userTextCtrl;
    wxTextCtrl* passwdTextCtrl;
    wxButton* cancelButton;
    wxButton* okButton;    
    Database& database;
    
    void onUserTextEnter(wxCommandEvent& event);
    void onPasswdTextEnter(wxCommandEvent& event);
    void onOkButton(wxCommandEvent& event);
    void onCancelButton(wxCommandEvent& event);
    
};
	
}

#endif /*WXHEPATUS_LOGINDIALOG_H_*/
