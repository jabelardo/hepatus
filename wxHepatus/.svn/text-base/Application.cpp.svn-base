#include <wxHepatus/Application.h>
#include <wxHepatus/LoginDialog.h>
#include <wxHepatus/GeneradorDialog.h>
#include <stdexcept>

namespace wxHepatus
{

Application::Application()
{
}

Application::~Application()
{
}

bool 
Application::OnInit()
{
	try{
		Database* db = new Database("wxHepatus.conf");
		database.reset(db);
		wxDialog* dlg = new GeneradorDialog(*database.get());
		dlg->ShowModal();
		dlg->Destroy();
		return true;
	} catch (std::exception const& e) {
		wxDialog* dlg= new wxMessageDialog(0, 
		                                   wxString(e.what(), *wxConvCurrent),
			            	    		   wxT("ERROR:"), 
								           wxOK | wxICON_EXCLAMATION);			 
		dlg->ShowModal();
		dlg->Destroy();
	}
	return false;
}
  
}
