#include <bits/stdc++.h>
using namespace std;

//#define DEBUG

// Structures
struct lungomare
{
	long long int result;
	long long int actual;
};

struct choosedStruct
{
	lungomare choosed;
	int increment = 0;
};


// Variabiles
vector<long long int> passerella;
vector<long long int> stradaLago;

long long int percorri(int N, long long int L, long long int D[], long long int P[]);
lungomare scegli(int index,  int stop,lungomare before);
choosedStruct compare(lungomare option1, lungomare option2, int i, int increment);

long long int percorri(int N, long long int L, long long int D[], long long int P[])
{
	// Inizialie variabiles
	long long int lastPasserella = 0;
	passerella.resize(N+1);
	stradaLago.resize(N+1);
	stradaLago.push_back(LONG_LONG_MAX - D[0] - P[0] - 1);
	for (size_t i = 0; i < N; ++i)
	{
		passerella.push_back(D[i] - lastPasserella);
		lastPasserella = D[i];
		stradaLago.push_back(P[i]);
	}
	passerella.push_back(L - lastPasserella);

#ifdef DEBUG
	cout << "LIST: " << endl;
	for (size_t i = 0; i < stradaLago.size(); ++i)
		cout << i << ")\tD: " << stradaLago[i] << "\tP: " << passerella[i] << endl;
#endif // DEBUG

	lungomare start;
	start.actual = 0;
	start.result = 0;
	return scegli(0, passerella.size(), start).result;
}

lungomare scegli(int index, int stop, lungomare before)
{
	lungomare option1;
	lungomare option2;

	for (size_t i = index; i < stop; ++i)
	{
		option1.actual = stradaLago[i] + passerella[i];
		option1.result = max(option1.actual, max(before.actual + stradaLago[i], before.result));

		option2.actual = before.actual + passerella[i];
		option2.result = max(option2.actual, max(before.actual + passerella[i], before.result));

		/*if (option1.actual >= option2.actual && option1.result >= option2.result)
		{
			before.actual = option2.actual;
			before.result = option2.result;
		}
		else if (option1.actual <= option2.actual && option1.result <= option2.result)
		{
			before.actual = option1.actual;
			before.result = option1.result;
		}
		else
		{
#ifdef DEBUG
			cout << "create: " << i << endl;
			cout << "\tbefore: " << before.actual << "\t" << before.result << endl;
			cout << "\toption1: " << option1.actual << "\t" << option1.result << endl;
			cout << "\toption2: " << option2.actual << "\t" << option2.result << endl;
#endif // DEBUG

			before.result = min(scegli(i + 1, option1).result, scegli(i + 1, option2).result);
			return before;
		}*/

		choosedStruct tmp = compare(option1, option2, i, 0);
		i += tmp.increment;
		before = tmp.choosed;
		
#ifdef DEBUG
		cout << "turn: " << i << endl;
		cout << "\tbefore: " << before.actual << "\t" << before.result << endl;
		cout << "\toption1: " << option1.actual << "\t" << option1.result << endl;
		cout << "\toption2: " << option2.actual << "\t" << option2.result << endl;
#endif // DEBUG
	}

	return before;
}

choosedStruct compare(lungomare option1, lungomare option2, int i, int increment)
{
	choosedStruct solution;
	solution.increment = increment;

	if (option1.actual >= option2.actual && option1.result >= option2.result)
	{
		solution.choosed.actual = option2.actual;
		solution.choosed.result = option2.result;
	}
	else if (option1.actual <= option2.actual && option1.result <= option2.result)
	{
		solution.choosed.actual = option1.actual;
		solution.choosed.result = option1.result;
	}
	else
	{
#ifdef DEBUG
		cout << "create: " << i << endl;
		cout << "\tsolution: " << solution.choosed.actual << "\t" << solution.choosed.result << endl;
		cout << "\toption1: " << option1.actual << "\t" << option1.result << endl;
		cout << "\toption2: " << option2.actual << "\t" << option2.result << endl;
#endif // DEBUG
		return compare(scegli(i + 1, i + 2, option1), scegli(i + 1, i + 2, option2), i + 1, increment + 1);
	}
	return solution;
}