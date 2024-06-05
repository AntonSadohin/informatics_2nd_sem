#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;
void ignoreLine();
class Wheel{
protected:
public:
double mileage_wheel;
int status;
Wheel() {status=0;mileage_wheel=0;};
double get_mileage_wheel() {
  return mileage_wheel;
}
void check_status(double mileage_wheel) {
  if(status!=1){
    double k=rand()%50 +(mileage_wheel/100);
    if (k>45) {
        status = 1; // Повреждено
    }
}
}
};
class Engine{
protected:
double engine_consumption;
double power;
public:
double calculating_consumption(double power)
{ return fabs(pow(power, 1 / 3) + sqrt(power) - 6.25);}
};
class Fuel_system{
protected:
double Volume_tank;
double Current_volume;
public:
void calc_current_volume(double Volume_tank, double lenght_of_the_track,int num_ref,double engine_consumption)
{
  Current_volume= Volume_tank + num_ref * Volume_tank - lenght_of_the_track / 100 * engine_consumption;
}
};
class Vehicle: public Engine, public Fuel_system {
private:
string carname;
int amount_wheels;
double speed;
double mileage;
public:
int brokenwheels=0;
Wheel* wheels;
Vehicle(){};
Vehicle(string vehicle_name, int wheels1) {
    set_name(vehicle_name);
    set_amount_wheels(wheels1);
    wheels = new Wheel[wheels1];
    for (int i = 0; i < wheels1; i++) {
        wheels[i]=Wheel();
    }
    cout << "Enter the power of the car:\t";
    cin >> power;
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
    mileage = 0;
    cout << "Enter the Volume of the tank:";
    cin >> Volume_tank;
        while (cin.fail()) {
         ignoreLine();
         cout << "You have entered a character, please enter a number" << endl;
         cin >> Volume_tank;
          }
    do
      {
        if(Volume_tank<=0)
        {
          cout<<"Error! Try again(Volume_tank>0)"<<"\n";
          cin >> Volume_tank;
        }
      } while(Volume_tank<=0);
      Current_volume=Volume_tank;
      engine_consumption=calculating_consumption(power);
      determination_speed();
    }
    void determination_speed() {
        speed=abs((sqrt(power) * ((70 / (amount_wheels)) - 2.5))/pow(2,brokenwheels));
    }
    void set_name(string carname) {this->carname=carname;}
    string get_name() {return carname;}
    double get_speed(){return speed;}
    double get_eng_consumption(){return engine_consumption;}
    void set_amount_wheels(int amount_wheels) {this->amount_wheels=amount_wheels;}
    int get_amount_wheels() { return amount_wheels;}
    double get_vol_tank(){return Volume_tank;}
    void Set_mileage(double mileage) {this->mileage=mileage;}
    int count_refueling(double lenght_of_the_track, int amount_vehicles, Vehicle *vehicles, int i,double power){
        int number_of_refuelings[amount_vehicles];
        number_of_refuelings[i]=(int)(((lenght_of_the_track/100)*vehicles[i].get_eng_consumption())/vehicles[i].Volume_tank);
    return number_of_refuelings[i];
    }
void after_track(double mileage) {
    for (int i = 0; i < amount_wheels; i++) {
        wheels[i].check_status(mileage);
    }
}
        friend ostream& operator<<(std::ostream& os, const Vehicle& vehicle) {
            os << "Vehicle: " << vehicle.carname << "\n";
            os << "Number of wheels: " << vehicle.amount_wheels << "\n";
            os << "Mileage: " << vehicle.wheels->get_mileage_wheel() << "\n";
            os << "Wheel status:\n";
            for (int i = 0; i < vehicle.amount_wheels; i++) {
                os << "Wheel " << i + 1 << ": ";
                if (vehicle.wheels[i].status == 1){
                    os << "Broken\n";
                } else if (vehicle.wheels[i].status == 0) {
                    os << "Good condition\n";
                } else {
                }
            }
            os << "Volume tank: " << vehicle.Volume_tank << "\n";
            os << "Current volume: " << vehicle.Current_volume << "\n";
            os << "Engine consumption: " << vehicle.engine_consumption << "\n";
            os << "Speed: " << vehicle.speed << "\n\n";
            return os;
        }
friend void Determination_track(double lenght_of_the_track, Vehicle *vehicles, int amount_vehicles,double power)
{
  int num_refuelings[amount_vehicles];
  for(int i=0;i<amount_vehicles;i++)
    {
      num_refuelings[i] = vehicles[i].count_refueling(lenght_of_the_track, amount_vehicles, vehicles, i,power);
    }
  double time_of_the_race[amount_vehicles];
  string name_v[amount_vehicles];
  for(int i=0;i<amount_vehicles;i++)
    {
      time_of_the_race[i]=lenght_of_the_track/vehicles[i].get_speed();
    }
    for(int i=0;i<amount_vehicles;++i)
       {
        name_v[i]=vehicles[i].get_name();
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
  for(int i=0;i<amount_vehicles;i++)
    {
    vehicles[i].PrintRaceResults(amount_vehicles, name_v, time_of_the_race, num_refuelings,i);
    }
}
void PrintRaceResults(int amount_vehicles, string* name_v, double* time_of_the_race, int* num_refuelings,int i) {
    cout << "Determination complete!\n";
        cout << "VEHICLE:" << name_v[i] << "\n";
        cout << "TIME OF THE RACE:" << (int)time_of_the_race[i] << " hours\n";
        cout << (int)((time_of_the_race[i] - (int)time_of_the_race[i]) * 60) << " min\n";
        cout << (int)(time_of_the_race[i] * 3600 - (int)(time_of_the_race[i]) * 3600 - (int)((time_of_the_race[i] - (int)time_of_the_race[i]) * 60) * 60) << " sec\n";
        cout << "Amount_refuelings: " << num_refuelings[i] << "\n";
        cout << "\n";
}
};
void ignoreLine()
{
    cin.clear();
    cin.ignore();
}
void Wheel_mileage(Vehicle *vehicles, int amount_vehicles, double length_of_the_track) {
    for (int i = 0; i < amount_vehicles; i++) {
        for (int j = 0; j < vehicles[i].get_amount_wheels(); j++) {
            vehicles[i].wheels[j].mileage_wheel += length_of_the_track;
        }
    }
}
void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<"\n";
    }
}
void menu(int amount_vehicles, Vehicle *vehicles, double lenght_of_the_track,string vehicle_name,int amount_wheels,double power)
{
  int choice;
  double mil=0;
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
         cin >> choice;
          }
  switch(choice)
  {
    case 1:
      new_page();
      for(int i=0;i<amount_vehicles;++i)
      {
            string vehicle_name;
            int wheels;
            cout << "Enter vehicle name " << ": ";
            cin >> vehicle_name;
            cout << "Enter number of wheels for vehicle " << ": ";
            cin >> wheels;
            while (cin.fail()) {
               ignoreLine();
               cout << "You have entered a character, please enter a number" << endl;
               cin >> wheels;
                }
            do
              {
                if(wheels<=0)
                {
                  cout<<"Error! Try again(amount wheels>0)"<<"\n";
                  cin >> wheels;
                }
              } while(wheels<=0);
            vehicles[i] = Vehicle(vehicle_name, wheels);
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
      for(int i=0;i<amount_vehicles;++i)
        {
      cout<<vehicles[i];
        }
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
          Determination_track(lenght_of_the_track, vehicles, amount_vehicles, power);
          determination_complete++;
          Wheel_mileage(vehicles,amount_vehicles,lenght_of_the_track);
          mil=mil+lenght_of_the_track;
          for(int k=0;k<amount_vehicles;++k)
            {
              for(int j=0;j<vehicles[k].get_amount_wheels();++j)
                {
                  if(vehicles[k].wheels[j].status==0)
                  {
                    for(int i = 0; i < amount_vehicles; ++i) {
                        vehicles[i].after_track(mil);
                    }
                  }
                }
            }
          for(int i=0;i<amount_vehicles;++i)
            {
              vehicles[i].brokenwheels=0;
              for(int j=0;j<vehicles[i].get_amount_wheels();++j)
                {
                  if(vehicles[i].wheels[j].status==1)
                  {
                    vehicles[i].brokenwheels++;
                    vehicles[i].determination_speed();
                  }
                }
              vehicles[i].calc_current_volume(vehicles[i].get_vol_tank(),lenght_of_the_track,vehicles[i].count_refueling(lenght_of_the_track,amount_vehicles, vehicles, i, power), vehicles[i].get_eng_consumption());
            }
          break;

        case 5:
          new_page();
          cout<<"Are you sure to exit? 1-yes 0-no\n";
          cin>>exit_menu;
          if(exit_menu==1)
          {
            return;
          }
          break;
        default:
          cout<<"Please enter number (1-5)"<<"\n";
          }
    }
}
int main()
{
  srand(time(0));
  int amount_vehicles=0;
  double lenght_of_the_track = 0;
  string vehicle_name;
  int amount_wheels=0;
  double power=0;
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
  Vehicle* vehicles = new Vehicle[amount_vehicles];
  menu(amount_vehicles, vehicles, lenght_of_the_track, vehicle_name, amount_wheels, power);
  delete[] vehicles;
  return 0;
}
