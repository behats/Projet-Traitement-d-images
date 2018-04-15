
#include "MyImage.hpp"
#include "MyPanel.hpp"
#include "MyRotateDialog.hpp"
#include "MyThresholdDialog.hpp"

//#include <vector>

using namespace std;

MyPanel::MyPanel(wxWindow *parent)
: wxPanel(parent){
    m_image = nullptr;
    m_savedimage =nullptr;
    m_returnimage=nullptr;
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
}

MyPanel::~MyPanel(){

}

void MyPanel::OpenImage(wxString filename){
    m_image = new MyImage(filename);
    m_savedimage=m_image;
    m_returnimage= m_image;

    m_width = m_image->GetWidth();
    m_height = m_image->GetHeight();
    SetSize(m_width,m_height);
    this->GetParent()->SetClientSize(m_width,m_height);

    Refresh();
}

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    if (m_image != nullptr){
        m_bitmap = wxBitmap(*m_image,wxBITMAP_SCREEN_DEPTH);

        wxPaintDC dc(this);
        dc.DrawBitmap(m_bitmap,0,0,false);
    }
}

void MyPanel::MirrorImage(bool b){
    if (m_image != nullptr){
        if(b){
            m_savedimage = new MyImage(m_width,m_height);
            *m_savedimage = m_image->Copy() ;
            m_image->Mirror(true);
        }
        else{
            m_savedimage = new MyImage(m_width,m_height);
            *m_savedimage = m_image->Copy() ;
            m_image->Mirror(false);
        }
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::BlurImage(){
    if (m_image != nullptr){
        m_savedimage = new MyImage(*m_image);
        m_returnimage = m_image;
        *m_image = m_image->Blur(20);
        Refresh();

    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::NegativeImage(){
    if (m_image != nullptr){
        m_savedimage = new MyImage(m_width,m_height);
        *m_savedimage = m_image->Copy() ;
        m_image->Negative();
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::RotateImage(){
    m_savedimage = new MyImage(*m_image);
     if (m_image != nullptr){
        m_savedimage = new MyImage(*m_image);
        MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal() == wxID_OK){
            if(dlg->RadioBox1->GetSelection()==0){
                *m_image = m_image->Rotate();
            }
            else if(dlg->RadioBox1->GetSelection()==1){
                *m_image = m_image->Rotate();
                *m_image = m_image->Rotate();
            }
            else{
                *m_image = m_image->Rotate();
                *m_image = m_image->Rotate();
                *m_image = m_image->Rotate();
            }
        }
        Refresh();
     }
     else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}



void MyPanel::DesaturateImage(){
    if (m_image != nullptr){
        m_savedimage = new MyImage(m_width,m_height);
        *m_savedimage = m_image->Copy() ;
        m_image->Desaturate();
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::ThresholdImage(){
    if (m_image != nullptr){
        m_savedimage = new MyImage(m_width,m_height);
        *m_savedimage = m_image->Copy() ;

        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        int rep = dlg->ShowModal() ;
        if (rep == wxID_OK){
            m_image->Threshold(dlg->m_threshold->GetValue());
        }
    //else if (dlg->ShowModal()== wx)
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
    //New version (TP7)
    /*if (m_image != nullptr){
        MyImage sauv = m_image;
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        if (dlg->ShowModal() == wxID_OK){

        }
        else{
            m_image = sauv;
            delete(sauv);
        }

    }*/
}

void MyPanel::PosterizeImage(){
    if(m_image != nullptr){
        m_savedimage = new MyImage(m_width,m_height);
        *m_savedimage = m_image->Copy() ;
        m_image->Posterize();
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::SaveImage(wxString fileName){
    m_image->SaveFile(fileName);
}

void MyPanel::UndoImage(){
    if(m_image != nullptr){
 //       m_savedimage = new MyImage(*m_image);

         //m_returnimage=m_image;
        //m_image=m_savedimage;
        //m_savedimage=m_returnimage;

        m_image=m_savedimage;

    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
}

    Refresh();

}

void MyPanel::RedoImage(){
    if(m_image != nullptr){
 //       m_savedimage = new MyImage(*m_image);
        //m_returnimage=m_savedimage;
       // m_savedimage=m_image;
        //m_image=m_returnimage;

        m_savedimage=m_returnimage;
       /* m_returnimage=m_image;
        m_image=m_savedimage;
        m_savedimage=m_returnimage; */





    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
}

    Refresh();

}
