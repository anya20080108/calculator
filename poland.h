#include <cmath>
#include <string>

using namespace std;

struct Stack{
    double number;
    char znak;
    Stack* next;
};
Stack* top1;
Stack* top2;

void push(Stack*& t, double long number, char ch){
    Stack* p = (Stack*)malloc(sizeof(Stack));
    (*p).number = number;
    (*p).znak = ch;
    (*p).next = t;
    t = p;
}

Stack pop(Stack*& t){
    Stack temp = (*t);
    t = (*t).next;
    return temp;
}

bool apply(Stack*& t, char m){
    if (t == nullptr){
        return false;

    }
    double a1 = (pop(t)).number;
    if (m == 'A' || m == 'B' || m == 'C' || m == 'D' || m == 'E' || m == 'M') {

        if (m == 'A') {
            push(t, sin(a1), '#');
        }
        if (m == 'B') {
            push(t, cos(a1), '#');
        }
        if (m == 'C') {
            push(t, tan(a1), '#');
        }
        if (m == 'D') {
            if (a1 < 0) {
                return false;

            }
            else {
                push(t, sqrt(a1), '#');
            }
        }
        if (m == 'E') {
            if (a1 <= 0) {
                return false;

            }
            else{
                push(t, log(a1), '#');
            }
        }
        if (m == 'M') {
            push(t, abs(a1), '#');
        }
    }
    else {
        if (t == nullptr) {
            return false;

        }
        double a2 = (pop(t)).number;
        if (m == '+') {
            push(t, a1 + a2, '#');
        }
        if (m == '-') {
            push(t, a2 - a1, '#');
        }
        if (m == '*') {
            push(t, a1 * a2, '#');
        }
        if (m == '/') {
            if (a1 == 0){
                return false;

            }
            else{
                push(t, a2 / a1, '#');
            }
        }
        if (m == '^') {
            push(t, pow(a2, a1), '#');
        }

    }
    return true;
}
int prior(char m){
    if (m == '+' or m == '-') {
        return 1;
    }
    if (m == '*' or m == '/') {
        return 2;
    }
    if (m == '(') {
        return 0;
    }
    if (m == '^') {
        return 3;
    }
    if (m == 'A' || m == 'B' || m == 'C' || m == 'D' || m == 'E' || m == 'M'){
        return 4;
    }
    return -1;
}

void replace_all(string& s, string ss, string ch){
    int pos = s.find(ss);
    while (pos != string::npos){
        s.replace(pos, ss.length(), ch);
        pos = s.find(ss);
    }
}

int err (string s1) {
    int balance = 0;
    for (int i = 1; i <= s1.size(); i++){
        if (s1[i - 1] == '('){
            balance++;
        }
        if (s1[i - 1] == ')'){
            balance--;
        }
        if (s1[i] == '/' && s1[i + 1] == 0){
            return 1;
        }
        if ((prior(s1[i - 1]) > 0 && prior(s1[i]) < 4) && (prior(s1[i]) > 0 && prior(s1[i]) < 4)) {
            return 1;
        }
        if (prior(s1[i - 1]) == 0 && s1[i] == ')') {
            return 1;
        }
    }
    if (balance != 0) {
        return 1;
    }
}
bool calculate (string s, double long& ans) {
    top1 = nullptr;
    top2 = nullptr;

    if (s[0] == '-') {
        s.insert(0, "0");
    }

    for (int i = 1; i <= s.size(); i++) {
        if (s[i - 1] == 's' && s[i] == 'i') {
            replace_all(s, "sin", "A");
        }
        if (s[i - 1] == 's' && s[i] == 'q') {
            replace_all(s, "sqrt", "D");
        }
        if (s[i - 1] == 't') {
            replace_all(s, "tg", "C");
        }
        if (s[i - 1] == 'c') {
            replace_all(s, "cos", "B");
        }
        if (s[i - 1] == 'l'){
            replace_all(s, "ln", "E");
        }
        if (s[i - 1] == 'a') {
            replace_all(s, "abs", "M");
        }
    }

    if (err(s) == 1){
        return false;
    }

    for (int i = 1; i <= s.size(); i++) {
        if (s[i - 1] == '(' && s[i] == '-') {
            s.insert(i, "0");
        }
    }

    for (int i = 0; i <= s.size(); i++) {
        double long d = 0;
        double long dr = 0;
        long long k = 0;

        if (s[i] >= '0' && s[i] <= '9') {
            while (s[i] >= '0' && s[i] <= '9') {
                d = d * 10 + (s[i] - '0');
                i++;
            }
            push (top1, d, '#');
        }
        if (s[i] =='.'){
            i++;
            while (s[i] >= '0' && s[i] <= '9') {
                dr = dr * 10 + (s[i] - '0');
                k++;
                i++;
            }
            pop (top1);
            push(top1, d + (dr / (pow(10, k))), '#');
        }
        if (s[i] == '(') {
            push(top2, 0.0, s[i]);
        }
        else if (s[i] == ')') {
            while ((*top2).znak != '(') {
                if (apply(top1, pop(top2).znak) == false) {
                    return false;
                }

            }

            pop(top2);
        }

        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == 'A' || s[i] == 'B' || s[i] == 'C' || s[i] == 'D' || s[i] == 'E' || s[i] == 'M') {
            while ((top2 != nullptr) && (prior(s[i]) <= prior((*top2).znak))){
                if (apply(top1, pop(top2).znak) == false) {
                    return false;
                }
            }
            push(top2, 0.0, s[i]);
        }
        else if (s[i] >= 'a' && s[i] <= 'z'){
            return false;
        }
    }

    while (top2 != nullptr){
        if (apply(top1, pop(top2).znak) == false) {
            return false;
        }
    }
    ans = top1->number;
    return true;
}
