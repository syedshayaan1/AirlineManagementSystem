#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include<string.h>
#include<iomanip>
#include<fstream>
#include <sstream>
#include <vector>

using namespace std;


//-------------------------------------------------------------------------------------------------------

class User
{
	protected: // SO that the inherited classes can access these attributes
		string username;
		string password;	
		
	public:
		bool login(string u, string p, string type);
		void resetUsername(string u);
    void resetPassword(string p);
};

//-------------------------------------------------------------------------------------------------------

class Passenger : public User //PASSENGER CLASS
{
	private:
		int CNIC, pastFlightsNumber;
		string passport_no;
		vector<string> res_list;
		 
	public:
		bool login(string u, string p, string type); //Polymorphism
		bool registr(string username, string password, int cnic, string pass_no);
		string addBooking(int flightID, string seatNum);
};

//--------------------------------------------------------------------------------------------------------

class Admin : public User //ADMIN CLASS inherits from USER CLASS
{
	private:
	public:
};

//---------------------------------------------------------------------------------------------------------

class Flight
{
	private:
		int flightID;
		bool isLocal, isDirect;
		string departureLoc, arrivalLoc, indirectLoc, arrivalTime, departureTime, flightCost;
		float totalHours;


	public:
		vector<string> bookedSeats;

		Flight(int id, bool localOrInt, bool directOrNot, string depLoc, string arrLoc, string indirLoc, string depTime, string arrTime, float flightHours, string cost, vector<string> bSeats); //constructor

		int getID()
		{
			return flightID;
		}

		string getIsLocal()
		{
			if (isLocal) {
				return "Yes";
			}
			else
			{
				return "No";
			}
		}

		void setIslocal(bool isLoc)
		{
			isLocal = isLoc;
		}

		string getIsDirect()
		{
			if (isDirect) {
				return "Yes";
			}
			else
			{
				return "No";
			}
		}

		void setIsDirect(bool isDir)
		{
			isDirect = isDir;
		}

		string getArrivalLoc()
		{
			return arrivalLoc;
		}

		void setArrivalLoc(string aL)
		{
			arrivalLoc = aL;
		}

		string getDepartureLoc()
		{
			return departureLoc;
		}

		void setDepartureLoc(string dL)
		{
			departureLoc = dL;
		}

		string getIndirectLoc()
		{
			return indirectLoc;
		}

		void setIndirectLoc(string iL)
		{
			indirectLoc = iL;
		}

		string getDepartureTime()
		{
			return departureTime;
		}

		void setDepartureTime(string dT)
		{
			departureTime = dT;
		}

		string getArrivalTime()
		{
			return arrivalTime;
		}

		void setArrivalTime(string aT)
		{
			arrivalTime = aT;
		}

		float getFlightHours()
		{
			return totalHours;
		}

		void setFlightHours(float fT)
		{
			totalHours = fT;
		}

		string getCost()
		{
			return flightCost;
		}

		void setCost(string c)
		{
			flightCost = c;
		}


		friend class Passenger;  //FRIEND FUNCTION HAS BEEN USED HERE
		friend class Admin;
		
};


//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

//Function to fill the flights array:

vector<Flight> flightFileRead() {

	string x, firstrow, l1, list, e;
 
	string fID, loc, dir, _arrLoc, _depLoc, _indirectLoc, _depTime, _arrTime, _flightHours, cost;
	bool found = false, _isLocal, _isDirect;

	vector<string> bSeats;

	vector<Flight> fList;

  ifstream fin("flights.txt");

	if (fin.is_open())
	{
		getline(fin, firstrow);

		while (getline(fin, x))
		{
			stringstream s(x);

			getline(s, fID, ',');
			getline(s, loc, ',');
			getline(s, dir, ',');
			getline(s, _depLoc, ',');
			getline(s, _arrLoc, ',');
			getline(s, _indirectLoc, ',');
			getline(s, _depTime, ',');
			getline(s, _arrTime, ',');
			getline(s, _flightHours, ',');
			getline(s, cost, ',');
			getline(s, list, ']');

			_isLocal = (loc == "yes") ? true : false;
			_isDirect = (dir == "yes") ? true : false;

			l1 =  list.substr(1,list.find("]")-1);
			stringstream a(l1);
		  while (getline(a, e, ','))
		  {
		  	bSeats.push_back(e);
		  }

			fList.push_back(Flight(stoi(fID), _isLocal, _isDirect, _depLoc, _arrLoc, _indirectLoc, _depTime, _arrTime, stof(_flightHours), cost, bSeats));
		}
	}

  fin.close();
  return fList;
}




