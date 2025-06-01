#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

string symbols="!#$%&()*+-/:;<=>?@[]^_{|}~";
vector<vector<char>> grid;
vector<vector<char>> syms;
vector<int> codes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 13, 14,  17, 18, 19, 22, 27, 28, 29, 34, 35, 36, 40, 41, 42, 45, 49, 88, 90, 93, 94, 95, 99, 100, 190, 196, 202};
vector<vector<int>> colors;
vector<string> buttons= {"Singleplayer", "Multiplayer", "Custom character palette", "Exit"};
int chosen=0;
bool restarted=0;

int n, m;
///To select indexation

void display()
{
    system("CLS");
    cout<<"  ";

    for(int i=0; i<m; i++) cout<<i<<' ';

    cout<<endl;

    for(int i=0; i<n; i++)
    {
        cout<<i<<' ';
        for(int j=0; j<m; j++)
        {
            if(grid[i][j]!='X')
            {
                cout<<"\x1b[38;5;"<<colors[i][j]<<"m"<<grid[i][j]<<"\x1b[0m"<<' ';
            }
            else cout<<"  ";

        }
        cout<<endl;
    }
}

void loading()
{
    Sleep(500);
    vector<vector<vector<bool>>> phases(3);
    vector<vector<bool>> phase(5, vector<bool>(5, 0));

    phase=
    {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    phases[0]=phase;

    phase=
    {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}
    };
    phases[1]=phase;

    phase=
    {
        {0, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {1, 0, 0, 0, 1},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0}
    };

    phases[2]=phase;

    int time=rand()%5+5;

    for(int i=0; i<time; i++)
    {
        for(int j=0; j<3; j++)
        {

            system("CLS");
            Sleep(250);

            vector<vector<bool>> v=phases[j];

            for(int x=0; x<5; x++)
            {
                for(int y=0; y<5; y++)
                {
                    if(v[x][y]==1) cout<<"\033[48;5;1m  \033[0m";
                    else cout<<"  ";
                }
                cout<<endl;
            }



            Sleep(250);
        }

    }


    Sleep(500);
    system("CLS");
}

void gen()
{
    vector<bool> used(symbols.size());

    random_shuffle(codes.begin(), codes.end());

    int chosen=0;

    while(chosen<n*m/2)
    {
        int pos=rand()%26;
        if(used[pos]==0)
        {
            chosen++;
            used[pos]=1;

            int color=codes[codes.size()-1];
            codes.pop_back();

            char c=symbols[pos];
            int br=0;

            while(br<2)
            {
                int x=rand()%n, y=rand()%m;
                if(syms[x][y]=='X')
                {
                    syms[x][y]=c;
                    colors[x][y]=color;
                    br++;
                }
            }
        }
    }
}

void wrong()
{
    cout<<"\x1b[38;5;88mWrong input!\x1b[0m";
    cout<<'\n';
}

pair<bool, int> get_high_score(int n, int m, int score) ///if its a new high score and the highscore
{
    ifstream f(to_string(n)+"x"+to_string(m)+".txt");

    int prev=-1;

    if(f.is_open())
    {
        string s;
        while(getline(f, s));

        f.close();

        prev=stoi(s);
    }

    if(prev>score || prev==-1)
    {
        ofstream f(to_string(n)+"x"+to_string(m)+".txt");
        f<<to_string(score);
        f.close();

        return {1, score};
    }

    return {0, prev};
}

