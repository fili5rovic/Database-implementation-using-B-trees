#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;
//<editor-fold desc="Ispisi">
const char topLeftCorner = '\xDA';
const char bottomLeftCorner = '\xC0';
const char topRightCorner = '\xBF';
const char bottomRightCorner = '\xD9';
const char middleLeftCorner = '\xC3';
const char middleRightCorner = '\xB4';
const char horizontalLine = '\xC4';
const char verticalLine = '\xB3';
const char intersection = '\xC5';
const char middleDown = '\xC2';
const char middleUp = '\xC1';


string printline(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += '\xC4';
    }
    return s;
}

string printspace(int n) {
    string s;
    for (int i = 0; i < n; ++i) {
        s += ' ';
    }
    return s;
}

void upperTableHeading(int n, bool closing = true, bool end = true) {
    cout << topLeftCorner << printline(n);
    if (closing) cout << topRightCorner;
    if (end) cout << endl;
}

void lowerTableHeading(int n, bool closing = true, bool end = true) {
    cout << bottomLeftCorner << printline(n);
    if (closing) cout << bottomRightCorner;
    if (end) cout << endl;
}

void newMenu(int line_len, int strlen, string options[], int pomeraj = 7) {
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - options[0].length()) / 2) << options[0]
         << printspace((line_len - options[0].length()) / 2) << verticalLine << endl;
    cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    for (int i = 1; i < strlen; ++i) {
        cout << verticalLine << printspace(pomeraj) << options[i]
             << printspace((line_len - options[i].length()) - pomeraj) << verticalLine << endl;
        if (i < strlen - 1)
            cout << middleLeftCorner << printline(line_len) << middleRightCorner << endl;
    }
    lowerTableHeading(line_len);
}

void newMessage(string poruka = "", int line_len = 40) {
    cout << endl;
    upperTableHeading(line_len);
    cout << verticalLine << printspace((line_len - poruka.length()) / 2) << poruka
         << printspace((line_len - poruka.length()) / 2) << verticalLine << endl;
    lowerTableHeading(line_len);
}

//</editor-fold>
int m = 4; // kada kazem 4, misli se na m = 3

struct Acc {
    long long CA_ID, CA_B_ID, CA_C_ID, CA_TAX_ST;
    long double CA_BAL;
    string CA_NAME;

    Acc() : CA_ID(0), CA_B_ID(0), CA_C_ID(0), CA_TAX_ST(0), CA_BAL(0) { CA_NAME = ""; }

    Acc(long long ca_id, long long ca_b_id, long long ca_c_id, long long ca_tax_st, long double ca_bal,
        string ca_name = "")
            : CA_ID(ca_id), CA_B_ID(ca_b_id), CA_C_ID(ca_c_id), CA_TAX_ST(ca_tax_st),
              CA_BAL(ca_bal) { CA_NAME = std::move(ca_name); }

    friend ostream &operator<<(ostream &os, const Acc &d) {
        os << d.CA_ID << " " << d.CA_B_ID << " " << d.CA_C_ID << " " << d.CA_TAX_ST << " " << d.CA_BAL << endl;
        return os;
    }

    bool operator==(Acc a) {
        return (a.CA_ID == CA_ID && a.CA_B_ID == CA_B_ID && a.CA_C_ID == CA_C_ID && a.CA_TAX_ST == CA_TAX_ST);
    }

    void add(Acc *newAcc) {
        Acc *curr = this;
    }

    long long getCaCID() const {
        return CA_C_ID;
    }

    void setCaCId(int a) { CA_C_ID = a; }

};

struct AccList {
    struct AccNode {
        Acc info;
        AccNode *next;

        AccNode(Acc info) : info(info), next(nullptr) {}

    };

    AccNode *first;

    AccList() { first = nullptr; }

    void add(const Acc &acc) {
        if (first == nullptr) {
            first = new AccNode(acc);
            return;
        }
        AccNode *curr = first;
        while (curr->next) { curr = curr->next; }
        curr->next = new AccNode(acc);
    }


    Acc *getIndex(int index) {
        AccNode *current = first;
        int currentIndex = 0;

        while (current != nullptr) {
            if (currentIndex == index) {
                return &(current->info);
            }
            current = current->next;
            currentIndex++;
        }

        return nullptr;
    }

