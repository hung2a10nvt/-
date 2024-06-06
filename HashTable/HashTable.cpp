#include <iostream>
#include <vector>
#include <cstring>
#include <random>

class SList{
    struct Node{
        char* data;
        Node* next;
        Node(char* str) : data(str), next(nullptr){};
    };
    Node* head;
    int size;

    public:
        SList() : head(nullptr), size(0){};

        ~SList(){
            Node* current = head;
            while (current != nullptr){
                Node* next = current->next;
                delete current;
                current = next;
            }
        }

        bool contains(char* str){
            Node* current = head;
            while (current != nullptr){
                if (strcmp(current->data, str) == 0){
                return true;
                }
                current = current->next;
            }
            return false;
        }

        void add(char* str){
            if (!contains(str)){
                Node* add = new Node(str);
                add->next = head;
                head= add;
                size++;
            }
        }

        void merge(SList &other){
            Node* current = other.head;
            while (current != nullptr){
                add(current->data);
                current = current->next;
            }
        }

        int find(char* str){
            int index;
            Node* current = head;
            while (current){
                if (strcmp(current->data, str) == 0){
                    return index;
                }
                current = current->next;
                index++;
            }
            return -1;
        }

        int getSize(){
            return size;
        }

        void Print(){
            Node* current = head;
            while (current != nullptr){
                std::cout << current->data << std::endl;
                current = current->next;
            }
        }
    };

class HashTable{
    std::vector<SList> HT;
    int q;

    int hash(char* str){
        int h = 0;
        while (*str) {
            h = (h * 31 + *str++) % q;
        }
        return h;
    }

    public:
        HashTable(int q) : q(q), HT(q) {};
        void add(char* str){
            int index = hash(str);
            HT[index].add(str);
        }

        SList UniqueTable(){
            SList res;
            for (auto& list : HT){
                res.merge(list);
            }

            return res;
        }

        int find(char* str){
            int index = hash(str);
            return HT[index].find(str);
        }
};

char* randomString(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";  
    char* randomString = new char[length + 1];

    for (int i = 0; i < length; ++i) {
        randomString[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    randomString[length] = '\0';
    return randomString;
}

// Создать п строки и сохрать в storage
void generateRandomStrings(std::vector<char*>& storage, int n) {
    std::mt19937 generator(time(nullptr));
    std::uniform_int_distribution<> limit(5, 10);

    for (int i = 0; i < n; ++i) {
        int length = limit(generator);
        storage.push_back(randomString(length));
    }
}

int main(){
    int n = 10000;
    std::vector<char*> strings;
    generateRandomStrings(strings, n);

    HashTable Table(n);

    for (int i = 0; i < n; i++){
        Table.add(strings[i]);
    } 

    //Test Find function
    char* Test = "Test";
    Table.add(Test);

    SList unique = Table.UniqueTable();
    unique.Print();

    std::cout << "Total unique strings: " << unique.getSize() << std::endl;

    std::cout << "Find: " << Table.find(Test) << std::endl;
    
    for (char* str : strings){
        delete[] str;
    }

    // s1 = 5 , s2 = 5

    return 0;
}