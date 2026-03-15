#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char *argv[]) {
    string filename = argv[1];
    ifstream ifs(filename);
    if (ifs.is_open()) {
        while (!ifs.eof()) {
            string city;
            double tmp = 0;
            double avg = 0;
            ifs >> city;
            if (ifs.fail()) {
                break;
            }
            for (int i = 0; i < 4; i++) {
                ifs >> tmp;
                avg += tmp;
            }
            avg /= 4;
            cout << city << " " << avg << "\n";
        }
	ifs.close();
    }
    else {
        cerr << "Nome file non valido\n";
        return 1;
    }
    return 0;
}
