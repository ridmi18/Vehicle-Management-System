#include <iostream>
#include <fstream> //File operation
#include <stdlib.h>
#include <sstream> //String stream for passing
#include <string>
#include <vector> //Dynamic array
#include <conio.h> //Console input output (for getch())
#include <regex> //For validate date,time,contact number,email
using namespace std;


// Convert a string to a number using a hash function
unsigned int Hash(const string& data){
    unsigned int result = 0;
    for (unsigned int ch : data)
        result = ch + (result << 4) + (result << 10) - result; // Update result based on each character
    return result;
}

// Get a password from the user, hiding input characters
string getPassword(){
    string password;
    char ch;

    cout << "\tEnter password: ";

    while (true)
    {
        ch = _getch(); // Read a character without showing it

        if (ch == 13) // Enter key pressed
        {
            cout << endl;
            break;
        }
        else if (ch == 8) // Backspace key pressed
        {
            if (!password.empty())
            {
                cout << "\b \b"; // Erase last character from display
                password.pop_back(); // Remove last character from password
            }
        }
        else
        {
            cout << '#'; // Show '#' for each typed character
            password.push_back(ch); // Add character to password
        }
    }

    return password; // Return the entered password
}

// Check if date is in DD/MM/YYYY format
bool DateValid(const string& date) {
    regex datePattern("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/(20)\\d\\d");
    return regex_match(date, datePattern); // Match date with pattern
}

// Check if time is in HH:MM format
bool TimeValid(const string& time) {
    regex timePattern("([01]?[0-9]|2[0-3]):[0-5][0-9]");
    return regex_match(time, timePattern); // Match time with pattern
}

// Check if contact number starts with '0' followed by 9 digits
bool ContactNumberValid(const string& contactNumber) {
    regex contactNumberPattern("^0\\d{9}$");
    return regex_match(contactNumber, contactNumberPattern); // Match contact number with pattern
}

// Check if email address contains '@'
bool EmailAddressValid(const string& emailAddress) {
    return emailAddress.find('@') != string::npos; // Check if '@' is in the email
}




// Structure to store customer details
struct Customer{
    string customerName; // Customer's name
    string customerUserName; // Username
    unsigned int customerHashedPassword; // Hashed password
    string customerContactNumber; // Contact number
    string customerEmailAddress; // Email address
};

// Structure to store appointment details
struct Appointment{
    string appointmentService; // Type of service
    string appointmentDate; // Date of appointment
    string appointmentTime; // Time of appointment
    string appointmentCustomer; // Customer's name
    string appointmentCustomerContact; // Customer's contact number
    string appointmentStatus; // Appointment status
    string appointmentNumber; // Unique appointment number
};

// Structure to store staff details
struct Staff{
    string staffUsername; // Staff's username
    unsigned int staffHashedPassword; // Hashed password
};

// Structure to store vehicle service records
struct VehicalRecords{
    string registerNum;
    string vehicalOwner; // Vehicle owner
    string ServiceHistory; // Service history
    string partsReplaced; // Parts replaced
    string recommendations; // Service recommendations
};




// Display main menu
void vehicleServiceCenterManagementSystemHome() {
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\t\t\tVehicle Service Center - HOME\n\n";
    cout << "\t\t1. Customer\n";
    cout << "\t\t2. Staff\n";
    cout << "\t\t3. Exit\n";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "   Enter the number you want to access (1/2/3) : ";
}

// Display customer menu
void customerMenu() {
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\t\t\t\tCustomer Menu\n\n";
    cout << "\t\t1. Sign up\n";
    cout << "\t\t2. Sign in\n";
    cout << "\t\t3. Exit\n";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "   Enter the number you choose (1/2/3) : ";
}

// Display staff menu
void staffMenu() {
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\t\t\tStaff Menu\n\n";
    cout << "\t\t1. Sign up\n";
    cout << "\t\t2. Sign in\n";
    cout << "\t\t3. Exit\n";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "   Enter the number you choose (1/2/3) : ";
}

// Display customer services menu
void customerServicesMenu() {
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\t\t\tAvailable Services for Customers \n\n";
    cout << "\t\t1. View Service Records\n";
    cout << "\t\t2. Schedule Service Appointments\n";
    cout << "\t\t3. Cancel Service Appointments\n";
    cout << "\t\t4. Update Personal Information\n";
    cout << "\t\t5. Exit\n";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "   Enter the option you choose (1-5) : ";
}

