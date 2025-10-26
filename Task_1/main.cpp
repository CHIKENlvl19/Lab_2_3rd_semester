#include "myStack.h"

using namespace std;

int priority(char op) {
    switch(op)
    {
        case '^': return 3;
        case '*': return 2;
        case '/': return 2;
        case '+': return 1;
        case '-': return 1;

        default: return 0;
    }
}

string infixToPostfix(const string& expression) {
    Stack<char> stack;
    string result;

    for(char c : expression)
    {
        if(isalpha(c) || isdigit(c))
        {
            result += c;
        }
        else if(c == '(')
        {
            stack.push(c);
        }
        else if(c == ')')
        {
            while(stack.getSize() && stack.peek() != '(')
            {
                result += stack.peek();
                stack.pop();
            }
            if(stack.getSize() && stack.peek() == '(')
            {
                stack.pop();
            }
        }
        else
        {
            while(stack.getSize() && priority(stack.peek()) >= priority(c))
            {
                result += stack.peek();
                stack.pop();
            }
            stack.push(c);
        }
    }

    while(stack.getSize())
    {
        result += stack.peek();
        stack.pop();
    }

    return result;
}

int main() {

    cout << "Введите выражение в формате А+В*С: ";
    string expression;
    cin >> expression;

    string postfix = infixToPostfix(expression);
    cout << "Постфиксная форма записи выражения: " << postfix;

    return 0;
}