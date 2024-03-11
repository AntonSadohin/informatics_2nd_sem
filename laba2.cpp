#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
class Vehicle{
private:


public:
char name[30];
int amount_wheels;
double speed;
double fuel_consumption;
double mileage;
double volume_tank;
double power;
Vehicle( ){
  {
  cout<<"Vehicle created"<<"\n";
  }
}
~Vehicle( )
{
  cout<<"Vehicle deleted"<<"\n";
}

};
void input(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
  {
    cout << "Enter the name of the vehicle: ";
    cin >> vehicles[i].name;
    cout << "Enter the amount of wheels: ";
    cin >> vehicles[i].amount_wheels;
    cout << "Enter the mileage: ";
    cin >> vehicles[i].mileage;
    cout << "Enter the volume of the tank: ";
    cin >> vehicles[i].volume_tank;
    cout << "Enter the power: ";
    cin >> vehicles[i].power;
  }
}
void determination_speed(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      vehicles[i].speed=sqrt(vehicles[i].power)*((70/vehicles[i].amount_wheels)-2.5);
    }
}
void determination_fuel_consumption(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      vehicles[i].fuel_consumption=(pow(vehicles[i].power,1/3)+sqrt(vehicles[i].power))-6.25;
    }
}
void output(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      cout<<vehicles[i].name<<": "<<vehicles[i].amount_wheels<<"wheels"<<","<<vehicles[i].power<<"horsepower"<<"/"<<vehicles[i].speed<<"km/h"<<"/"<<vehicles[i].fuel_consumption<<"l/100km"<<"\n";
    }
}
void Determination_track(int lenght_of_the_track,Vehicle *vehicles,int amount_vehicles)
{
  double time_of_the_race[amount_vehicles];
  int number_of_refuelings[amount_vehicles];
  char name_v[amount_vehicles][30];
  double refuelings_double[amount_vehicles];
  for(int i=0;i<amount_vehicles;i++)
    {
      refuelings_double[i]=(((lenght_of_the_track/100)*vehicles[i].fuel_consumption)/vehicles[i].volume_tank);
      number_of_refuelings[i]=(int)refuelings_double[i];
    }
  for(int i=0;i<amount_vehicles;i++)
    {
      time_of_the_race[i]=lenght_of_the_track/vehicles[i].speed;
    }
    for(int i=0;i<amount_vehicles;++i)
       {
        strcpy(name_v[i],vehicles[i].name);
       }
  for(int i=0;i<amount_vehicles;i++)
    {
      for(int j=0;j<amount_vehicles-1;++j)
      {
        
          if(time_of_the_race[j]>time_of_the_race[j+1])
        {
          double temp=time_of_the_race[j];
          time_of_the_race[j]=time_of_the_race[j+1];
          time_of_the_race[j+1]=temp;
          int temp_refuelings=number_of_refuelings[j];
          number_of_refuelings[j]=number_of_refuelings[j+1];
          number_of_refuelings[j+1]=temp_refuelings;
          char temp_name[30];
          strcpy(temp_name,name_v[j]);
          strcpy(name_v[j],name_v[j+1]);
          strcpy(name_v[j+1],temp_name);
        }
        if(time_of_the_race[j]==time_of_the_race[j+1])
        {
          if(number_of_refuelings[j]>number_of_refuelings[j+1])
          {
            int temp=time_of_the_race[j];
            time_of_the_race[j]=time_of_the_race[j+1];
            time_of_the_race[j+1]=temp;
            int temp_refuelings=number_of_refuelings[j];
            number_of_refuelings[j]=number_of_refuelings[j+1];
            number_of_refuelings[j+1]=temp_refuelings;
            char temp_name[30];
            strcpy(temp_name,name_v[j]);
            strcpy(name_v[j],name_v[j+1]);
            strcpy(name_v[j+1],temp_name);
          }
        }
      }
    }
  cout<<"Determination complete!\n";
  for(int i=0;i<amount_vehicles;i++)
  {
    cout<<"VEHICLE: "<<name_v[i]<<"\n";
    cout<<"TIME OF THE RACE:"<<time_of_the_race[i]<<" hours\n";
    cout<<"Amount_refuelings: "<<number_of_refuelings[i]<<"\n";
    cout<<"\n";
  }
}
void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<"\n";
    }
}
void menu(int amount_vehicles,Vehicle *vehicles,int lenght_of_the_track)
{
  int choice;
  int exit_menu=0;
  int determination_complete=0;
  int car=0;
  
  while(exit_menu==0)
    {
      cout<<"1.Input some vehicles"<<"\n";
      cout<<"2.Check information about vehicles"<<"\n";
      cout<<"3.Enter lenght of the track"<<"\n";;
      cout<<"4.Determine the race"<<"\n";
      cout<<"5.Exit"<<"\n";
  cin>>choice;
  switch(choice) 
  {
    case 1:
      new_page();
      input(amount_vehicles,vehicles);
      determination_speed(amount_vehicles,vehicles);
      determination_fuel_consumption(amount_vehicles,vehicles);
      car++;
      break;
    case 2:
      new_page();
      if(car==0)
      {
        cout<<"Firstly input vehicle!\n";
        break;
      }
      output(amount_vehicles,vehicles);
      break;
    case 3:
      new_page();
      if(car==0)
      {
        cout<<"Firstly input vehicle!\n";
        break;
      }
      cout<<"Enter the lenght of the track: ";
      cin>>lenght_of_the_track;
      
      break;
    case 4:
      if(lenght_of_the_track==0)
      {
        cout<<"ENTER LENGHT OF THE TRACK , before determinate track!"<<"\n";
        break;
      }
      new_page();
      Determination_track(lenght_of_the_track,vehicles,amount_vehicles);
      determination_complete++;
      break;
    
    case 5:
      new_page();
      cout<<"Are you sure to exit? 1-yes 0-bo\n";
      cin>>exit_menu;
      if(exit_menu==1)
      {
        return;
      }
      break;
  }
  }
}
int main() {
  int amount_vehicles;
  int lenght_of_the_track=0;
  cout << "How many vehicles do you want to create?";
  cin >> amount_vehicles;
  Vehicle *vehicles=new Vehicle[amount_vehicles];
  menu(amount_vehicles,vehicles,lenght_of_the_track);
  delete [] vehicles;
  return 0;

}