    AccList copy() {
        AccNode *curr = first;
        AccList newList;
        while (curr) {
            newList.add(curr->info);
            curr = curr->next;
        }
        return newList;
    }

    void print() const {
        AccNode *curr = first;
        while (curr) {
            cout << curr->info << endl;
            curr = curr->next;
        }
    }

    void clear() {
        AccNode *current = first;
        while (current != nullptr) {
            AccNode *temp = current;
            current = current->next;
            delete temp;
        }
        first = nullptr;
    }

    void remove(long long id) {
        if (!first) return;
        AccNode *curr = first, *prev = nullptr;

        while (curr) {
            if (curr->info.CA_ID == id) {
                if (prev) {
                    prev->next = curr->next;
                } else {
                    first = curr->next;
                }
                delete curr;
                break;
            }
            prev = curr;
            curr = curr->next;
        }
    }


    bool isEmpty() const {
        return first == nullptr;
    }
};

struct Data {
private:
    long long id; // dok ne dodam, id je -1
public:
    AccList list;
    Data() {
        id = -1;
        list = AccList();
    }

    Data(const Acc &a) {
        id = a.getCaCID();
        list = AccList();
        list.add(a);
    }

    Data(Data &d) {
        id = d.id;
        list = d.list.copy();
    }

    void add(const Acc &d) {
        if (d.getCaCID() == id || list.isEmpty()) {
            id = d.getCaCID();
            list.add(d);
        } else {
            cout << "GRESKA UBACIVANJE" << endl;
        }
    }


    long long getId() { return id; }

    void setId(long long id) { this->id = id; }

    void clear() {
        this->id = -1;
        //list.clear();
        list = AccList();
    }

    friend ostream &operator<<(ostream &os, Data &d) {
        cout << "ID: " << d.id << endl;
        d.list.print();
    }

};

class Node {
    Data *data;
    Node **elems{};
    int parentIndex = -1;

    void sortData() {
        // za -1, jer mi treba za najdesnji kad ga cuvam
        for (int i = 0; i < m - 1; ++i) {
            for (int j = i + 1; j < m - 1; ++j) {
                if ((data[i].getId() == -1 && data[j].getId() != -1)) {
                    Data temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                    break;
                }
            }
        }
        for (int i = 0; i < m - 1; ++i) {
            for (int j = i + 1; j < m - 1; ++j) {
                if (data[i].getId() != -1 && data[j].getId() != -1) {
                    if (data[i].getId() > data[j].getId()) {
                        Data temp = data[i];
                        data[i] = data[j];
                        data[j] = temp;
                        break;
                    }
                }
            }
        }
//        cout << "SORTED DATA: ";
//        for (int i = 0; i < m-1; ++i) {
//            cout << data[i].getId() << " ";
//        }
//        cout << endl;
    }

    void addDataHelp(const Acc &a) {
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() == -1) {
                data[i].add(a);
                sortData();
                break;
            }
        }
    }

public:
    Node() {
        elems = new Node *[m]{};
        data = new Data[m - 1]{};
    }

    Node(const Acc &a) {
        elems = new Node *[m]{};
        data = new Data[m - 1]{};

        addDataHelp(a);
        sortData();
    }

    bool addData(Data &d) {
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() == -1) {
                data[i] = d;
                sortData();
                return true;
            }
        }
        return false;
    }

    void addAcc(Acc &a) {
        bool found = false;
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() == a.getCaCID()) {
                data[i].add(a);
                found = true;
                break;
            }
        }
        if (!found) {
            addDataHelp(a);
        }
    }

    void printNode() {
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() != -1) {
                cout << data[i].getId() << " ";
            }
        }
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() != -1) {
                data[i].list.print();
            }
        }
    }

    Node *getElemAt(int index) {
        if (elems == nullptr) {
            cout << this->getData()[0].getId() << endl;
            cout << "ELEMENTI PRAZNI!" << endl;
            exit(3);
        }
        if (index >= 0 && index < m)
            return elems[index];
        else {
            cout << "UZAS! " << index << endl;
            return nullptr;
        }
    }

    void setElemAt(int index, Acc &acc) {
        if (!elems) {
            cout << "ELEMENTI PRAZNI!" << endl;
            exit(3);
        }
        elems[index] = new Node();
        elems[index]->addAcc(acc);
    }

    void setElemNodeAt(int index, Node *node) {
        if (!elems) {
            cout << "ELEMENTI PRAZNI!" << endl;
            exit(3);
        }
        elems[index] = node;
        if (node != nullptr)
            node->setParentIndex(index);

    }


    bool isFull() {
        for (int i = 0; i < m - 1; ++i) {
            if (data[i].getId() == -1) {
                return false;
            }
        }
        return true;
    }


    void deleteData(const Acc &a) {
        for (int i = 0; i < m - 1; ++i) {
            if (a.getCaCID() == data[i].getId()) {
                data[i].clear();
                break;
            }
        }
    }

    Data *getData() {
        return data;
    }

    void setData(int index, Data &d) {
        data[index] = d;
    }

    void clearDataOn(int index) {
        data[index] = Data();
    }

    void sortDataFromTree() {
        sortData();
    }

