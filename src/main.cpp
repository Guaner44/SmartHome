// 智能家居设备控制模拟系统 —— Lab01：智能设备基本类
// 本文件只负责"界面与流程"：打印菜单、收集输入、把操作结果翻译成中文提示、
// 调用 Device / DeviceManager 完成实际工作。业务规则不写在这里。

#include <iostream>
#include <string>

#include "ConsoleInput.h"
#include "Device.h"
#include "DeviceManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace {

// Windows 控制台默认是 GBK，源码与提示是 UTF-8，这里统一切到 UTF-8 才能正常显示中文。
void enableUtf8Console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void printMenu(const DeviceManager& manager) {
    std::cout << "\n========== 智能家居设备控制模拟系统（Lab01）==========\n";
    std::cout << " 当前设备数：" << manager.size() << "\n";
    std::cout << "  1. 添加设备\n";
    std::cout << "  2. 显示全部设备\n";
    std::cout << "  3. 查看单个设备\n";
    std::cout << "  4. 开启设备\n";
    std::cout << "  5. 关闭设备\n";
    std::cout << "  0. 退出\n";
}

// 只显示一台设备的完整信息
void printDevice(const Device& device) {
    std::cout << device.toString();
}

// 把操作结果代码翻译成可以说明原因的提示
std::string failureReason(Result result, const std::string& id) {
    switch (result) {
        case Result::EmptyId:
            return "设备编号不能为空。";
        case Result::DuplicateId:
            return "设备编号 " + id + " 已存在，不能重复创建。";
        case Result::EmptyName:
            return "设备名称不能为空。";
        case Result::NotFound:
            return "设备编号 " + id + " 不存在。";
        case Result::Ok:
            break;
    }
    return "";
}

// 1. 添加设备
void handleAddDevice(DeviceManager& manager) {
    std::string id;
    std::string name;
    std::string room;
    if (!ConsoleInput::readLine("请输入设备编号（例如 D01）：", id) ||
        !ConsoleInput::readLine("请输入设备名称（例如 客厅主灯）：", name) ||
        !ConsoleInput::readLine("请输入所在房间（直接回车表示“未分配”）：", room)) {
        std::cout << "\n输入结束，未完成的创建已取消。\n";
        return;
    }
    if (room.empty()) {
        room = "未分配";
    }

    const Result result = manager.addDevice(id, name, room);
    if (result != Result::Ok) {
        std::cout << "创建失败：" << failureReason(result, id) << "\n";
        std::cout << "当前设备总数仍为 " << manager.size() << " 台。\n";
        return;
    }
    std::cout << "创建成功，设备信息如下：\n";
    printDevice(*manager.findById(id));
}

// 2. 显示全部设备
void handleListDevices(const DeviceManager& manager) {
    manager.printAll(std::cout);
}

// 3. 查看单个设备
void handleShowDevice(DeviceManager& manager) {
    std::string id;
    if (!ConsoleInput::readLine("请输入要查看的设备编号：", id)) {
        std::cout << "\n输入结束。\n";
        return;
    }
    const Device* device = manager.findById(id);
    if (device == nullptr) {
        std::cout << "查询失败：" << failureReason(Result::NotFound, id) << "\n";
        return;
    }
    printDevice(*device);
}

// 4 / 5. 开启或关闭设备：两个菜单项共用同一段逻辑，只是目标状态不同
void handleSwitch(DeviceManager& manager, bool turnOn) {
    const std::string action = turnOn ? "开启" : "关闭";
    std::string id;
    if (!ConsoleInput::readLine("请输入要" + action + "的设备编号：", id)) {
        std::cout << "\n输入结束。\n";
        return;
    }

    const Result result = manager.setPower(id, turnOn);
    if (result != Result::Ok) {
        std::cout << action << "失败：" << failureReason(result, id)
                  << "其他设备的状态没有改变。\n";
        return;
    }
    const Device* device = manager.findById(id);
    std::cout << action << "成功：" << device->id() << " " << device->name()
              << " 当前状态：" << device->statusText() << "\n";
}

}  // namespace

int main() {
    enableUtf8Console();

    std::cout << "欢迎使用智能家居设备控制模拟系统（Lab01：智能设备基本类）\n";

    DeviceManager manager;
    bool running = true;
    while (running) {
        printMenu(manager);

        int choice = -1;
        if (!ConsoleInput::readMenuNumber("请输入操作编号：", choice)) {
            if (std::cin.eof()) {
                std::cout << "\n输入结束，程序退出。\n";
                break;
            }
            std::cout << "输入无效：请输入菜单中列出的操作编号（0-5），本次操作已取消。\n";
            continue;  // 回到菜单，程序不退出、数据不改变
        }

        switch (choice) {
            case 0:
                running = false;
                break;
            case 1:
                handleAddDevice(manager);
                break;
            case 2:
                handleListDevices(manager);
                break;
            case 3:
                handleShowDevice(manager);
                break;
            case 4:
                handleSwitch(manager, true);
                break;
            case 5:
                handleSwitch(manager, false);
                break;
            default:
                std::cout << "菜单项 " << choice << " 不存在，已返回主菜单。\n";
                break;
        }
    }

    std::cout << "感谢使用，再见。\n";
    return 0;
}
