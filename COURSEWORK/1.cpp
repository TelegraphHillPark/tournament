#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
#include <random>
#include <cassert>
using namespace std;

typedef struct team {
	unsigned number;
	unsigned win;
	unsigned lose;
	unsigned who;
} team;

void teams_init(unsigned num_of_teams, vector <team>& teams) {
	for (unsigned f = 0; f < num_of_teams; f++) {
		teams[f].number = f + 1;
		teams[f].win = 0;
		teams[f].lose = 0;
	}
	//return (teams);
}

void sort(unsigned x, unsigned y, vector <team>& teams) {
	for (int i = x + 1; i <= y - 1; i++) {
		for (int j = y - 1; j >= i; j--) {
			if (teams[j - 1].win < teams[j].win) {
				team a = teams[j];
				teams[j] = teams[j - 1];
				teams[j - 1] = a;
			}
		}
	}
}

void win_lose(unsigned num_of_teams, vector <team>& teams, unsigned j, unsigned i, unsigned n, unsigned* tab[]) {
	double probability_of_winning_first = (1.0 / 2) * 100 + ((j - i) * 1.0 / (pow(2, n + 1))) * 100;
	double probability_of_winning_second = 100 - probability_of_winning_first;
	double result = rand() * 100.0 / RAND_MAX;
	if (result <= probability_of_winning_first) {
		teams[i].win += 1;
		teams[j].lose += 1;
		tab[i][j] = 1;
	}
	else {
		teams[j].win += 1;
		teams[i].lose += 1;
		tab[j][i] = 1;
	}
}

void circle(unsigned n, unsigned num_of_teams, vector <team>& teams) {
	unsigned** tab = new unsigned* [num_of_teams];
	for (unsigned i = 0; i < num_of_teams; i++) {
		tab[i] = new unsigned[num_of_teams];
	}

	for (unsigned i = 0; i < num_of_teams; i++) {
		for (unsigned j = 0; j < num_of_teams; j++) {
			tab[i][j] = 0;
		}
	}

	// Круговая классификация
	for (unsigned i = 0; i != num_of_teams; i++) {
		for (unsigned j = i + 1; j != num_of_teams; j++) {
			win_lose(num_of_teams, teams, j, i, n, tab);
		}
	}

	/*cout << "\n";

	for (unsigned i = 0; i < num_of_teams; i++) {
		for (unsigned j = 0; j < num_of_teams; j++) {
			cout << tab[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";*/

	/*cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].number << "  ";
	}
	cout << "\n";
	cout << "\n";

	cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].win << "  ";
	}
	cout << "\n";
	cout << "\n";*/

	sort(0, num_of_teams, teams);

	unsigned flag = 1;
	vector <unsigned> same_vic;
	for (unsigned i = 0; i < num_of_teams - 1; i++) {
		if (teams[i].win == teams[i + 1].win && i + 1 == num_of_teams - 1) {
			same_vic.push_back(teams[i].number);
			same_vic.push_back(teams[i + 1].number);
			for (unsigned q = 1; q <= same_vic.size() - 1; q++) {
				for (unsigned w = same_vic.size() - 1; w >= q; w--) {
					unsigned tmp1 = 0, tmp2 = 0;
					for (unsigned g = 0; g < num_of_teams; g++) {
						if (tab[w - 1][g] == 1) {
							for (unsigned h = 0; h < num_of_teams; h++) {
								tmp1 += tab[g][h];
							}
						}
					}
					for (unsigned g = 0; g < num_of_teams; g++) {
						if (tab[w][g] == 1) {
							for (unsigned h = 0; h < num_of_teams; h++) {
								tmp2 += tab[g][h];
							}
						}
					}
					if (tmp1 < tmp2) {
						unsigned a = same_vic[w];
						same_vic[w] = same_vic[w - 1];
						same_vic[w - 1] = a;
					}
				}
			}

			/*cout << "\n";
			for (unsigned j = 0; j < same_vic.size(); j++) {
				cout << same_vic[j] << "  ";
			}
			cout << "\n";*/

			flag = 1;
			unsigned tmp = 0;
			for (unsigned j = i - same_vic.size() + 2; j < i + 2; j++) {
				teams[j].number = same_vic[tmp];
				tmp++;
			}
			same_vic.clear();
			vector <unsigned> same_vic;


		}

		else if (flag != 1 && teams[i].win != teams[i + 1].win) {
			same_vic.push_back(teams[i].number);
			for (unsigned q = 1; q <= same_vic.size() - 1; q++) {
				for (unsigned w = same_vic.size() - 1; w >= q; w--) {
					unsigned tmp1 = 0, tmp2 = 0;
					for (unsigned g = 0; g < num_of_teams; g++) {
						if (tab[same_vic[w - 1] - 1][g] == 1) {
							for (unsigned h = 0; h < num_of_teams; h++) {
								tmp1 += tab[g][h];
							}
						}
					}
					for (unsigned g = 0; g < num_of_teams; g++) {
						if (tab[same_vic[w] - 1][g] == 1) {
							for (unsigned h = 0; h < num_of_teams; h++) {
								tmp2 += tab[g][h];
							}
						}
					}
					//cout << same_vic[w] << ": " << tmp2 << "  " << same_vic[w - 1] << ": " << tmp1 << "  ";
					if (tmp1 < tmp2) {
						unsigned a = same_vic[w];
						same_vic[w] = same_vic[w - 1];
						same_vic[w - 1] = a;
					}
				}
			}

			/*cout << "\n";
			for (unsigned j = 0; j < same_vic.size(); j++) {
				cout << same_vic[j] << "  ";
			}
			cout << "\n";*/

			flag = 1;
			unsigned tmp = 0;
			for (unsigned j = i - same_vic.size() + 1; j < i + 1; j++) {
				teams[j].number = same_vic[tmp];
				tmp++;
			}
			same_vic.clear();
			vector <unsigned> same_vic;
		}

		else if (teams[i].win == teams[i + 1].win && i + 1 != num_of_teams - 1) {
			flag++;
			same_vic.push_back(teams[i].number);
		}

		else {
			flag = 1;
		}
	}

	vector <unsigned>().swap(same_vic);
	
	/*cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].number << "  ";
	}

	cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].win << "  ";
	}

	cout << "\n";*/

	for (int j = 0; j < num_of_teams; j++){
		delete[] tab[j];
	}
	delete[] tab;

}

