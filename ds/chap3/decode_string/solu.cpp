#include <string>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
        public:
                string decodeString(string s) {
                        if (!isValid(s)) return "";

                        stack<string> _stack;
                        stack<int> _nstack;

                        string result;
                        string tmp;
                        int n=0;
                        for (int i=0; i<s.size(); i++) {

                                if ( isNum(s[i]) ) {
                                        n = 0;
                                        for(; isNum(s[i]); i++ ) {
                                                n = n*10 + s[i] - '0'; 
                                        }
                                }

                                if (s[i] == '[') {
                                        tmp="";
                                        _stack.push(tmp);
                                        _nstack.push(n);
                                } else if (s[i] == ']') {
                                        n = _nstack.top(); 
                                        tmp="";
                                        for (; n>0; n--) {
                                                tmp += _stack.top();  // cat n times
                                        }
                                        _stack.pop();
                                        _nstack.pop();
                                        if ( ! _stack.empty() ) {
                                                _stack.top() += tmp;
                                        }else {
                                                result += tmp;
                                        }
                                } else {
                                        if ( ! _stack.empty() ) {  // collect chars
                                                _stack.top() += s[i];
                                        } else {
                                                result += s[i];  // deal with char directly
                                        }

                                }
                        }

                        return result;
                }

        private:

                //only check the following rules:
                // 1) the number must be followed by '['
                // 2) the '[' and ']' must be matched.
                bool isValid(string& s) {
                        stack<char> _stack;
                        for (int i=0; i<s.size(); i++) {
                                if ( isNum(s[i]) ) {
                                        for(; isNum(s[i]); i++);
                                        if (s[i] != '[') {
                                                return false;
                                        } 
                                        _stack.push('[');
                                        continue;
                                } else if (s[i] == ']' ) {
                                        if ( _stack.top() != '[' ) return false;
                                        _stack.pop();
                                }
                        }

                        return (_stack.size() == 0);
                }

                bool isNum(char ch) {
                        return (ch>='0' && ch<='9');
                }
};

int main()
{
        Solution solu;
        cout << solu.decodeString(string("3[a]2[bc]")) << endl;  // 输出 aaabcbc
        cout << solu.decodeString(string("3[a2[c]]")) << endl;  // 输出 accaccacc
        cout << solu.decodeString(string("2[abc]3[cd]ef")) << endl;  // 输出 abcabccdcdcdef
}
