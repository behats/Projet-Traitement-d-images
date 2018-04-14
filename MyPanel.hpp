#ifndef MYPANEL_H
#define MYPANEL_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/filedlg.h>
#endif
#include "MyImage.hpp"


class MyPanel: public wxPanel{

public:
    MyPanel(wxWindow *parent);
    //MyPanel(wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize);
    void OpenImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void MirrorImage(bool b);
    void BlurImage();
    void RotateImage();
    void NegativeImage();
    void DesaturateImage();
    void ThresholdImage();
    void OnThresholdImage(wxCommandEvent& event);
    void PosterizeImage();
    void NbColorImage();
    void SaveImage(wxString fileName);
    void UndoImage();
    void RedoImage();
    void ResetImage();

    ~MyPanel() ;

private:

    wxBitmap m_bitmap ;	// used to display the image
    MyImage *m_image ;	// used to load and process the image
    MyImage *m_originimage;
    MyImage *m_undoimage; //used to undo the image
    MyImage *m_redoimage;
    int m_width;
    int m_height;

};
#endif // MYPANEl_H
