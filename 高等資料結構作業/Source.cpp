#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <fcntl.h>
#include <io.h>

using namespace std;

struct _record {
    _record() {};
    string date;
    string id;
    string age;
    string area;
    string item_class;
    string item;
    int num;
    int cost;
    int price;

    void print() {
        cout << date << "," << id << "," << age << "," << area << "," << item_class << "," << item << "," << num << "," << cost << "," << price << endl;
    }
    string write() {
        return date + id +  age + area + item_class + item + to_string(num) + to_string(cost) + to_string(price);
    }
};

_record get_a_record(string line, _record* temp) {

    stringstream ss(line);
    string value;

    getline(ss, temp->date, ',');
    getline(ss, temp->id, ',');
    getline(ss, temp->age, ',');
    getline(ss, temp->area, ',');
    getline(ss, temp->item_class, ',');
    getline(ss, temp->item, ',');
    getline(ss, value, ',');
    temp->num = stoi(value);
    getline(ss, value, ',');
    temp->cost = stoi(value);
    getline(ss, value, ',');
    temp->price = stoi(value);

    return *temp;
}
string hashing(int key,int &level) {

    int temp = key % (10 * int(pow(2, level)));
    return to_string(temp);

}
void insert(string data_file ,int key , _record record) {


}
int main() {

    string line;
    string data_file = "data.db";
	ifstream file("D100K.txt");
    int level = 0;
    int next = 0;
    int bucket_num = 2;

    if (!file) {
        cerr << "Error: Unable to open the D100K file." << endl;
        system("pause");
        return 1;
    }

    int fd = _open(data_file.c_str(), O_CREAT | O_RDWR);
    if (fd < 0) {
        cerr << "Error: Unable to create/open the data file." << endl;
        exit(EXIT_FAILURE);
    }




    getline(file, line);
    while (getline(file, line)) {

        _record* record = new _record();
        get_a_record(line, record);

        insert(data_file, stoi(record->id), *record);

        char buffer[58];
        _write(fd, record->write().c_str(), 58);
        if(_read(fd, buffer, sizeof(buffer))) cout << buffer << endl;

        cout << 1;
    }





    _close(fd);
    return 0;
}