#include<iostream>
#include<string>
using namespace std;

//parent or base class -> vehicle

class Vehicle{ 
protected:
      string brand;
      string model;
      double rentPerday;
public:
     // constructor to initialize vehicle attributes
      Vehicle(string brand,string model,double rentPerday){
          this->brand = brand;
          this->model = model;
          this->rentPerday = rentPerday;
      }
   //Virtual function for displaying vehicle information
   virtual void displayInfo(){
    cout <<"Brand: " <<this->brand <<", Model: " <<this->model<<endl;
    cout <<"Rent per day: " <<this->rentPerday <<" BDT" <<endl;
   }

   // Virtual function to calculate total rent 
   virtual double calculateRent(int days){
     return rentPerday * days;
   }

   // virtual destructor 
   virtual ~Vehicle(){}

};

// derived Class -> Car 

class Car : public Vehicle {
private:
  int seats;

public:
     //constructor to initialize car attributes
     Car (string brand,string model,double rentPerday,int seats)
         : Vehicle (brand,model,rentPerday){
            this->seats = seats;
         }
    
     // Override displayInfo to include car-specific details
     void displayInfo() override {
        cout << "Car --> ";
        Vehicle :: displayInfo();
        cout << "Seats: " <<this->seats <<endl;
     }

     // Rent calculation for car (no Extra charge) 
     double calculateRent(int days) override {
        return rentPerday * days;
     }
};

// derived Class -> Bike

class Bike : public Vehicle {
private :
    bool hasHelmet;

public:
     //constructor to initialize bike attributes
     Bike(string brand,string model,double rentPerday,bool hasHelmet)
         : Vehicle (brand,model,rentPerday){
           this->hasHelmet = hasHelmet;
         }

    // Override displayInfo to include helmet info
    void displayInfo() override{
        cout <<"Bike --> ";
        Vehicle :: displayInfo();
        cout <<"Helmet Included: " <<(hasHelmet ? "Yes" : "No") <<endl;
    } 

    // Rent calculation includes optional helmet change
    double calculateRent(int days) override {
        double helmetCharge = hasHelmet ? 20.0 : 0.0;
        return (rentPerday + helmetCharge ) * days;
    }
};

// Rental system class

class Rentalsystem {
public:
   // Rent any vehicle using a base class pointer 
   void rentVehicle( Vehicle* v,int days){
       cout <<"\n--- Vehicle Info ---" <<endl;
       v->displayInfo(); // Polymorphic call
       cout <<"Total Rent for " <<days <<" day(s): "
            <<v->calculateRent(days) <<" BDT\n" <<endl;   
   }

};

// Main Fuunction !!!

int main(){
    // create Car and Bike objects 
   Car myCar("Toyota","Corolla",1500.0,5);
   Bike myBike("Yamaha","R15",800.0,true);

   Rentalsystem system;

   int choice,days;
   cout<<"Welcome to Vehicle Rental System"<<endl;
   cout<< "1.Rent a Car" <<endl <<"2.Rent a Bike"<<endl;
   cout <<"Choose : ";
   cin >> choice;

   cout <<"Enter Number of days : ";
   cin >> days;

   //Use rental system based on user's choice

   if(choice == 1){
    system.rentVehicle(&myCar,days);
   }else if(choice == 2){
     system.rentVehicle(&myBike,days);
   }else {
    cout <<"Invalid choice.\n";
   }

    return 0;
}