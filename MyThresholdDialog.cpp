#include "MyThresholdDialog.hpp"

using namespace std;

wxDECLARE_EVENT(MON_EVENEMENT, wxCommandEvent);

MyThresholdDialog::MyThresholdDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(60,10), wxSize(120,50), wxSL_HORIZONTAL|wxSL_LABELS );

	m_threshold->Bind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );

	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(130,80), wxSize(100,30), 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, wxT("Annuler"), wxPoint(20,80), wxSize(100,30), 0 );


}

void MyThresholdDialog::OnScroll( wxScrollEvent& event )
{
    //wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);

<<<<<<< HEAD
	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(20,10), wxSize(100,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("Valider"), wxPoint(140,60), wxSize(100,30), 0 );
	//m_cancelButton = new wxButton(this, wxID_CANCEL, _("Annuler"), wxPoint(20,60), wxSize(100,30), 0 );
	m_cancelButton  = new wxButton(this, wxID_CANCEL, _("Annuler"), wxPoint(20,60), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
=======
    wxCommandEvent outEvent(MON_EVENEMENT) ;	// création d'un événement propre
    outEvent.SetInt(m_threshold->GetValue()) ;	// stockage de la valeur du seuil dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f
}

MyThresholdDialog::~MyThresholdDialog(){
   m_threshold->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );
}