//------------------------------------------------------------------------------------



void flightDetails(vector<Flight> flights) {
	cout<<endl<<"Flights Schedule: "<<endl;

	for (int i = 0; i < flights.size(); i++) 
	{
	  cout<<endl<<"Flight "<< i+1 <<":"<< endl
	  		<< "ID: "<< flights.at(i).getID() << ", Local: "<<flights.at(i).getIsLocal()<< ", Direct: "<<flights.at(i).getIsDirect()<<endl
	  		<<"Departure Location: "<<flights.at(i).getDepartureLoc()<<", Arrival Location: "<<flights.at(i).getArrivalLoc()<<", Layover Airport Location: "<<flights.at(i).getIndirectLoc()<<endl
	  		<<"Departure Time: "<<flights.at(i).getDepartureTime()<<", Arrival Time: "<<flights.at(i).getArrivalTime()<<", Flight Hours: "<<flights.at(i).getFlightHours()<<endl
	  		<<"Total Cost: "<<flights.at(i).getCost()<<endl<<endl;
	}
}


void flightsFileUpdate(vector<Flight> fList)//This method is used to reflect the changes made to a movie screening to the file.
{ 
	string isLoc, isDir;
	string seats = "";
	ofstream fout("flights.txt");

	fout<<"flightId, isLocal, isDirect, departureLoc, arrivalLoc, indirectLoc, departureTime, arrivalTime, totalHours, flightCost, bookedSeats"<<endl;

	for (int i = 0; i < fList.size(); i++)
	{
		if (fList.at(i).getIsLocal() == "Yes")
		{
			isLoc = "yes";
		}	
		else
		{
			isLoc = "no";
		}	

		if (fList.at(i).getIsDirect() == "No")
		{
			isDir = "yes";
		}	
		else
		{
			isDir = "no";
		}	

		for(int i = 0; i < fList.at(i).bookedSeats.size(); i++)
		{
			if (seats.length() < 1)
			{
				seats = seats + fList.at(i).bookedSeats.at(i);
			}	
			else
			{
				seats = seats + "," + fList.at(i).bookedSeats.at(i);
			}	
		}	

		fout<< to_string(fList.at(i).getID()) << ","
        << isLoc << ","
        << isDir << ","
        << fList.at(i).getDepartureLoc() << ","
        << fList.at(i).getArrivalLoc() << ","
        << fList.at(i).getIndirectLoc() << ","
        << fList.at(i).getDepartureTime() << ","
        << fList.at(i).getArrivalTime() << ","
        << to_string(fList.at(i).getFlightHours()) << ","      
        << fList.at(i).getCost() << ","
        << "["
        << seats
        << "]"
        << endl;
	}
}



