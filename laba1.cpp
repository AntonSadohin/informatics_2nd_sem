#include <iostream>
#include <math.h>
using namespace std;
struct polygon
{
  double modul_side;
  int amount_angles;
  double P;
  double S;
};
void input(int amount_polygons,polygon *p_polygon) {
  for(int i=0;i<amount_polygons;i++)
    {
      cout<<"Polygon  "<<i+1<<"\n";
      cout<<"Enter modul of side";
      cin>>p_polygon[i].modul_side;
      cout<<"Amount of angles";
      cin>>p_polygon[i].amount_angles;
    }
}
void output(int amount_polygons,polygon *p_polygon)
{
    for(int i=0;i<amount_polygons;++i)
    {
        cout<<"\n"<<"Polygon:"<<i+1<<"\n";
        cout <<"Modul side="<<p_polygon[i].modul_side<<"\n";
        cout <<"Amount angles="<<p_polygon[i].amount_angles<<"\n";
        cout <<"Perimeter of polygon="<<p_polygon[i].P<<"\n";
        cout<<"Area of polygon="<<p_polygon[i].S<<"\n";
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
      if(p_polygon[i].S==max_square)
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

int main(){
    int amount_polygons;
    cout<<"Enter amount of polygons";
    cin>>amount_polygons;
    polygon *p_polygon=new polygon[amount_polygons];
    input(amount_polygons,p_polygon);
    P_S(amount_polygons,p_polygon);
    output(amount_polygons,p_polygon);
    max_square(amount_polygons,p_polygon);
    max_perimetr(amount_polygons,p_polygon);
}