void swiss_rec(unsigned num_of_teams,  unsigned n, unsigned x, unsigned y, vector <team>& teams) {
	unsigned len = y - x;

	if (len == 1) return ;

	for (unsigned i = x; i < x + len / 2; i++) {
		if (teams[i].number <= teams[len / 2 + i].number) { 
			double probability_of_winning_first = (1.0 / 2) * 100 + ((teams[len / 2 + i].number - teams[i].number) * 1.0 / (pow(2, n + 1))) * 100;
			double probability_of_winning_second = 100 - probability_of_winning_first;
			double result = rand() * 100.0 / RAND_MAX;
			if (result <= probability_of_winning_first) {
				teams[i].win += 1;
				teams[len / 2 + i].lose += 1;
			}
			else {
				teams[len / 2 + i].win += 1;
				teams[i].lose += 1;
			}
		}
		else {
			double probability_of_winning_first = (1.0 / 2) * 100 + ((teams[i].number - teams[len / 2 + i].number) * 1.0 / (pow(2, n + 1))) * 100;
			double probability_of_winning_second = 100 - probability_of_winning_first;
			double result = rand() * 100.0 / RAND_MAX;
			if (result <= probability_of_winning_first) {
				teams[len / 2 + i].win += 1;
				teams[i].lose += 1;
			}
			else {
				teams[i].win += 1;
				teams[len / 2 + i].lose += 1;
			}
		}
	}

	sort(x, y, teams);

	swiss_rec(num_of_teams, n, x, x + len / 2, teams);
	swiss_rec(num_of_teams, n, x + len / 2, y, teams);
}