// Display staff services menu
void staffServicesMenu() {
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "\t\t\tAvailable Services for Staff\n\n";
    cout << "\t\t1. View Schedule\n";
    cout << "\t\t2. Access Vehicle Records\n";
    cout << "\t\t3. Update Service Records\n";
    cout << "\t\t4. Mark Service as Complete\n";
    cout << "\t\t5. Exit\n";
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "   Enter the option you choose (1-5) : ";
}




// Function to get service name based on user input
string Services(string& input){
    string output;
    // Check input and set service name
    if (input == "1") {
        output = "Oil Change";
    } else if (input == "2") {
        output = "Tire Rotation";
    } else if (input == "3") {
        output = "Brake Inspection";
    } else if (input == "4") {
        output = "Battery Check";
    } else if (input == "5") {
        output = "AC Service";
    } else if (input == "6") {
        output = "Engine Diagnostic";
    } else if (input == "7") {
        output = "All Service";
    } else {
        cout << "Invalid input"; // Inform user if input is not valid
    }
    return output;
}




// Function to save customer data to a file
void writeCustomerFile(vector<Customer>& customers){
    ofstream customerFile("customer data.txt", ios::in); // Open file to write

    if (customerFile.is_open()) // Check if file is open
    {
        // Write each customer's details to the file
        for (Customer& customer : customers)
        {
            customerFile << customer.customerName
                        << ";" << customer.customerUserName
                        << " " << customer.customerContactNumber
                        << " " << customer.customerEmailAddress
                        << " " << customer.customerHashedPassword
                        << endl;
        }
        customerFile.close(); // Close the file
    }
    else
    {
        cout << "\n\tError opening file for save data.\n"; // Error message if file can't be opened
    }
}

// Function to save staff data to a file
void writeStaffFile(vector<Staff>& staffs){
    ofstream staffFile("staff data.txt", ios::in); // Open file to write

    if (staffFile.is_open()) // Check if file is open
    {
        // Write each staff's details to the file
        for (Staff& staff : staffs)
        {
            staffFile <<  staff.staffUsername
                        << " " << staff.staffHashedPassword
                        << endl;
        }
        staffFile.close(); // Close the file
    }
    else
    {
        cout << "\n\tError opening file for save data.\n"; // Error message if file can't be opened
    }
}

// Function to save appointment data to a file
void writeAppointmentFile(vector<Appointment>& appointments){
    ofstream appointmentFile("appointment data.txt"); // Open file to write

    if (appointmentFile.is_open()) // Check if file is open
    {
        // Write each appointment's details to the file
        for (Appointment& appointment : appointments)
        {
            appointmentFile << appointment.appointmentNumber << ";"
                        << appointment.appointmentService << ";"
                        << appointment.appointmentCustomer << ";"
                        << appointment.appointmentCustomerContact << ";"
                        << appointment.appointmentDate << ";"
                        << appointment.appointmentTime << ";"
                        << appointment.appointmentStatus
                        << endl;
        }

        appointmentFile.close(); // Close the file
    }
    else
    {
        cout <<"\n\tError opening file for save data.\n"; // Error message if file can't be opened
    }
}

// Function to save vehicle record data to a file
void writeVehicalRecordFile(vector<VehicalRecords>& vehicalRecords){
    ofstream VRecordFile("vehical record data.txt"); // Open file to write

    if (VRecordFile.is_open()) // Check if file is open
    {
        // Write each vehicle record's details to the file
        for (VehicalRecords& vehicalRecord : vehicalRecords)
        {
            VRecordFile << vehicalRecord.vehicalOwner
                        << ";" << vehicalRecord.registerNum
                        << ";" << vehicalRecord.ServiceHistory
                        << ";" << vehicalRecord.partsReplaced
                        << ";" << vehicalRecord.recommendations
                        << ";" << endl;
        }

        VRecordFile.close(); // Close the file
    }
    else{
        cout <<"\n\tError opening file for save data.\n"; // Error message if file can't be opened
    }
}




// Function to read customer data from a file
vector<Customer> readCustomerFile() {
    vector<Customer> customers;
    ifstream CusFile("customer data.txt"); // Open file to read

    if (!CusFile.is_open()) { // Check if file is open
        cout << "\n\tError opening the file"; // Error message if file can't be opened
        return customers; // Return empty list
    }

    string line;
    while (getline(CusFile, line)) { // Read each line from the file
        Customer customer;
        istringstream iss(line);

        // Extract customer details from the line
        getline(iss, customer.customerName, ';');
        iss >> customer.customerUserName
            >> customer.customerContactNumber
            >> customer.customerEmailAddress
            >> customer.customerHashedPassword;

        customers.push_back(customer); // Add customer to list
    }

    CusFile.close(); // Close the file

    return customers; // Return the list of customers
}

