#include <iomanip>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double mod_func (const double x) {
	return (x * x) * exp(sin(x));
}

double multimod_func (const double x) {
	return mod_func(x) * sin(5 * x);
}

const double A = 9;
const double B = 14;

const vector<double> p_probob  = { 0.9, 0.91, 0.92, 0.93, 0.94,
						   0.95, 0.96, 0.97, 0.98, 0.99 };

const vector<double> q_probob = { 0.005, 0.01, 0.015, 0.02, 0.025,
						   0.03, 0.035, 0.04, 0.045, 0.05,
						   0.055, 0.06, 0.065, 0.07, 0.075,
						   0.08, 0.085, 0.09, 0.095, 0.1 };


vector<vector<double>> counter_num() {
	vector<vector<double>> num_count(q_probob.size());
	
	for (size_t i = 0; i < q_probob.size(); i++) {
		num_count[i].resize(p_probob.size());
		for (size_t j = 0; j < p_probob.size(); j++) {
			num_count[i][j] = ceil(log(1 - p_probob[j]) / log(1 - q_probob[i]));
		}
	}
	return num_count;
}


double random() {
	return A + rand() * 1. / RAND_MAX * (B - A);
}

vector<vector<double>> result_rand(
	const vector<vector<double>>& count,
	double (*f)(const double x)) {
	
	vector<vector<double>> result;
	result.resize(count.size());
	
	for (size_t i = 0; i < count.size(); ++i) {
		result[i].resize(count[i].size());
		for (size_t j = 0; j < result[i].size(); ++j) {
			result[i][j] = f(A);
			for (size_t k = 0; k < count[i][j]; ++k) {
				double newValue = f(random());
				if (newValue < result[i][j]) {
					result[i][j] = newValue;
				}
			}
		}
	}
	return result;
}


void print_header() {
	   cout << '+' << string(7, '-') << '+' << string(10, '-')
				<< '+' << string(10, '-') << '+' << string(10, '-')
				<< '+' << string(10, '-') << '+' << string(10, '-')
				<< '+' << string(10, '-') << '+' << string(10, '-')
				<< '+' << string(10, '-') << '+' << string(10, '-')
				<< '+' << string(10, '-') << '+' << endl;
}

void print_probob() {
	cout << '|' << setw(5) << "q/P" << std::setw(3) << '|';
	for (auto p : p_probob) cout << setw(9) << p << " |";
	cout << endl;
}

void print(const std::vector<std::vector<double>>& v) {
	print_header();
	print_probob();
	print_header();

	for (size_t i = 0; i < q_probob.size(); i++) {
		cout << '|' << setw(6) << q_probob[i] << " |";
		for (size_t j = 0; j < p_probob.size(); j++) {
			cout << setw(9) << v[i][j] << " |";
		}
		cout << endl;
	}

	print_header();
}






int main()
{
	srand(time(NULL));
	cout << "Function 1:  (x * x) * exp(sin(x))" << endl
		<< "Function 2:  (x * x) * exp(sin(x))*sin(5*x)" << endl
		<< "Interval : [ " << A << "; " << B << " ]" << endl;
	
	vector<vector<double>> counter = counter_num();
	cout << "Table with number :" << endl;
	print(counter);
	
	vector<vector<double>> f1 = result_rand(counter, mod_func);
	cout << "Function 1: " << endl;
	print(f1);
	vector<vector<double>> f2 = result_rand(counter, multimod_func);
	cout << "Function 2: " << endl;
	print(f2);

}