void singleplayer()
{
    int revealed=0, turns=0;

    Sleep(400);
    loading();
    system("CLS");
    if(!restarted)
    {
        cout<<"Palette is: ";
        string counter;
        cin>>counter;
    }
    cin.ignore(symbols.size()+1, '\n');

    cout<<"What are going to be the dimensions of the grid? Their product has to be an even number and needs to be less than or equal to "<<symbols.size()*2<<"\n";
    Sleep(200);
    cin>>n>>m;

    while(1)
    {
        if(n*m%2==0 && n*m<=symbols.size()*2) break;

        system("CLS");
        wrong();
        cout<<"Their product has to be an even number and needs to be less than or equal to "<<symbols.size()*2<<"\n";
        cin>>n>>m;
    }

    grid.resize(n, vector<char>(m, 'X'));
    syms.resize(n, vector<char>(m, 'X'));
    colors.resize(n, vector<int>(m, -1));

    gen();

    while(revealed<n*m/2)
    {
        display();
        cout<<"Choose the first position; (0<=x<n; 0<=y<m and the card needs to be closed): ";

        int x1=-1, y1=-1;
        cin>>x1>>y1;

        while(1)
        {
            display();
            if(x1>=0 && x1<n && y1>=0 && y1<m && grid[x1][y1]=='X') break;


            wrong();
            cout<<"x has to be in the interval [0, "<<n<<") and y has to be in the interval [0, "<<m<<") and the card needs to be closed! Try again: ";
            cin>>x1>>y1;
        }

        grid[x1][y1]=syms[x1][y1];

        display();

        cout<<"Choose the second position; (0<=x<n; 0<=y<m and the card needs to be closed): ";

        int x2=-1, y2=-1;
        cin>>x2>>y2;

        while(1)
        {
            display();
            if(x2>=0 && x2<n && y2>=0 && y2<m && grid[x2][y2]=='X') break;


            wrong();
            cout<<"x has to be in the interval [0, "<<n<<") and y has to be in the interval [0, "<<m<<") and the card needs to be closed! Try again: ";
            cin>>x2>>y2;
        }

        grid[x2][y2]=syms[x2][y2];

        display();

        if(grid[x1][y1]==grid[x2][y2])
        {
            cout<<"It's a match! The cards will be revealed for the rest of the game. Press space to continue\n";
            revealed++;
            while(1)
            {
                if(GetKeyState(VK_SPACE) & 0x8000)
                {
                    Sleep(200);
                    break;
                }
            }
        }
        else
        {
            cout<<"It isn't a match! Press space to continue\n";

            grid[x1][y1]='X';
            grid[x2][y2]='X';

            while(1)
            {
                if(GetKeyState(VK_SPACE) & 0x8000)
                {
                    Sleep(200);
                    break;
                }
            }
        }

        turns++;
    }

    pair<bool, int> p=get_high_score(n, m, turns);

    if(p.first==0)
    {
        cout<<"Congratulations! You won with "<<turns<<" turns, but you weren't able to beat your previous record of "<<p.second<<"! Press R to play again and Q or Escape to exit the game!";
    }
    else
    {
        cout<<"Congratulations! You won with "<<turns<<" turns and got a new high score! Press R to play again and Q or Escape to exit the game!";
    }



    while(1)
    {
        if(GetKeyState('R') & 0x8000)
        {
            Sleep(200);
            restarted=1;
            break;
        }
        if(GetKeyState('Q') & 0x8000) exit(0);
        if(GetKeyState(VK_ESCAPE) & 0x8000) exit(0);
    }
}

