#ifndef MYEXITDDIALOG_H
#define MYEXITDDIALOG_H
#include <wx/wxprec.h>
//#include "MyPanel.hpp"
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/filedlg.h>
#endif

class MyExitDialog : public wxDialog
{
private:
	wxButton* m_saveButton;
	wxButton* m_nosaveButton;
	wxButton* m_cancelButton;
	//MyPanel *m_panel;
public:
	//wxSlider* m_threshold;
	/*wxButton* m_saveButton;
	wxButton* m_nosaveButton;
	wxButton* m_cancelButton;*/
	MyExitDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
		const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
    void OnSave(wxCommandEvent& event);

    ~MyExitDialog();
};
#endif // MYEXITDIALOG_H