int main()
{
	Admin a;     //OBJECTS
	Passenger p;
	vector<Flight> flights;
	
	int id,opt,command,CNIC; //FOR ADMIN OR PASSENGER LOGIN
	string username,password, passNum;
	
	bool login_success = false;  //FOR LOGIN 
	
	cout<<"________________________________________________________________________________________________" << endl << endl;
	
	cout<<"**************************  NEW PAK AIRLINE FLIGHT SYSTEM (NPAFS) ******************************" << endl << endl;
	
	cout<<"________________________________________________________________________________________________" << endl << endl;
	
	cout<< "                                      MENU                                                    " << endl << endl;
	
	cout<<" THE BASIC DETAILS ARE AS FOLLOWS: " << endl;
	
	cout<<" 1 HR TRAVEL *LOCAL FLIGHT* = Rs 10,000 /- "<<endl;
	cout<<"(LOCAL FLIGHTS ARE SUBJECT TO 5% GOVERNMENT TAX)" << endl << endl;
	
	cout<<" 1 HR TRAVEL *INTERNATION FLIGHT* = Rs 20,000 /- " << endl;
	cout<<"(INTERNATIONAL FLIGHTS ARE SUBJECT TO 10% GOVERNMENT TAX)" << endl << endl;
	
	cout<<"_____________________________________________________________________________________________" << endl << endl;
	
	cout << "YOU MAY (ENTER 0) IF YOU ARE AN *ADMIN* OR YOU MAY (ENTER 1) IF YOU ARE AN *PASSENGER* " << endl;
	cin>>id;
	
	switch (id)
    {
			
	      case 0:
	    {
	    	do
    	 {
    		cout<<" HELLO ADMIN! "<<endl;
    		
	    	cout<<"Please enter your username and password to login"<<endl;
	    	
			cout<<"Enter Username: ";
	    	cin >> username;
	    	
	    	cout<<"Enter Password: ";
	    	cin >> password;
	    	
	    	
	    	login_success = a.login(username, password, "admin");  //CALL FOR LOGIN SUCCESS

			if (login_success == false)
			{
				cout<< "Invalid login credentials! Please try again!" <<endl;
			}
			
			else
			cout<<endl<<"Sucessfully Logged in!"<<endl;

				
    	 }while (login_success == false);
		 	  
	 	 break;
	 	 
	    }
	    
	    
	    //------------------------------------------------------------------------------------
	    
	
	     case 1:
	    {
	    	cout<<" HELLO PASSENGER! "<< endl;
	    	 
    
	    cout<<" Please Enter (0) to *Login* OR Enter (1) to *Register* "<< endl;
	    cin>>opt;
	    
	    do
	    {

	    	if (opt == 0)
	    	{
	    		cout<<"Please enter your username and password to login."<<endl;
	    		
				cout<<"Enter Username: " << endl;
	    	cin>>username;
	    		
	    	cout<<"Enter Password: " << endl;
	    	cin>>password;
	    		
	    		login_success = p.login(username,password,"passenger");

	    		if (login_success == false)
				{
					cout<< "Invalid login credentials! Please try again!" <<endl;
				}
			
				else
				cout<<endl<<"Sucessfully Logged in!"<<endl;
				
	    	}
	    	
	    	else if (opt == 1)
	    	{
	    		cout<<"Please enter your following details:"<<endl;
	    		
				cout<<"Enter username: "<< endl;
	      cin>>username;
	    		
	    		cout<<"Enter password: " << endl;
	    		cin>> password;
	    		
	    		cout<< endl << endl;
	    		
	    		cout<<"If you want to register yourself, Enter your CNIC: "<< endl;
	    		cout<<"If you want to register as a minor (under 18) you may enter your CNIC as well. " << endl;

	    		cout<<"Please Enter CNIC: " << endl;
	    		cin>>CNIC;

	    		cout<<"Enter Passport Number: " << endl;
	    		cin>>passNum;
	    		
	    		login_success = p.registr(username, password, CNIC, passNum);

	    		if (login_success == false)
				{
					cout<< "User with entered CNIC already exists! / INVALID CNIC number entered. " <<endl;
				}
			
				else
				cout<<"Sucessfully Registered and Logged in!"<<endl;
	    	}
	    	

	    	} while (login_success == false);
	    	  break;
		
	    
	    
	     default:
	     cout<< " INVALID ENTRY " << endl;
      }
	
  }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//

  //Now let's fill the flights vector using the data from our text file. 
  flights = flightFileRead();

  if (flights.empty() == true)
  {
  	cout<<"No flights found"<<endl;
  }
  else
  {
  	flightDetails(flights);
  }

    //FOR DISPLAYING OF COMMANDS
    
    if ( id == 0 )
    {
    	do 
		  {
			 	//DISPLAY ALL ADMIN COMMANDS
		    	
		    	cout<<"List of available Commands for Admin: "<< endl << endl;
		    	
				cout<< " Enter (1) to Update the details of local flights "<< endl;
				cout<< " Enter (2) to Update the details of International flights "<< endl;
				cout<< " Enter (3) to add new flight"<< endl;
				cout<< " Enter (4) to delete an existing flight "<< endl;
				cout<< " Enter (5) to EXIT " << endl;

				cout << "PLEASE ENTER THE SR. OF THE COMMAND:  "<< endl;

				cin>> command;
				
				if (command == 1) 
				{
					int fid;

					cout<<"Please enter ID of the LOCAL flight you want to change details of: " << endl;  //LOCAL INPUT
					cin>>fid;

					for (int i=0;i<flights.size();i++)
					{
						if(flights.at(i).getID() == fid)
						{
							cout << "Please Enter NEW Arrival Location: "<< endl;
							string arrLoc;

							cin>>arrLoc;

							cout << "Please Enter NEW Deaprture Location:  "<<endl;
							string depLoc;

							cin>>depLoc;

							cout << "Please Enter NEW Departure Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string arrT;
							cin>>arrT;

							cout << "Please Enter NEW Arrival Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string depT;
							cin>>depT;

							cout << "Please Enter the flights hours: " << endl;

							float flhrs;
							cin>>flhrs;

							float cost = (10000 * flhrs) + (0.05 * 10000 * flhrs);

							string cost_of_Flight = to_string(cost);

							cout << " THE TOTAL COST OF FLIGHT AFTER APPLICATION OF GOVT TAXES IS Rs " << cost_of_Flight << " /- "<< endl;

							flights.at(i).setDepartureLoc(depLoc);
							flights.at(i).setArrivalLoc(arrLoc);
							flights.at(i).setArrivalTime(arrT);
							flights.at(i).setDepartureTime(depT);
							flights.at(i).setFlightHours(flhrs);
							flights.at(i).setCost(cost_of_Flight);

							flightsFileUpdate(flights);
						}

					}

				}
				
				else if (command == 2)
				{
					int fid;

					cout<<"Please enter ID of the INTERNATIONAL flight you want to change details of: " << endl;  //LOCAL INPUT
					cin>>fid;

					for (int i=0;i<flights.size();i++)
					{
						if(flights.at(i).getID() == fid)
						{

							cout << "Is the flight DIRECT? (you may answer with a 'yes' or 'no " << endl;
							string reply;

							bool isDir;
							string layloc;

							cin>>reply;

							if (reply == "no" || reply == "NO")
							{
								cout << "Please Enter Layover Location: " << endl;
								string layloc;

								cin>>layloc;

								isDir = false;

							}

							else 
							{
								isDir = true;
								layloc = '-';

							}


							cout << "Please Enter NEW Arrival Location: "<< endl;
							string arrLoc;

							cin>>arrLoc;

							cout << "Please Enter NEW Deaprture Location:  "<<endl;
							string depLoc;

							cin>>depLoc;

							cout << "Please Enter NEW Departure Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string arrT;
							cin>>arrT;

							cout << "Please Enter NEW Arrival Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string depT;
							cin>>depT;

							cout << "Please Enter the flights hours: " << endl;

							float flhrs;
							cin>>flhrs;

							float cost = (20000 * flhrs) + (0.1 * 20000 * flhrs);

							string cost_of_Flight = to_string(cost);

							cout << " THE TOTAL COST OF FLIGHT AFTER APPLICATION OF GOVT TAXES IS Rs " << cost_of_Flight << " /- "<<endl;

							flights.at(i).setIsDirect(isDir);
							flights.at(i).setDepartureLoc(depLoc);
							flights.at(i).setArrivalLoc(arrLoc);
							flights.at(i).setIndirectLoc(layloc);
							flights.at(i).setArrivalTime(arrT);
							flights.at(i).setDepartureTime(depT);
							flights.at(i).setFlightHours(flhrs);
							flights.at(i).setCost(cost_of_Flight);
							flightsFileUpdate(flights);
						}	
					}
				}
				
				else if (command == 3)
				{
					cout<<"Enter details of a flight you want to add: "<<endl;

					cout<<"Enter the flight ID: "<<endl;
					int fid;
					cin>>fid;

					cout << "Is the flight Local? (you may answer with a 'yes' or 'no " << endl;
					string reply;

    			bool isLoc;

					cin>>reply;

					if (reply == "no" || reply == "NO")
					{
						isLoc = false;
					}
					else 
					{
						isLoc = true;
					}

					cout << "Is the flight DIRECT? (you may answer with a 'yes' or 'no " << endl;

							bool isDir;
							string layloc;

							cin>>reply;

							if (reply == "no" || reply == "NO")
							{
								cout << "Please Enter Layover Location: " << endl;
								string layloc;

								cin>>layloc;

								isDir = false;

							}

							else 
							{
								isDir = true;
								layloc = '-';

							}


							cout << "Please Enter NEW Arrival Location: "<< endl;
							string arrLoc;

							cin>>arrLoc;

							cout << "Please Enter NEW Deaprture Location:  "<<endl;
							string depLoc;

							cin>>depLoc;

							cout << "Please Enter NEW Departure Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string arrT;
							cin>>arrT;

							cout << "Please Enter NEW Arrival Time: " << endl;
							cout<<" Enter time in the format hh::mm (eg. 10:40) " << endl;
							
							string depT;
							cin>>depT;

							cout << "Please Enter the flights hours: " << endl;

							float flhrs;
							cin>>flhrs;

							float cost;

							if (isLoc)
							{
								cost = (10000 * flhrs) + (0.05 * 10000 * flhrs);
							} 
							else
							{
								cost = (20000 * flhrs) + (0.1 * 20000 * flhrs);
							}

							string cost_of_Flight = to_string(cost);

							cout << " THE TOTAL COST OF FLIGHT AFTER APPLICATION OF GOVT TAXES IS Rs " << cost_of_Flight << " /- "<<endl;

							vector<string> bSeat;

							flights.push_back(Flight(fid, isLoc, isDir, depLoc, arrLoc, layloc, depT, arrT, flhrs, cost_of_Flight, bSeat));

							flightsFileUpdate(flights);
				}
				
				else if (command == 4) 
				{
					cout<<"Please enter the ID of the flight that you want to delete: "<<endl;
					int fid;
					cin>>fid;

					for (int i=0;i<flights.size();i++)
					{
						if (fid == flights.at(i).getID())
						{
							flights.erase(flights.begin()+i);
						}
					}
					flightsFileUpdate(flights);
				}
				
				else if (command == 5)
				{

					break;
				}
				
				else 
				{
					cout << "INVALID COMMAND! " << endl;
				}
		
     } while (command != 5);
 	
		
	}
	
	else if (id == 1 )
	{
		//DISLPLAY ALL PASSENGER COMMANDS
		cout<<"List of available Commands for Passenger: "<< endl << endl;
    	
		cout<< " Enter (1) to ADD BOOKINGS "<< endl;
		cout<< " Enter (2) to RESET USERNAME "<< endl;
		cout<< " Enter (3) to RESET PASSWORD "<< endl;
		cout<< " Enter (4) to DISPLAY FLIGHTS LIST"<< endl;
		cout<< " Enter (5) to EXIT " << endl;
		
		do 
	 {
	    cout << "PLEASE ENTER THE SR. OF THE COMMAND:  "<< endl;
		cin>> command;
		
		if (command == 1)  //CALL FOR ADDING BOOKING
		{
			string bookedSeat;
			cout<<"Please enter flightID of the flight you want to book: "<<endl;
			int fid;
			cin>>fid;

			cout<<"Please enter seat number you want to book: "<<endl;
			string seat;
			cin>>seat;
			

			bookedSeat = p.addBooking(fid,seat);

			if (bookedSeat != " ")
			{
				for(int i = 0; i < flights.size(); i++)
				{
					if(flights.at(i).getID() == fid)
					{
						flights.at(i).bookedSeats.push_back(seat);
						
					}
				}

				   flightsFileUpdate(flights);
			}
		}
		
		else if (command == 2)  //CALL TO RESET USERNAME
		{
			cout<<"Please enter new username: "<<endl;
			string u;
			cin>>u;
			p.resetUsername(u);
		}
		
		else if (command == 3)  //CALL TO RESET PASSWORD
		{
			cout<<"Please enter new password: "<<endl;
			string pas;
			cin>>pas;
			p.resetPassword(pas);			
		}
		
		else if (command == 4)  //CALL TO DISPLAY FLIGHTS LIST		
		{
			flightDetails(flights);
		}
		
		else if (command == 5) 
		{
			break;
		}
		
		
		else 
		{
			cout << "INVALID COMMAND! " << endl;
		}
	
  } while (command != 5);
	
		
 }
	
	
	return 0;
}



