//    ~Node() {
//        for (int i = 0; i < m; ++i) {
//            delete elems[i];
//            elems[i] = nullptr;
//        }
//        delete[] elems;
//        elems = nullptr;
//    }

    void setParentIndex(int id) {
        parentIndex = id;
    }

    int getParentIndex() {
        return parentIndex;
    }

    friend ostream &operator<<(ostream &os, Node &n) {
        for (int i = 0; i < m - 1; ++i) {
            cout << n.data[i];
        }
        return os;
    }

    bool hasChildren() {
        for (int i = 0; i < m - 1; ++i) {
            if (elems[i] != nullptr) {
                return true;
            }
        }
        return false;
    }
};

// Funkcija za citanje podataka iz datoteke i kreiranje objekata
vector<Acc> readDataToVector(const string &filename) {
    ifstream file(filename);
    string line;
    vector<Acc> accounts;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 6) {
                long long ca_id = stoll(tokens[0]);
                long long ca_b_id = stoll(tokens[1]);
                long long ca_c_id = stoll(tokens[2]);
                int ca_tax_st = stoi(tokens[4]);
                long double ca_bal = stold(tokens[5]);
                string ca_name = tokens[3];

                Acc account(ca_id, ca_b_id, ca_c_id, ca_tax_st, ca_bal, ca_name);
                accounts.push_back(account);
            }
        }
        file.close();
    } else {
        cout << "Nije uspesno unet naziv fajla\n";
    }
    return accounts;

}

void resetFile() {
    ofstream file("korisnik.txt");
    if (file.is_open()) {
        file << "";
        file.close();
    } else {
        cout << "Nije uspesno unet naziv fajla\n";
    }
}

void appendToFile(string line) {
    ofstream file("korisnik.txt", ios::app);
    if (file.is_open()) {
        file << line << endl;
        file.close();
    } else {
        cout << "Nije uspesno unet naziv fajla\n";
    }
}


void writeToCustomerNull(long long id) {
    ifstream file("Customer.txt");
    string line;
    vector<Acc> accounts;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 5) {
                long long c_id = stoll(tokens[0]);
                string c_f_name = tokens[1];
                string c_l_name = tokens[2];
                string c_email = tokens[3];
                long double c_ad_id = stold(tokens[4]);
                if(c_id == id) {
                    string lineToAppend = to_string(c_id) + "|" + c_f_name + "|" + c_l_name + "|" + c_email + "|null|null|null|null";
                    appendToFile(lineToAppend);
                    cout << "Ime " << c_f_name << endl;
                    cout << "Prezime " << c_l_name << endl;
                    cout << "Email " << c_email << endl;
                    return;
                }
                // Acc account(ca_id, ca_b_id, ca_c_id, ca_tax_st, ca_bal, ca_name);
                // accounts.push_back(account);
            }
        }
        file.close();
    } else {
        cout << "Nije uspesno unet naziv fajla\n";
    }
}