// Function to read staff data from a file
vector<Staff> readStaffFile() {
    vector<Staff> staffs;
    ifstream StaFile("staff data.txt"); // Open file to read

    if (!StaFile.is_open()) { // Check if file is open
        cout << "\n\tError opening the file"; // Error message if file can't be opened
        return staffs; // Return empty list
    }

    string line;
    while (getline(StaFile, line)) { // Read each line from the file
        Staff staff;
        istringstream iss(line);

        // Extract staff details from the line
        iss >> staff.staffUsername
            >> staff.staffHashedPassword;

        staffs.push_back(staff); // Add staff to list
    }

    StaFile.close(); // Close the file

    return staffs; // Return the list of staff members
}

// Function to read appointment data from a file
vector<Appointment> readAppointmentFile() {
    vector<Appointment> appointments;
    ifstream AppFile("appointment data.txt"); // Open file to read

    if (!AppFile.is_open()) { // Check if file is open
        cout << "\n\tError opening the file"; // Error message if file can't be opened
        return appointments; // Return empty list
    }

    string line;
    while (getline(AppFile, line)) { // Read each line from the file
        Appointment appointment;
        istringstream iss(line);

        // Extract appointment details from the line
        getline(iss, appointment.appointmentNumber, ';');
        getline(iss, appointment.appointmentService, ';');
        getline(iss, appointment.appointmentCustomer, ';');
        getline(iss, appointment.appointmentCustomerContact, ';');
        getline(iss, appointment.appointmentDate, ';');
        getline(iss, appointment.appointmentTime, ';');
        getline(iss, appointment.appointmentStatus, ' ');

        appointments.push_back(appointment); // Add appointment to list
    }

    AppFile.close(); // Close the file

    return appointments; // Return the list of appointments
}

// Function to read vehicle record data from a file
vector<VehicalRecords> readVehicalRecordFile(){
    vector<VehicalRecords> vehicalRecords;
    ifstream VRecordFile("vehical record data.txt"); // Open file to read

    if (!VRecordFile.is_open()) { // Check if file is open
        cout << "\n\tError opening the file"; // Error message if file can't be opened
        return vehicalRecords; // Return empty list
    }

    string line;
    while (getline(VRecordFile, line)) { // Read each line from the file
        VehicalRecords vehicalRecord;
        istringstream iss(line);

        // Extract vehicle record details from the line
        getline(iss, vehicalRecord.vehicalOwner, ';');
        getline(iss, vehicalRecord.registerNum, ';');
        getline(iss, vehicalRecord.ServiceHistory, ';');
        getline(iss, vehicalRecord.partsReplaced, ';');
        getline(iss, vehicalRecord.recommendations, ';');

        vehicalRecords.push_back(vehicalRecord); // Add vehicle record to list
    }

    VRecordFile.close(); // Close the file

    return vehicalRecords; // Return the list of vehicle records
}




// Function for a customer to sign up
void customerSignUp() {
    vector<Customer> customers = readCustomerFile(); // Read existing customer data
    string username, name, password, contactNumber, emailAdd;

    cout << "\n\t*************************************\n";
    cout << "\t*          Customer Sign Up         *\n";
    cout << "\t*************************************\n";
    cout << "Enter your details below:\n";

    cout << "\tEnter your full name: ";
    cin.ignore();
    getline(cin, name);

    cout << "\tEnter your contact number: ";
    getline(cin, contactNumber);

    while (!ContactNumberValid(contactNumber)) {
        cout << "\tInvalid contact number. Please try again: ";
        getline(cin, contactNumber);
    }

    cout << "\tEnter your email address: ";
    getline(cin, emailAdd);

    while (!EmailAddressValid(emailAdd)) {
        cout << "\tInvalid email address. Please try again: ";
        getline(cin, emailAdd);
    }

    cout << "\n\t-------------------------------------\n";
    cout << "\tEnter your login credentials below:\n";

    cout << "\tEnter your desired username: ";
    cin >> username;

    cout << "\tEnter your password: ";
    cin >> password;

    Customer newCustomer;

    newCustomer.customerName = name;
    newCustomer.customerUserName = username;
    newCustomer.customerContactNumber = contactNumber;
    newCustomer.customerEmailAddress = emailAdd;
    newCustomer.customerHashedPassword = Hash(password);

    customers.push_back(newCustomer); // Add new customer to the list

    cout << "\n\t*************************************\n";
    cout << "\t**      Sign Up Successful!        **\n";
    cout << "\t*************************************\n";
    cout << "You have successfully signed up as a customer.\n";
    writeCustomerFile(customers); // Save updated customer data
}

