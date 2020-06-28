#include <wxHepatus/Utils.h> 

namespace wxHepatus
{
	
bool 
isEmptyTextCtrlWithAlert(wxWindow& parent, wxTextCtrl& textCtrl, char const* alert)
{
	if (textCtrl.GetLastPosition() == 0) {	
		wxMessageDialog messageDialog(&parent, 
		                              wxString(alert, *wxConvCurrent),
								      wxT("Aviso"), 
								      wxOK | wxICON_EXCLAMATION);			 
		messageDialog.ShowModal();
		textCtrl.SetFocus();		
		return true;
	}
	return false;
}

}