void readCustomerWithId(long long id) {
    ifstream file("Customer.txt");
    string line;
    vector<Acc> accounts;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> tokens;

            while (getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 5) {
                long long c_id = stoll(tokens[0]);
                string c_f_name = tokens[1];
                string c_l_name = tokens[2];
                string c_email = tokens[3];
                long double c_ad_id = stold(tokens[4]);
                if(c_id == id) {
                    cout << "Ime " << c_f_name << endl;
                    cout << "Prezime " << c_l_name << endl;
                    cout << "Email " << c_email << endl;

                    appendToFile(to_string(id) + "|" + c_f_name + "|" + c_email + "|" + to_string(c_ad_id));
                    return;
                }
                // Acc account(ca_id, ca_b_id, ca_c_id, ca_tax_st, ca_bal, ca_name);
                // accounts.push_back(account);
            }
        }
        file.close();
    } else {
        cout << "Nije uspesno unet naziv fajla\n";
    }
}

class B_tree {
public:
    Node *root;

    B_tree() : root(nullptr) {}

    B_tree(const Node &n) {
        root = new Node(n);
    }

    void checkForSplit(Node *curr, stack<Node *> &prevStack) {
        if (!curr->isFull())
            return;
//        cout << "POCETAK FUNKCIJE! Za cvor ";
//        for (int i = 0; i < m - 1; ++i) {
//            if (curr->getData()[i].getId() != -1)
//                cout << curr->getData()[i].getId() << " ";
//        }
//        cout << endl << "Sa stekom koji je " << prevStack.empty() << endl;


        // ovo radim u prvom slucaju
        if (prevStack.empty()) {
            Node *newNode1 = new Node();
            newNode1->setParentIndex(0);

            Node *newNode2 = new Node();
            newNode2->setParentIndex(1);

            //prevezivanje dece
            int ind = 0;
            for (int i = 0; i < m; ++i) {
                if (i < m / 2) {
                    if (curr->getElemAt(i)) {
                        newNode1->setElemNodeAt(i, curr->getElemAt(i));
//                        cout << "PRVI: " << i << endl;
                    }
                } else {
                    if (curr->getElemAt(i)) {
                        newNode2->setElemNodeAt(i, curr->getElemAt(i));
                        if (newNode2->getElemAt(i) == curr->getElemAt(i)) {
                            curr->setElemNodeAt(i, nullptr);
                        }
                        newNode2->getElemAt(i)->setParentIndex(ind++);
//                        cout << "DRUGI: " << i << endl;
                    }
                }
            }
            // odvezivanje ostalih, osim prva dva
            for (int i = 0; i < m; ++i) {
                curr->setElemNodeAt(0, nullptr);
            }
            curr->setElemNodeAt(0, newNode1);
            curr->setElemNodeAt(1, newNode2);

            for (int i = 0; i < m - 1; ++i) {
                if (i < (m - 1) / 2) {
                    newNode1->addData(curr->getData()[i]);
                } else if (i > (m - 1) / 2) {
                    newNode2->addData(curr->getData()[i]);
                }
            }
            curr->setData(0, curr->getData()[(m - 1) / 2]); // OVDE PUCA PROGRAM!
            for (int i = 1; i < m - 1; ++i) {
                curr->getData()[i].clear();
            }
            return;
        }

        // ovo u ostalim slucajevima
        if (curr->getData()[m - 2].getId() != -1) {
            prevStack.top()->addData(curr->getData()[(m - 1) / 2]);
//            cout << "Treba da ga podelim kad smestam " << curr->getData()[m - 2].getId() << endl;
//            cout << "Dodao sam cvor " << curr->getData()[(m - 1) / 2].getId() << " u njegovog tatu." << endl;

            Node *novi = new Node();
            novi->setParentIndex(curr->getParentIndex() + 1);

            int ind = 0;
            for (int i = 0; i < m; ++i) {
                if (prevStack.top()->getElemAt(i)) {
//                    cout << "NA INDEKSU " << i << " SE NALAZI ";
//                    cout << prevStack.top()->getElemAt(i)->getData()[0].getId() << endl;
                }
                if (i < m / 2) {
                } else {
                    if (prevStack.top()->getElemAt(i)) {
                        novi->setElemNodeAt(i, prevStack.top()->getElemAt(i));
                        if (novi->getElemAt(i) == prevStack.top()->getElemAt(i)) {
                            prevStack.top()->setElemNodeAt(i, nullptr);
                        }
                        novi->getElemAt(i)->setParentIndex(++ind);
//                        cout << endl << "SETOVANO: " << i << endl;

                    }
                }
            }

            // pomeranje indeksa
            for (int i = novi->getParentIndex(); i < m; i += 2) {
                if (prevStack.top()->getElemAt(i)) {
//                    cout << "SADA JE ";
                    for (int j = 0; j < m - 1; ++j) {
                        if (prevStack.top()->getElemAt(i)->getData()[j].getId() != -1) {
//                            cout << prevStack.top()->getElemAt(i)->getData()[j].getId() << " ";
                        }
                    }
//                    cout << "na indeksu " << i + 1 << endl;
                    prevStack.top()->setElemNodeAt(i + 1, prevStack.top()->getElemAt(i));
                }
            }

            // dodajem novi element na njegov indeks, nakon sto sam pomerio ostale
            prevStack.top()->setElemNodeAt(novi->getParentIndex(), novi);

            Data *temp = curr->getData();
            for (int i = 0; i < m - 1; ++i) {
                if (i >= (m - 2) / 2) {
                    if (i > (m - 2) / 2) {
                        novi->addData(temp[i]);
                    }
                    curr->getData()[i].clear();
                }
            }
        }
    }