// Function for staff to sign up
void staffSignUp() {
    vector<Staff> staffs = readStaffFile(); // Read existing staff data
    string username, password;

    cout << "\n\t*************************************\n";
    cout << "\t*          Staff Sign Up           *\n";
    cout << "\t*************************************\n";
    cout << "Enter your details below:\n";

    cout << "\tEnter your desired username: ";
    cin.ignore();
    getline(cin, username);

    cout << "\tEnter your password: ";
    cin >> password;

    Staff newStaff;

    newStaff.staffUsername = username;
    newStaff.staffHashedPassword = Hash(password);

    staffs.push_back(newStaff); // Add new staff to the list

    cout << "\n\t*************************************\n";
    cout << "\t**      Sign Up Successful!        **\n";
    cout << "\t*************************************\n";
    cout << "You have successfully signed up as a staff member.\n";
    writeStaffFile(staffs); // Save updated staff data
}




// Display the list of available services
void availableServices() {
    vector<Appointment> appointments = readAppointmentFile(); // Read existing appointments
    bool haveApp = false; // Flag to check if there are any appointments

    // Print the list of services
    cout << "\n*********************************************************************************\n";
    cout << "\n\nAvailable Service lists\n\n";
    cout << " 1. Oil Change\n";
    cout << " 2. Tire Rotation\n";
    cout << " 3. Brake Inspection\n";
    cout << " 4. Battery Check\n";
    cout << " 5. AC Service\n";
    cout << " 6. Engine Diagnostic\n";
    cout << " 7. All Service\n";
    cout << "\n*********************************************************************************\n";
}

// Schedule a new appointment
void scheduleAppointment(Customer& customer) {
    vector<Appointment> appointments = readAppointmentFile(); // Get current appointments
    string time, date, serviceNo;
    bool overlappingService = false; // Flag to check if the service already exists

    // Input service number
    cout << "\n\tEnter Service no: ";
    cin >> serviceNo;

    // Input and validate appointment time
    cout << "\tEnter Appointment Time (HH:MM): ";
    cin >> time;
    while (!TimeValid(time)) {
        cout << "\n\tInvalid time format. (Correct format : HH:MM) : ";
        cin >> time;
    }

    // Input and validate appointment date
    cout << "\tEnter Appointment Date (DD/MM/YYYY): ";
    cin >> date;
    while (!DateValid(date)) {
        cout << "\n\tInvalid date format. (Correct format : DD/MM/YYYY) : ";
        cin >> date;
    }

    // Check for overlapping services
    for (Appointment& appointment : appointments) {
        if (date == appointment.appointmentDate && time == appointment.appointmentTime && serviceNo == appointment.appointmentService) {
            overlappingService = true;
            break;
        }
    }

    // Add new appointment if no overlap
    if (!overlappingService) {
        Appointment newAppointment;
        newAppointment.appointmentNumber = to_string(appointments.size() + 1); // Assign a new appointment number
        newAppointment.appointmentService = serviceNo;
        newAppointment.appointmentCustomer = customer.customerName;
        newAppointment.appointmentCustomerContact = customer.customerContactNumber;
        newAppointment.appointmentDate = date;
        newAppointment.appointmentTime = time;
        newAppointment.appointmentStatus = "PENDING";

        appointments.push_back(newAppointment); // Add the new appointment to the list
        writeAppointmentFile(appointments); // Save updated appointments
        cout << "\tAppointment placed successfully !!!\n";
        cout << "\n*********************************************************************************\n";
    }else {
        cout << "\tAppointment is overlapping...";
    }
}