//--------------------------------------------------------------------------------------------------------------------------------
// User Methods:
//--------------------------------------------------------------------------------------------------------------------------------

bool User::login(string u, string p, string type)
{
	string x, firstrow;
	string usrname, pass;
	bool found = false;
	
	ifstream fin;

	if (type == "admin")
	{
		fin.open("admins.txt");
	}	
	else if (type == "passenger")
	{
		fin.open("passengers.txt");
	}
	
	if (fin.is_open())
	{
		getline(fin, firstrow);

		while (getline(fin, x))
		{
			stringstream s(x);

			getline(s, usrname, ',');
		
			getline(s, pass);

			//Below lines are used to appropriately set attributes guest object by taking corresponding data from the file

			if (usrname == u && pass == p)
			{
				found = true;
				username = usrname;
				password = pass;
	       break;
			}	
		}
	}
	else
	{
		cout<<endl<<"Cannot open the record file!"<<endl;
	}
	fin.close();
  return found;
}

//--------------------------------------------------------------------------------------------------------------------------------



void User::resetUsername(string u)
{
	username = u;
	cout<<"Username Succesfully Updated!"<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------

void User::resetPassword(string p)
{
	password = p;
	cout<<"Password Succesfully Updated!"<<endl;
}

//--------------------------------------------------------------------------------------------------------------------------------










































//--------------------------------------------------------------------------------------------------------------------------------
// Passenger Methods:
//--------------------------------------------------------------------------------------------------------------------------------

bool Passenger::login(string u, string p, string type) //Polymorphism
{
	string x, firstrow;
	string usrname, pass;
	string cnic_no, pastFlightsNum, pp_no, list, l1, e;
	bool found = false;
	
	ifstream fin;

	if (type == "admin")
	{
		fin.open("admins.txt");
	}	
	else if (type == "passenger")
	{
		fin.open("passengers.txt");
	}

	if (fin.is_open())
	{
		getline(fin, firstrow);

		while (getline(fin, x))
		{
			stringstream s(x);

			getline(s, usrname, ',');
			
	  	getline(s, pass, ',');
			
			getline(s, cnic_no, ',');
			
			getline(s, pp_no, ',');
			
			getline(s, pastFlightsNum, ',');

			getline(s, list, ']');
			

			//Below lines are used to appropriately set attributes passenger object by taking corresponding data from the file

			if (usrname == u && pass == p)
			{
			  found = true;
				username = usrname;
				password = pass;
     		CNIC = stoi(cnic_no);
     		passport_no = pp_no;
     		pastFlightsNumber = stoi(pastFlightsNum);

				//Below lines are used to enter data from the list in file to the passenger's booking linked list

				l1 =  list.substr(1,list.find("]")-1);
				stringstream a(l1);
		    while (getline(a, e, ','))
		   	{
		   		res_list.push_back(e);
		   	}
	      break;
			}	
		}
	}
	else
	{
		cout<<endl<<"Cannot open the record file!"<<endl;
	}
	fin.close();
  return found;
}

//--------------------------------------------------------------------------------------------------------------------------------

bool Passenger::registr(string u, string p, int cnic, string pass_no)
{
	bool unique = true;
	string _cnic, x, firstrow, usrname, pass, passNo, line;

	ifstream fin("passengers.txt");
	if (fin.is_open())
	{
		getline(fin, firstrow);
		while (getline(fin, x)) //Check if the generated id for the guest is unique
		{
			stringstream s(x);

			getline(s, usrname, ',');
			getline(s, pass, ',');
			getline(s, _cnic, ',');

			if (cnic == stoi(_cnic)) //check if the CNIC entered matches with any other passenger's CNIC
			{
				unique = false;
				return unique;
			}	
		}
	}
	else
	{
		cout<<endl<<"Cannot open the record file!"<<endl;
	}
  
  fin.close();


  //Below lines are used to initiate the attributes of the guest object to log the passenger in and allow him to perform actions right after registering
  ifstream file("passengers.txt");
	ofstream fout("newpassengers.txt");
	if (file.is_open() && fout.is_open())
	{
		while (getline(file, line))
		{
			fout<<line<<endl;
		}

		fout << u << ","
             << p << ","
             << cnic << ","
             << pass_no << ","
             << "0" << ","
             << "[]"
             << endl;

      //Now setting the passenger attributes to log them in:

      username = u;
      password = p;
      CNIC = cnic;
      passport_no = pass_no;
      pastFlightsNumber = 0;

	}
	else
	{
		cout<<endl<<"Can't open passengers file!"<<endl;
	}

	fout.close();
	file.close();

	remove("passengers.txt");
	rename("newpassengers.txt", "passengers.txt");

	return unique;
}

//--------------------------------------------------------------------------------------------------------------------------------














string Passenger::addBooking(int flightID, string seatNum)
{
string x, firstrow, list, l1, e;
string fID, loc, dir, _arrLoc, _depLoc, _indirectLoc, _depTime, _arrTime, _flightHours, cost;
bool found = false, _isLocal, _isDirect;
bool available = true; //if no seats are available, this becomes false and passenger is provided with the message accordingly
vector<string> bSeats;

  ifstream fin("flights.txt");
	if (fin.is_open())
	{
		getline(fin, firstrow);

		while (getline(fin, x))
		{
			stringstream s(x);

			getline(s, fID, ',');
			getline(s, loc, ',');
			getline(s, dir, ',');
			getline(s, _depLoc, ',');
			getline(s, _arrLoc, ',');
			getline(s, _indirectLoc, ',');
			getline(s, _depTime, ',');
			getline(s, _arrTime, ',');
			getline(s, _flightHours, ',');
			getline(s, cost, ',');
			getline(s, list, ']');


			l1 =  list.substr(1,list.find("]")-1);
			stringstream a(l1);
		  while (getline(a, e, ','))
		  {
		  	bSeats.push_back(e);
		  }


			if (fID == to_string(flightID))
			{
				found = true;

				for (int i=0; i < bSeats.size(); i++)
				{
					if (seatNum == bSeats.at(i))
					{
						available = false;
						cout<<"Sorry, seat already taken!"<<endl;
						break;
					}
				}
			}
		}

		if (found == false)
		{
			cout<<endl<<"Could not find flight with the ID you provided!"<<endl;
		}

	}
	else
	{
		cout<<endl<<"Cannot open the record file!"<<endl;
	}
	fin.close();

	if (available == true & found == true)
	{
		cout<<endl<<"Booked successfully!"<<endl;
		res_list.push_back(to_string(flightID));
		return "successful";
	}
	else
	{
		return "";
	}
}






















//--------------------------------------------------------------------------------------------------------------------------------
// Flight Methods:
//--------------------------------------------------------------------------------------------------------------------------------

Flight::Flight(int id, bool localOrInt, bool directOrNot, string depLoc, string arrLoc, string indirLoc, string depTime, string arrTime, float flightHours, string cost, vector<string> bSeats)
{
	flightID = id;
	isLocal = localOrInt;
	isDirect = directOrNot;
	arrivalLoc = arrLoc;
	departureLoc = depLoc;
	indirectLoc = indirLoc;
	departureTime = depTime;
	arrivalTime = arrTime;
	totalHours = flightHours;
	flightCost = cost;
	bookedSeats = bSeats;
}