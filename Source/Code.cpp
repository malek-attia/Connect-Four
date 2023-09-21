#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <conio.h>


using namespace std;

//Global Variables
int row, col;
int scoreX, scoreO;
bool running_game=0;
bool loaded_game=0;
int moves=0;
vector<vector<char>> arr;
unordered_set<int> not_full;


int count_4(char);
void print_board();
void run_game();
void high_score(int);
bool sort_records(pair<string,int> &a, pair<string,int> &b);
void menu();
void print_dashboard();
void save();
void load();



int main()
{
    menu();

    return 0;
}


void menu(){
    int choice = -1;
    while(choice != 6){
        system("cls");
        cout<<"Enter your choice 1 - 6:\n"
            <<"1.Start a New Game\n"
            <<"2.Save This Game\n"
            <<"3.Load a Game\n"
            <<"4.Back To The Game\n"
            <<"5.Print Dash Board\n"
            <<"6.Exit\n";
        cin >> choice;
        if(choice < 1 || choice > 6){
            cout << "Invalid Input Press Enter to try again\n";
            choice = -1;
            _getch();
        }
        else if(choice==1){
            running_game = loaded_game = moves = 0;
            run_game();
        }
        else if(choice==2){
            if(!arr.size()){
                cout << "There is no game to be saved yet!\n"
                    << "Press Enter To Continue...\n";
                _getch();
                continue;
            }
            save();
        }
        else if(choice==3){
            load();
        }
        else if(choice==4){
            if(!running_game){
                cout << "There is no Games opened at the moment!\n"
                    <<"you can play a New Game ;)\n"
                    <<"Press Enter to Continue...";
                _getch();
            }
            else{
                return;
            }
        }
        else if(choice==5){
            print_dashboard();
        }
        else{
            system("cls");
            cout << "Good Bye :)\n";
            exit(0);
        }
    }
}


void print_board(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");
    for (int j = row-1; j >= 0; j--){
        for (int i = 0; i < col; i++){
            cout <<" ";
            if(arr[i][j]=='x')
                SetConsoleTextAttribute(hConsole, 12);//Red
            else if(arr[i][j]=='o')
                SetConsoleTextAttribute(hConsole, 14);//Yellow
            cout << arr[i][j];
            SetConsoleTextAttribute(hConsole, 7);//Default
            cout <<" |";
        }
        cout<<"\n";
    }
    for(int i=0;i<col;i++)
        cout <<" "<<i+1<<" -";
    cout <<"\n";
}

int count_4(char c){
    int cnt = 0;
    //Count columns (Horizontal/rotated Columns)
    for(int i=0;i<col;i++){
        int tmp=0;
        for(int j=0;j<row;j++){
            if(arr[i][j]==c) tmp++;
            else tmp=0;
            if(tmp==4){
                cnt++;
                tmp=0;
            }
        }
    }
    //Count rows
    for(int i=0;i<row;i++){
        int tmp=0;
        for(int j=0;j<col;j++){
            if(arr[j][i]==c) tmp++;
            else tmp=0;
            if(tmp==4){
                cnt++;
                tmp=0;
            }
        }
    }
    //Count Diagonals from right down to up left <^
    int i=3;
    while(i < col+row-4){
        int j;
        if(i < col)j = 0;
        else j = i%(col-1);
        int save = i;
        int tmp=0;
        if(i >= col) i = col-1;
        while(i >= 0 && j < row){
            if(arr[i--][j++]==c) tmp++;
            else tmp=0;
            if(tmp==4){
                cnt++;
                tmp=0;
            }
        }
        i = save;
        i++;
    }
    //Count Diagonals from left down to up right ^>
    int j = row-4;
    while(j >= 4-col){
        int i;
        if(j >= 0)i = 0;
        else i = -1*j;
        int save = j;
        int tmp=0;
        if(j < 0) j = 0;
        while(i < col && j < row){
            if(arr[i++][j++]==c) tmp++;
            else tmp=0;
            if(tmp==4){
                cnt++;
                tmp=0;
            }
        }
        j = save;
        j--;
    }

    return cnt;
}