    void add(Acc &acc) {
        addAcc(acc);
        stack<Node *> stack1;
        checkForSplit(root, stack1);
    }

    void searchBTree(long long id) {
        int steps = 0;
        Node *curr = root;
        if(curr == nullptr) {
            newMessage("Stablo je prazno! ");
            return;
        }
        resetFile();
        while (true) {
            steps++;
            for (int i = 0; i < m - 1; ++i) {
                if (curr->getData()[i].getId() == id) {
                    //otvori fajl Customer.txt i pronadji podatke sa tim id

                    cout << "Pronadjen je korisnik sa id " << id << endl;
                    //  appendToFile(to_string(id) + "|");
                    cout << "Broj koraka: " << steps << endl;
                    cout << "--------- Podaci o korisniku ----------" << endl;
                    cout << "ID: " << curr->getData()[i].getId() << endl;
                    readCustomerWithId(id);
                    cout << "Racuni: " << endl;
                    curr->printNode();
                    //  newMessage("Fajl uspesno kreiran.");
                    // appendToFile("\n");
                    return;
                }
            }
            int najdesnje = -1;
            for (int j = m - 2; j > 0; --j) {
                if (curr->getData()[j].getId() != -1) {
                    najdesnje = j;
                    break;
                }
            }
            najdesnje += 2;
            if (najdesnje == m - 1) {
                najdesnje--;
            }
            if (curr->getElemAt(najdesnje) == nullptr) {
                cout << "Nije pronadjen korisnik sa id " << id << endl;
                cout << "Broj koraka: " << steps << endl;
                writeToCustomerNull(id);
                return;
            } else {
                curr = curr->getElemAt(najdesnje);
            }
        }
    }

    void addAcc(Acc &acc) {
//        cout << acc.getCaCID() << " :" << endl;
        Node *curr = root;
        stack<Node *> prevStack;
        if (curr == nullptr) {
            root = new Node(acc);
            return;
        }
        checkForSplit(curr, prevStack);

        long long newId = acc.getCaCID();
        int i;
        while (true) { // moram zbog slucaja van fora kad je najdesnji sin
            for (i = 0; i < m - 1; ++i) {
                if (curr->getData()[i].getId() == -1)
                    continue;
                // ako nije full, SIGURNO mogu da ga dodam u taj cvor. Ako je identican id, dodaj ga na listu
                if ((!curr->isFull() && !curr->hasChildren()) || newId == curr->getData()[i].getId()) {
                    curr->addAcc(acc);
                    checkForSplit(curr, prevStack);
                    return;
                }
                    // ako je manji, probaj da ga ubacis
                else if (newId < curr->getData()[i].getId()) {
                    // ako ne postoji vise sinova, dodaj element
                    if (!curr->getElemAt(i)) {
                        curr->setElemAt(i, acc);
                        curr->getElemAt(i)->setParentIndex(i);
                        checkForSplit(curr, prevStack);
                        return;
                    }
                    // ako postoji, iteriraj dalje
                    prevStack.push(curr);
                    curr = curr->getElemAt(i);
                    i = -1;
                }
            }
            int najdesnje = -1;
            for (int j = m - 2; j > 0; --j) {
                if (curr->getData()[j].getId() != -1) {
                    najdesnje = j;
                    break;
                }
            }

            najdesnje += 2;
            if (najdesnje == m - 1) {
                najdesnje--;
            }

            // ako se zavrsio ciklus, dodajem elemente skroz desno, jer nije nigde manji
            if (curr->getElemAt(najdesnje) == nullptr) {
                for (int j = 0; j < m - 2; ++j) {
                    if (curr->getData()[j].getId() != -1) {
                        break;
                    }
                }
                curr->setElemAt(najdesnje, acc);
                curr->getElemAt(najdesnje)->setParentIndex(najdesnje);
                checkForSplit(curr, prevStack);
                return;
            }
            // ako nije nullptr, onda idem skroz desno pa idem sve ispocetka
            checkForSplit(curr, prevStack);

            prevStack.push(curr);
            curr = curr->getElemAt(najdesnje);


        }
    }

