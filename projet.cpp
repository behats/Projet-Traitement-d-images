// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <wx/filedlg.h>
#endif
#include "MyImage.hpp"
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.hpp"
#include <wx/cmdproc.h>

class MyApp: public wxApp{

public:
    virtual bool OnInit();
};

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

	MyPanel *m_panel; // the panel inside the main frame

};

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_Hello = 1,
	ID_Encours,	// a pour valeur 2
	ID_PlusLarge, // a pour valeur 3
	ID_MoinsLarge, // a pour valeur 4
	ID_MirrorH,
	ID_MirrorV,
	ID_Blur,
	ID_Rotate,
	ID_Negative,
	ID_Desaturate,
	ID_Threshold,
	ID_Posterize,
	ID_save

};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit(){

	MyFrame *frame = new MyFrame( wxT("The Amazing Image Processing"), wxPoint(50, 50), wxSize(850, 640) );
	frame->Show(true);
	frame->Centre(wxBOTH);
	wxInitAllImageHandlers();
	return true;
}

MyPanel::MyPanel(wxWindow *parent)
: wxPanel(parent){
    m_image = nullptr;
    m_savedimage =nullptr; //ajouté
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this) ;
}

MyPanel::~MyPanel(){

}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) //A RECOPIER
: wxFrame(NULL, wxID_ANY, title, pos, size){

    m_panel = new MyPanel(this);

    // Barre des tâches

	wxMenuBar *menuBar = new wxMenuBar ;
	SetMenuBar(menuBar) ;

    //Menu des fichiers

	wxMenu *menuFile = new wxMenu ;
	menuBar->Append( menuFile, wxT("File" )) ;

	menuFile->Append(wxID_OPEN);
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, wxID_OPEN);

	menuFile->Append(ID_save, wxT("Save\tCtrl-S"));
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_save);

	menuFile->Append(ID_PlusLarge, wxT("Plus Large...\tCtrl+"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_PlusLarge);

	menuFile->Append(ID_MoinsLarge, wxT("Moins Large...\tCtrl-"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_MoinsLarge);

	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), wxT("hello")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

	//Menu relatif aux manipulations

    wxMenu *menuEdit = new wxMenu ;
	menuBar->Append( menuEdit, wxT("Edit" ));

	menuEdit->Append(wxID_UNDO);
	Bind(wxEVT_MENU, &MyFrame::OnUndoImage, this, wxID_UNDO);

	// Menu relatif au traitement des images

	wxMenu *menuProcess = new wxMenu;
	menuBar->Append( menuProcess, wxT("Process" ));

	//Miroirs

	menuProcess->Append(ID_MirrorH, wxT("Miroir horizontal"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorH);

	menuProcess->Append(ID_MirrorV, wxT("Miroir vertical"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorV);

	//Flou
	menuProcess->Append(ID_Blur, wxT("Flou"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);

	//Rotation
	menuProcess->Append(ID_Rotate, wxT("Rotation"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotate);

	menuProcess->Append(ID_Negative, wxT("Negatif"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative);

	menuProcess->Append(ID_Desaturate, wxT("Desaturate"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate);

	menuProcess->Append(ID_Threshold, wxT("Threshold"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold);

	menuProcess->Append(ID_Posterize, wxT("Posterize"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Posterize);

	// Menu aide

	wxMenu *menuHelp = new wxMenu;
	menuBar->Append( menuHelp, wxT("Help" ));
	menuHelp->Append(ID_Encours, wxT("En cours...\tCtrl-E"));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_Encours);


	//

	Bind(wxEVT_MOTION, &MyFrame::OnMouse, this);
    CreateStatusBar();
    SetStatusText(wxT("Hello!"));
}

void MyPanel::OpenImage(wxString filename){
    m_image = new MyImage(filename);
    m_savedimage=m_image;

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
                m_savedimage = new MyImage(*m_image);
            m_image->Mirror(true);
        }
        else{
            m_savedimage = new MyImage(*m_image);
            m_image->Mirror(false);
        }
        Refresh();
    }
}

void MyPanel::BlurImage(){
    if (m_image != nullptr){

         m_savedimage = new MyImage(*m_image);

        *m_image = m_image->Blur(20);

        Refresh();

    }
}

void MyPanel::RotateImage(){
     if (m_image != nullptr){
         m_savedimage = new MyImage(*m_image);
        MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal()== wxID_OK){
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
}

void MyPanel::NegativeImage(){
    m_savedimage = new MyImage(*m_image);
    if (m_image != nullptr){
        m_image->Negative();
        Refresh();
    }
}

void MyPanel::DesaturateImage(){
    m_savedimage = new MyImage(*m_image);
    if (m_image != nullptr){
        m_image->Desaturate();
        Refresh();
    }
}

void MyPanel::ThresholdImage(){
    m_savedimage = new MyImage(*m_image);
    if (m_image != nullptr){
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        dlg->ShowModal() ;
        m_image->Threshold(dlg->m_threshold->GetValue());
        Refresh();
    }
}

void MyPanel::PosterizeImage(){
    m_savedimage = new MyImage(*m_image);
    if(m_image != nullptr){
        m_image->Posterize();
        Refresh();
    }
}

void MyPanel::SaveImage(wxString fileName){
    m_image->SaveFile(fileName);
}

void MyPanel::UndoImage(){
    if(m_image != nullptr){
 //       m_savedimage = new MyImage(*m_image);
        m_image= m_savedimage;

    }
    else{
    wxLogMessage(wxT("Hello world from wxWidgets!"));
}

    Refresh();

}



// Méthodes de la fenêtre

void MyFrame::OnHello(wxCommandEvent& event){
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnExit(wxCommandEvent& event){
	Close( true );
}

void MyFrame::OnOpenImage(wxCommandEvent& event){
    wxString img = wxFileSelector();
    if (!img.empty()){
        m_panel->OpenImage(img);
    }
}

void MyFrame::OnAbout(wxCommandEvent& event){
    wxLogMessage(wxT("Auteur: Antoine Jayet-Laraffe 2017/2018"));
}

void MyFrame::OnEnCours(wxCommandEvent& event){
    wxLogMessage(wxT("En construction !"));
}

void MyFrame::OnResize(wxCommandEvent& event){
    int w = 0;
    int h = 0;

    GetSize(&w,&h);

    if (event.GetId() == ID_PlusLarge){
        SetSize(w+100,h+100);
    }

    if (event.GetId() == ID_MoinsLarge){
        SetSize(w-100,h-100);
    }
}

void MyFrame::OnMouse(wxMouseEvent& event){
    wxCoord x = event.GetX();
    wxCoord y = event.GetY();
    wxString coord;
    coord.sprintf("x=%d y=%d", x,y);

    SetStatusText(coord);
}

void MyFrame::OnSaveImage(wxCommandEvent& event){
    wxString filename = wxSaveFileSelector(wxT("Save as"),wxT(".png"),wxT("NomFichier"));
    //SetClientSize(m_width,m_height);
    if( !filename.empty()){
        m_panel->SaveImage(filename);
    }
}

void MyFrame::OnUndoImage (wxCommandEvent& event){

        m_panel->UndoImage();
}

void MyFrame::OnProcessImage(wxCommandEvent& event){

    switch(event.GetId()) {

        case ID_MirrorH:
            m_panel->MirrorImage(true);
            break;

        case ID_MirrorV:
            m_panel->MirrorImage(false);
            break;

        case ID_Blur:
            m_panel->BlurImage();
            break;

        case ID_Rotate:
            m_panel->RotateImage();
            break;

        case ID_Negative:
            m_panel->NegativeImage();
            break;

        case ID_Desaturate:
            m_panel->DesaturateImage();
            break;

        case ID_Threshold:
            m_panel->ThresholdImage();
            break;

        case ID_Posterize:
            m_panel->PosterizeImage();
            break;
    }
}
