#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <Windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_BACK 8
#define KEY_ENTER 13

using namespace std;
vector<string> lines;

int selectedLine = 0;
int offset = 0;
int maxLines = 29;

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void render(bool back = false) {
    for (int i = 0; i < 30; i++) cout << "" << endl;
    int i = offset; int y = 0;
    for (int j = 0; j < maxLines; j++) {
        setCursorPosition(0, y);
        if(i == selectedLine + offset) cout << "\033[1;32m" << lines[i] << "\033[0m";
        else cout << lines[i];
        if (back) {
            if (i - 1 > -1) for (auto x : lines[i - 1]) cout << " ";
        }
        else {
            if ( + 1 < lines.size()) for (auto x : lines[i + 1]) cout << " ";
        }
        i++; y++;
    }
}

void enter() {
    lines.insert(lines.begin() + selectedLine + offset + 1, "");
    selectedLine++;
    render();
}

void updateLine(bool back = false, int updateOffset = 0) {
    setCursorPosition(0, selectedLine + offset + updateOffset);
    if (updateOffset == 0) {
        if (back) cout << "\033[1;32m" << lines[selectedLine + offset + updateOffset] + " " << "\033[0m";
        else cout << "\033[1;32m" << lines[selectedLine + offset + updateOffset] << "\033[0m";
    }
    else cout << lines[selectedLine + offset + updateOffset];
    //render();
}

void loadFile() {
    string line;
    ifstream file("TextEditor.cpp");
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
            updateLine(false, 1);
            updateLine();
            break;
        case KEY_DOWN:
            selectedLine++;
            updateLine(false, -1);
            updateLine();
            break;
        case KEY_LEFT:
            break;
        case KEY_RIGHT:
            break;
        case KEY_BACK:
            if (lines[selectedLine + offset].size() == 0) { lines.erase(lines.begin() + selectedLine + offset); selectedLine--; render(); }
            else { lines[selectedLine + offset].erase(lines[selectedLine + offset].end() - 1); updateLine(true); }
            break;
        case KEY_ENTER:
            enter();
            break;
        default:
            //cout << c; break;
            if (c > 200) break;
            lines[selectedLine + offset] += char(c);
            updateLine();
        }
    }
}

void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    loadFile();
    render();
    hideCursor();
    mainLoop();
}
