#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
class Vehicle{
private:
string carname;
int amount_wheels;
double mileage;
double volume_tank;
double power;
double travel_time;
double speed;
double fuel_consumption;
public:
Vehicle(int amount_vehicles,Vehicle* vehicles);
void Set_name(string carname) {this->carname=carname;}
string Get_name() {return carname;}
void Set_amount_wheels(int amount_wheels) {this->amount_wheels=amount_wheels;}
int Get_amount_wheels() { return amount_wheels;}
void Set_mileage(double mileage) {this->mileage=mileage;}
double Get_mileage() {return mileage;}
void Set_volume_tank(double volume_tank) {this->volume_tank=volume_tank;}
double Get_volume_tank(){ return volume_tank;}
void Set_power(double power) {this->power=power;}
double Get_power(){ return power;}
void Set_travel_time(double travel_time) {this->travel_time=travel_time;}
double Get_travel_time() {return travel_time;}
void determination_speed(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      vehicles[i].speed=fabs(sqrt(vehicles[i].power)*((70/(double)vehicles[i].amount_wheels)-2.5));
    }
}
friend void ShowSpeed(int amount_vehicles,Vehicle *vehicles,int i)
{
  cout<<"Speed:";
  cout<<vehicles[i].speed;
  cout<<"\n";
}
double Get_speed() { return speed; }
void determination_fuel_consumption(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      vehicles[i].fuel_consumption=fabs(((pow(vehicles[i].power,1/3)+sqrt(vehicles[i].power))-6.25));
    }
}
double Get_fuel_consumption() { return fuel_consumption; }
friend void Showfuelcons(int amount_vehicles,Vehicle *vehicles,int i)
{
  cout<<"Fuel consumption:";
  cout<<vehicles[i].fuel_consumption;
  cout<<"\n";
}
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
int count_refueling(int lenght_of_the_track, int amount_vehicles, Vehicle *vehicles, int i){
      int number_of_refuelings[amount_vehicles];
      number_of_refuelings[i]=(int)(((lenght_of_the_track/100)*vehicles[i].Get_fuel_consumption())/vehicles[i].Get_volume_tank());
  return number_of_refuelings[i];
}
void PrintRaceResults(int amount_vehicles, string* name_v, double* time_of_the_race, int* num_refuelings) {
    cout << "Determination complete!\n";
    for (int i = 0; i < amount_vehicles; i++) {
        cout << "VEHICLE: " << name_v[i] << "\n";
        cout << "TIME OF THE RACE:" << (int)time_of_the_race[i] << " hours\n";
        cout << (int)((time_of_the_race[i] - (int)time_of_the_race[i]) * 60) << " min\n";
        cout << (int)(time_of_the_race[i] * 3600 - (int)(time_of_the_race[i]) * 3600 - (int)((time_of_the_race[i] - (int)time_of_the_race[i]) * 60) * 60) << " sec\n";
        cout << "Amount_refuelings: " << num_refuelings[i] << "\n";
        cout << "\n";
    }
}
void Determination_track(int lenght_of_the_track, Vehicle *vehicles, int amount_vehicles)
{
  int num_refuelings[amount_vehicles];
  for(int i=0;i<amount_vehicles;i++)
    {
      num_refuelings[i] = count_refueling(lenght_of_the_track, amount_vehicles, vehicles, i);
    }
  double time_of_the_race[amount_vehicles];
  string name_v[amount_vehicles];
  for(int i=0;i<amount_vehicles;i++)
    {
      time_of_the_race[i]=lenght_of_the_track/vehicles[i].Get_speed();
    }
    for(int i=0;i<amount_vehicles;++i)
       {
        name_v[i]=vehicles[i].Get_name();
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
          int temp_refuelings=num_refuelings[j];
          num_refuelings[j]=num_refuelings[j+1];
          num_refuelings[j+1]=temp_refuelings;
          string temp_name;
          temp_name=name_v[j];
          name_v[j]=name_v[j+1];
          name_v[j+1]=temp_name;
        }
        if(time_of_the_race[j]==time_of_the_race[j+1])
        {
          if(num_refuelings[j]>num_refuelings[j+1])
          {
            double temp=time_of_the_race[j];
            time_of_the_race[j]=time_of_the_race[j+1];
            time_of_the_race[j+1]=temp;
            int temp_refuelings=num_refuelings[j];
            num_refuelings[j]=num_refuelings[j+1];
            num_refuelings[j+1]=temp_refuelings;
            string temp_name;
            temp_name=name_v[j];
            name_v[j]=name_v[j+1];
            name_v[j+1]=temp_name;
          }
        }
      }
    }
  PrintRaceResults(amount_vehicles, name_v, time_of_the_race, num_refuelings);
}
void ignoreLine()
{
    cin.clear();
    cin.ignore();
}
Vehicle::Vehicle(int amount_vehicles,Vehicle* vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
  {
    string carname;
    int amount_wheels;
    /*double mileage;*/
    double volume_tank;
    double power;
    /*double travel_time;*/
    cout<<"\nCAR №"<<i+1<<"\n";
    cout<<"Enter name of the car: ";
    cin>>carname;
    vehicles[i].Set_name(carname);
    cout<<"Enter amount of wheels: ";
    cin>>amount_wheels;
    while (cin.fail()) {
         ignoreLine();
         cout << "You have entered a character, please enter a number" << endl;
         cin >> amount_wheels;
     }
    do
    {
      if(amount_wheels<=0)
      {
        cout<<"Error! Try again(amount wheels>0)"<<"\n";
        cin >> amount_wheels;
      }
    } while(amount_wheels<=0);
    vehicles[i].Set_amount_wheels(amount_wheels);
    /*cout<<"Enter mileage: ";
    cin>>mileage;
    while (cin.fail()) {
       ignoreLine();
       cout << "You have entered a character, please enter a number" << endl;
       cin >> mileage;
    }*/
    /*vehicles[i].Set_mileage(mileage);*/
    cout<<"Enter volume of tank: ";
    cin>>volume_tank;
    while (cin.fail()) {
       ignoreLine();
       cout << "You have entered a character, please enter a number" << endl;
       cin >> volume_tank;
    }
   do
    {
      if(volume_tank<=0)
      {
        cout<<"Error! Try again(volume tank>0)"<<"\n";
        cin >> volume_tank;
      }
    } while(volume_tank<=0);
    vehicles[i].Set_volume_tank(volume_tank);
    cout<<"Enter power: ";
    cin>>power;
    while (cin.fail()) {
       ignoreLine();
       cout << "You have entered a character, please enter a number" << endl;
       cin >> power;
    }
    do
    {
      if(power<=0)
      {
        cout<<"Error! Try again(power>0)"<<"\n";
        cin >> power;
      }
    } while(power<=0);
    vehicles[i].Set_power(power);
    /*cout<<"Enter travel time (in hours): ";
    cin>>travel_time;
    while (cin.fail()) {
       ignoreLine();
       cout << "You have entered a character, please enter a number" << endl;
       cin >> travel_time;
    }
    vehicles[i].Set_travel_time(travel_time);
    cout<<"\n";*/

  }
}
void output(int amount_vehicles,Vehicle *vehicles)
{
  for(int i=0;i<amount_vehicles;i++)
    {
      cout<<"Name: "<<vehicles[i].Get_name()<<"\n";
      cout<<"Amount of wheels: "<<vehicles[i].Get_amount_wheels()<<"\n";
      /*cout<<"Mileage: "<<vehicles[i].Get_mileage()<<"\n";*/
      ShowSpeed(amount_vehicles, vehicles, i);
      cout<<"Volume of tank: "<<vehicles[i].Get_volume_tank()<<"\n";
      Showfuelcons(amount_vehicles, vehicles, i);
      cout<<"Power: "<<vehicles[i].Get_power()<<"\n";
      /*cout<<"Travel time: "<<vehicles[i].Get_travel_time()<<"\n\n";*/
    }
 }