// View a customer's service records
void viewServiceRecord(Customer& customer) {
    vector<Appointment> appointments = readAppointmentFile(); // Get all appointments
    vector<Customer> updateCustomers = readCustomerFile(); // Get all customer data

    bool hasUpcomingAppointments = false; // Flag for upcoming appointments
    bool hasPreviousAppointments = false; // Flag for previous appointments

    // Print customer's information
    for(Customer& updateCustomer : updateCustomers){
        if(customer.customerName == updateCustomer.customerName){
            cout << "\n*********************************************************************************\n" << endl;
            cout << "\t\t\tCustomer's informations" << endl;
            cout << "\n\t\tName :\t\t\t" << customer.customerName << endl;
            cout << "\t\tContact number :\t" << updateCustomer.customerContactNumber << endl;
            cout << "\t\tEmail address :\t\t" << updateCustomer.customerEmailAddress << endl;
            cout << "\n*********************************************************************************\n" << endl;
        }
    }

    // Check for upcoming appointments
    for (Appointment& appointment : appointments) {
        if (customer.customerName == appointment.appointmentCustomer && appointment.appointmentStatus == "PENDING") {
            hasUpcomingAppointments = true;
        }
    }

    // Print upcoming appointments
    if (hasUpcomingAppointments){
        cout << "\tUpcoming appointments\n" << endl;
        for (Appointment& appointment : appointments) {
            if (customer.customerName == appointment.appointmentCustomer && appointment.appointmentStatus == "PENDING") {
                string input = appointment.appointmentService;
                string service = Services(input);
                cout << "\nService : " << service
                     << "\nDate : " << appointment.appointmentDate
                     << "\nTime : " << appointment.appointmentTime << "\n\n\n" <<endl;
            }
        }
    }

    // Check for previous appointments
    for (Appointment& appointment : appointments) {
        if (customer.customerName == appointment.appointmentCustomer && appointment.appointmentStatus == "OK") {
            hasPreviousAppointments = true;
        }
    }

    // Print previous appointments
    if (hasPreviousAppointments){
        cout << "\tPrevious appointments\n" << endl;
        for (Appointment& appointment : appointments) {
            if (customer.customerName == appointment.appointmentCustomer && appointment.appointmentStatus == "OK") {
                string input = appointment.appointmentService;
                string service = Services(input);
                cout << "\nService : " << service
                     << "\nDate : " << appointment.appointmentDate
                     << "\nTime : " << appointment.appointmentTime << "\n\n\n" <<endl;
            }
        }
    }

    // No previous appointments message
    if (!hasPreviousAppointments) {
        cout << "\tYou have no previous appointments !\n";
    }

    // No upcoming appointments message
    if (!hasUpcomingAppointments) {
        cout << "\n\tYou have no upcoming appointments !\n";
    }
}

// Update a customer's contact information and email address
void updateCustomerData(Customer& customerUpdate) {
    vector<Customer> customers = readCustomerFile(); // Get all customers
    vector<Appointment> appointments = readAppointmentFile(); // Get all appointments

    string newContactNumber;
    string newEmailAddress;
    cin.ignore(); // Ignore leftover input
    cout << "\tEnter Your new Contact number: ";
    getline(cin, newContactNumber);

    // Validate new contact number
    while (!ContactNumberValid(newContactNumber)) {
        cout << "\tInvalid contact number : ";
        getline(cin, newContactNumber);
    }

    cout << "\tEnter Your Email Address: ";
    getline(cin, newEmailAddress);

    // Validate new email address
    while (!EmailAddressValid(newEmailAddress)) {
        cout << "\tInvalid Email address : ";
        getline(cin, newEmailAddress);
    }
    // Find and update customer information
    for (Customer& customer : customers) {
        if (customerUpdate.customerName == customer.customerName) {

            // Update customer data
            customer.customerContactNumber = newContactNumber;
            customer.customerEmailAddress = newEmailAddress;

            // Save updated customer data to file
            ofstream customerFile("customer data.txt");
            if (customerFile.is_open()) {
                for (const Customer& updatedCustomer : customers) {
                    customerFile << updatedCustomer.customerName
                                << ";" << updatedCustomer.customerUserName
                                << " " << updatedCustomer.customerContactNumber
                                << " " << updatedCustomer.customerEmailAddress
                                << " " << updatedCustomer.customerHashedPassword
                                << endl;
                }
                customerFile.close();
                cout << "Successfully saved your data\n";
            } else {
                cout << "\n\tError opening file for saving data.\n";
            }

            // Update appointments with new contact number
            for (Appointment& appointment : appointments) {
                if (appointment.appointmentCustomer == customer.customerName) {
                    appointment.appointmentCustomerContact = newContactNumber;
                    ofstream appointmentFile("appointment data.txt");

                    if (appointmentFile.is_open()) {
                        for (const Appointment& updatedAppointment : appointments) {
                            appointmentFile << updatedAppointment.appointmentNumber << ";"
                                            << updatedAppointment.appointmentService << ";"
                                            << updatedAppointment.appointmentCustomer << ";"
                                            << updatedAppointment.appointmentCustomerContact << ";"
                                            << updatedAppointment.appointmentDate << ";"
                                            << updatedAppointment.appointmentTime << ";"
                                            << updatedAppointment.appointmentStatus
                                            << endl;
                        }
                        appointmentFile.close();
                    } else {
                        cout << "\n\tError opening file for saving data.\n";
                    }
                }
            }
        }
    }
}

