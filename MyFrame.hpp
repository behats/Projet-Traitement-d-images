#ifndef MYFRAME_H
#define MYFRAME_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/event.h>
#include <wx/filedlg.h>
#include "MyPanel.hpp"
#endif

class MyFrame: public wxFrame{

public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnEnCours(wxCommandEvent& event);
	void OnResize(wxCommandEvent& event);
	void OnMouse(wxMouseEvent& event);
	void OnOpenImage(wxCommandEvent& event);
	void OnProcessImage(wxCommandEvent& event);
	void OnSaveImage(wxCommandEvent& event);
	void OnUndoImage (wxCommandEvent& event); //sami
    void OnRedoImage (wxCommandEvent& event);
    void OnDrawImage(wxPaintEvent& event);

	MyPanel *m_panel; // the panel inside the main frame

};
#endif
