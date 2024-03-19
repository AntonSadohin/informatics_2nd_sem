#include <iostream>
#include <math.h>
using namespace std;
struct polygon
{
  double lenght_side;
  int amount_angles;
  double P;
  double S;
  double x1;
  double y1;
};
void ignoreLine()
{
    cin.clear();
    cin.ignore();
}
void input_coordinates(int current,int amount_polygons,polygon *p_polygon)
 {
     for(int i=amount_polygons-1;i<amount_polygons;++i)
     {
        double Radius = p_polygon[i].lenght_side/(2*sin(M_PI/p_polygon[i].amount_angles));
        cout<<"\n"<<"Polygon number:"<<i+1<<"\n";
        cout<<"Enter coordinate x of the farest polygon vertex";
        cin>>p_polygon[amount_polygons-1].x1;
        while (cin.fail()) {
            ignoreLine();
            cout << "You have entered a character, please enter a number" << endl;
            cin >> p_polygon[amount_polygons-1].x1;
        }
        double y=sqrt(pow(Radius,2)-pow(p_polygon[amount_polygons-1].x1,2));
        cout<<"Enter coordinate y of the farest polygon vertex"<<"  ";
        cout<<"Y must be more than  "<<y<<"\n";
        cin>>p_polygon[amount_polygons-1].y1;
       while (cin.fail()) {
           ignoreLine();
           cout << "You have entered a character, please enter a number" << endl;
           cin >> p_polygon[amount_polygons-1].y1;
       }
       if((sqrt(pow(p_polygon[i].x1, 2) + pow(p_polygon[i].y1, 2)) - Radius) < 0)
         {
             cout<<"Error coordinate\n";
             input_coordinates(current,amount_polygons,p_polygon);
         }
     }
 }
