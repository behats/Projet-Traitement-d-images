#include "MyExitDialog.hpp"

using namespace std;

MyExitDialog::MyExitDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
    SetClientSize(wxSize(350,100));

	m_saveButton = new wxButton( this, wxID_OK, wxT("Save"), wxPoint(20,60), wxSize(100,30), 0 , wxDefaultValidator, _T("wxID_OK"));

	m_nosaveButton = new wxButton( this, wxID_CLOSE_ALL, wxT("Don't save"), wxPoint(125,60), wxSize(100,30),0, wxDefaultValidator, _T("wxID_CLOSE_ALL"));
//	Bind(wxEVT_BUTTON, &MyExitDialog::OnNosave, this, wxID_CLOSE_ALL) ;
	//m_cancelButton = new wxButton(this, wxID_CANCEL, wxT("Annuler"), wxPoint(225,60), wxSize(100,30), 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(225,60), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyExitDialog::~MyExitDialog(){

}





