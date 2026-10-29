#include "ConsoleInput.h"

#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

namespace {

// 判断标准输入是否来自键盘。来自键盘时控制台会自动回显用户输入；
// 当输入被重定向为文件（如测试用例）时不会回显，需要由程序补上，
// 这样"运行记录"读起来和真实操作过程一致，便于提交和复查。
bool stdinIsInteractive() {
#ifdef _WIN32
    return _isatty(_fileno(stdin)) != 0;
#else
    return isatty(STDIN_FILENO) != 0;
#endif
}

}  // namespace

namespace ConsoleInput {

std::string trim(const std::string& text) {
    std::size_t begin = 0;
    while (begin < text.size() && std::isspace(static_cast<unsigned char>(text[begin])) != 0) {
        ++begin;
    }
    std::size_t end = text.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(text[end - 1])) != 0) {
        --end;
    }
    return text.substr(begin, end - begin);
}

bool readLine(const std::string& prompt, std::string& out) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::string line;
    if (!std::getline(std::cin, line)) {
        return false;  // 输入结束（例如测试用的输入文件已读完）
    }
    if (!stdinIsInteractive()) {
        std::cout << line << "\n";  // 补回显，让运行记录看到实际输入
    }
    out = trim(line);
    return true;
}

bool readMenuNumber(const std::string& prompt, int& out) {
    std::string line;
    if (!readLine(prompt, line)) {
        return false;
    }
    if (line.empty() || line.size() > 3) {
        return false;  // 空行或明显过长的输入都不是合法编号
    }
    int value = 0;
    for (char ch : line) {
        if (std::isdigit(static_cast<unsigned char>(ch)) == 0) {
            return false;  // 混有字母、符号、负数等一律判为非法
        }
        value = value * 10 + (ch - '0');
    }
    out = value;
    return true;
}

}  // namespace ConsoleInput