void input(int current,int &amount_polygons,polygon *&p_polygon) {
  amount_polygons++;
  polygon *new_p_polygon = new polygon[amount_polygons];
  for(int i=0;i<amount_polygons-1;++i)
    {
      new_p_polygon[i]=p_polygon[i];
    }
  delete p_polygon;
  p_polygon=new_p_polygon;
  for(int i=amount_polygons-1;i<amount_polygons;i++)
    {
      cout<<"Polygon  "<<i+1<<"\n";
      cout<<"Enter lenght of side";
      do{
      cin>>p_polygon[i].lenght_side;
        while (cin.fail()) {
          ignoreLine();
          cout << "You have entered a character, please enter a number" << endl;
          cin >> p_polygon[i].lenght_side;
        }
      if(p_polygon[i].lenght_side<0)
      {
        cout<<"Error lenght of side, side must be more than 0, Try again\n";
      }
      }
      while(p_polygon[i].lenght_side<0);
      cout<<"Amount of angles";
      do{
      cin>>p_polygon[i].amount_angles;
        while (cin.fail()) {
          ignoreLine();
          cout << "You have entered a character, please enter a number" << endl;
          cin >> p_polygon[i].amount_angles;
        }
      if(p_polygon[i].amount_angles<3)
      {
        cout<<"Amount of angles must be more than 2, Try again";
      }
      }
      while(p_polygon[i].amount_angles<3);
      input_coordinates(current,amount_polygons,p_polygon);
    }
}
void output(int current,int amount_polygons,polygon *p_polygon)
{
  if(amount_polygons==0)
  {
    cout<<"No polygons\n";
  }
    for(int i=0;i<amount_polygons;++i)
    {
      cout<<"\n"<<"Polygon:"<<i+1<<"\n";
      cout <<"Lenght of side="<<p_polygon[i].lenght_side<<"\n";
      cout <<"Amount angles="<<p_polygon[i].amount_angles<<"\n";
      cout <<"Perimeter of polygon="<<p_polygon[i].P<<"\n";
      cout<<"Area of polygon="<<p_polygon[i].S<<"\n";
      double R;
      double dxR;
      double dyR;
      double xR;
      double yR;
      double k;
      double modx1=fabs(p_polygon[i].x1);
      double mody1=fabs(p_polygon[i].y1);
      int flagX=1;
      int flagY=1;
      if(p_polygon[i].x1<0){flagX=-1;}
      if(p_polygon[i].y1<0){flagY=-1;}
      R = p_polygon[i].lenght_side/(2*sin(M_PI/p_polygon[i].amount_angles));
      k=atan((mody1)/(modx1));
      dxR=R*cos(k);
      dyR=R*sin(k);
      xR=modx1-dxR;
      yR=mody1-dyR;
      double angle=2*M_PI/p_polygon[i].amount_angles;
      cout<<"Coordinates of polygon: "<<i+1<<"\n";
      cout<<"Vertex 1: "<<p_polygon[i].x1<<";"<<p_polygon[i].y1<<"\n";
      for(int j=1;j<p_polygon[i].amount_angles;++j)
      {
         if(flagX != flagY){
            double NewAngle=((atan(mody1/modx1))-(j)*angle);
            double Next_X=xR+R*cos(NewAngle);
            double Next_Y=yR+R*sin(NewAngle);
            cout<<"Vertex"<<1+j<<": " <<Next_X*flagX<<";"<<Next_Y*flagY<<"\n";
          }else{
            double NewAngle=atan(mody1/modx1)+(j)*angle;
            double Next_X=xR+R*cos(NewAngle);
            double Next_Y=yR+R*sin(NewAngle);
            cout<<"Vertex"<<1+j<<": " <<Next_X*flagX<<";"<<Next_Y*flagY<<"\n";
          }

        }
    }
}
void P(int amount_polygons,polygon *p_polygon)
{
  for(int i=0;i<amount_polygons;++i)
    {
      p_polygon[i].P=p_polygon[i].lenght_side*p_polygon[i].amount_angles;
    }
}
void S(int amount_polygons,polygon* p_polygon){
    for(int i=0;i<amount_polygons;++i)
      {
        if(p_polygon[i].amount_angles==3)
        {
          p_polygon[i].S=sqrt(3)/4*pow(p_polygon[i].lenght_side,2);
        }
        if(p_polygon[i].amount_angles==4)
        {
          p_polygon[i].S=pow(p_polygon[i].lenght_side,2);
        }
        if(p_polygon[i].amount_angles>4)
        {
p_polygon[i].S=p_polygon[i].amount_angles*pow(p_polygon[i].lenght_side,2)/(4*tan(M_PI/p_polygon[i].amount_angles));
        }
      }
}
void max_p_max_s(int amount_polygons,polygon *p_polygon,int p)
{
  if(amount_polygons==0)
  {
    cout<<"No polygons\n";
  }
  double max_value=0;
  int max_value_index[amount_polygons];
  int amount_max=0;
  if(p==1)
  {
    for(int i=0; i<amount_polygons;++i)
      {
        if(p_polygon[i].P-max_value>0)
        {
          max_value=p_polygon[i].P;
        }
      }
    for(int i=0;i<amount_polygons;++i)
      {
        if(p_polygon[i].P==max_value)
        {
          max_value_index[amount_max]=i;
          amount_max++;
        }
      }
    if(amount_max==1)
    {
      cout<<"Polygon with max perimeter is polygon number "<<max_value_index[0]+1<<"\n";
    }
    if(amount_max>1)
    {
      cout<<"Polygons with max perimeter:\n";
        for(int i=0;i<amount_max;++i)
        {
          cout<<max_value_index[i]+1<<"\n";
        }
    }
  }
  if(p==0)
  {
    for(int i=0; i<amount_polygons;++i)
      {
        if(p_polygon[i].P-max_value>0)
        {
          max_value=p_polygon[i].S;
        }
      }
    for(int i=0;i<amount_polygons;++i)
      {
        if(p_polygon[i].S==max_value)
        {
          max_value_index[amount_max]=i;
          amount_max++;
        }
      }
    if(amount_max==1)
    {
      cout<<"Polygon with max square is polygon number "<<max_value_index[0]+1<<"\n";
    }
    if(amount_max>1)
    {
      cout<<"Polygons with max square:\n";
        for(int i=0;i<amount_max;++i)
        {
          cout<<max_value_index[i]+1<<"\n";
        }
    }
  }
}
void delete_polygon(int& amount_polygons, polygon*& p_polygon)
{
  if(amount_polygons==0)
  {
    cout<<"No polygons\n";
    return;
  }
  int number_polygon;
  cout << "Enter number of polygon: ";
  cin >> number_polygon;
  while (cin.fail()) {
    ignoreLine();
    cout << "You have entered a character, please enter a number" << endl;
    cin >> number_polygon;
  }
  if (number_polygon < 1 || number_polygon > amount_polygons)
  {
    cout << "No polygon with this number\n";
    return;
  }

  polygon* new_p_polygon = new polygon[amount_polygons - 1];

  for (int i = 0; i < number_polygon - 1; ++i)
  {
    new_p_polygon[i] = p_polygon[i];
  }

  for (int i = number_polygon; i < amount_polygons; ++i)
  {
    new_p_polygon[i - 1] = p_polygon[i];
  }

  delete[] p_polygon;
  p_polygon = new_p_polygon;
  amount_polygons--;
}
void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<"\n";
    }
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
    while (cin.fail()) {
      ignoreLine();
      cout << "You have entered a character, please enter a number" << endl;
      cin >> choice_submenu;
    }
  int p=1;
  switch(choice_submenu)
    {
  
      case 1:
      new_page();
      P(amount_polygons,p_polygon);
      S(amount_polygons,p_polygon);
      p=0;
      max_p_max_s(amount_polygons,p_polygon,p);
      break;

      case 2:
      new_page();
      P(amount_polygons,p_polygon);
      S(amount_polygons,p_polygon);
      p=1;
      max_p_max_s(amount_polygons,p_polygon,p);
      break;

      case 3:
      new_page();
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
    while (cin.fail()) {
      ignoreLine();
      cout << "You have entered a character, please enter a number" << endl;
      cin >> choice;;
    }
  switch(choice)
    {

      case 1:
      new_page();
      current++;
      input(current,amount_polygons,p_polygon);
      break;

      case 2:
      new_page();
      P(amount_polygons,p_polygon);
      S(amount_polygons,p_polygon);
      output(current,amount_polygons,p_polygon);
      break;

      case 3:
      new_page();
      delete_polygon(amount_polygons,p_polygon);
      current--;
      break;

      case 4:
      new_page();
      submenu(amount_polygons,p_polygon);
      break;

      case 5:
      new_page();
      cout<<"Are you sure to exit? If yes press 1 if no press 2\n";
      int choice_exit;
      cin>>choice_exit;
      if(choice_exit==1)
      {
        exit++;
      }
      if(choice_exit==2)
      {
        new_page();
        menu(amount_polygons,p_polygon);
      }
      break;
      default:
      cout<<"Error\n";

    }
  }
}
int main(){
    int amount_polygons=0;
    polygon *p_polygon=NULL;
    menu(amount_polygons,p_polygon);
    delete[] p_polygon;
}
