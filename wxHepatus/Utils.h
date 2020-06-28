#ifndef UTILS_H_
#define UTILS_H_

#include <wx/wx.h>
#include <string>

namespace wxHepatus
{
	
bool isEmptyTextCtrlWithAlert(wxWindow& parent, wxTextCtrl& textCtrl, char const* alert);
	
}

#endif /*UTILS_H_*/
