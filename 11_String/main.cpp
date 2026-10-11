#include <iostream>
#include <string>
#include <string_view>

void print_log(std::string_view log_result) {
    std::cout << log_result << '\n';
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    
    std::string dummy;
    std::getline(std::cin, dummy);

    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(std::cin, line);

        size_t first_pipe = line.find('|');
        size_t second_pipe = line.find('|', first_pipe + 1);

        std::string name = line.substr(0, first_pipe);
        std::string level_str = line.substr(first_pipe + 1, second_pipe - first_pipe - 1);
        std::string message = line.substr(second_pipe + 1);

        int level = std::stoi(level_str);

        while (!message.empty() && message.front() == ' ') 
        {
            message.erase(0, 1);
        }
        
        while (!message.empty() && message.back() == ' ') 
        {
            message.erase(message.size() - 1, 1);
        }

        if (message.empty()) {
            message = "(empty)";
        } else {
            size_t pos = message.find("Java");
            while (pos != std::string::npos) {
                message.replace(pos, 4, "C++");
                pos = message.find("Java", pos + 3);
            }

            if (message.back() != '!') {
                message += '!';
            }
        }

        std::string result = "[Lv." + std::to_string(level) + "] " + name + ": " + message;

        print_log(result);
    }

    return 0;
}