#include <iostream> 
#include <fstream>
#include <cstring>
#include <iomanip>


using namespace std;

const int MAX_LENGTH_NAME = 100;
const int MAX_LENGTH_AUTHOR = 50;
const int MAX_NUM_BOOKS = 100;

struct Book
{
    char name[MAX_LENGTH_NAME];
    char author[MAX_LENGTH_AUTHOR];
    char data[8];
    float score;
};

Book books[MAX_NUM_BOOKS];
int cnt = 0;

void Replace(char* str, char aim, char repTo) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == aim) {
            str[i] = repTo;
        }
    }
}

void SaveFile(const char *filename, Book NewBook) {
    ofstream fout(filename, ios::app);
    if (!fout){
        cout << "Невозможно сохранить файл" << endl;
        return;
    }

    char name[MAX_LENGTH_NAME];
    char author[MAX_LENGTH_AUTHOR];
    strcpy(name, NewBook.name);
    strcpy(author, NewBook.author);
    
    Replace(name, ' ', '_');
    Replace(author, ' ', '_');
    
    fout << name << " " << author << " " << NewBook.data << " " << NewBook.score << endl;
    fout.close();
}

void LoadFile(const char *filename){
    ifstream fin(filename);
    if (!fin){
        return;
    }

char name[MAX_LENGTH_NAME];
char author[MAX_LENGTH_AUTHOR];

while (fin >> name >> author >> books[cnt].data >> books[cnt].score) {
    Replace(name, '_', ' ');
    Replace(author, '_', ' ');
    
    strcpy(books[cnt].name, name);
    strcpy(books[cnt].author, author);
    
    cnt++;
}
    fin.close();
}


void AddBook(){
    if (cnt >= MAX_NUM_BOOKS){
        cout << "Введено максимальное кол-во книг" << endl;
        return;
    }
    Book NewBook;

    cin.ignore();
    
    cout << "Введите название книги: ";
    cin.getline(NewBook.name, MAX_LENGTH_NAME); 

    cout << "Введите имя автора: ";
    cin.getline(NewBook.author, MAX_LENGTH_AUTHOR);

    cout << "Введите дату прочтения (дд.мм.гг): ";
    cin >> NewBook.data;

    cout << "Введите оценку (0-10): ";
    cin >> NewBook.score;

    if((NewBook.score < 0) || (NewBook.score > 10)){
        cout << "Неверный ввод! " << endl;
        return;
    }

    books[cnt++] = NewBook;
    SaveFile("Books.txt", NewBook);

    cout << "Книга добавлена!" << endl;
}


void ShowBooks(){
    if (cnt == 0){
        cout << "Нет книг" << endl;
        return;
    }
    
    cout << " --- Все книги --- \n" << endl;
    cout << left << setw(50) << "Название" << " | "
         << setw(30) << "Автор" << " | "
         << setw(15) << "Год прочтения "  << " | "
         << "Оценка \n";
    cout << string(100, '-') << endl;

    for (int i = 0; i < cnt; i++ ){
        cout << left << setw(50) << books[i].name << " | "
            << setw(30) << books[i].author << " | "
            << setw(15) << books[i].data << " | "
            << books[i].score << endl;
        cout << string(100, '-') << endl;
    }
}

void ShowStat(){
    if (cnt == 0){
        cout << "Не найдено статистики" << endl;
        return;
    }
    float sr_znach = 0;
    float sum_sc = 0;
    float max_sc = books[0].score;

    for (int i = 0; i < cnt; i++){

        sum_sc += books[i].score;

        if (max_sc < books[i].score){
            max_sc = books[i].score;
        }
    }

    sr_znach = sum_sc / cnt;

    cout << " " << endl;
    cout << " --- Статистика --- " << endl;
    cout << "Всего книг прочитано - " << cnt << endl;
    cout << "Средняя оценка  - " << sr_znach << endl;
    cout << "Самая высокая оценка - " << max_sc << endl;
}


void Menu(){
    cout << " " << endl;
    cout << "Добро пожаловать в трекер книг!" << endl;
    cout << "1. Добавить книгу" << endl;
    cout << "2. Показать все книги" << endl;
    cout << "3. Показать статистику" << endl;
    cout << "4. Выход" << endl;
    cout << "Выберите пункт меню - " << endl;
}

int main(){

    LoadFile("Books.txt");

    int choice;

    do{
        Menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            AddBook();
            break;
        case 2:
            ShowBooks();
            break;
        case 3:
            ShowStat();
            break;
        case 4:
            cout << "Выход из программы" << endl;
            break;
        default:
            cout << "Неверный выбор" << endl;
        }
    } while (choice != 4);
     return 0;
}