    int getHeight(Node *node) {
        if (node == nullptr) {
            return -1;
        }
        queue<Node *> q;
        q.push(node);
        int height = -1;
        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node *curr = q.front();
                q.pop();
                for (int j = 0; j < m; ++j) {
                    if (curr->getElemAt(j)) {
                        q.push(curr->getElemAt(j));
                    }
                }
            }

            height++;
        }
        return height;
    }

    void printTree() {
        if(root == nullptr)  {
            newMessage("Stablo je prazno! ");
            return;
        }
        queue<Node *> q;
        int i, line_len = 62, first_skip = line_len, in_between_skip;
        q.push(root);
        int treeHeight = getHeight(this->root);
        int nodesOnLevel = 1; // Broj čvorova na trenutnom nivou

        for (i = 0; i <= treeHeight + 1; i++) {
            first_skip = first_skip / m; // Prilagođavanje za naredni nivo
            in_between_skip = first_skip;
            for (int k = 0; k < first_skip; k++) putchar(' ');

            for (int k = 0; k < nodesOnLevel; k++) {
                Node *btn = q.front();
                q.pop();
                if (btn) {
                    for (int f = 0; f < m; f++) {
                        q.push(btn->getElemAt(f));
                    }
                    if (btn->getParentIndex() != -1)
                        cout << btn->getParentIndex();
                    cout << "[ ";
                    for (int w = 0; w < m - 1; ++w) {
                        if (btn->getData()[w].getId() != -1)
                            cout << btn->getData()[w].getId() << " ";
                    }
                    cout << "]";
                } else {
                    for (int g = 0; g < m; g++) {
                        q.push(nullptr);
                    }
                    printf("  ");
                }
                for (int l = 0; l < in_between_skip; l++) putchar(' ');
            }
            cout << endl;
            nodesOnLevel *= m; // Ažuriranje broja čvorova za naredni nivo
        }
    }

    void level_order1() {
        if (root == nullptr) return;
        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node *curr = q.front();
                q.pop();

                // Ispisuje trenutni čvor u formatu [id1 id2 ... idn]
                if (curr->getParentIndex() != -1)
                    cout << curr->getParentIndex();
                cout << "[ ";
                for (int j = 0; j < m - 1; j++) {
                    cout << curr->getData()[j].getId() << " ";
                }
                cout << "] ";

                // Dodaje potomke trenutnog čvora u red
                for (int j = 0; j < m; j++) {
                    if (curr->getElemAt(j) != nullptr) {
                        q.push(curr->getElemAt(j));
                    }
                }
            }
            cout << endl; // Prebacuje na sledeći nivo
        }
    }

    void level_order() {
        if (root == nullptr) return;
        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++) {
                Node *curr = q.front();
                q.pop();

                // Ispisuje trenutni čvor u formatu [id1 id2 ... idn]
                if (curr->getParentIndex() != -1)
                    cout << curr->getParentIndex();
                cout << "[ ";
                for (int j = 0; j < m - 1; j++) {
                    if (curr->getData()[j].getId() != -1) {
                        cout << curr->getData()[j].getId() << " ";
                    }
                }
                cout << "] ";

                // Dodaje potomke trenutnog čvora u red
                for (int j = 0; j < m; j++) {
                    if (curr->getElemAt(j) != nullptr) {
                        q.push(curr->getElemAt(j));
                    }
                }
            }
            cout << endl; // Prebacuje na sledeći nivo
        }
    }




};