// Cancel an existing appointment
void cancelAppointment(Customer& customer) {
    string decision;
    bool hasUpcomingAppointments = false;
    vector<Appointment> appointments = readAppointmentFile(); // Get all appointments

    // Print upcoming appointments
    cout << "\tUpcoming appointments\n" << endl;
    for (const Appointment& appointment : appointments) {
        if (customer.customerName == appointment.appointmentCustomer && appointment.appointmentStatus == "PENDING") {
            hasUpcomingAppointments = true;
            string input = appointment.appointmentService;
            string service = Services(input);
            cout << " " << appointment.appointmentNumber
                 << "  Service : " << service
                 << "     Date : " << appointment.appointmentDate
                 << "     Time : " << appointment.appointmentTime << endl;
        }
    }

    // No upcoming appointments message
    if (!hasUpcomingAppointments) {
        cout << "\t\tYou have no upcoming appointments !\n";
    }

    // Cancel an appointment if available
    if (hasUpcomingAppointments) {
        cout << "   Enter appointment number to cancel the appointment : ";
        cin >> decision;

        bool appointmentFound = false;
        for (Appointment& appointment : appointments) {
            if (customer.customerName == appointment.appointmentCustomer && decision == appointment.appointmentNumber && appointment.appointmentStatus == "PENDING") {
                appointment.appointmentStatus = "DELETED"; // Set appointment status to DELETED
                appointmentFound = true;
                break;
            }
        }

        if (appointmentFound) {
            writeAppointmentFile(appointments); // Save updated appointments
            cout << "Appointment canceled successfully.\n";
        } else {
            cout << "Appointment number not found.\n";
        }
    }
    cout << "\n*********************************************************************************\n" << endl;
}




// Function to view all upcoming appointments
void viewSchedule(){
    vector<Appointment> appointments = readAppointmentFile(); // Read appointments from file
    bool appointmentFound =  false;
    cout << "\n*********************************************************************************\n" << endl;
    cout << "\t\tUpcoming Schedules";

    for(Appointment& appointment : appointments){
        if(appointment.appointmentStatus == "PENDING"){ // Check if appointment is pending
            appointmentFound = true;

            string input = appointment.appointmentService;
            string service = Services(input); // Get the service name
            cout
                 << "\nService : " << service
                 << "\nDate : " << appointment.appointmentDate
                 << "\nTime : " << appointment.appointmentTime
                 << "\nCustomer Name : " << appointment.appointmentCustomer
                 <<"\nCustomer Contact : " << appointment.appointmentCustomerContact << "\n\n\n" <<endl;
        }
    }

    if(!appointmentFound){ // If no pending appointments
        cout << "There are no upcoming service appointments" << endl;
    }
}

// Function to view vehicle records and update if needed
void accessVehicleRecords(){
    vector<VehicalRecords> vehicalRecords = readVehicalRecordFile(); // Read vehicle records from file
    string registrationNumber;
    bool vehicalFound = false;
    bool hasRecords = false;


    cout << "\n*********************************************************************************\n" << endl;
    cout << "List of Vehicle Reports\n\n";

    for(VehicalRecords& vehicalRecord : vehicalRecords){
        cout << "Reg.No : " << vehicalRecord.registerNum << "\tOwner name : " << vehicalRecord.vehicalOwner << endl;
        hasRecords = true;
    }

    if(hasRecords){
        cout << "Enter vehicle Registration number to view service record : ";
        cin.ignore();
        getline(cin,registrationNumber);

        for(VehicalRecords& vehicalRecord : vehicalRecords){
            if(registrationNumber == vehicalRecord.registerNum){ // Find the selected vehicle owner
                vehicalFound = true;
                cout << "\t\tService History : " << vehicalRecord.ServiceHistory << endl;
                cout << "\t\tReplaced parts : " << vehicalRecord.partsReplaced << endl;
                cout << "\t\tVehical Recommendations : " << vehicalRecord.recommendations << endl;
            }
        }
        if(!vehicalFound){ // If the vehicle owner is not found
            cout << "Invalid Vehical registration number !!!";
        }

    } else {
        cout << "No Vehicle Records Available !";
    }

    cout << "\n*********************************************************************************\n" << endl;
}

