#include <iostream>
#include <limits>
#include <string>

using namespace std;

class publication {
protected:
	string title;
	float price;

public:
	void getdata() {
		cout << "Enter title: ";
		getline(cin, title);

		cout << "Enter price: ";
		cin >> price;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void putdata() const {
		cout << "Title: " << title << '\n';
		cout << "Price: " << price << '\n';
	}
};

class sales {
protected:
	float monthly_sales[3];

public:
	void getdata() {
		for (int i = 0; i < 3; ++i) {
			cout << "Enter sales amount for month " << (i + 1) << ": ";
			cin >> monthly_sales[i];
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	void putdata() const {
		cout << "Sales for last 3 months:\n";
		for (int i = 0; i < 3; ++i) {
			cout << "Month " << (i + 1) << ": " << monthly_sales[i] << '\n';
		}
	}
};

class book : public publication, public sales {
private:
	int page_count;

public:
	void getdata() {
		publication::getdata();
		cout << "Enter page count: ";
		cin >> page_count;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		sales::getdata();
	}

	void putdata() const {
		publication::putdata();
		cout << "Page count: " << page_count << '\n';
		sales::putdata();
	}
};

class tape : public publication, public sales {
private:
	float playing_time;

public:
	void getdata() {
		publication::getdata();
		cout << "Enter playing time (minutes): ";
		cin >> playing_time;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		sales::getdata();
	}

	void putdata() const {
		publication::putdata();
		cout << "Playing time (minutes): " << playing_time << '\n';
		sales::putdata();
	}
};

class disk : public publication, public sales {
private:
	enum disk_type { CD, DVD } type;

public:
	void getdata() {
		char choice;

		publication::getdata();
		cout << "Enter disk type (c for CD, d for DVD): ";
		cin >> choice;
		while (choice != 'c' && choice != 'C' && choice != 'd' && choice != 'D') {
			cout << "Invalid choice. Enter c for CD or d for DVD: ";
			cin >> choice;
		}
		type = (choice == 'c' || choice == 'C') ? CD : DVD;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		sales::getdata();
	}

	void putdata() const {
		publication::putdata();
		cout << "Disk type: " << (type == CD ? "CD" : "DVD") << '\n';
		sales::putdata();
	}
};

int main() {
	book b;
	tape t;
	disk d;

	cout << "Enter details for BOOK\n";
	b.getdata();

	cout << "\nEnter details for TAPE\n";
	t.getdata();

	cout << "\nEnter details for DISK\n";
	d.getdata();

	cout << "\n--- BOOK DATA ---\n";
	b.putdata();

	cout << "\n--- TAPE DATA ---\n";
	t.putdata();

	cout << "\n--- DISK DATA ---\n";
	d.putdata();

	return 0;
}
