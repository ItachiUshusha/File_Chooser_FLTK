#include <FL/Fl.H>
#include "g.h"
#include <fstream>
#include <iostream>
#include <cmath>
static int n;
static double x [10000]; double y [10000];
static char buff[100];


double dist(double x1, double y_1, double x2, double y2)
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y_1) * (y2 - y_1)));
}


double perimeter()
{
    double p = 0;
    for (int i = 0; i < n-1; i++){
        p += dist(x[i],y[i],x[i+1],y[i+1]);
    }
    p += dist(x[n-1],y[n-1],x[0],y[0]);
    return p;
}


double area()
{
    double s = 0, s2=0;
    for (int i = 0; i < n-1; i++)
    {
        s += x[i]*y[i+1];
        s2 += x[i+1]*y[i];
    }
    s += x[n-1]*y[0];
    s2 += x[0]*y[n-1];
    return std::abs((s-s2)/2);
}


double diametr()
{
    double res = 0;
    for (int i = 0; i < n-1; i++)
    {
        for(int j = i+1; j < n; j++)
        {
           if(dist(x[i],y[i],x[j],y[j]) > res) res = dist(x[i],y[i],x[j],y[j]);
        }
    }
    return res;
}


Fl_Input *P=(Fl_Input *)0;


static void cb_P(Fl_Input*, void*)
{
    sprintf(buff,"%lf", perimeter());
    P->value(buff) ;
}


Fl_Input *S=(Fl_Input *)0;


static void cb_S(Fl_Input*, void*)
{
    sprintf(buff,"%lf", area());
    S->value(buff);
}


Fl_Input *D=(Fl_Input *)0;


static void cb_D(Fl_Input*, void*)
{
    sprintf(buff,"%lf", diametr());
    D->value(buff);
}


// функция отображающая Filechooser
void fileChooserCallback(Fl_Widget* button, void* userdata)
{
    Fl_File_Chooser chooser(".", "*.txt", Fl_File_Chooser::SINGLE, "Выберите файл");
    chooser.show();

    while(chooser.shown()){
        Fl::wait();
    }

    if (chooser.value() != NULL) {
        std::ifstream fin;
        std::string Filename = chooser.value();
        fin.open(Filename.c_str(), std::ifstream::in);

        if (!fin.is_open()) fl_alert("File did not open");
        else {
            std::cout<<"File opened succesfull"<<"\n";

            fin >> n;

            for (int i = 0; i < n; i++)
            {
                fin >> x[i] >> y[i];
            }

            cb_P(NULL,NULL); cb_S(NULL,NULL); cb_D(NULL,NULL);
        };
    }
}


int main(int argc, char *argv[])
{
    Fl_Window window(355, 270, "Программа");

    Fl_Button button(130, 10, 100, 40, "Выбрать файл");
    button.callback(fileChooserCallback);

    P = new Fl_Input(125, 91, 135, 24, "\320\237\320\265\321\200\320\270\320\274\320\265\321\202\321\200");
    P->callback((Fl_Callback*)cb_P);

    S = new Fl_Input(125, 126, 135, 24, "\320\237\320\273\320\276\321\211\320\260\320\264\321\214");
    S->callback((Fl_Callback*)cb_S);

    D = new Fl_Input(125, 56, 135, 24, "\320\224\320\270\320\260\320\274\320\265\321\202\321\200");
    D->callback((Fl_Callback*)cb_D);

    window.show();
    return Fl::run();
}