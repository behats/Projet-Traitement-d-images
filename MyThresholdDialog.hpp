#ifndef MYTHRESHOLDDIALOG_H
#define MYTHRESHOLDDIALOG_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/filedlg.h>
#endif

class MyThresholdDialog : public wxDialog
{
private:
	wxButton* m_okButton;
	wxButton* m_cancelButton;
public:
	wxSlider* m_threshold;
	MyThresholdDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
    ~MyThresholdDialog();
};
#endif // MYTHRESHOLDDIALOG_H
