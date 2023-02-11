/*!
\file
\brief Файл лабораторной работы

Данный файл содержит в себе определения и описания элементов, используемых в лабораторной
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
/*!
    \brief Класс записи из CSV
    \author Никита Романов
    \version 1.0
    \date Январь 2023 года

    Содержит ФИО, название улицы, номер дома, квартиры, дату рождения. Перегружены операторы сравнения.
    Приоритет сравнения: улица, дом, квартира, фио, рождение.
*/
class Entry {
public:
    Entry() {}
    Entry(string fio, string street, int home, int flat, int birth){
        this->street=street;
        this->fio=fio;
        this->home=home;
        this->flat=flat;
        this->birth=birth;
    }

    //приоритет сравнения: улица дом квартира фио рождение
    bool operator>(Entry &second) {
        if (this->street!=second.street) {
            return this->street > second.street;

        } else if(this->home!=second.home) {
            return this->home > second.home;

        } else if(this->flat!=second.flat) {
            return this->flat > second.flat;

        } else if(this->fio!=second.fio) {
            return this->fio > second.fio;

        } else{
            return this->birth > second.birth;
        }
    }

    bool operator<(Entry &second) {
        if (this->street!=second.street) {
            return this->street < second.street;

        } else if(this->home!=second.home) {
            return this->home < second.home;

        } else if(this->flat!=second.flat) {
            return this->flat < second.flat;

        } else if(this->fio!=second.fio) {
            return this->fio < second.fio;

        } else {
            return this->birth < second.birth;
        }
    }

    bool operator>=(Entry &second) {
        if (this->street!=second.street) {
            return this->street >= second.street;

        } else if(this->home!=second.home) {
            return this->home >= second.home;

        } else if(this->flat!=second.flat) {
            return this->flat >= second.flat;

        } else if(this->fio!=second.fio) {
            return this->fio >= second.fio;

        } else {
            return this->birth >= second.birth;
        }
    }

    bool operator<=(Entry &second) {
        if (this->street!=second.street) {
            return this->street <= second.street;

        } else if(this->home!=second.home) {
            return this->home <= second.home;

        } else if(this->flat!=second.flat) {
            return this->flat <= second.flat;

        } else if(this->fio!=second.fio) {
            return this->fio <= second.fio;

        } else {
            return this->birth <= second.birth;
        }
    }

    string fio;
    string street;
    int home;
    int flat;
    int birth;
};

