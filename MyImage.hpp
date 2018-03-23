#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif



class MyImage : public wxImage{

public:
    MyImage(const wxString& fileName) ;
    MyImage(wxImage image) ;
    MyImage(int largeur, int hauteur) ;
    MyImage() ;

    void Negative() ;
    void Desaturate() ;
    void Threshold(int seuil);
    void Mirror(bool h);
    MyImage Rotate();
    void Posterize();
    //int NbColor();

private:
};
#endif // MYIMAGE_H
