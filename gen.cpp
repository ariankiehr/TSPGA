#include<iostream>
#include <stdlib.h>
#include <time.h>
#define LIMITE 80
#define MAXCOO 99

using namespace std;

int main(){
	srand(time(NULL));
	int ciudades = (rand() % LIMITE) + 5;
	cout << ciudades << endl;
	for(int i=0; i < ciudades; i++) {
		cout << rand() % MAXCOO << " " << rand() % MAXCOO << endl;
	}
	return 0;
}