void swiss(unsigned n, unsigned num_of_teams, vector <team>& teams) {
	vector <team> fixed;
	for (unsigned i = 0; i < num_of_teams; i++) {
		teams[i].win = 0;
		teams[i].lose = 0;
		fixed.push_back(teams[i]);
	}
	swiss_rec(num_of_teams, n, 0, num_of_teams, teams);
	
	for (int i = 0; i < num_of_teams; i++) {
		for (int j = 0; j < num_of_teams; j++) {
			if (teams[j].number == fixed[i].number) {
				fixed[i].win = teams[j].win;
				break;
			}
		}
	}

	sort(0, num_of_teams, fixed);

	for (int j = 0; j < num_of_teams; j++) {
		teams[j] = fixed[j];
	}

	fixed.clear();
	//cout << "\n";
	//cout << "\n";
	//cout << "\n";
	//for (unsigned i = 0; i != num_of_teams; i++) {
	//	cout << teams[i].number << "  ";
	//}

	//cout << "\n";

	//for (unsigned i = 0; i != num_of_teams; i++) {
	//	cout << teams[i].win << "  ";
	//}
	//cout << "\n";

}

void elemination(unsigned n, unsigned num_of_teams, vector <team>& teams) {
	/*team* elem = new team[num_of_teams];
	elem = teams_init(num_of_teams, elem);

	for (unsigned i = 0; i < num_of_teams; i++) {
		unsigned a = rand() % num_of_teams;
		elem[i] = teams[a];
	}*/

	vector <int> elem(num_of_teams);
	for (int i = 0; i < num_of_teams; i++) {
		elem[i] = i + 1;
	}
	std::random_device rd;
	std::mt19937 g(rd());
	shuffle(elem.begin(), elem.end(), g);
	/*while (elem.size() != num_of_teams) {
		int a = rand() % num_of_teams + 1;
		if (!(find(elem.begin(), elem.end(), a) != elem.end())) {
			elem.push_back(a);
		}
	}*/
	/*cout << "\n";
	cout << "\n";
	for (unsigned i = 0; i < elem.size(); i++) {
		cout << elem[i] << "  ";
	}
	cout << "\n";*/

	unsigned tmp_num = num_of_teams;
	vector <int> tours(tmp_num);

	for (int i = 0; i < num_of_teams; i++) {
		teams[i].number = i + 1;
		teams[i].win = 0;
		teams[i].lose = 0;
		tours[i] = elem[i];
	}

	for (int tour = 0; tour < n; tour++) {
		vector <int> tmp;
		tmp.reserve(tmp_num / 2);

		for (int i = 0; i < tmp_num - 1; i += 2) {
			if (tours[i] <= tours[i + 1]) { 
				double probability_of_winning_first = (1.0 / 2) * 100 + ((tours[i + 1] - tours[i]) * 1.0 / (pow(2, n + 1))) * 100;
				double probability_of_winning_second = 100 - probability_of_winning_first;
				double result = rand() * 100.0 / RAND_MAX;
				if (result <= probability_of_winning_first) {
					teams[tours[i] - 1].win += 1;
					teams[tours[i + 1] - 1].lose += 1;
					teams[tours[i + 1] - 1].who = tours[i];
					tmp.push_back(tours[i]);
				}
				else {
					teams[tours[i + 1] - 1].win += 1;
					teams[tours[i] - 1].lose += 1;
					teams[tours[i] - 1].who = tours[i + 1];
					tmp.push_back(tours[i + 1]);
				}
			}
			else {
				double probability_of_winning_first = (1.0 / 2) * 100 + ((tours[i] - tours[i + 1]) * 1.0 / (pow(2, n + 1))) * 100;
				double probability_of_winning_second = 100 - probability_of_winning_first;
				double result = rand() * 100.0 / RAND_MAX;
				if (result <= probability_of_winning_first) {
					teams[tours[i + 1] - 1].win += 1;
					teams[tours[i] - 1].lose += 1;
					teams[tours[i] - 1].who = tours[i + 1];
					tmp.push_back(tours[i + 1]);
				}
				else {
					teams[tours[i] - 1].win += 1; 
					teams[tours[i + 1] - 1].lose += 1;
					teams[tours[i + 1] - 1].who = tours[i];
					tmp.push_back(tours[i]);
				}
			}
		}

		tmp_num /= 2;
		for (int i = 0; i < tmp_num; i++) {
			tours[i] = tmp[i];
		}
	}

	sort(0, num_of_teams, teams);
	if (n != 1) {
		int num_sorted = 2;
		for (int i = 1; i != n; i++) {
			vector <team> mid_sort((int)pow(2, i));
			for (int j = 0; j < num_sorted; j++) {
				for (int cur = num_sorted; cur < num_sorted + (int)pow(2, i); cur++) {
					if (teams[cur].who == teams[j].number) {
						mid_sort.push_back(teams[cur]);
						break;
					}
				}
			}
			for (int j = num_sorted; j < num_sorted + (int)pow(2, i); j++) {
				teams[j] = mid_sort[j];
			}
			num_sorted += (int)pow(2, i);
		}
	}

	/*cout << "\n";
	cout << "\n";
	cout << "\n";
	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].number << "  ";
	}

	cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].win << "  ";
	}
	cout << "\n";*/

	//return (teams);
} 