void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<"\n";
    }
}
void menu(int amount_vehicles, Vehicle *vehicles, int lenght_of_the_track)
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
      while (cin.fail()) {
         ignoreLine();
         cout << "You have entered a character, please enter a number" << endl;
         cin >> amount_vehicles;
      }
  switch(choice) 
  {
    case 1:
      new_page();
      Vehicle(amount_vehicles,vehicles);
      for(int i=car-1;i<car;++i)
      {
      vehicles[i].determination_fuel_consumption(amount_vehicles, vehicles);
      vehicles[i].determination_speed(amount_vehicles, vehicles);
      }
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
      Determination_track(lenght_of_the_track, vehicles, amount_vehicles);
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
    default:
      cout<<"Error! Try again"<<"\n";
  }
  }
}
int main() {
  int amount_vehicles;
  int lenght_of_the_track=0;
  cout << "How many vehicles do you want to create?";
  cin >> amount_vehicles;
  while (cin.fail()) {
      ignoreLine();
      cout << "You have entered a character, please enter a number" << endl;
      cin >> amount_vehicles;
  }
  do
    {
      if(amount_vehicles<=0)
       {
          cout<<"Error! Try again(amount vehicles>0)"<<"\n";
          cin >> amount_vehicles;
      }
    } while(amount_vehicles<=0);
  Vehicle *vehicles=new Vehicle[amount_vehicles];
  menu(amount_vehicles, vehicles, lenght_of_the_track);
  delete [] vehicles;
  return 0;
}
