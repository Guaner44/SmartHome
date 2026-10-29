#include "DeviceManager.h"

#include <ostream>
#include <string>

namespace {

// 控制台里一个汉字的显示宽度等于 2 列，而它在 std::string 中占 3 个字节，
// 所以按 UTF-8 字节数补齐会导致表格错位，这里按"显示列数"计算。
std::size_t displayWidth(const std::string& text) {
    std::size_t width = 0;
    for (std::size_t i = 0; i < text.size(); ++i) {
        const unsigned char byte = static_cast<unsigned char>(text[i]);
        if ((byte & 0xC0) == 0x80) {
            continue;  // UTF-8 续字节，属于上一个字符，不重复计数
        }
        width += (byte < 0x80) ? 1 : 2;
    }
    return width;
}

std::string padRight(const std::string& text, std::size_t width) {
    std::string cell = text;
    const std::size_t current = displayWidth(text);
    if (current < width) {
        cell.append(width - current, ' ');
    }
    return cell;
}

constexpr std::size_t kIdWidth = 8;
constexpr std::size_t kNameWidth = 18;
constexpr std::size_t kRoomWidth = 12;

}  // namespace

Result DeviceManager::addDevice(const std::string& id, const std::string& name,
                                const std::string& room) {
    if (id.empty()) {
        return Result::EmptyId;
    }
    if (findById(id) != nullptr) {
        return Result::DuplicateId;
    }
    if (name.empty()) {
        return Result::EmptyName;
    }
    devices_.push_back(Device(id, name, room));
    return Result::Ok;
}

Result DeviceManager::setPower(const std::string& id, bool on) {
    if (id.empty()) {
        return Result::EmptyId;
    }
    Device* device = findById(id);
    if (device == nullptr) {
        return Result::NotFound;
    }
    if (on) {
        device->turnOn();
    } else {
        device->turnOff();
    }
    return Result::Ok;
}

Device* DeviceManager::findById(const std::string& id) {
    for (Device& device : devices_) {  // 用引用遍历，拿到的是容器里的真实对象而不是副本
        if (device.id() == id) {
            return &device;
        }
    }
    return nullptr;
}

void DeviceManager::printAll(std::ostream& os) const {
    if (devices_.empty()) {
        os << "当前没有设备，请先使用“1. 添加设备”创建。\n";
        return;
    }

    os << "共 " << devices_.size() << " 台设备：\n";
    os << padRight("编号", kIdWidth) << padRight("名称", kNameWidth)
       << padRight("所在房间", kRoomWidth) << "状态\n";
    os << std::string(kIdWidth + kNameWidth + kRoomWidth + 6, '-') << "\n";
    for (const Device& device : devices_) {
        os << padRight(device.id(), kIdWidth) << padRight(device.name(), kNameWidth)
           << padRight(device.room(), kRoomWidth) << device.statusText() << "\n";
    }
}

std::size_t DeviceManager::size() const { return devices_.size(); }

bool DeviceManager::empty() const { return devices_.empty(); }

const std::vector<Device>& DeviceManager::devices() const { return devices_; }
