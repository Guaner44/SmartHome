#ifndef SMART_HOME_CONSOLE_INPUT_H
#define SMART_HOME_CONSOLE_INPUT_H

#include <string>

// 控制台输入的公共工具：统一负责"读一行、去空白、把文本转成菜单编号"。
// 集中在一处实现，避免每个菜单分支各写一套 std::cin 逻辑，
// 也保证非法输入不会让 std::cin 进入错误状态而影响后续读取。
namespace ConsoleInput {

// 去掉首尾空白（空格、制表符、回车）
std::string trim(const std::string& text);

// 提示并读取一整行，结果已去掉首尾空白。
// 返回 false 表示输入流已结束（EOF），调用方应结束程序而不是继续循环。
bool readLine(const std::string& prompt, std::string& out);

// 读取菜单编号：只有"纯数字"才算成功并写入 out。
// 返回 false 时 out 不变；调用方用 std::cin.eof() 区分"输入结束"和"输入非法"。
bool readMenuNumber(const std::string& prompt, int& out);

}  // namespace ConsoleInput

#endif  // SMART_HOME_CONSOLE_INPUT_H
