
#include "MyImage.hpp"
#include "MyPanel.hpp"
#include "MyRotateDialog.hpp"
#include "MyThresholdDialog.hpp"

//#include <vector>

using namespace std;
//wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);


MyPanel::MyPanel(wxWindow *parent)
: wxPanel(parent){
    m_image = nullptr;
<<<<<<< HEAD
    m_savedimage =nullptr;
    m_returnimage=nullptr;
=======
    m_undoimage = nullptr;
    m_originimage = nullptr;
    m_redoimage = nullptr;
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
}

/*MyPanel::MyPanel( wxWindow *parent, wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize)
: wxPanel(parent, id, pos, size){
    m_image = nullptr;
    m_savedimage =nullptr;
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
}*/
MyPanel::~MyPanel(){

}

void MyPanel::OpenImage(wxString filename){
    m_image = new MyImage(filename);
<<<<<<< HEAD
    m_savedimage=m_image;
    m_returnimage= m_image;
=======
    m_originimage = new MyImage(m_width,m_height);
    *m_originimage = m_image->Copy();
    m_undoimage = m_image;
    m_redoimage = m_image;

    wxSize panel_size = GetSize();
    m_width = panel_size.GetWidth();
    m_height = panel_size.GetHeight();
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f

    int img_width = m_image->GetWidth();
    int img_height = m_image->GetHeight();

    int dw = m_width-img_width;
    int dh = m_height-img_height;
    SetSize(img_width,img_height);

    wxSize frame_size = this->GetParent()->GetSize();
    this->GetParent()->SetClientSize(frame_size.GetWidth()-dw,frame_size.GetHeight()-dh);

    /*m_width = m_image->GetWidth();
    m_height = m_image->GetHeight();

    SetSize(m_width,m_height);
    this->GetParent()->SetClientSize(m_width,m_height);*/

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
        if(!b){
            m_undoimage = new MyImage(m_width,m_height);
            *m_undoimage = m_image->Copy() ;
            m_image->Mirror(true);
        }
        else{
            m_undoimage = new MyImage(m_width,m_height);
            *m_undoimage = m_image->Copy() ;
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
<<<<<<< HEAD
        m_savedimage = new MyImage(*m_image);
        m_returnimage = m_image;
=======
        m_undoimage = new MyImage(*m_image);
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f
        *m_image = m_image->Blur(20);
        Refresh();

    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::NegativeImage(){
    if (m_image != nullptr){
        m_undoimage = new MyImage(m_width,m_height);
        *m_undoimage = m_image->Copy() ;
        m_image->Negative();
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

void MyPanel::RotateImage(){
    m_undoimage = new MyImage(*m_image);
     if (m_image != nullptr){
        m_undoimage = new MyImage(*m_image);
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
        m_undoimage = new MyImage(m_width,m_height);
        *m_undoimage = m_image->Copy() ;
        m_image->Desaturate();
        Refresh();
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
}

wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);

void MyPanel::ThresholdImage(){
    /*if (m_image != nullptr){
        m_savedimage = new MyImage(m_width,m_height);
        *m_savedimage = m_image->Copy() ;

        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        int rep = dlg->ShowModal() ;
        if (rep == wxID_OK){
            m_image->Threshold(dlg->m_threshold->GetValue());
        }
    //else if (dlg->ShowModal()== wx)
        Refresh();
<<<<<<< HEAD
    }
    else{
    wxLogMessage(wxT("Il n'y a aucune image à traiter."));
    }
=======
    }*/
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f
    //New version (TP7)
    if (m_image != nullptr){
        m_undoimage = new MyImage(*m_image);
        *m_undoimage = m_image->Copy() ;

        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        int n = dlg->ShowModal();

        if (n == wxID_OK){
            m_image->Threshold(dlg->m_threshold->GetValue());
            Refresh();
        }
        if (n == wxID_CANCEL){
            m_image = m_undoimage;
            Refresh();
        }

    }
}

void MyPanel::OnThresholdImage(wxCommandEvent& event){
    int seuil = event.GetInt();
    m_image->Threshold(seuil);
    Refresh();
}

void MyPanel::PosterizeImage(){
    if(m_image != nullptr){
        m_undoimage = new MyImage(m_width,m_height);
        *m_undoimage = m_image->Copy() ;
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
<<<<<<< HEAD

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
=======
        *m_redoimage = m_image->Copy();
        m_image = m_undoimage;
        Refresh();

    }
}
void MyPanel::RedoImage(){
    if(m_image != nullptr){
        m_image = m_redoimage;
        Refresh();
    }
>>>>>>> 58d9973b989f0f3f773549108074a067cc56a99f
}

void MyPanel::ResetImage(){
    if(m_image != nullptr){
        m_image = m_originimage;
        Refresh();
    }
}