void multiplayer()
{
    int revealed=0, turns=0;
    vector<int> rev= {0, 0};

    system("CLS");



    loading();
    vector<string> name= {"", ""};
    Sleep(200);

    system("CLS");
    if(!restarted)
    {
        cout<<"Palette is: ";
        string counter;
        cin>>counter;
    }

    cin.ignore(symbols.size()+1, '\n');

    Sleep(400);
    cout<<"What is Player 1's name? \n";
    getline(cin, name[0]);
    cout<<endl;

    cout<<"What is Player 2's name? \n";
    Sleep(400);
    getline(cin, name[1]);
    cout<<endl;

    cout<<"What are going to be the dimensions of the grid? Their product has to be an even number and needs to be less than or equal "<<symbols.size()*2<<"\n";
    cin>>n>>m;

    while(1)
    {
        if((n*m)%2==0 && n*m<=symbols.size()*2) break;

        system("CLS");
        wrong();
        cout<<"Their product has to be an even number and needs to be less than or equal to "<<symbols.size()*2<<"\n";
        cin>>n>>m;
    }

    grid.resize(n, vector<char>(m, 'X'));
    syms.resize(n, vector<char>(m, 'X'));
    colors.resize(n, vector<int>(m, -1));

    gen();

    while(revealed<n*m/2)
    {
        display();
        cout<<name[turns%2]<<"'s turn! Choose the first position; (0<=x<n; 0<=y<m and the card needs to be closed): ";

        int x1=-1, y1=-1;
        cin>>x1>>y1;

        while(1)
        {
            display();
            if(x1>=0 && x1<n && y1>=0 && y1<m && grid[x1][y1]=='X') break;


            wrong();
            cout<<"x has to be in the interval [0, "<<n<<") and y has to be in the interval [0, "<<m<<") and the card needs to be closed! Try again: ";
            cin>>x1>>y1;
        }

        grid[x1][y1]=syms[x1][y1];

        display();

        cout<<"Choose the second position; (0<=x<n; 0<=y<m and the card needs to be closed): ";

        int x2=-1, y2=-1;
        cin>>x2>>y2;

        while(1)
        {
            display();
            if(x2>=0 && x2<n && y2>=0 && y2<m && grid[x2][y2]=='X') break;


            wrong();
            cout<<"x has to be in the interval [0, "<<n<<") and y has to be in the interval [0, "<<m<<") and the card needs to be closed! Try again: ";
            cin>>x2>>y2;
        }

        grid[x2][y2]=syms[x2][y2];

        display();

        if(grid[x1][y1]==grid[x2][y2])
        {
            cout<<"It's a match! The cards will be revealed for the rest of the game. Press space to continue\n";

            revealed++;
            rev[turns%2]+=2;

            cout<<name[turns%2]<<"'s score is now "<<rev[turns%2]<<", while "<<name[(turns+1)%2]<<" still has "<<rev[(turns+1)%2]<<" points!";

            while(1)
            {
                if(GetKeyState(VK_SPACE) & 0x8000)
                {
                    Sleep(200);
                    break;
                }
            }


        }
        else
        {
            cout<<"It isn't a match! Press space to continue\n";
            cout<<name[turns%2]<<"'s score remains "<<rev[turns%2]<<", while "<<name[(turns+1)%2]<<" still has "<<rev[(turns+1)%2]<<" points!";

            grid[x1][y1]='X';
            grid[x2][y2]='X';

            while(1)
            {
                if(GetKeyState(VK_SPACE) & 0x8000)
                {
                    Sleep(200);
                    break;
                }
            }


        }

        turns++;
    }

    display();

    if(rev[0]>rev[1])
    {
        cout<<name[0]<<" won with "<<rev[0]<<" points and "<<name[1]<<" has "<<rev[1]<<"! To play again press R and to exit press Q or Escape";
    }
    if(rev[1]>rev[0])
    {
        cout<<name[1]<<" won with "<<rev[1]<<" points and "<<name[0]<<" has "<<rev[0]<<"! To play again press R and to exit press Q or Escape";
    }
    if(rev[0]==rev[1])
    {
        cout<<"Its a draw! Both players finished with "<<rev[0]<<" points! To play again press R and to exit press Q or Escape";
    }

    while(1)
    {
        if(GetKeyState('R') & 0x8000)
        {
            Sleep(200);
            restarted=1;
            break;
        }
        if(GetKeyState('Q') & 0x8000) exit(0);
        if(GetKeyState(VK_ESCAPE) & 0x8000) exit(0);
    }
}

void selected_color()
{
    cout<<"\033[1;30;107m";
}

void default_color()
{
    cout<<"\033[0m";
}

void button(string s, bool selected)
{
    if(selected) selected_color();

    string bord=" ";
    for(int i=0; i<s.size(); i++) bord+="-";
    bord+=" ";
    cout<<bord<<'\n';

    cout<<"|"<<s<<"|\n";

    cout<<bord<<'\n';

    default_color();

    cout<<endl;
}

void refresh()
{
    system("CLS");
    ifstream f("name.txt");

    string str;
    while(getline(f, str)) cout<<str<<endl;

    for(int i=0; i<4; i++)
    {
        button(buttons[i], chosen==i);
    }

    f.close();
}

void welcome()
{
    srand(time(0));
    refresh();
    while(1)
    {
        if(GetKeyState(VK_UP) & 0x8000)
        {
            Sleep(200);
            chosen=(chosen-1+4)%4;
            refresh();
        }

        if(GetKeyState(VK_DOWN) & 0x8000)
        {
            Sleep(200);
            chosen=(chosen+1)%4;
            refresh();
        }

        if(GetKeyState(VK_RETURN) & 0x8000)
        {
            if(chosen==3)
            {
                exit(0);
            }

            if(chosen==2)
            {
                system("CLS");
                cout<<"Current palette: "<<symbols<<"\n";
                cout<<"Enter the palette you would like to use. If it contains the letter X it will be removed. If it contains a space, everything after the space will be wiped. If there are repeating characters, there will be only one copy. If the size after these changes is over 32, it will be shortened. You can't change the palette after you have started the game.\n";
                string s;
                cin>>s;

                vector<bool> used(257);
                string t="";

                int si=s.size();
                int lim=min(32, si);

                for(int i=0; i<lim; i++)
                {
                    if(s[i]!='X' && s[i]!=' ' && !used[s[i]-0]) t+=s[i];

                    used[s[i]-0]=1;
                }

                symbols=t;

                Sleep(200);

                refresh();
            }

            if(chosen==0)
            {
                while(1) singleplayer();
            }

            if(chosen==1)
            {
                while(1) multiplayer();
            }


        }
    }
}

int main()
{
    welcome();
}