void deleteAccFromTree(B_tree tree, long long int unos);

void deleteUserFromTree(B_tree &b, long long id) {
    B_tree b1;
    vector<Acc> accs = readDataToVector("CustomerAccount20.txt");
    for (int i = 0; i < accs.size(); ++i) {
        if(accs[i].CA_C_ID != id)
            b1.add(accs[i]);
        else {
            cout << "Obrisao sam: " << accs[i];
        }
    }
    b = b1;
    newMessage("Uspesno obrisani racuni korisnika!");
}

void makeObjects(B_tree &b) {
    vector<Acc> accs = readDataToVector("CustomerAccount20.txt");
    for (int i = 0; i < accs.size(); ++i) {
//        cout << accs[i];
        b.add(accs[i]);
    }
    newMessage("Uspesno kreirano stablo!");
}


//Brisanje svih računa jednog CUSTOMER-a. Zadaje se parametar CA_C_ID. Potrebno je, na standardan izlaz, ispisati ukupan broj koraka za koje je celokupna operacija završena, kao i sve zapise koji su obrisani. Ukoliko nije obrisan ni jedan zapis, ispisati informacionu poruku o tome.
void deleteAccount(B_tree &b, long long id) {
    int steps = 0;
    Node *curr = b.root;
    if(curr == nullptr) {
        cout << "Stablo je prazno!" << endl;
        return;
    }
    while (true) {
        steps++;
        for (int i = 0; i < m - 1; ++i) {
            if (curr->getData()[i].getId() == id) {
                curr->getData()[i].clear();
                return;
            }
        }
        int najdesnje = -1;
        for (int j = m - 2; j > 0; --j) {
            if (curr->getData()[j].getId() != -1) {
                najdesnje = j;
                break;
            }
        }
        najdesnje += 2;
        if (najdesnje == m - 1) {
            najdesnje--;
        }
        if (curr->getElemAt(najdesnje) == nullptr) {
            cout << "Nije pronadjen korisnik sa id " << id << endl;
            cout << "Broj koraka: " << steps << endl;
            return;
        } else {
            curr = curr->getElemAt(najdesnje);
        }
    }
}


void addAccount(B_tree& b) {
    long long CA_ID, CA_B_ID, CA_C_ID, CA_TAX_ST;
    long double CA_BAL;
    string CA_NAME;

    newMessage("Unesite CA_ID:  ", 60);
    cout << "->";
    cin >> CA_ID;
    newMessage("Unesite CA_B_ID:  ", 60);
    cout << "->";
    cin >> CA_B_ID;
    newMessage("Unesite CA_C_ID:  ", 60);
    cout << "->";
    cin >> CA_C_ID;
    newMessage("Unesite CA_TAX_ST:  ", 60);
    cout << "->";
    cin >> CA_TAX_ST;
    newMessage("Unesite CA_BAL: ", 60);
    cout << "->";
    cin >> CA_BAL;
    newMessage("Unesite CA_NAME:  ", 60);
    cout << "->";
    cin >> CA_NAME;
    Acc a(CA_ID, CA_B_ID, CA_C_ID, CA_TAX_ST, CA_BAL, CA_NAME);
    cout << a << endl;
    b.add(a);
}

void deleteAccFromTree(B_tree tree, long long id, long long unos) {
    int steps = 0;
    Node *curr = tree.root;
    if(curr == nullptr) {
        newMessage("Stablo je prazno! ");
        return;
    }
    resetFile();
    while (true) {
        steps++;
        for (int i = 0; i < m - 1; ++i) {
            if (curr->getData()[i].getId() == id) {
                //otvori fajl Customer.txt i pronadji podatke sa tim id
                curr->getData()[i].list.remove(unos);
                return;
            }
        }
        int najdesnje = -1;
        for (int j = m - 2; j > 0; --j) {
            if (curr->getData()[j].getId() != -1) {
                najdesnje = j;
                break;
            }
        }
        najdesnje += 2;
        if (najdesnje == m - 1) {
            najdesnje--;
        }
        if (curr->getElemAt(najdesnje) == nullptr) {
            cout << "Nije pronadjen korisnik sa id " << id << endl;
            cout << "Broj koraka: " << steps << endl;
            writeToCustomerNull(id);
            return;
        } else {
            curr = curr->getElemAt(najdesnje);
        }
    }
}



