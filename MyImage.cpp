
#include "MyImage.hpp"
#include <vector>

using namespace std;

MyImage::MyImage(const wxString& fileName):
    wxImage(fileName) {}

MyImage::MyImage(wxImage image):
     wxImage(image) {}

MyImage::MyImage(int largeur, int hauteur):
    wxImage(largeur, hauteur) {}

MyImage::MyImage():
    wxImage() {}

void MyImage::Negative(){
    unsigned char* data = this->GetData();
    for(int i=0; i<(this->GetHeight()*this->GetWidth()*3); i++){
        data[i] = 255-data[i];
    }
}

void MyImage::Desaturate(){

    unsigned long L;
    unsigned char* data= this->GetData();
    for(int i=0; i < this->GetHeight()*this->GetWidth()*3; i=i+3){
        L= 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
        data[i]=L;
        data[i+1]=L;
        data[i+2]=L;
    }

}



void MyImage::Threshold(int seuil){
    Desaturate();
    unsigned char* data = this->GetData();
    for(int i=0; i<(this->GetHeight()*this->GetWidth()*3); i++){
        if(data[i]<=seuil){
            data[i]=0;
        }
        else{
            data[i]=255;
        }
    }
}

void MyImage::Mirror(bool h){
    unsigned char* data = this->GetData();
    unsigned char sauvR, sauvV, sauvB;

    int largeur = this->GetWidth();
    int hauteur = this->GetHeight();
    int j, i, x, y;

    if(h){
        for(int ligne=0; ligne<hauteur/2; ligne++){
            for(int colonne=0; colonne<largeur; colonne++){
                i = (ligne*largeur+colonne)*3;
                y = (hauteur-ligne-1);
                j = (y*largeur+colonne)*3;

                sauvR = data[i];
                sauvV = data[i+1];
                sauvB = data[i+2];

                data[i] = data[j];
                data[i+1] = data[j+1];
                data[i+2] = data[j+2];

                data[j] = sauvR;
                data[j+1] = sauvV;
                data[j+2] = sauvB;
            }

        }
    }
    else{
        for(int ligne=0; ligne<hauteur; ligne++){
            for(int colonne=0; colonne<largeur/2; colonne++){
                i = (ligne*largeur+colonne)*3;
                x = (largeur-colonne-1);
                j = (ligne*largeur+x)*3;

                sauvR = data[i];
                sauvV = data[i+1];
                sauvB = data[i+2];

                data[i] = data[j];
                data[i+1] = data[j+1];
                data[i+2] = data[j+2];

                data[j] = sauvR;
                data[j+1] = sauvV;
                data[j+2] = sauvB;
            }

        }
    }

}

MyImage MyImage::Rotate(){
    unsigned char* data = this->GetData();
    int largeur = this->GetWidth();
    int hauteur = this->GetHeight();
    unsigned char* rotation = (unsigned char*) malloc(largeur*hauteur*3);

    int i,x,j;

    for(int ligne=0; ligne<hauteur; ligne++){
        for(int colonne=0; colonne<largeur; colonne++){
            i = (ligne*largeur+colonne)*3;
            x =  hauteur-1-ligne;
            j = (colonne*hauteur+x)*3;

            rotation[j] = data[i];
            rotation[j+1] = data[i+1];
            rotation[j+2] = data[i+2];


        }
    }

    MyImage res = MyImage(hauteur, largeur);
    res.SetData(rotation);
    return res;
}

void MyImage::Posterize(){
    unsigned char* data = GetData();
    int largeur = this->GetWidth();
    int hauteur = this->GetHeight();

   for(int i=0; i<(hauteur*largeur*3); i++){
        if(data[i]<127){
            data[i]=0;
        }
        else{
            data[i]=255;
        }
   }

}

/*int MyImage::NbColor(){
    unsigned char* data = GetData();
    int largeur = this->GetWidth();
    int hauteur = this->GetHeight();
    vector<unsigned char> countcolor;

    countcolor.push_back(data[0]);
    countcolor.push_back(data[1]);
    countcolor.push_back(data[2]);

    for(int i=0; i<(hauteur*largeur*3); i++){
        int j=0;
        while(data[i]!=countcolor[j] && data[i+1]!=countcolor[j+1] && data[i+2]!=countcolor[j]){
            j++;
        }
        if(data[i]!=countcolor[j]){
            countcolor.push_back(data[i]);
            countcolor.push_back(data[i+1]);
            countcolor.push_back(data[i+2]);
        }
    }
    return countcolor.size();
}*/
