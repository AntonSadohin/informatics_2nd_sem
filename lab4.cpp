#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <limits>
#define refueling_time 0.016
#define reWheel_time 0.004 
#define dt 0.0003
using namespace std;
int checkinput(int input_value)
{
    cin >> input_value;
    if (cin.fail() || input_value <= 0) {
        while (!(cin >> input_value) && input_value <= 0) {
            cout << "Uncorrect, try again\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return input_value;
}
class wheel {
  double current_mileage;
  int status;
public:
  void check_status(double mileage, double speed); 
  wheel() {status=0;current_mileage=0;};
virtual ~wheel(){};
  int get_status() { return status; }
  void set_status(int status) {
    this->status = status;
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
void calc_current_volume(double engine_consumption,double mileage)
{
  Current_volume=Volume_tank-((engine_consumption/100)*mileage);
}
};

class Vehicle: public Engine, public Fuel_system {
private:
string carname;
int amount_wheels;
double speed;
double mileage;
int brokenwheels=0;
double time;
int current_laps;
double current_mileage;
int amount_refuelings=0;
public:
vector<wheel> vec_wheels;
int stat_of_car;
double pits_time=0;
string get_carname(){return carname;}
void determination_speed() {
    speed=abs((sqrt(power) * ((70 / (amount_wheels)) - 2.5))*pow(0.75,brokenwheels));
}
void mileage_plus(){this->mileage+=speed*dt;}
void current_mileage_plus(){this->current_mileage+=(speed*dt);}
double get_current_mileage(){return current_mileage;};
double get_consumption(){return calculating_consumption(power);}
double get_mileage(){return mileage;};
double get_current_mil(){return current_mileage;}
double get_speed(){return speed;};
void set_time(double time){this->time=time;};
void output_time();
void calc_broken_wheels();
int get_broken_wheels(){return brokenwheels;};
int get_current_laps(){return current_laps;};
void plus_current_laps(){this->current_laps++;}
double get_current_volume(){return Current_volume;};
void set_current_laps(int current_laps){this->current_laps=current_laps;};
double get_time(){return time;};
double get_amout_refuelings(){return amount_refuelings;};
void total_time()
{
  time=time+pits_time;
}
int lap_check(double lenght_lap)
{
  if (current_mileage-lenght_lap>=0)
  {
    current_laps=int(mileage/lenght_lap);
    current_mileage=0;
    return 1;
  }
  else {return 0;}
}
void check_refuel(double lenght_lap)
{
  if (Current_volume <= (engine_consumption * (lenght_lap/100)))
  {
    amount_refuelings++;
    pits_time+=refueling_time;
    Current_volume=Volume_tank;
  }
}
void check_change_wheels();
Vehicle(){};
friend istream &operator >> (istream &stream,Vehicle& vehicle)
{
  cout<<"Enter vehicle name: ";
  stream>>vehicle.carname;
  try
    {
      cout<<"Enter amount of wheels: ";
      stream>>vehicle.amount_wheels;
      if (vehicle.amount_wheels < 0){
          throw "amount wheels must be more than 0 ";
    }
    }    
    catch (const char* error_message) {
      cerr << "exception thrown: " << error_message <<endl;
      vehicle.amount_wheels=checkinput(vehicle.amount_wheels);
    }
    for (int i = 0; i < vehicle.amount_wheels; i++) {
      wheel wheel1;
      vehicle.vec_wheels.push_back(wheel1);
      }
    try
      {
        cout<<"Enter Volume tank: ";
        stream>>vehicle.Volume_tank;;
        if (vehicle.Volume_tank<=0){
          throw "Volume tank must more than 0";
        }
      }
      catch (const char* error_message)
      {
        cerr << "exception thrown: " <<error_message<<endl;
        vehicle.Volume_tank=checkinput(vehicle.Volume_tank);
      }
    try
      {
        cout<<"Enter engine power: ";
        stream>>vehicle.power;
        if (vehicle.power<=0){
          throw "Power must more than 0";
        }
      }
      catch (const char* error_message)
      {
        cerr << "exception thrown: " <<error_message<<endl;
          vehicle.power=checkinput(vehicle.power);
      }
      vehicle.current_mileage=0;
      vehicle.current_laps=0;
      vehicle.mileage=0;
      vehicle.stat_of_car=0;
      vehicle.Current_volume=vehicle.Volume_tank;
      vehicle.engine_consumption=vehicle.calculating_consumption(vehicle.power);
      vehicle.determination_speed();
  return stream;
}
  friend ostream &operator << (ostream &stream,Vehicle& vehicle)
{
  stream<<"\nName of the car: "<<vehicle.carname<<endl;
  stream<<"Amount of wheels: "<<vehicle.amount_wheels<<endl;
  stream<<"Broken wheels: "<<vehicle.brokenwheels<<endl;
  stream<<"Speed: "<<vehicle.speed<<endl;
  stream<<"Volume tank: "<<vehicle.Volume_tank<<endl;
  stream<<"Current volume: "<<vehicle.Current_volume<<endl;
  stream<<"Engine power: "<<vehicle.power<<endl;
  stream<<"Engine consumption: "<<vehicle.engine_consumption<<endl;
  stream<<"Mileage: "<<vehicle.mileage<<endl;
  return stream;
}
Vehicle& operator=(const Vehicle& s) {
  carname = s.carname;
  amount_wheels = s.amount_wheels;
  speed = s.speed;
  mileage = s.mileage;
  current_mileage=s.current_mileage;
  current_laps=s.current_laps;
  time=s.time;
  return *this;
}
};
void outputResults(vector<Vehicle> v);
void new_page()
{
  for(int i=0;i<100;++i)
    {
      cout<<"\n";
    }
}
int end_race(vector<Vehicle> &vehicles,int amount_laps,double lenght_lap);
void menu()
{
  vector<Vehicle> vehicles;
  int choice;
  int exit_menu=0;
  int amount_laps=0;
  double lenght_lap=0;
  int carcheck=0;
  while(exit_menu==0)
    {
      cout<<"1.Input new vehicle"<<"\n";
      cout<<"2.Check information about vehicles"<<"\n";
      cout<<"3.Enter lenght of the track"<<"\n";;
      cout<<"4.Determine the race"<<"\n";
      cout<<"5.Results:"<<"\n";
      cout<<"6.Exit"<<"\n";
      try{
      cin>>choice;
        if ((choice > 6) || (choice < 1)) {
          throw "Error, try another number!";
          }
        }
        catch (const char* error_message)
        {
          cerr << "exception thrown: " << error_message << endl;
          cout<<"Enter number(1-6) ";
          choice = checkinput(choice);
        }
    
  switch(choice)
    {
      case 1: {
      new_page();
      Vehicle newcar;
      cin>> newcar;
      vehicles.push_back(newcar);
      new_page();
      cout<<"Vehicle: "<<newcar.get_carname()<<" was added"<<endl;
        carcheck++;
        break;
    }
      case 2: {
        new_page();
        if(carcheck==0)
          {
            cout<<"No vehicles"<<endl;
            break;
          }
        for(int i=0;i<vehicles.size();++i)
          {
            cout<<vehicles[i];
          }
        break;
        }
      case 3: {
        new_page();
        if(carcheck==0)
          {
            cout<<"No vehicles"<<endl;
            break;
          }
        try{
            cout<<"Enter number of laps: ";
            amount_laps=checkinput(amount_laps);
            if (amount_laps<=0){
              throw "Amount of laps must be more than 0";
            }
          }
          catch (const char* error_message)
            {
              cerr << "exception thrown: " << error_message << endl;
              cout<<"try again ";
              amount_laps=checkinput(amount_laps);
            }
          cout << "Enter the length of the track: ";
          lenght_lap = checkinput(lenght_lap);
          break;
        }
      case 4: {
        new_page();
        if(carcheck==0)
        {
          cout<<"No vehicles"<<endl;
          break;
        }
        if(amount_laps==0)
        {
          cout<<"No laps"<<endl;
          break;
        }
        double current_time=0;
        int racing_cars=vehicles.size();
        while(!end_race(vehicles,amount_laps,lenght_lap))
          {
            if(racing_cars<=0)
              {
                break;
              }
            for(int i=0;i<vehicles.size();++i)
              {
                int exit=0;
                if (vehicles[i].stat_of_car==0)
                {
                  vehicles[i].mileage_plus();
                  vehicles[i].current_mileage_plus();
                  for (int j = 0; j < vehicles[i].vec_wheels.size(); j++)
                  {
                        vehicles[i].vec_wheels[j].check_status(vehicles[i].get_mileage(),vehicles[i].get_speed());
                  }
                  vehicles[i].calc_broken_wheels();
                  vehicles[i].calc_current_volume(vehicles[i].get_consumption(),vehicles[i].get_current_mil());
                  vehicles[i].determination_speed();
                  vehicles[i].set_time(current_time);
                  vehicles[i].output_time();
                  cout<<"Vehicle: "<<vehicles[i].get_carname()
                    <<" Lap: "<<vehicles[i].get_current_laps()+1<<endl
                    <<" Current Speed: "<<vehicles[i].get_speed()<<"\n"
                    <<" Current fuel "<<vehicles[i].get_current_volume()
                    <<" Broken wheels: "<<vehicles[i].get_broken_wheels()<<"\n"
                    <<" Mileage: "<<vehicles[i].get_mileage()<<"\n";
                  if (vehicles[i].get_broken_wheels()==vehicles[i].vec_wheels.size() || (vehicles[i].get_current_volume()<=0))
                    {
                        exit=1;
                        vehicles[i].set_time(current_time);
                        vehicles[i].plus_current_laps();
                    }
                  if ((lenght_lap*amount_laps)-(vehicles[i].get_mileage())<=0) 
                    {
                      exit=1;
                      vehicles[i].set_time(current_time);
                      vehicles[i].set_current_laps(amount_laps);
                      vehicles[i].output_time();
                      cout<<vehicles[i].get_carname()<<" FINISHED"<<endl;
                    }
                  if (exit==1)
                    {
                      vehicles[i].stat_of_car=1;
                      racing_cars=racing_cars-1;
                      break;
                    }
                  if (vehicles[i].lap_check(lenght_lap)==1)
                    {
                      vehicles[i].check_refuel(lenght_lap);
                      vehicles[i].check_change_wheels();
                    }
                }
                else {
                  continue;
                }
              }
            current_time+=dt;
          }
        for(int i=0;i<vehicles.size();++i)
          {
            vehicles[i].total_time();
          }
        break;
      }
      case 5:{
      new_page();
      outputResults(vehicles);
      break;
      }
      case 6:{
        new_page();
        cout<<"Are you sure to exit? 1-yes 0-no\n";
        cin>>exit_menu;
        if(exit_menu==1)
        {
          vehicles.clear();
          return;
        }
        break;
      }
      }
    }
  }
int end_race(vector<Vehicle> &vehicles,int amount_laps,double lenght_lap)
{
  int finished_cars=0;
    for (int i=0;i<vehicles.size();i++)
      {
        if (vehicles[i].get_current_mil()>=amount_laps*lenght_lap)
        {
          finished_cars++;
        }
      }
    if ( finished_cars==vehicles.size())
    {
      return 1;
    }
    else return 0;
  }

int main() {
  srand(time(NULL));
  menu();
  return 0;
}
void wheel::check_status(double mileage, double speed){
  if(status!=1){
    double k=rand()%50 +(mileage/100);
    if (k>49) {
        status = 1; // Повреждено
    }
  }
  }
void Vehicle::calc_broken_wheels() 
{
  int count = 0;
  for (int i = 0; i < vec_wheels.size(); i++) 
  {
    if (vec_wheels[i].get_status() == 1) {
      count++;
    }
  }
  brokenwheels=count;
}
void Vehicle::output_time() 
{
  double t = this->time;
  int hours = int(t);
  double cur_time = (t - hours) * 60;
  int minutes = int(cur_time);
  int seconds = int((cur_time - minutes) * 60);
  cout << "TIME: "<<hours << ":" <<minutes << ":" <<seconds <<endl;
}
void Vehicle::check_change_wheels()
{
  {
    if((brokenwheels!=0)&&(brokenwheels<amount_wheels))
    {
      pits_time+=reWheel_time*brokenwheels;
      for(int i=0;i<vec_wheels.size();++i)
        {
          if(vec_wheels[i].get_status()==1)
          {
            vec_wheels[i].set_status(0);
          }
        }
    }
  }
}
vector<Vehicle>  RatingResults(vector<Vehicle> v) {
    sort(v.begin(), v.end(), []( Vehicle& a,  Vehicle& b) {
    if (a.get_time() != b.get_time()) {
      return a.get_time() < b.get_time();
    } 
    else {
      return a.get_amout_refuelings() < b.get_amout_refuelings(); 
    }
  });
  return v;
}
void outputResults(vector<Vehicle> v) {
  vector<Vehicle> results = RatingResults(v);
  for (int i = 0; i < results.size(); i++) {
    cout << results[i].get_carname() << endl;
    results[i].output_time();
    cout<<"Laps: "<<results[i].get_current_laps()<<endl;
    cout << "Amount refuelings: " << int(results[i].get_amout_refuelings()) << endl;
  }
}