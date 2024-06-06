#ifndef OLYMPIAD_H
#define OLYMPIAD_H
#include <ctime>
#include <cstdlib>

class Olympiad{

    private:
        int ID;
        static int nextID;
        int Solved_problems;
        double Time;
        double Point;
        int Attemps;

    public:
        Olympiad(int Solved_problems = 0, double Time = 300, double Point = 0, int Attemps = 20) : ID(nextID++), Solved_problems(Solved_problems), Time(Time), Point(Point), Attemps(Attemps){};
        //Создать случайный участник
        static Olympiad Random();
        bool operator<(const Olympiad& obj);
        Olympiad & operator[](int n);
        friend std::ostream & operator << (std::ostream &r, Olympiad &x);
};

int Olympiad::nextID = 1;

Olympiad Olympiad::Random(){
    int Solved_problems = rand() % 6;
    double Time = rand() % 241 + 60;
    double Point;
    switch (Solved_problems){ // ещё не знаю минимальный балл, получен после решал задачу, считаю 1 балл.
        case 0:
            Point = 0;
            break;
        case 1:
            Point = rand() % 6;
            break;
        case 2:
            Point = rand() % 9 + 2;
            break;
        case 3:
            Point = rand() % 13 + 3;
            break;
        case 4:
            Point = rand() % 17 + 4;
            break;
        case 5:
            Point = rand() % 21 + 5;
            break;
    };
    int Attemps = rand() % 21;

    return Olympiad(Solved_problems, Time, Point, Attemps);
};

bool Olympiad::operator<(const Olympiad& obj){
    if (Point != obj.Point){
        return Point < obj.Point;
    }

    if (Solved_problems != obj.Solved_problems){
        return Solved_problems < obj.Solved_problems;
    }

    if (Time != obj.Time){
        return Time > obj.Time;
    }

    if (Attemps != obj.Attemps){
        return Attemps > obj.Attemps;
    }

    return ID > obj.ID;
}


std::ostream & operator << (std::ostream &r, Olympiad &obj){
    r << "ID: " << obj.ID << std::endl << "Points: " << obj.Point << std::endl << "Solved: " << obj.Solved_problems << std::endl
    << "Time: " << obj.Time << std::endl << "Attempts: " << obj.Attemps;
    return r;
};

#endif