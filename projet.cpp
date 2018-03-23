// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/filedlg.h>
#endif
#include "MyFrame.hpp"
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.hpp"

class MyApp: public wxApp{

public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){

	MyFrame *frame = new MyFrame( wxT("wxProcess"), wxPoint(50, 50), wxSize(850, 640) );
	frame->Show(true);
	frame->Centre(wxBOTH);
	wxInitAllImageHandlers();
	return true;
}
