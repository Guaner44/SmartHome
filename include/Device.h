#ifndef SMART_HOME_DEVICE_H
#define SMART_HOME_DEVICE_H

#include <string>

// Device 表示"一台智能设备"这一实体对象。
// 它只保存自己的属性、只回答关于自己的问题，不负责查找、列表和输入输出，
// 因此可以被单独创建、单独测试，也可以被其它类（如后续的 Room）复用。
class Device {
public:
    // 构造函数：创建设备时必须给出编号、名称、所在房间；新设备一律处于关闭状态。
    Device(const std::string& id, const std::string& name, const std::string& room);

    // ---------- 只读查询（const 成员函数：承诺不修改对象状态） ----------
    const std::string& id() const;       // 设备编号，创建后不允许改变
    const std::string& name() const;     // 设备名称
    const std::string& room() const;     // 所在房间
    bool isOn() const;                   // 是否处于开启状态
    const char* statusText() const;      // 状态的中文描述："开启" / "关闭"

    // ---------- 行为（成员函数修改私有成员，外部无法直接改状态） ----------
    void turnOn();                       // 开启
    void turnOff();                      // 关闭

    // 把一台设备格式化成多行文本，用于"显示单个设备的完整信息"
    std::string toString() const;

private:
    std::string id_;
    std::string name_;
    std::string room_;
    bool on_;
};

#endif  // SMART_HOME_DEVICE_H
