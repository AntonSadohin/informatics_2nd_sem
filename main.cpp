#include <iostream>
#include <math.h>
#define PI 3.14159265358979323846
using namespace std;
struct polygon
{
  double modul_side;
  int amount_angles;
  double P;
  double S;
  double x1;
  double y1;
  double x[100];
  double y[100];
};
void input_coordinates(int current,int amount_polygons,polygon *p_polygon)
 {
     for(int i=current-1;i<current;++i)
     {
        cout<<"\n"<<"Polygon number:"<<i+1<<"\n";
        cout<<"Enter coordinate x of the farest polygon vertex";
        cin>>p_polygon[current-1].x1;
        cout<<"Enter coordinate y of the farest polygon vertex";
        cin>>p_polygon[current-1].y1;
     }
 }
 void calculation_coordinates(int current,int amount_polygons,polygon *p_polygon)
 {
     double R;
     double dxR;
     double dyR;
     double xR;
     double yR;
     double k;
     R = p_polygon[0].modul_side/(2*sin(M_PI/p_polygon[0].amount_angles));
     k=atan(p_polygon[current-1].y1/p_polygon[current-1].x1);
     dxR=R*cos(k);
     dyR=R*sin(k);
     xR=p_polygon[current-1].x1-dxR;
     yR=p_polygon[current-1].y1-dyR;
     cout<<xR<<"\n";
     cout<<yR<<"\n";
     cout<<R<<"\n";
     double angle=2*M_PI/p_polygon[0].amount_angles;
     for(int i=1;i<p_polygon[0].amount_angles;++i)
     {
         double NewAngle=2*M_PI-i*angle;
         double Next_X=xR-R*cos(NewAngle);
         double Next_Y=yR-R*sin(NewAngle);
         cout<<"Coordinates of polygon:\n";
         cout<<p_polygon[current-1].x1;
         cout<<p_polygon[current-1].y1;
         cout<<1+i<<"Vertex X coordinate:"<<Next_X<<"\n";
         cout<<1+i<<"Vertex Y coordinate:"<<Next_Y<<"\n";
     }



 }
void input(int current,int amount_polygons,polygon *p_polygon) {
  for(int i=current-1;i<current;i++)
    {
      cout<<"Polygon  "<<i+1<<"\n";
      cout<<"Enter modul of side";
      cin>>p_polygon[i].modul_side;
      cout<<"Amount of angles";
      cin>>p_polygon[i].amount_angles;
      input_coordinates(current,amount_polygons,p_polygon);
    }
}
void output(int current,int amount_polygons,polygon *p_polygon)
{
    for(int i=0;i<current;++i)
    {
        cout<<"\n"<<"Polygon:"<<i+1<<"\n";
        cout <<"Modul side="<<p_polygon[i].modul_side<<"\n";
        cout <<"Amount angles="<<p_polygon[i].amount_angles<<"\n";
        cout <<"Perimeter of polygon="<<p_polygon[i].P<<"\n";
        cout<<"Area of polygon="<<p_polygon[i].S<<"\n";
        calculation_coordinates(current,amount_polygons,p_polygon);
    }
}
void P_S(int amount_polygons,polygon* p_polygon){
    for(int i=0;i<amount_polygons;++i)
      {
        if(p_polygon[i].amount_angles==3)
        {
          p_polygon[i].P=3*p_polygon[i].modul_side;
          p_polygon[i].S=sqrt(3)/4*pow(p_polygon[i].modul_side,2);
        }
        if(p_polygon[i].amount_angles==4)
        {
          p_polygon[i].P=4*p_polygon[i].modul_side;
          p_polygon[i].S=pow(p_polygon[i].modul_side,2);
        }
        if(p_polygon[i].amount_angles>4)
        {
          p_polygon[i].P=p_polygon[i].amount_angles*p_polygon[i].modul_side;
          p_polygon[i].S=p_polygon[i].amount_angles*pow(p_polygon[i].modul_side,2)/(4*tan(M_PI/p_polygon[i].amount_angles));
        }
      }
}
void max_square(int amount_polygons,polygon* p_polygon)
{
  int number_max_s=0;
  double max_square=p_polygon[0].S;
  int max_square_polygons=0;
  int array_number_max_square[amount_polygons];
  for(int i=1;i<amount_polygons;++i)
    {
      if(p_polygon[i].S>p_polygon[number_max_s].S)
      {
        number_max_s=i;
        max_square=p_polygon[i].S;
      }
    }
  for(int i=0;i<amount_polygons;++i)
    {
      if((p_polygon[i].S==max_square)&&(amount_polygons!=0))
      {
        max_square_polygons++;
        array_number_max_square[i]=i+1;
      }
    }
  if(max_square_polygons==1)
  {
    cout<<"Polygon with max square is polygon number:"<<number_max_s+1;
  }
  if(max_square_polygons>1)
  {
    cout<<"Polygons with max square:\n";
    for(int i=0;i<max_square_polygons;++i)
      {
        cout<<"Polygon number:"<<array_number_max_square[i]<<"\n";
      }
  }
  cout<<"\n";
}
void max_perimetr(int amount_polygons,polygon* p_polygon)
{
  int number_max_p=0;
  double max_perimeter=p_polygon[0].P;
  int max_perimeter_polygons=0;
  int array_number_max_perimeter[amount_polygons];
  for(int i=1;i<amount_polygons;++i)
    {
      if(p_polygon[i].P>p_polygon[number_max_p].P)
      {
        number_max_p=i;
        max_perimeter=p_polygon[i].P;
      }
    }
  for(int i=0;i<amount_polygons;++i)
    {
      if(p_polygon[i].P==max_perimeter)
      {
        max_perimeter_polygons++;
        array_number_max_perimeter[i]=i+1;
      }
    }
  if(max_perimeter_polygons==1)
  {
    cout<<"Polygon with max perimeter is polygon number:"<<number_max_p+1;
  }
  if(max_perimeter_polygons>1)
  {
    cout<<"Polygons with max perimeter:\n";
    for(int i=0;i<max_perimeter_polygons;++i)
      {
        cout<<"Polygon number:"<<array_number_max_perimeter[i]<<"\n";
      }
  }
  cout<<"\n";
}
 void output_coordinates(int amount_polygons,polygon *p_polygon)
 {
     for(int i=0;i<amount_polygons;++i)
     {
        cout<<"\n"<<"Polygon number:"<<i+1<<"\n";
        cout<<"X=";
        cout<<p_polygon[i].x1<<"\n";
        cout<<"Y=";
        cout<<p_polygon[i].y1<<"\n";
     }
 }
