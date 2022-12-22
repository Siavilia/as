#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <conio.h>
using namespace std;

void Init(int acount, vector <multiset<int>>& avec);
void Print(vector <multiset<int>> avec);
void DefMLS(multiset<int>& mls1, multiset<int>& mls2, vector <multiset<int>> avec);
set<int> DefineResultSt(int j, vector <multiset<int>> avec);

int main()
{
    setlocale(0, "RUS");
    vector <multiset <int>> vecmls (0);
    int i = 0; //номер операции
    puts("1.Ввод множества \n2.Вычислить пересечение \n3.Вычислить объединение \n4.Вычислить дополнение \n5.Проверить есть ли элемент во множестве \n6.Вывод \n7.Выход \n");
    while (i != 7) {
        cout << "\nВыберите операцию: ";
        scanf("%d", &i);
        switch (i) {

        case 1: {
            int count;
            cout << "Сколько Вы хотите добавить множеств? ";
            scanf("%d", &count);
            Init(count, vecmls);
            break;
        };

        case 5: {
            int el, num;
            multiset <int> mls;
            cout << "Введите элемент ";
            scanf("%d", &el);
            Print(vecmls);
            cout << "Выберите множество ";
            scanf("%d", &num);
            mls = vecmls[num];
            (mls.find(el) == mls.end()) ? (puts("Такого элемента нет")) : (puts("Такой элемент есть"));
            break;
        };

        case 6: {
            cout << "Введенные множества:\n";
            Print(vecmls);
            break;
        };

        case 7: break;

        default: {
            set <int> st;
            st = DefineResultSt(i, vecmls);
            cout << "Результат: ";
            copy(st.begin(), st.end(), ostream_iterator<int>(cout, " "));
            cout << '\n';
        };
        };
    };
    cout << "Работа завершена";
    return 0;
}

set<int> DefineResultSt(int j, vector <multiset<int>> avec) {
    set <int> ast;
    multiset <int> mls1, mls2;
    DefMLS(mls1, mls2, avec); //инициализация mls1 mls2
    switch (j) {
    case (2): set_intersection(mls1.begin(), mls1.end(), mls2.begin(), mls2.end(), inserter(ast, ast.begin())); break;
    case (3): set_union(mls1.begin(), mls1.end(), mls2.begin(), mls2.end(), inserter(ast, ast.begin())); break;
    case (4): set_difference(mls1.begin(), mls1.end(), mls2.begin(), mls2.end(), inserter(ast, ast.begin())); break;
    };
    return ast;
}

void Init(int acount,  vector <multiset<int>>& avec) {
    multiset <int> mls;
    int num = 0; //вводимая цифра
    while (acount != 0) {
        puts("Введите множество: ");
        cin.clear();
        while (cin >> num) {
            mls.insert(num);
        };
        avec.insert(avec.end(), mls);
        mls.clear();
        acount--;
    };
};

void Print(vector <multiset<int>> avec) {
    vector <multiset<int>> ::iterator it = avec.begin();
    int num1 = 0;
    while (it != avec.end()) {
        cout << num1 << ". ";
        copy((*it).begin(), (*it).end(), ostream_iterator<int>(cout, " "));
        cout << '\n';
        it++;
        num1++;
    };
};

void DefMLS(multiset<int> &mls1, multiset<int> &mls2, vector <multiset<int>> avec) {
    int num1, num2;
    Print(avec);
    cout << "Выберите 2 множества: ";
    scanf("%d %d", &num1, &num2);
    mls1 = avec[num1];
    mls2 = avec[num2];
};