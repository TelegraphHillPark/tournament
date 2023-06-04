#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <vector>
using namespace std;

// ���� ��������� ����� ��� �� ��� �������, ��� ������� ���� ������� R � M ��� ��� �� ���� ������ ��������, � ��������� ������� R � M. �������� �� ������ � ���������.
// ������� ������ ������ � ��������� ������� ��� ��� � ���� ������� � ��������� �� ��������� ���.

// ������� (�������) � ������������ DONE, ������������� � ����������� ������ �� ���. (�� while'��) ����� ������ ���������� �� ����� ���� ������ ���� ������ � ������ ������ DONE

// �����������: ����������� �������� �� ��������, ���� �� ����� �������.

// ������ � ����������� ����������

//������������ ������

typedef struct team {
	unsigned number;
	unsigned win;
	unsigned lose;
} team;

struct team* teams_init(unsigned num_of_teams, team* teams) {
	for (unsigned i = 0; i != num_of_teams; i++) {
		teams[i].number = i + 1;
		teams[i].win = 0;
		teams[i].lose = 0;
	}
	return (teams);
}

struct team* sort(unsigned x, unsigned y, team* teams) {
	for (unsigned i = x + 1; i <= y - 1; i++) {
		unsigned j = i;
		team a = teams[i];
		while ((j > 0) && (a.win > teams[j - 1].win)) {
			teams[j] = teams[j - 1];
			j--;
		}
		teams[j] = a;
	}
	return (teams);
}

struct team* sort_circle(unsigned x, unsigned y, team* teams, unsigned* tab[]) { // ����������, �� �����
	for (int i = x + 1; i < y; i++) {
		unsigned j = i;
		team a = teams[i];
		while ((j > 0) && (a.win > teams[j - 1].win)) {
			teams[j] = teams[j - 1];
			j--;
		}
		if (a.win == teams[j].win) {
			unsigned cur = 0, next = 0;
			for (unsigned g = 0; g < y; g++) {
				if (tab[i][g] == 1) {
					for (unsigned h = 0; h < y; h++) {
						cur += tab[g][h];
					}
				}
			}
			for (unsigned g = 0; g < y; g++) {
				if (tab[j - 1][g] == 1) {
					for (unsigned h = 0; h < y; h++) {
						next += tab[g][h];
					}
				}
			}
			if (next < cur) {
				teams[j] = a;
				team tmp = teams[j];
				teams[j] = teams[j - 1];
				teams[j - 1] = tmp;
			}
		}
		else {
			teams[j] = a;
		}

	}
	return (teams);
}

struct team* win_lose(unsigned num_of_teams, team* teams, unsigned j, unsigned i, unsigned n, unsigned* tab[]) {
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
	return (teams);
}

struct team* circle(unsigned n, unsigned num_of_teams, team* teams) {
	unsigned** tab = new unsigned* [num_of_teams];
	for (unsigned i = 0; i < num_of_teams; i++) {
		tab[i] = new unsigned[num_of_teams];
	}

	for (unsigned i = 0; i < num_of_teams; i++) {
		for (unsigned j = 0; j < num_of_teams; j++) {
			tab[i][j] = 0;
		}
	}

	// �������� �������������
	for (unsigned i = 0; i != num_of_teams; i++) {
		for (unsigned j = i + 1; j != num_of_teams; j++) {
			teams = win_lose(num_of_teams, teams, j, i, n, tab);
		}
	}

	for (unsigned i = 0; i < num_of_teams; i++) {
		for (unsigned j = 0; j < num_of_teams; j++) {
			cout << tab[i][j] << " ";
		}
		cout << "\n";
	}

	cout << "\n";

	teams = sort(0, num_of_teams, teams);

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
			for (unsigned j = i - same_vic.size() + 2; j < i + 1; j++) {
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

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].number << "  ";
	}

	cout << "\n";

	for (unsigned i = 0; i != num_of_teams; i++) {
		cout << teams[i].win << "  ";
	}

	delete tab;

	return (teams);
}

int main() {
	srand(time(NULL));
	unsigned int n;
	cout << "Enter a power of two: ";
	cin >> n;
	unsigned num_of_teams{ (unsigned)pow(2, n) };
	cout << "Number of teams: " << num_of_teams << "\n";

	team *teams = new team[num_of_teams];
	teams = teams_init(num_of_teams, teams);
	
	// �������� ������
	teams = circle(n, num_of_teams, teams);

	// Swiss system
	/*unsigned half = num_of_teams / 2;

	team* swiss = new team[num_of_teams];
	swiss = teams_init(num_of_teams, swiss);

	for (unsigned i = 0; i != num_of_teams; i++) {
		swiss[i] = teams[i];
		swiss[i].win = 0;
		swiss[i].lose = 0;
	}*/

	//// ������ ���
	//for (unsigned i = 0; i != half; i++) {
	//	if (swiss[i + half].number > swiss[i].number) {
	//		swiss = win_lose(num_of_teams, swiss, swiss[i + half].number, swiss[i].number, n);
	//	}
	//	else {
	//		swiss = win_lose(num_of_teams, swiss, swiss[i].number, swiss[i + half].number, n);
	//	}
	//}

	return 0;
}