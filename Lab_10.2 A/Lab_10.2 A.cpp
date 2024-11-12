#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

/*
{ "Ivanenko", 2, 0 3 4 5 },
{ "Petrenko", 3, 1 2 3 4  },
{ "Sydorenko", 1, 2 5 5 5 }
*/

enum Specialnist { RI, IK, SSHI };
string specialnistStr[] = { "в", "��", "�ز" };

struct Student {
    string prizv;
    unsigned kurs;
    Specialnist specialnist;
    int ocinkaFizyka;
    int ocinkaMatematika;
    int ocinkaInformatika;

    double avg() const { // ������� ��� ���������� ���������� ����
        return (ocinkaFizyka + ocinkaMatematika + ocinkaInformatika) / 3.0;
    }
};

void Create(Student* s, const int N);
void Print(const Student* s, const int N);
int FindStudentWithMinAverage(const Student* s, const int N);
void CountSatisfactoryGrades(const Student* s, const int N);
void PrintStudentWithMinAverage(const Student* s, const int N);
void SortPhysical(Student* s, const int N);
void PrintIndexSorted(const Student* s, const int* I, const int N);
int* IndexSort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, unsigned kurs, double avg);

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: "; cin >> N;

    Student* s = new Student[N];
    double mark;

    string prizv;
    unsigned kurs;
    int specialnist;

    int menuItem;
    int indexBin = -1;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� �����" << endl << endl;
        cout << " [4] - �������� ������������� �����" << endl << endl;
        cout << " [5] - ������� �����" << endl << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem)
        {
        case 1:
            Create(s, N);
            break;
        case 2:
            Print(s, N);
            break;
        case 3:
            SortPhysical(s, N);
            break;
        case 4:
            PrintIndexSorted(s, IndexSort(s, N), N);
            break;
        case 5: 
            cout << "������ ������� �������� ��� ������: "; cin >> prizv;
            cout << "������ ���� ��������: "; cin >> kurs;
            cout << "������� ������������ (0 - в, 1 - ��, 2 - �ز): "; cin >> specialnist;

            indexBin = BinSearch(s, N, prizv, kurs, (Specialnist)specialnist);

            if (indexBin != -1) {
                cout << "������� ���������:" << endl;
                cout << "�������: " << s[indexBin].prizv << endl;
                cout << "����: " << s[indexBin].kurs << endl;
                cout << "������������: " << specialnistStr[s[indexBin].specialnist] << endl;
                cout << "������� ���: " << fixed << setprecision(2) << s[indexBin].avg() << endl;
            }
            else {
                cout << "�������� � ����� ��������, ������ �� ������������� �� ��������!" << endl;
            }
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! "
                "��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    PrintStudentWithMinAverage(s, N);
    CountSatisfactoryGrades(s, N);

    delete[] s;
    return 0;
}

void Create(Student* s, const int N) {
    int specialnist;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.get();
        cout << " �������: "; getline(cin, s[i].prizv);
        cout << " ����: "; cin >> s[i].kurs;
        cout << " ������������ (0 - в, 1 - ��, 2 - �ز): ";
        cin >> specialnist;
        s[i].specialnist = (Specialnist)specialnist;
        cout << " ������ � ������: "; cin >> s[i].ocinkaFizyka;
        cout << " ������ � ����������: "; cin >> s[i].ocinkaMatematika;
        cout << " ������ � �����������: "; cin >> s[i].ocinkaInformatika;
        cout << endl;
    }
}

void Print(const Student* s, const int N) {
    cout << "=================================================================================" << endl;
    cout << "| � | �������       | ���� | ������������ | Գ���� | ���������� | ����������� |" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << i + 1
            << " | " << setw(15) << left << s[i].prizv
            << "|  " << setw(3) << left << s[i].kurs
            << " | " << setw(13) << left << specialnistStr[s[i].specialnist]
            << " | " << setw(6) << s[i].ocinkaFizyka
            << " | " << setw(10) << s[i].ocinkaMatematika
            << " | " << setw(11) << s[i].ocinkaInformatika << " |" << endl;
    }
    cout << "=================================================================================" << endl;
}

int FindStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = 0;
    double minAvg = s[0].avg();

    for (int i = 1; i < N; i++) {
        double avg = s[i].avg();
        if (avg < minAvg) {
            minAvg = avg;
            minIndex = i;
        }
    }
    return minIndex;
}

void PrintStudentWithMinAverage(const Student* s, const int N) {
    int minIndex = FindStudentWithMinAverage(s, N);
    cout << "������� � ��������� ������� �����: " << s[minIndex].prizv << endl;
}

void CountSatisfactoryGrades(const Student* s, const int N) {
    int satisfactoryPhysics = 0, satisfactoryMath = 0, satisfactoryInformatics = 0;

    for (int i = 0; i < N; i++) {
        if (s[i].ocinkaFizyka == 3) satisfactoryPhysics++;
        if (s[i].ocinkaMatematika == 3) satisfactoryMath++;
        if (s[i].ocinkaInformatika == 3) satisfactoryInformatics++;
    }

    cout << "ʳ������ ������ '���������' � ������: " << satisfactoryPhysics << endl;
    cout << "ʳ������ ������ '���������' � ����������: " << satisfactoryMath << endl;
    cout << "ʳ������ ������ '���������' � �����������: " << satisfactoryInformatics << endl;
}

void SortPhysical(Student* s, const int N) {
    Student tmp;
    for (int i0 = 0; i0 < N - 1; i0++) { // ����� "���������"
        for (int i1 = 0; i1 < N - i0 - 1; i1++) {
            // ���� ������� ��� ��������� �������� �����, �� � ����������
            if (s[i1].avg() < s[i1 + 1].avg() ||
                (s[i1].avg() == s[i1 + 1].avg() && s[i1].prizv < s[i1 + 1].prizv) ||
                (s[i1].avg() == s[i1 + 1].avg() && s[i1].prizv == s[i1 + 1].prizv && s[i1].kurs > s[i1 + 1].kurs)) {
                tmp = s[i1]; 
                s[i1] = s[i1 + 1];
                s[i1 + 1] = tmp;
            }
        }
    }
}

int BinSearch(Student* s, const int N, const string prizv, unsigned kurs, double avg )
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (s[m].prizv == prizv && s[m].kurs == kurs && s[m].avg() == avg)
            return m;
        if (s[m].prizv < prizv 
            || (s[m].prizv == prizv && s[m].kurs < kurs) 
            ||
            (s[m].prizv == prizv && s[m].kurs == kurs && s[m].avg() < avg))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);
    return -1;
}

int* IndexSort(Student* s, const int N)
{ 
    int* I = new int[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        I[i] = i; // ��������� ���� ����������� ������

    int i, j, value; // �������� ��������� ����� �������
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((s[I[j]].avg() > s[I[j + 1]].avg() || (s[I[j]].avg() == s[I[j + 1]].avg() && s[I[j]].prizv > s[I[j + 1]].prizv) ||
                (s[I[j]].avg() == s[I[j + 1]].avg() && s[I[j]].prizv == s[I[j + 1]].prizv && s[I[j]].kurs > s[I[j + 1]].kurs)));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;
    }
    return I;
}

void PrintIndexSorted(const Student* s, const int* I, const int N) {
    cout << "������� ���������� �� ������� �����:" << endl;
    cout << "============================================================" << endl;
    cout << "| � | �������       | ���� | ������������ | ������� ��� |" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < N; i++) {
        cout << "| " << setw(1) << i + 1
            << " | " << setw(14) << left << s[I[i]].prizv
            << " |  " << setw(3) << left << s[I[i]].kurs
            << " | " << setw(13) << left << specialnistStr[s[I[i]].specialnist]
            << " | " << setw(12) << fixed << setprecision(2) << s[I[i]].avg() << " |" << endl;
    }
    cout << "============================================================" << endl;
}
