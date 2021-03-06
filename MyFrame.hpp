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
<<<<<<< HEAD
	void OnUndoImage (wxCommandEvent& event); //sami
    void OnRedoImage (wxCommandEvent& event);
    void OnDrawImage(wxPaintEvent& event);
=======
	void OnUndoImage(wxCommandEvent& event);
    void OnRedoImage(wxCommandEvent& event);
    void OnResetImage(wxCommandEvent& event);
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f


	MyPanel *m_panelPrincipal; // the panel inside the main frame
    MyPanel *m_panelSecondaire;
    MyPanel *m_panelProcess;

};
#endif
