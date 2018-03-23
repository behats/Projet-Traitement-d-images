
#include "MyFrame.hpp"

using namespace std;

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

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size){

    m_panel = new MyPanel(this);

	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello...\tCtrl-H"), wxT("hello")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(wxID_OPEN);
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, wxID_OPEN);

	menuFile->Append(ID_save, wxT("Save\tCtrl-S"));
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_save);

	menuFile->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

	menuFile->Append(ID_PlusLarge, wxT("Plus Large...\tCtrl+"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_PlusLarge);

	menuFile->Append(ID_MoinsLarge, wxT("Moins Large...\tCtrl-"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_MoinsLarge);

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

	wxMenu *menuEdit = new wxMenu ;
    menuEdit->Append(wxID_UNDO);
	Bind(wxEVT_MENU, &MyFrame::OnUndoImage, this, wxID_UNDO);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_Encours, wxT("En cours...\tCtrl-E"));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_Encours);

	wxMenu *menuProcess = new wxMenu;
	menuProcess->Append(ID_MirrorH, wxT("Miroir horizontal"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorH);

	menuProcess->Append(ID_MirrorV, wxT("Miroir vertical"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorV);

	menuProcess->Append(ID_Blur, wxT("Flou"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);

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

	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
	menuBar->Append( menuEdit, wxT("Edit"));
	menuBar->Append( menuHelp, wxT("Help" ));
	menuBar->Append( menuProcess, wxT("Process" ));
	SetMenuBar(menuBar) ;

	Bind(wxEVT_MOTION, &MyFrame::OnMouse, this);
    CreateStatusBar();
    SetStatusText(wxT("Hello!"));
}

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