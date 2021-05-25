#include <iostream>
#include <string>
using namespace std;

class SandGrain{
	public:
		int x;
		int y;
};

int main(void){
	SandGrain sg;
	sg.x = 10;
	sg.y = 12;
	
	string sandDescription = "X-Coord: "+to_string(sg.x)+" Y-Coord: "+to_string(sg.y)+"\n";
	cout << sandDescription;
	return 0;
}