// Function to update service records for a vehicle
void updateServiceRecords(){
    vector<Appointment> appointments = readAppointmentFile(); // Read appointments
    vector<VehicalRecords> vehicalrecords = readVehicalRecordFile(); // Read vehicle records
    string number, ServiceHistory, partsReplaced, recommendations, vehicleOwner;
    bool appointmentFound = false;
    bool recordUpdated = false;
    bool hasAppointment = false;

    cout << "\n=================================================================================\n" << endl;
    cout << "\tSelect Vehicle owner's name to Update detail :\n\n";
    for (Appointment& appointment : appointments) {
            if(appointment.appointmentStatus == "OK"){ // Show only completed appointments
                cout << "\t" << appointment.appointmentNumber << " - " << appointment.appointmentCustomer << endl;
                hasAppointment = true;
            }
        }

    if (!hasAppointment){ // If no completed appointments
        cout << "\t\t  There are no Completed Service Appointments \n";
        return;
    }

        cout << "\n=================================================================================\n" << endl;
        cout << "   Enter Number : ";
        cin.ignore();
        getline(cin, number); // Get vehicle owner's name
        cout << "\n\tEnter vehicle's Service History: ";
        getline(cin, ServiceHistory);
        cout << "\tEnter Replaced parts of vehicle: ";
        getline(cin, partsReplaced);
        cout << "\tEnter Vehical Recommendations: ";
        getline(cin, recommendations);

        for (Appointment& appointment : appointments) {
            if (appointment.appointmentNumber == number && appointment.appointmentStatus == "OK") { // Find the appointment by owner name
                appointmentFound = true;
                for (VehicalRecords& vehicalrecord : vehicalrecords) {
                    if (appointment.appointmentCustomer == vehicalrecord.vehicalOwner) { // Update existing record
                        vehicalrecord.ServiceHistory = ServiceHistory;
                        vehicalrecord.partsReplaced = partsReplaced;
                        vehicalrecord.recommendations = recommendations;
                        recordUpdated = true;
                        vehicleOwner = appointment.appointmentCustomer;
                        break;
                    }
                }

                if (!recordUpdated) { // Add new record if not found
                    VehicalRecords newRecord;
                    newRecord.vehicalOwner = vehicleOwner;
                    newRecord.registerNum = to_string(vehicalrecords.size() +1);
                    newRecord.ServiceHistory = ServiceHistory;
                    newRecord.partsReplaced = partsReplaced;
                    newRecord.recommendations = recommendations;
                    vehicalrecords.push_back(newRecord);
                }
                break;
            }
        }

        if (!appointmentFound) { // If appointment owner not found
            cout << "\n\tInvalid number\n";
        } else {
            writeVehicalRecordFile(vehicalrecords); // Save updates to file
            cout << "\n\t\tCustomer record updated successfully !\n";
        }

    cout << "\n=================================================================================\n" << endl;
}

// Function to mark a service appointment as complete
void markServiceComplete(){
    vector<Appointment> appointments = readAppointmentFile(); // Read appointments
    string appNo;
    bool appointmentFound = false;
    bool pendingAppointment = false;

    cout << "\n*********************************************************************************\n" << endl;
    cout << "\tPending Appointments\n" << endl;
    for (Appointment& appointment : appointments) {
        if (appointment.appointmentStatus == "PENDING") { // Show pending appointments
            pendingAppointment = true;
            string input = appointment.appointmentService;
            string service = Services(input); // Get the service name
            cout << "\nAppointment Number : " << appointment.appointmentNumber
                 << "\nService : " << service
                 << "\nDate : " << appointment.appointmentDate
                 << "\nTime : " << appointment.appointmentTime
                 << "\nCustomer Name : " << appointment.appointmentCustomer
                 <<"\nCustomer Contact : " << appointment.appointmentCustomerContact << "\n\n\n" <<endl;
        }
    }

    cout << "\n*********************************************************************************\n" << endl;
    if (!pendingAppointment){ // If no pending appointments
        cout << "\t\tYou haven't any pending Appointments !" << endl;
    }

    if (pendingAppointment){
        cout << "\tEnter the appointment number to mark complete: ";
        cin >> appNo; // Get appointment number to mark as complete

        for (Appointment& appointment : appointments) {
            if (appNo == appointment.appointmentNumber && appointment.appointmentStatus == "PENDING") { // Find and complete the appointment
                appointment.appointmentStatus = "OK";
                cout << "\n\t\tAppointment Completed!\n";
                appointmentFound = true;
                break;
            }
        }

        if (!appointmentFound) { // If appointment number is not valid
            cout << "\t\tInvalid number\n";
        } else {
            writeAppointmentFile(appointments); // Save updates to file
        }
    }
}




