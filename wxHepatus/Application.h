#ifndef WXHEPATUS_APPLICATION_H_
#define WXHEPATUS_APPLICATION_H_

#include <wx/app.h>
#include <wxHepatus/Database.h>
#include <memory>

namespace wxHepatus
{

class Application : public wxApp
{
	typedef wxApp Super;
	
public:
	Application();
	virtual ~Application();
	virtual bool OnInit();
	
private:
	std::auto_ptr<Database> database;		
};

DECLARE_APP(Application)

}

#endif /*WXHEPATUS_APPLICATION_H_*/
