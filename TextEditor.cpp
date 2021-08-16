#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_BACK 8
#define KEY_ENTER 13

using namespace std;
vector<string> lines;
int selectedLine = -1;

void render() {
    system("CLS");
    for (int i = 0; i < lines.size(); i++) {
        if(i == selectedLine) cout << "\033[1;32m" << lines[i] << "\033[0m" << endl;
        else cout << lines[i] << endl;
    }
}

void loadFile() {
    string line;
    ifstream file("file.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    else cout << "Unable to open file";
}

void mainLoop() {
    int c = 0;
    while (1) {
        c = 0;
        switch ((c = _getch())) {
        case KEY_UP:
            selectedLine--;
            render();
            break;
        case KEY_DOWN:
            selectedLine++;
            render();
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        case KEY_BACK:
            if (lines[selectedLine].size() == 0) { lines.erase(lines.begin() + selectedLine); selectedLine--; }
            else lines[selectedLine].erase(lines[selectedLine].end() - 1);
            render();
            break;
        case KEY_ENTER:
            lines.insert(lines.begin() + selectedLine + 1, "");
            selectedLine++;
            render();
            break;
        default:
            //cout << c; break;
            if (c > 200) break;
            lines[selectedLine] += char(c);
            render();
        }
    }
}

int main(){
    loadFile();
    render();
    mainLoop();
}