void run_game(){
    srand(time(0));
    if(!loaded_game){
        row = -1;
        while(row == -1){
            system("cls");
            cout << "Enter no. of rows > 3 and no. of columns > 3\n"
                <<"(Default 6 x 7): ";
            cin >> row >> col;
            if(row < 4 || col < 4){
                cout<<"Invalid Input Press Enter to try again\n";
                row=-1;
                _getch();
            }
        }
        arr.clear();
        arr.resize(col, vector<char>(row+1, '.'));
        for(int i=0; i<col; i++){
        //Reset Counters (The last element in every column)
            arr[i][row]=0;
        //Adding Empty Columns To an Unordered_set for randomized choice  
            not_full.insert(i);
        }
    }
    
    int twoPlayers=-1;
    while(twoPlayers==-1){
    cout << "For 2 players mode enter 2\n"
         << "For 1 player  mode enter 1: ";
    cin >> twoPlayers;
    if(twoPlayers!=1 && twoPlayers!=2){
        cout<<"Invalid Input try again\n";
        twoPlayers=-1;
        }
    }
    twoPlayers--;
     for (int i = moves; i < row*col; i++)
    {
        //Switching Turns
        char player = ((i+1)%2)?'x':'o';
        
        //Counting fours
        scoreX = count_4('x');
        scoreO = count_4('o');
        print_board();
        cout<< "player X Score: "<<scoreX<<"\n"
            << "player O Score: "<<scoreO<<"\n"
            << "To Exit to Menu Enter -1\n"
            << "player "<<player<<" turn, Enter a Column: ";
        
        int c;
        if(twoPlayers || player=='x'){
            cin >> c;
            c--;
        }
        //random choice
        else{
            // Generate a random iterator
            auto randIt = next(not_full.begin(), rand()%not_full.size());
            c = *randIt;
        }
        if(c==-2){
            running_game=1;
            menu();
            i--;continue;
        }

        //Cheking Input validity
        if(c < 0 || c > col-1){
            cout<<"Invalid Input Press Enter to try again\n";
            _getch();
            i--;continue;
        }

        //Cheking space validity
        if(arr[c][row]==row){
            cout<<"Full Column Press Enter to try again\n";
            _getch();
            i--;continue;
        }

        arr[c][arr[c][row]]=player;
        arr[c][row]++;
        if(arr[c][row]==row) not_full.erase(c);
        
    }
    running_game = loaded_game = moves = 0;
    print_board();
    cout << "player X Score: "<<scoreX<<"\n";
    cout << "player O Score: "<<scoreO<<"\n";
    arr.clear();
    if(scoreX!=scoreO){
        cout << "player "<<(scoreX>scoreO? "X":"O")<<" Won!!\n";
        high_score((scoreX>scoreO? scoreX:scoreO));
    }else{
        cout << "Draw\n";
        cout<<"Press Enter to Continue...\n";
        _getch();
    }
}

bool sort_records(pair<string,int> &a, pair<string,int> &b){
    if(a.second != b.second)
        return a.second > b.second;
    return a.first < b.first;
}

void high_score(int score){
    cout << "Enter your Name: ";
    string name;
    cin.ignore();
    getline(cin, name);
    auto status = ios::in | ios::out | ios::app;
    fstream scores("High Scores.txt", status);
    vector<pair<string, int>> users;
    string line;
    bool found = 0;
    int i=0;
    while(getline(scores, line) && i<10){
        pair<string, int> user;
        user.first = line;
        scores >> user.second;
        if(name==line){
            found = 1;
            if(user.second < score) user.second = score;
        }
        scores.ignore(numeric_limits<streamsize>::max(), '\n');
        users.push_back(user);
        i++;
    }
    if(!found){
        if(i<10)
            users.push_back(make_pair(name, score));
        else{
            if(score != users[9].second){
                if(score > users[9].second)
                    {users[9].first=name; users[9].second=score;}
            }else{
                if(name < users[9].first)
                    users[9].first=name;
            }
        }
    }
    scores.close();
    sort(users.begin(), users.end(), sort_records);
    status = ios::in | ios::out | ios::trunc;
    scores.open("High Scores.txt", status);
    for(auto user : users){
        scores << user.first <<"\n"<<user.second<<"\n";
    }
}

void print_dashboard(){
    auto status = ios::in | ios::app;
    ifstream scores("High Scores.txt", status);
    string line, score;
    cout << "\tTop 10 Players\n";
    int i = 1;
    while(getline(scores, line)){
        scores >> score;
        cout << i << ". Name: " << line <<"\t"
             << "Score: "<< score<<"\n";
        scores.ignore(numeric_limits<streamsize>::max(), '\n');
        i++;
    }
    scores.close();
    cout << "Press Enter to continue...";
    _getch();
}

void save(){
    // Get the current time and format it as a string
    auto now = chrono::system_clock::now();
    time_t currentTime = chrono::system_clock::to_time_t(now);
    string formattedTime = ctime(&currentTime);
    ofstream save("Saved.txt", ios::out | ios::app);
    save << formattedTime;
    save <<row<<"\n"<<col<<"\n";
    for(int i=0;i<col;i++)
        for(int j=0;j<row+1;j++)
            save << arr[i][j];
    save << "\n";
    save.close();
    cout << "Saved!\n"
        <<"Press Enter to Continue...";
    _getch();
}

void load(){
    ifstream load("Saved.txt", ios::in | ios::app);
    string history, board;
    int new_row, new_col;
    vector<tuple<string, int, int, string>> saved;
    while(getline(load, history)){
        load >> new_row >> new_col;
        load >> board;
        saved.push_back(make_tuple(history, new_row, new_col, board));
        load.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    int choice = -1;
    while(choice==-1){
        system("cls");
        cout << "\tSaved Games:\n";
        for(int i=0; i<saved.size(); i++){
            cout <<i+1<<") "<<get<0>(saved[i])<<" "
                <<get<1>(saved[i])<<" x "<<get<2>(saved[i])<<"\n";
        }
        cout << "Enter Game No. To Load: ";
        cin >> choice;
        if(choice<1 || choice > saved.size()){
            cout << "Invalid Input Press Enter to try again\n";
            _getch();
            choice = -1;
            continue;
        }
        choice--;
    }
    row = get<1>(saved[choice]);
    col = get<2>(saved[choice]);
    not_full.clear();
    arr.clear();
    arr.resize(col, vector<char>(row+1, '.'));
    int it = 0;
    moves = 0;
    for(int i=0;i<col;i++){
        for(int j=0;j<row+1;j++){
            arr[i][j] = get<3>(saved[choice])[it++];
            if(j==row-1)
                moves += get<3>(saved[choice])[it];
            if(get<3>(saved[choice])[it]<row)
                not_full.insert(i);
        }
    }
    cout << "Loaded Successfully!\n"
        <<"Press Enter to Play...\n";
    loaded_game = 1;
    _getch();
    run_game();
}

