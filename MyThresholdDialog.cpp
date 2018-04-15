#include "MyThresholdDialog.hpp"

using namespace std;

MyThresholdDialog::MyThresholdDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	//m_threshold->Bind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );

	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(20,10), wxSize(100,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("Valider"), wxPoint(140,60), wxSize(100,30), 0 );
	//m_cancelButton = new wxButton(this, wxID_CANCEL, _("Annuler"), wxPoint(20,60), wxSize(100,30), 0 );
	m_cancelButton  = new wxButton(this, wxID_CANCEL, _("Annuler"), wxPoint(20,60), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyThresholdDialog::~MyThresholdDialog(){
   // m_threshold->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );
}
