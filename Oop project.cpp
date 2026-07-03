#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class announcement {
private:
    int id;
    string title;
    string category;
    string depart;
    string content;

public:
    announcement(int i, string t, string c, string d, string cont) {
        id = i;
        title = t;
        category = c;
        depart = d;
        content = cont;
    }

    int getId() {
        return id; 
    }

    string getDepartment() {
        return depart; 
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Category: " << category << endl;
        cout << "Department: " << depart << endl;
        cout << "Content: " << content << endl;
    }

    void file() {
        ofstream file("announcements.txt", ios::app);
        file << id << "|" << title << "|" << category << "|" << depart << "|" << content << endl;
        file.close();
    }
};

class notification {
public:
    // pure virtual function
    virtual void send(string msg) = 0;
};

class emailNotification : public notification {
public:
    void send(string msg) {
        cout << "Email Notification: " << msg << endl;
    }
};

class user {
protected:
    string name;
    string department;

public:
    user(string n, string d) {
        name = n;
        department = d;
    }

    // polymorphism
    virtual void menu() = 0;
};

class student : public user {
public:
    student(string n, string d) : user(n, d) {}

    void menu() {
        cout << "\nStudent Menu - " << name << endl;
        cout << "1. View Announcements" << endl;
        cout << "2. Exit" << endl;
    }

    void viewAnnouncements() {
        ifstream file("announcements.txt");
        string line;
        cout << "\nAvailable Announcements: \n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
};

// Faculty class
class faculty : public user {
public:
    faculty(string n, string d) : user(n, d) {}

    void menu() {
        cout << "\nFaculty Menu - " << name << endl;
        cout << "1. Post Announcement" << endl;
        cout << "2. Exit" << endl;
    }

    void postAnnouncement() {
        int id;
        string title, category, content;
        cout << "Enter Announcement ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Category (Academic/Event/Emergency): ";
        getline(cin, category);
        cout << "Enter Content: ";
        getline(cin, content);

        announcement a(id, title, category, department, content);
        a.file();

        notification* n = new emailNotification();
        n->send("New announcement posted");
    }
};

// Admin class
class admin : public user {
public:
    admin(string n) : user(n, "All") {}

    void menu() {
        cout << "\nAdmin Menu - " << name << endl;
        cout << "1. Post Announcement" << endl;
        cout << "2. Exit" << endl;
    }

    void postAnnouncement() {
        int id;
        string title, category, department, content;
        cout << "Enter Announcement ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Category: ";
        getline(cin, category);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter Content: ";
        getline(cin, content);

        announcement a(id, title, category, department, content);
        a.file();

        notification* n = new emailNotification();
        n->send("New announcement posted");
    }
};

// Main function
int main() {
    int choice;
    cout << "DIGITAL NOTICE BOARD SYSTEM" << endl;
    cout << "1. Student" << endl;
    cout << "2. Faculty" << endl;
    cout << "3. Admin" << endl;
    cout << "Select User Type: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        student s("Ali", "CS");
        s.menu();
        int op;
        cin >> op;
        if (op == 1) {
            s.viewAnnouncements();
        }
    }
    else if (choice == 2) {
        faculty f("Dr. Ahmad", "CS");
        f.menu();
        int op;
        cin >> op;
        if (op == 1) {
            f.postAnnouncement();
        }
    }
    else if (choice == 3) {
        admin a("System Admin");
        a.menu();
        int op;
        cin >> op;
        if (op == 1) {
            a.postAnnouncement();
        }
    }
    else {
        cout << "Invalid choice" << endl;
    }

    return 0;
}

