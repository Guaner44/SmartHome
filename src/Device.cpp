#include "Device.h"

Device::Device(const std::string& id, const std::string& name, const std::string& room)
    : id_(id), name_(name), room_(room), on_(false) {
    // 初始化列表完成成员初始化：新设备默认关闭，编号/名称/房间不可能处于未定义状态
}

const std::string& Device::id() const { return id_; }

const std::string& Device::name() const { return name_; }

const std::string& Device::room() const { return room_; }

bool Device::isOn() const { return on_; }

const char* Device::statusText() const { return on_ ? "开启" : "关闭"; }

void Device::turnOn() { on_ = true; }

void Device::turnOff() { on_ = false; }

std::string Device::toString() const {
    std::string text;
    text += "设备编号：" + id_ + "\n";
    text += "设备名称：" + name_ + "\n";
    text += "所在房间：" + room_ + "\n";
    text += "开关状态：" + std::string(statusText()) + "\n";
    return text;
}
