#include <iostream>
#include <fstream>
#include "stack-vm.h"
using namespace std;
int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " <filename>" << endl;
		return 0;
	}

	ifstream r(argv[1], ios::binary);
	           if (!r) {
                cerr << "Error: Could not open file " << argv[1] << endl;
                return 1;
        }

	i32 i;
	vector<i32> prog;

	while (r.read((char*)&i, sizeof(i))) {
		prog.push_back(i);
	}
	r.close();
	StackVM vm;
	vm.loadProgram(prog);
	vm.run();

	return 0;
}
