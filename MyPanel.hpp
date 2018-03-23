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
    MyPanel( wxWindow *parent ) ;
    void OpenImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void MirrorImage(bool b);
    void BlurImage();
    void RotateImage();
    void NegativeImage();
    void DesaturateImage();
    void ThresholdImage();
    void PosterizeImage();
    void NbColorImage();
    void SaveImage(wxString fileName);
    void UndoImage();
    ~MyPanel() ;

private:

    wxBitmap m_bitmap ;	// used to display the image
    MyImage *m_image ;	// used to load and process the image
    MyImage *m_savedimage; //used to undo or redo the image
    int m_width;
    int m_height;
};
#endif // MYPANEl_H
