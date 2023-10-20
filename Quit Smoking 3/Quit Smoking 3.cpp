#include <iostream>
#include<string>
using namespace std;

struct Smoker {
    string name;
    int cigaretesSmoked[30];
    double average;
    Smoker* next;
};

Smoker* first;

void AddSmoker(Smoker*& first, string name)
{
    Smoker* newSmoker = new Smoker;
    newSmoker->name = name;
    newSmoker->average = 0;
    newSmoker->next = NULL;
    for (int i = 0; i < 30; i++)
    {
        newSmoker->cigaretesSmoked[i] = -1;
    }
    if (first == NULL)
    {
        first = newSmoker;
    }
    else
    {
        Smoker* current = first;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newSmoker;
    }
}

Smoker* SearchSmoker(Smoker* first, string name)
{
    Smoker* current = first;
    while (current != NULL)
    {
        if (current->name == name)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

double CalculateSmokerAverage(Smoker* smoker)
{
    double average = 0;
    int i;
    for (i = 0; i < 30; i++)
    {
        if (smoker->cigaretesSmoked[i] == -1)
        {
            break;
        }
        average += smoker->cigaretesSmoked[i];
    }
    return average / (double)(i);
}

int MinSmokerDay(Smoker* smoker)
{
    int min = 9999;
    for (int i = 0; i < 30; i++)
    {
        if (smoker->cigaretesSmoked[i] == -1)
        {
            break;
        }
        if (min > smoker->cigaretesSmoked[i])
        {
            min = smoker->cigaretesSmoked[i];
        }
    }
    if (min != 9999) {
        return min;
    }
    return -1;
}

int MaxSmokerDay(Smoker* smoker)
{
    int max = -1;
    for (int i = 0; i < 30; i++)
    {
        if (smoker->cigaretesSmoked[i] == -1)
            break;
        if (max < smoker->cigaretesSmoked[i])
            max = smoker->cigaretesSmoked[i];
    }
    return max;
}

int MaxSmokersDay(Smoker* first)
{
    int max = -1;
    int tempMax;
    Smoker* current = first;
    while (current != NULL)
    {
        tempMax = MaxSmokerDay(current);
        if (tempMax != -1 && tempMax > max)
            max = tempMax;
    }
    return max;
}

int MinSmokersDay(Smoker* first)
{
    int min = 9999;
    int tempMin;
    Smoker* current = first;
    while (current != NULL)
    {
        tempMin = MinSmokerDay(current);
        if (tempMin != -1 && tempMin < min)
            min = tempMin;
        current = current->next;
    }
    if (min != 9999)
        return min;
    return -1;
}

double CalculateSmokersAverage(Smoker* first)
{
    double average = 0;
    int count = 0;
    Smoker* current = first;
    while (current != NULL)
    {
        average += CalculateSmokerAverage(current);
        count++;
        current = current->next;
    }
    return average / count;
}

void DisplaySmokers(Smoker* first)
{
    Smoker* current = first;
    while (current != NULL)
    {
        cout << "Smoker's name " << current->name << " has smoked an average of " << CalculateSmokerAverage(current) << endl;
        for (int i = 0; i < 30; i++)
        {
            if (current->cigaretesSmoked[i] == -1)
            {
                break;
            }
            cout << "On day " << i + 1 << " he/she has smoked " << current->cigaretesSmoked[i] << "cigaretes!" << endl;
        }
        cout << endl;
        current = current->next;
    }
}

void RemoveSmoker(Smoker*& first, string name)
{
    if (first == NULL)
    {
        cout << "List already empty! No smokers here!";
        return;
    }
    if (first->name == name)
    {
        Smoker* remove = first;
        first = first->next;
        delete remove;
    }
    else
    {
        Smoker* current = first;
        while (current != NULL && current->name != name)
        {
            current = current->next;
        }
        if (current == NULL)
        {
            cout << "Smoker nowhere to be found!";
            return;
        }
        Smoker* currentPrev = first;
        while (currentPrev->next != current)
        {
            currentPrev = currentPrev->next;
        }
        currentPrev->next = current->next;
        delete current;
    }

}

int SumSmokerSmoked(Smoker* smoker)
{
    int sum = 0;
    int i = 0;
    while (smoker->cigaretesSmoked[i] != -1)
    {
        sum += smoker->cigaretesSmoked[i];
    }
    return sum;
}

int SumSmokersSmoked(Smoker* first)
{
    int sum = 0;
    Smoker* current = first;
    while (current != NULL)
    {
        sum += SumSmokerSmoked(current);
    }
    return sum;
}

void AddSmokerDay(Smoker* first, string name, int numberOfCigaretes)
{
    Smoker* smoker = SearchSmoker(first, name);
    int i;
    for (i = 0; i < 30; i++)
    {
        if (smoker->cigaretesSmoked[i] == -1)
        {
            smoker->cigaretesSmoked[i] = numberOfCigaretes;
            return;
        }
    }
    if (i > 29)
    {
        cout << "Already added a month's worth of data for " << smoker->name << "!";
    }
    smoker->cigaretesSmoked[i] = numberOfCigaretes;
}

void AddSmokerDays(Smoker* first, string name, int numberOfCigaretes[])
{
    Smoker* smoker = SearchSmoker(first, name);
    int i;
    for (i = 0; i < 30; i++)
    {
        if (smoker->cigaretesSmoked[i] == -1) {
            break;
        }
    }
    for (int j = 0; j < 30; j++)
    {
        if (i == 30) {
            cout << "Already added a month's worth of data for " << smoker->name << "!";
        }
        smoker->cigaretesSmoked[i] = numberOfCigaretes[j];
        i++;
    }
}

void DisplayOptions()
{
    cout << "1) For adding a smoker press 1 " << endl;
    cout << "2) For adding a day of smoking to a smoker press 2 " << endl;
    cout << "3) for adding a few days of smoking to a smoker press 3" << endl;
    cout << "4) for calculating smoker average press 4 " << endl;
    cout << "5) for calculating smoker min press 5 " << endl;
    cout << "6) for calculating smoker max press 6 " << endl;
    cout << "7) for calculating all of smokers average press 7 " << endl;
    cout << "8) for calculating all of smokers min press 8 " << endl;
    cout << "9) for calculating all of smokers max press 9 " << endl;
    cout << "10) for removing smoker press 10 " << endl;
    cout << "11) for displaying all smoker's info " << endl;
    cout << "12) for exit " << endl;
}

void AddDatabase(Smoker*& first)
{
    AddSmoker(first, "Galadriel");
    AddSmoker(first, "Gandalf");
    AddSmoker(first, "Frodo");
    AddSmoker(first, "Elrond");
    AddSmoker(first, "Legolas");
    int gal[30] = { 20, 19, 19, 18, 18, 17, 17, 16, 16, 15, 15, 14, 14, 13, 13, 12, 12, 11, 11, 10, 10, 9, 9, 8, 8, 7, 7, 6, 6, 5 };
    int gan[30] = { 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16 };
    int fr[30] = { 100, 97, 94, 91, 88, 85, 82, 79, 76, 73, 70, 67, 64, 61, 58, 55, 52, 49, 46, 43, 40, 37, 34, 31, 28, 25, 22, 19, 16, 13 };
    int el[30] = { 200, 196, 192, 188, 184, 180, 176, 172, 168, 164, 160, 156, 152, 148, 144, 140, 136, 132, 128, 124, 120, 116, 112, 108, 104, 100, 96, 92, 88, 84 };
    int le[30] = { 60, 58, 56, 54, 52, 50, 48, 46, 44, 42, 40, 38, 36, 34, 32, 30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2 };
    AddSmokerDays(first, "Galadriel", gal);
    AddSmokerDays(first, "Gandalf", gan);
    AddSmokerDays(first, "Frodo", fr);
    AddSmokerDays(first, "Elrond", el);
    AddSmokerDays(first, "Legolas", le);

}

int main()
{
    Smoker* first = NULL;
    cout << "With the help of linked lists this program shall keep track of any number of people who wish to reduce the amount of cigaretes they smoke in 30 days." << endl;
    cout << "This shall also compute min, max for each person and for all the people participating in the test." << endl;
    cout << "Let's start building the database! " << endl;
    int choice;
    AddDatabase(first);
    DisplayOptions();
    cin >> choice;
    string name;
    int days, i;
    int smokeddays[30];
    for (i = 0; i < 30; i++)
    {
        smokeddays[i] = -1;
    }
    while (choice > 0 && choice < 12)
    {
        if (choice == 1) {
            cout << "Please input smoker's name = ";
            cin >> name;
            AddSmoker(first, name);
        }
        else if (choice == 2) {
            cout << "Please input name of smoker you wish to add a smoking day to = ";
            cin >> name;
            cout << "Please input number of smoked cigaretes = ";
            int no;
            cin >> no;
            AddSmokerDay(first, name, no);
        }
        else if (choice == 3) {
            cout << "please input name of smoker you wish to add a smoking day to = ";
            cin >> name;
            cout << "Please input how many days you wish to add = ";
            cin >> days;
            for (i = 0; i < days; i++)
            {
                cout << "For day " << i++ << " how many cigaretes has " << name << "smoked ? = ";
                cin >> smokeddays[i];
            }
            AddSmokerDays(first, name, smokeddays);
        }
        else if (choice == 4) {
            cout << "Please input name of smoker : ";
            cin >> name;
            cout << name << " has smoked an average of " << CalculateSmokerAverage(SearchSmoker(first, name));
        }
        else if (choice == 5) {
            cout << "Please input name of smoker : ";
            cin >> name;
            cout << name << " has smoked an average of " << MinSmokerDay(SearchSmoker(first, name));
        }
        else if (choice == 6) {
            cout << "Please input name of smoker : ";
            cin >> name;
            cout << name << " has smoked an average of " << MaxSmokerDay(SearchSmoker(first, name));
        }
        else if (choice == 7) {
            cout << "All the smokers have smoked an average of " << CalculateSmokersAverage(first) << " cigaretes so far!";
        }
        else if (choice == 8) {
            cout << "The least a smoker has smoked is " << MinSmokersDay(first) << " cigaretes in a day!";
        }
        else if (choice == 9) {
            cout << "The most a smoker has smoked is " << MaxSmokersDay(first) << " cigaretes in a day!";
        }
        else if (choice == 10) {
            cout << "Please input name of smoker that has managed to quit = ";
            cin >> name;
            RemoveSmoker(first, name);
        }
        else if (choice == 11) {
            DisplaySmokers(first);
        }
        else {
            return 0;
        }
        DisplayOptions();
        cin >> choice;
    }
}

