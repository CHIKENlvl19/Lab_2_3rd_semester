#include "../Task_2/mySet.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 5) 
    {
        cerr << "Usage: ./main --file file.data --query 'cmd'\n";
        return 1;
    }

    string filename, query;
    for(int i = 1; i < argc; ++i) 
    {
        string arg = argv[i];
        if(arg == "--file" && i+1 < argc)
        {
            filename = argv[++i];
        }
        else if(arg == "--query" && i+1 < argc)
        {
            for(int j = i + 1; j < argc; j++)
            {
                if(!query.empty())
                {
                    query += " ";
                }
                query += argv[j];
            }
            break;
        }
    }

    if(filename.empty() || query.empty()) {
        cerr << "Error: --file and --query are required\n";
        return 1;
    }

    stringstream ss(query);
    string cmdStr;
    ss >> cmdStr;
    Command cmd = getCommand(cmdStr);

    mySet<int> st;
    st.loadFromFile(filename);

    switch(cmd) {
        case Command::SETADD: {
            int value;
            ss >> value;

            st.insert(value);
            st.saveToFile(filename);
            break;
        }

        case Command::SETDEL: {
            int value;
            ss >> value;

            st.remove(value);
            st.saveToFile(filename);
            break;
        }

        case Command::SET_AT: {
            int value;
            ss >> value;

            cout << (st.contains(value) ? "yes\n" : "no\n");
            break;
        }

        case Command::SETPRINT: {
            st.print();
            break;
        }

        default:
            cerr << "Unknown command!" << endl;
    }
}