int main() {
	srand(time(NULL));
	unsigned int n;
	cout << "Enter a power of two: ";
	cin >> n;
	unsigned num_of_teams{ (unsigned)pow(2, n) };
	cout << "Number of teams: " << num_of_teams << "\n";

	vector <team> teams(num_of_teams);
	teams_init(num_of_teams, teams);

	cout << "\n" << "1: Circle and Swiss" << "\n";

	vector <team> teams1(num_of_teams);
	vector <team> teams2(num_of_teams);
	vector <double> rs;
	vector <int> ms;
	teams_init(num_of_teams, teams1);
	teams_init(num_of_teams, teams2);

	double sec = (num_of_teams * num_of_teams * num_of_teams - num_of_teams) * 1.0;

	for (int i = 0; i < 10; i++) {

		circle(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams1[j] = teams[j];
		}

		swiss(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams2[j] = teams[j];
		}

		vector <unsigned> circle_pls(num_of_teams);
		vector <unsigned> swiss_pls(num_of_teams);
		for (int j = 0; j < num_of_teams; j++) {
			circle_pls[teams1[j].number] = j;
			swiss_pls[teams2[j].number] = j;
		}

		int m = 0;
		double r = 0.0, s = 0.0;
		for (int g = 0; g < num_of_teams; g++) {
			if (teams1[g].number == teams2[g].number) m++;
			int circle_pl, swiss_pl;
			circle_pl = circle_pls[g + 1];
			swiss_pl = swiss_pls[g + 1];
			
			//for (int j = 0; j < num_of_teams; j++) {
			//	if (teams1[j].number == g + 1) {
			//		//circle_pl = j;
			//		assert(j == circle_pl);
			//		break;
			//	}
			//}
			//for (int j = 0; j < num_of_teams; j++) {
			//	if (teams2[j].number == g + 1) {
			//		//swiss_pl = j;
			//		assert(j == swiss_pl);
			//		break;
			//	}
			//}

			
			double fir = (circle_pl - swiss_pl) * (circle_pl - swiss_pl) * 1.0;
			s += fir;
		}

		r = 1 - 6 * (s / sec);
		rs.push_back(r);
		ms.push_back(m);

		/*cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].win << "  ";
		}
		cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].win << "  ";
		}*/

		teams_init(num_of_teams, teams);
		teams_init(num_of_teams, teams1);
		teams_init(num_of_teams, teams2);
		circle_pls.clear();
		swiss_pls.clear();
	}


	double sumr = 0.0;
	double r = 0.0;
	int summ = 0;
	int m = 0;
	int max = 0;
	for (int i = 0; i < rs.size(); i++) {
		sumr += rs[i];
		summ += ms[i];
		if (ms[i] > max) max = ms[i];
	}
	r = sumr / rs.size();
	m = summ / ms.size();

	cout << "R = " << r << " M = " << m << " MAX M = " << max << "\n";
	rs.clear();
	ms.clear();



	teams_init(num_of_teams, teams);

	cout << "\n" << "2: Circle and Elemination" << "\n";

	teams_init(num_of_teams, teams1);
	teams_init(num_of_teams, teams2);

	for (int i = 0; i < 10; i++) {

		circle(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams1[j] = teams[j];
		}

		elemination(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams2[j] = teams[j];
		}

		vector <unsigned> circle_pls(num_of_teams);
		vector <unsigned> elem_pls(num_of_teams);
		for (int j = 0; j < num_of_teams; j++) {
			circle_pls[teams1[j].number] = j;
			elem_pls[teams2[j].number] = j;
		}

		m = 0;
		r = 0.0;
		double s = 0.0;
		for (int g = 0; g < num_of_teams; g++) {
			if (teams1[g].number == teams2[g].number) m++;
			int circle_pl, elem_pl;
			circle_pl = circle_pls[g + 1];
			elem_pl = elem_pls[g + 1];
			/*for (int j = 0; j < num_of_teams; j++) {
				if (teams1[j].number == g + 1) {
					circle_pl = j;
					break;
				}
			}
			for (int j = 0; j < num_of_teams; j++) {
				if (teams2[j].number == g + 1) {
					elem_pl = j;
					break;
				}
			}*/

			double fir = (circle_pl - elem_pl) * (circle_pl - elem_pl) * 1.0;
			s += fir;
		}
		r = 1 - 6 * (s / sec);

		rs.push_back(r);
		ms.push_back(m);

		/*cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].win << "  ";
		}
		cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].win << "  ";
		}*/

		teams_init(num_of_teams, teams);
		teams_init(num_of_teams, teams1);
		teams_init(num_of_teams, teams2);
		circle_pls.clear();
		elem_pls.clear();
	}


	sumr = 0.0;
	r = 0.0;
	summ = 0;
	m = 0;
	max = 0;
	for (int i = 0; i < rs.size(); i++) {
		sumr += rs[i];
		summ += ms[i];
		if (ms[i] > max) max = ms[i];
	}
	r = sumr / rs.size();
	m = summ / ms.size();

	cout << "R = " << r << " M = " << m << " MAX M = " << max << "\n";
	rs.clear();
	ms.clear();



	teams_init(num_of_teams, teams);

	cout << "\n" << "3: Swiss and Elemination" << "\n";

	teams_init(num_of_teams, teams1);
	teams_init(num_of_teams, teams2);

	for (int i = 0; i < 10; i++) {

		circle(n, num_of_teams, teams);
		swiss(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams1[j] = teams[j];
		}

		elemination(n, num_of_teams, teams);
		for (int j = 0; j < num_of_teams; j++) {
			teams2[j] = teams[j];
		}

		vector <unsigned> swiss_pls(num_of_teams);
		vector <unsigned> elem_pls(num_of_teams);
		for (int j = 0; j < num_of_teams; j++) {
			swiss_pls[teams1[j].number] = j;
			elem_pls[teams2[j].number] = j;
		}

		m = 0;
		r = 0.0;
		double s = 0.0;
		for (int g = 0; g < num_of_teams; g++) {
			if (teams1[g].number == teams2[g].number) m++;
			int swiss_pl, elem_pl;
			swiss_pl = swiss_pls[g + 1];
			elem_pl = elem_pls[g + 1];
			/*for (int j = 0; j < num_of_teams; j++) {
				if (teams1[j].number == g + 1) {
					swiss_pl = j;
					break;
				}
			}
			for (int j = 0; j < num_of_teams; j++) {
				if (teams2[j].number == g + 1) {
					elem_pl = j;
					break;
				}
			}*/

			double fir = (swiss_pl - elem_pl) * (swiss_pl - elem_pl) * 1.0;
			s += fir;
		}
		r = 1 - 6 * (s / sec);

		rs.push_back(r);
		ms.push_back(m);

		/*cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams1[i].win << "  ";
		}
		cout << "\n";
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].number << "  ";
		}
		cout << "\n";
		for (int i = 0; i < num_of_teams; i++) {
			cout << teams2[i].win << "  ";
		}*/

		teams_init(num_of_teams, teams);
		teams_init(num_of_teams, teams1);
		teams_init(num_of_teams, teams2);
		swiss_pls.clear();
		elem_pls.clear();
	}


	sumr = 0.0;
	r = 0.0;
	summ = 0;
	m = 0;
	max = 0;
	for (int i = 0; i < rs.size(); i++) {
		sumr += rs[i];
		summ += ms[i];
		if (ms[i] > max) max = ms[i];
	}
	r = sumr / rs.size();
	m = summ / ms.size();

	cout << "R = " << r << " M = " << m << " MAX M = " << max << "\n";
	rs.clear();
	ms.clear();

	return 0;
}