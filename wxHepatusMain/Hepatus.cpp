//---------------------------------------------------------------------------

#if 0
#include <vcl.h>
#pragma hdrstop
USERES("Hepatus.res");
USEFORM("unitInfo.cpp", frmClaves);
USELIB("zlib_bor.lib");
USEFORM("unitCatalogo.cpp", frmCatalogo);
USEFORM("unitData.cpp", datModulo); /* TDataModule: File Type */
USEFORM("unitLogin.cpp", frmLogin);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmLogin), &frmLogin);
                 Application->CreateForm(__classid(TfrmClaves), &frmClaves);
                 Application->CreateForm(__classid(TfrmCatalogo), &frmCatalogo);
                 Application->CreateForm(__classid(TdatModulo), &datModulo);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
#endif

#include <wxHepatus/Application.h>

using wxHepatus::Application;

IMPLEMENT_APP(Application)
