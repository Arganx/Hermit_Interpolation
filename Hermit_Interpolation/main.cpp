#include <iostream>

using namespace std;

void fill(double* T, int size)
{
	for (int i = 0; i < size; i++)
	{
		cin >> T[i];
	}
}

double silnia(double a)
{
	double result=1;
	for (int i = 1; i <= a; i++)
	{
		result *= i;
	}
	return result;
}


double* wspolczynniki(double* Arg, double*Val, double** Der, int size, int derivatives)
{
	int tmp = 0;
	double* wsp = new double[(derivatives + 1)*size];//pomocna tablica
	for (int j = 0; j < size; j++)
	{
		for (int i = 0; i < derivatives + 1; i++)
		{
			wsp[tmp] = Val[j];
			tmp++;
		}
	}
	tmp = 0;//wartosci derivatives np 0 1 2
	int tmp2 = 0;
	double* wyniki = new double[(derivatives + 1)*size];
	for (int j = 0; j < size*(derivatives + 1) - 1; j++)
	{
		wyniki[j] = wsp[0];
		for (int i = 0; i < size*(derivatives + 1)-j-1; i++)
		{
			if (wsp[i] == wsp[i+1])
			{
				tmp = i / (derivatives + 1);//zaokragla w dol
				wsp[i] = Der[j][tmp];//co deriviate+1 przeskok o +1
				wsp[i] = wsp[i] / silnia(j+1);
			}
			else
			{
				tmp = i / (derivatives + 1);
				tmp2 =(i+1+j) / (derivatives + 1);
				wsp[i] = (wsp[i+1] - wsp[i]) / (Arg[tmp2] - Arg[tmp]);//Nie te Argumenty te sa: 0,1,2 a musza byc 0...8
			}
		}
		wyniki[size*(derivatives + 1) - 1] = wsp[0];
	}
	delete[] wsp;
	return wyniki;
}

double Hermit(double* Arg, double*Val, double** Der, int size, int derivatives, double x)
{
	double* wsp = wspolczynniki(Arg,Val,Der,size,derivatives);
	cout << "Wspolczynniki:" << endl;
	double result=wsp[0];
	double tmp = 1;
	for (int i = 1; i < size*(derivatives + 1); i++)
	{
		cout << "Przejscie: " << i << " tmp: " << tmp << endl;
		tmp *= x - Arg[(i-1)/(derivatives+1)];
		result += wsp[i] * tmp;
	}
	delete[] wsp;
	return result;
}

int main() {
	
	cout << "Podaj liczbe znanych pochodnych" << endl;
	int derivatives;
	cin >> derivatives;
	cout << "Podaj liczbe znanych punktow" << endl;
	int size;
	cin >> size;
	double* Arg = new double[size];
	double* Val = new double[size];
	double** Der = new double*[derivatives];
	for (int i = 0; i < derivatives; i++)
	{
		Der[i] = new double[size];
	}
	cout << "Podaj po kolei znane argumenty" << endl;
	fill(Arg, size);
	cout << "Podaj po kolei znane wartosci funkcji" << endl;
	fill(Val, size);
	for (int i = 0; i < derivatives; i++)
	{
		cout << "Podaj znane wartosci " << i+1 << " pochodnej" << endl;
		fill(Der[i], size);
	}
	cout << "Podaj liczbe dla ktorej chcesz policzyc wartosc wielomianu" << endl;
	double x;
	cin >> x;
	cout << "Wynik to: " << Hermit(Arg, Val, Der, size, derivatives,x) << endl;
	//usowanie
	for (int i = 0; i < derivatives; i++)
	{
		delete [] Der[i];
	}
	delete[] Der;
	delete[] Arg;
	delete[] Val;
	
	system("pause");
}