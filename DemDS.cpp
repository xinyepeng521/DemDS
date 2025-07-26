#include<iostream>
#include<fstream>
#include<sstream>
#include"DemDS.h"
using namespace std;

int main(int argc, char* argv[])
{
    stringstream ss;
    string filename;
    ss << argv[1];
    ss >> filename;
    ss.clear();
    ss << argv[2];
    ss >> seed;
    ss.clear();
    ss << argv[3];
    ss >> cutoff_time;
    ss.clear();
    ss << argv[4];
    ss >> alpha;
    ss.clear();
    ifstream infile(filename);
    if (!infile) {
        cerr << "Open instance file failed." << endl;
        return 1;
    }
    gen.seed(seed);
    MDSP a;
    infile >> a;
    
    a.DemDS();
    cout << filename << "," << a.X2.size() + 1 << "," << a.best_time << endl;
}