// Function to handle customer services menu
void customerServices(Customer& customer){
    string decision; // User's choice
    while(true)
    {
        customerServicesMenu(); // Show the menu
        cin >> decision; // Get user choice

        // Handle each option
        if (decision == "1"){
            viewServiceRecord(customer); // View service records
        }
        else if (decision == "2"){
            availableServices(); // Show available services
            scheduleAppointment(customer); // Schedule a new appointment
        }
        else if (decision == "3"){
            cancelAppointment(customer); // Cancel an existing appointment
        }
        else if (decision == "4"){
            updateCustomerData(customer); // Update customer information
        }
        else if (decision == "5"){
            cout << "Exiting..."; // Exit the menu
            return;
        }
        else{
            cout << "\n\t\tInvalid choice. Please try again.\n"; // Handle invalid input
        }
    }
}

// Function to handle staff services menu
void staffServices(){
    string decision; // User's choice
    while(true)
    {
        staffServicesMenu(); // Show the menu
        cin >> decision; // Get user choice

        // Handle each option
        if (decision == "1"){
            viewSchedule(); // View the staff schedule
        }
        else if (decision == "2"){
            accessVehicleRecords(); // Access vehicle records
        }
        else if (decision == "3"){
            updateServiceRecords(); // Update service records
        }
        else if (decision == "4"){
            markServiceComplete(); // Mark service as complete
        }
        else if (decision == "5"){
            cout << "Exiting..."; // Exit the menu
            return;
        }
        else{
            cout << "\n\t\tInvalid choice. Please try again.\n"; // Handle invalid input
        }
    }
}




// Function to handle customer login
bool customerLogIn(){
    vector<Customer> customers = readCustomerFile(); // Load customer data
    string username;

    cout << "\n\tEnter username: ";
    cin >> username; // Get username

    string password = getPassword(); // Get password

    unsigned int hashedPassword = Hash(password); // Hash the password

    // Check if the username and password match any customer
    for (Customer& customer : customers)
    {
        if (customer.customerUserName == username && customer.customerHashedPassword == hashedPassword)
        {
            cout << "\n\t\t\tLogin successful !\n";
            customerServices(customer); // Show customer services
            return true;
        }
    }

    cout << "\n\t\tLogin failed !!! Invalid username or password !\n";
    return false;
}

// Function to handle staff login
bool staffLogin(){
    vector<Staff> staffs = readStaffFile(); // Load staff data
    string username;

    cout << "\n\tEnter username: ";
    cin >> username; // Get username

    string password = getPassword(); // Get password

    unsigned int hashedPassword = Hash(password); // Hash the password

    // Check if the username and password match any staff
    for (Staff& staff : staffs)
    {
        if (staff.staffUsername == username && staff.staffHashedPassword == hashedPassword)
        {
            cout << "\n\t\t\tLogin successful !\n";
            staffServices(); // Show staff services
            return true;
        }
    }

    cout << "\n\t\tLogin failed !!! Invalid username or password !\n";
    return false;
}




// Function to handle the customer menu
void customerHome(){
    while(true)
    {
        string decision; // User's choice
        customerMenu(); // Show the menu
        cin >> decision; // Get user choice

        // Handle each option
        if (decision == "1"){
            customerSignUp(); // Sign up a new customer
        }
        else if (decision == "2"){
            customerLogIn(); // Log in an existing customer
        }
        else if (decision == "3"){
            cout << "\n\t\t\t\tExiting...";
            return; // Exit the menu
        }
        else {
            cout << "\n\t\tInvalid input. Please try again !"; // Handle invalid input
        }
    }
}

// Function to handle the staff menu
void staffHome(){
    while(true)
    {
        string decision; // User's choice
        staffMenu(); // Show the menu
        cin >> decision; // Get user choice

        // Handle each option
        if (decision == "1"){
            staffSignUp(); // Sign up a new staff member
        }
        else if (decision == "2"){
            staffLogin(); // Log in an existing staff member
        }
        else if (decision == "3"){
            cout << "\n\t\t\t\tExiting...";
            return; // Exit the menu
        }
        else {
            cout << "\n\t\tInvalid input. Please try again !"; // Handle invalid input
        }
    }
}



// Main function to control the program flow
int main(){
    while (true)
    {
        vehicleServiceCenterManagementSystemHome(); // Show main menu
        string decision; // User's choice
        cin >> decision; // Get user choice

        // Handle each option
        if (decision == "1"){
            customerHome(); // Go to customer menu
        }
        else if (decision == "2"){
            staffHome(); // Go to staff menu
        }
        else if (decision == "3"){
            cout << "Exiting....\n";
            cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n" <<endl;
            break; // Exit the program
        }
        else{
            cout << "\n\t\tInvalid input. Please try again !"; // Handle invalid input
        }
    }

    return 0;
}