void mojTest(B_tree& b) {
    Acc a1(10, 10, 10, 10, 10.0);
    Acc a2(20, 20, 20, 20, 20.0);
    Acc a3(30, 30, 30, 30, 30.0);
    Acc a4(40, 40, 40, 40, 40.0);
    Acc a45(45, 45, 45, 45, 45.0);
    Acc a5(50, 50, 50, 50, 50.0);
    Acc a6(60, 60, 60, 60, 60.0);
    Acc a7(70, 70, 70, 70, 70.0);
    Acc a8(80, 80, 80, 80, 80.0);
//    Node n_a2(a2);
//    Node n_a6(a6);
    b.add(a1);
    b.add(a2);
    b.add(a3);
    b.add(a4);
    b.add(a45);
    b.add(a5);
    b.add(a6);
    b.add(a7);
    b.add(a8);

//    B_tree b(n_a2);
//    b.add(a5);
//    b.add(a1);
//    b.add(a45);
//    b.add(a6);
//    b.add(a7);
//    b.add(a8);
//    b.add(a3);
//    b.add(a6);
//    b.add(a8);
//    b.add(a7);
//    b.add(a3);
//    b.add(a45);
//    b.add(a1);
//    b.add(a2);
//    cout << b.root->getElemAt(1)->getElemAt(1)->getData()[0].getId();
//    b.add(a5);

    b.level_order();
    cout << endl;
    b.level_order1();
    cout << endl << endl;
    b.printTree();
}

void menu1() {
    newMessage("Unesite vrednost m: ");
    while (true) {
        int tempM;
        cout << "->";
        cin >> tempM;
        if (tempM < 11 && tempM > 2) {
            m = tempM + 1;
            break;
        }
    }
}

void mainMenu() {
    menu1();
    B_tree b;
    while (true) {
        string options[]{"GLAVNI MENI",
                         "(1) Kreiranje stabla",
                         "(2) Brisanje stabla",
                         "(3) Brisanje svih racuna",
                         "(4) Brisanje jednog racuna",
                         "(5) Ubacivanje racuna",
                         "(6) Pretraga korisnika",
                         "(7) Ispis stabla",
                         "(0) Izlaz"};
        newMenu(41, 9, options);
        int option = 2;
        while (true) {
            cout << "->";
            cin >> option;
            if (option < 8 && option >= 0) {
                break;
            }
        }
        switch (option) {
            case 0:
                newMessage("Uspesan izlazak iz programa.");
                return;
            case 1: {
                makeObjects(b);
                break;
            }
            case 2: {
                delete b.root;
                b = B_tree();
                break;
            }
            case 3:
            {
                newMessage("Unesite id korisnika kojeg zelite da obrisete:  ", 60);
                cout << "->";
                long long idUnos;
                cin >> idUnos;
                deleteUserFromTree(b,idUnos);
                break;
            }
            case 4:
            {
                newMessage("Unesite id korisnika ciji racun zelite da obrisete: ", 60);
                cout << "->";
                long long idKor;
                cin >> idKor;
                newMessage("Unesite id racuna kojeg zelite da obrisete: ", 60);
                cout << "->";
                long long idUnos;
                cin >> idUnos;
                deleteAccFromTree(b,idKor,idUnos);
                newMessage("Uspesno obrisan racun!");
                break;
            }
            case 5:
            {
                addAccount(b);
                break;
            }
            case 6: {
                newMessage("Unesite id korisnika: ");
                cout << "->";
                long long idUnos;
                cin >> idUnos;
                b.searchBTree(idUnos);
                break;
            }
            case 7: {
                //  b.level_order();
//                b.level_order1();
                b.printTree();
                break;
            }
            default:
            {
                break;
            }
        }
    }


}



int main() {
    mainMenu();
}