void delete_polygon(int amount_polygons,polygon *p_polygon)
{
  int number_polygon;
  cout<<"Enter number of polygon";
  cin>>number_polygon;
  for(int i=number_polygon-1;i<amount_polygons;++i)
    {
      p_polygon[i]=p_polygon[i+1];
    }
  amount_polygons--;
}
void submenu(int amount_polygons,polygon *p_polygon)
{
  int exit_sub=0;
  while(exit_sub==0)
  {
  int choice_submenu;
  cout<<"1.Determine polygon with max square\n";
  cout<<"2.Determine polygon with max perimeter\n";
  cout<<"3.Return to previous menu\n";
  cin>>choice_submenu;
  switch(choice_submenu)
    {
      case 1:
      P_S(amount_polygons,p_polygon);
      max_square(amount_polygons,p_polygon);
      break;

      case 2:
      P_S(amount_polygons,p_polygon);
      max_perimetr(amount_polygons,p_polygon);
      break;

      case 3:
      exit_sub++;
      break;

      default:
      cout<<"Error";

    }
  }
}
void menu(int amount_polygons,polygon *p_polygon)
{
  int exit=0;
  int current=0;
  while(exit==0)
  {
  int choice;
  cout<<"MENU\n";
  cout<<"1.Input new polygon\n";
  cout<<"2.Output information about all polygons\n";
  cout<<"3.Delete polygon\n";
  cout<<"4.Submenu max square and max perimetr\n";
  cout<<"5.Exit\n";
  cin>>choice;
  switch(choice)
    {

      case 1:
      current++;
      input(current,amount_polygons,p_polygon);
      break;

      case 2:
      P_S(amount_polygons,p_polygon);
      output(current,amount_polygons,p_polygon);
      break;

      case 3:
      delete_polygon(amount_polygons,p_polygon);
      current--;
      break;

      case 4:
      submenu(amount_polygons,p_polygon);
      break;

      case 5:
      cout<<"Are you sure to exit? If yes press 1 if no press 2\n";
      int choice_exit;
      cin>>choice_exit;
      if(choice_exit==1)
      {
        exit++;
      }
      if(choice_exit==2)
      {
        menu(amount_polygons,p_polygon);
      }
      break;
      default:
      cout<<"Error\n";

    }
  }
}

int main(){
    int amount_polygons;
    cout<<"Enter amount of polygons";
    cin>>amount_polygons;
    polygon *p_polygon=new polygon[amount_polygons];
    menu(amount_polygons,p_polygon);
}