ostream& operator<<(ostream& out, const Entry& entry) {
    return out << entry.street << "," << entry.home << "," << entry.flat << "," << entry.fio << "," << entry.birth << endl;
}
/*!
Сортирует методом вставок
\param[a] a Массив данных
\param[size] size Размер массива
\return Ничего не возвращает
*/
template<class T> void insertSort(vector<T>& a, long size) {
    T x;
    long i, j;

    for (i = 0; i < size; i++) { //номер шага
        x = a[i]; //знач перемещаемого элемента
        for ( j=i-1; j>=0 && a[j] > x; j--) {
            a[j+1] = a[j];//если проверяемый больше нашего, то перетираем им следующий элемент
        }
        a[j+1] = x;//если проверяемый меньше нашего, то перетираем нашим элементом следующий
    }
}
/*!
Сортирует методом шейкер-сортировки
\param[a] a Массив данных
\param[size] size Размер массива
\return Ничего не возвращает
*/
template<class T> void shakerSort(vector<T>& a, long size) {
  long j, k = size-1;
  long lb=1, ub = size-1; // границы неотсортированной части массива
  T x;

  do {
    // пробегаем сверху вниз
    for( j=ub; j>0; j-- ) {
      if ( a[j-1] > a[j] ) {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }
    lb = k+1;

    // пробегаем снизу вверх
    for (j=1; j<=ub; j++) {
      if ( a[j-1] > a[j] ) {
        x=a[j-1]; a[j-1]=a[j]; a[j]=x;
        k=j;
      }
    }
    ub = k-1;
  } while ( lb < ub );
}
/*!
Собирает из массива "кучу"
\param[a] a Массив данных
\param[k] k номер элемента с которого бежим вниз
\param[n] n Размер массива
\return Ничего не возвращает
*/
template<class T> void createHeap(vector<T>& a, long k, long n){
    long child;
    //будем продолжать спускаться вниз по куче, пока есть элемент у которого потомок больше него
    while (((2*k+1<=n and a[2*k+1]>a[k]) or (2*k+2<=n and a[2*k+2]>a[k]))) {
        child = 2*k+1;
        //выбираем бОльшего ребёнка(заодно проверяем, что элемент не последний, иначе КУДА ТЫ ЕГО УВЕЛИЧИВАТЬ ТО БУДЕШЬ НА ОДИН?)
        if (child < n and a[child]<a[child+1]) {
            ++child;
        }
        //махнём неглядя два элемента и будем смотреть дальше по куче относительно позиици ребёнка (свопать и его потомов тоже)
        if (a[child]>a[k]) {
            swap(a[k],a[child]);
            k = child;
        } else {
            break;
        }
    }
}
/*!
Сортирует методом кучи (пирамиды)
\param[arr] a Массив данных
\param[size] size Размер массива
\return Ничего не возвращает
*/
template<class T> void heapSort(vector<T>& a,long size) {
    //идем по элементам у которых есть потомки и собираем первичкую кучу
    for (long i = size/2-1; i>=0; --i) {
        createHeap(a,i,size-1);
    }
    for (long j = size; j>=2; --j) {
        swap(a[0],a[j-1]);
        createHeap(a,0,j-2);
    }
}

/*!
Парсит данные из файла, сортирует в соответствии с выбранным алгоритмом. Записывает результат в файл /out/имяфайла.
\param[fileName] fileName Имя файла
\param[sortAlgo] sortAlgo Нормер алгоритма
\return Ничего не возвращает
*/
void handleFile(string fileName, int sortAlgo) {
    string openPath = "tests/" + fileName;
    ifstream file(openPath);

    vector<Entry> data;
    string line, field;

    //parce from the file into data
    while ( getline(file,line) )    // get next line in file
    {
        stringstream ss(line);
        int i = 0;
        string fio, street;
        int home, flat, birth;
        while (getline(ss,field,','))
        {
            switch (i) {
            case 0:
                fio = field;
                break;
            case 1:
                street = field;
                break;
            case 2:
                home = stoi(field);
                break;
            case 3:
                flat = stoi(field);
                break;
            case 4:
                birth = stoi(field);
                break;
            default:
                break;
            }
            ++i;
        }
        Entry entry(fio,street,home,flat,birth);
        data.push_back(entry);
    }

    auto begin = std::chrono::steady_clock::now();
    switch (sortAlgo) {
    case 1:
        insertSort(data,data.size());
        break;
    case 2:
        shakerSort(data,data.size());
        break;
    case 3:
        heapSort(data,data.size());
        break;
    default:
        break;
    }
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - begin);
    cout << "File:" << fileName << " Alg:" << sortAlgo << " Time:" << elapsed_ms.count() << " ms\n";

    string outStr = "out/" +fileName;
    ofstream out(outStr);
    for (int i = 0; i < data.size(); ++i){
        out << data[i];
    }
}

int main() {
    //1 - insertSort, 2 - shakerSort, 3 - heapSort
    handleFile("test200.txt",1);
    handleFile("test500.txt",1);
    handleFile("test1000.txt",1);
    handleFile("test8000.txt",1);
    handleFile("test30000.txt",1);
    handleFile("test60000.txt",1);
    handleFile("test120000.txt",1);
    cout << "---------------------" << endl;
    handleFile("test200.txt",2);
    handleFile("test500.txt",2);
    handleFile("test1000.txt",2);
    handleFile("test8000.txt",2);
    handleFile("test30000.txt",2);
    handleFile("test60000.txt",2);
    handleFile("test120000.txt",2);
    cout << "---------------------" << endl;
    handleFile("test200.txt",3);
    handleFile("test500.txt",3);
    handleFile("test1000.txt",3);
    handleFile("test8000.txt",3);
    handleFile("test30000.txt",3);
    handleFile("test60000.txt",3);
    handleFile("test120000.txt",3);
    return 0;

}
