#include "BinHeap.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
using namespace std;

int runSim(int a1, int a2, int a3);
float average(vector<float> set);
float standardDeviation(vector<float> set, int avg);


int main(int argc, char* argv[]){
	srand(time(NULL));
	int persianWinCount = 0;
	int spartanWinCount = 0;
	int a1 = atoi(argv[1]);
	int a2 = atoi(argv[2]);
	int a3 = atoi(argv[3]);
	int result = 0;

	int totalAliveSpartans = 0;
	int totalAlivePersians = 0;

	float totalTime = 0;
	clock_t start;
	float elapsed;

	vector<float> time;
	vector<float> persianCount;
	vector<float> spartanCount;
	for (int i = 0; i < a1; i++){
		
		start = clock();
		
		result = runSim(a1, a2, a3);
		totalTime = float(clock() - start) / CLOCKS_PER_SEC;
		cout << "\tTime: " << totalTime << " seconds" << endl;
		time.push_back(totalTime);

		if (result > 0){
			spartanCount.push_back(abs(result));
			spartanWinCount++;
		}
		if (result < 0){
			persianCount.push_back(abs(result));
			persianWinCount++;
		}
	}

	cout << "\nThe number of times the Persians won was " << persianWinCount << endl;
	cout << "The number of times the Spartans won was " << spartanWinCount << "\n" << endl;

	cout << "The average amount of time it took to run a single simulation was " << average(time) << endl;
	cout << "\tStandard Deviation: " << standardDeviation(time, average(time)) << "\n" << endl;

	cout << "The average number of Spartans remaining when they win is: " << average(spartanCount) << endl;
	cout << "\tStandard Deviation: " << standardDeviation(spartanCount, average(spartanCount)) << "\n" << endl;
	
	cout << "The average number of Persians remaining when they win is: " << average(persianCount) << endl;
	cout << "\tStandard Deviation: " << standardDeviation(persianCount, average(persianCount)) << "\n" << endl;

	system("pause");
}

int runSim(int a1, int a2, int a3){
	BinaryHeap<Soldier> test;
	test.buildSoldiers(a2, a3);
	return test.events();
	test.makeEmpty();

}

float standardDeviation(vector<float> set, int avg){
	float total = 0;
	for (int i = 0; i < set.size(); i++){
		total += (pow((set.at(i) - avg), 2));
	}
	return total / set.size();
}

float average(vector<float> set){
	float avg = 0;
	for (int i = 0; i < set.size(); i++){
		avg += set.at(i);
	}
	avg = avg / set.size();
	return avg;
}