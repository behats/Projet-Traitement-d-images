
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

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) //A RECOPIER
: wxFrame(NULL, wxID_ANY, title, pos, size){

    //Création du wxBoxSizer horizontal
    wxBoxSizer *sizer_horizontal = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(sizer_horizontal);

    m_panelPrincipal = new MyPanel(this);

    sizer_horizontal->Add(m_panelPrincipal, 2, wxALL | wxEXPAND, 5);

    //Création du wxBoxSizer vertical (pour la partie de droite)
    wxBoxSizer *sizer_vertical = new wxBoxSizer(wxVERTICAL);
    sizer_horizontal->Add(sizer_vertical, 1, wxTOP | wxBOTTOM | wxRIGHT | wxEXPAND, 5);

    //Création de la zone du haut à droite
    MyPanel *m_panelProcess = new MyPanel(this);

    m_panelProcess->SetBackgroundColour('#bfbfbf');

    wxButton *btn_miroirH = new wxButton(m_panelProcess,ID_MirrorH,wxT("Miroir horizontal"),wxPoint(25,10),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_MirrorH);

    wxButton *btn_miroirV = new wxButton(m_panelProcess,ID_MirrorV,wxT("Miroir vertical"),wxPoint(145,10),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_MirrorV);

    wxButton *btn_rotate = new wxButton(m_panelProcess,ID_Rotate,wxT("Rotation"),wxPoint(25,50),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Rotate);

    wxButton *btn_flou = new wxButton(m_panelProcess,ID_Blur,wxT("Flou"),wxPoint(145,50),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Blur);

    wxButton *btn_negatif = new wxButton(m_panelProcess,ID_Negative,wxT("Négatif"),wxPoint(25,90),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Negative);

    wxButton *btn_desaturate = new wxButton(m_panelProcess,ID_Desaturate,wxT("Désaturer"),wxPoint(145,90),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Desaturate);

    wxButton *btn_threshold = new wxButton(m_panelProcess,ID_Threshold,wxT("Seuillage"),wxPoint(25,130),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Threshold);

    wxButton *btn_posterize = new wxButton(m_panelProcess,ID_Posterize,wxT("Postériser"),wxPoint(145,130),wxSize(110,30),0,wxDefaultValidator,wxButtonNameStr);
    Bind(wxEVT_BUTTON, &MyFrame::OnProcessImage, this, ID_Posterize);
    sizer_vertical->Add(m_panelProcess, 1, wxBOTTOM | wxEXPAND, 5);

    //Création de la zone du bas à droite
    MyPanel *m_panelSecondaire = new MyPanel(this);
    m_panelSecondaire->SetBackgroundColour('#dbd7d7');
    sizer_vertical->Add(m_panelSecondaire, 2, wxALL | wxEXPAND, 0);


    //menu file
	wxMenu *menuFile = new wxMenu ;

	menuFile->Append(wxID_OPEN);
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, wxID_OPEN);

	menuFile->Append(ID_save, wxT("Save\tCtrl-S"));
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_save);

	menuFile->Append(wxID_EXIT) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

	//menu edit
	wxMenu *menuEdit = new wxMenu ;
    menuEdit->Append(wxID_UNDO);
	Bind(wxEVT_MENU, &MyFrame::OnUndoImage, this, wxID_UNDO);

	menuEdit->Append(wxID_REDO);
	Bind(wxEVT_MENU, &MyFrame::OnRedoImage, this, wxID_REDO);

	//menu window
	wxMenu *menuWindow = new wxMenu;
	menuWindow->Append(ID_PlusLarge, wxT("Plus Large...\tCtrl+"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_PlusLarge);

	menuWindow->Append(ID_MoinsLarge, wxT("Moins Large...\tCtrl-"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_MoinsLarge);

	//menu help
	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(ID_Hello, wxT("Hello...\tCtrl-H"), wxT("hello")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuHelp->Append(wxID_ABOUT);
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);

	menuHelp->Append(ID_Encours, wxT("En cours...\tCtrl-E"));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_Encours);

	//barre menu
	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("File" )) ;
	menuBar->Append( menuEdit, wxT("Edit"));
	menuBar->Append( menuWindow, wxT("Window"));
	menuBar->Append( menuHelp, wxT("Help" ));
	SetMenuBar(menuBar) ;

	//barre de statut
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
        m_panelPrincipal->OpenImage(img);
       // m_panelSecondaire->OpenImage(img);
        //m_panelPrincipal->SetSize
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
        m_panelPrincipal->SaveImage(filename);
    }
}

void MyFrame::OnUndoImage (wxCommandEvent& event){

        m_panelPrincipal->UndoImage();
}

void MyFrame::OnRedoImage (wxCommandEvent& event){}

void MyFrame::OnProcessImage(wxCommandEvent& event){

    switch(event.GetId()) {

        case ID_MirrorH:
            m_panelPrincipal->MirrorImage(true);
            break;

        case ID_MirrorV:
            m_panelPrincipal->MirrorImage(false);
            break;

        case ID_Blur:
            m_panelPrincipal->BlurImage();
            break;

        case ID_Rotate:
            m_panelPrincipal->RotateImage();
            break;

        case ID_Negative:
            m_panelPrincipal->NegativeImage();
            break;

        case ID_Desaturate:
            m_panelPrincipal->DesaturateImage();
            break;

        case ID_Threshold:
            m_panelPrincipal->ThresholdImage();
            break;

        case ID_Posterize:
            m_panelPrincipal->PosterizeImage();
            break;

    }
}
