#ifndef SMART_HOME_DEVICE_MANAGER_H
#define SMART_HOME_DEVICE_MANAGER_H

#include <cstddef>
#include <iosfwd>
#include <string>
#include <vector>

#include "Device.h"

// 一次操作的结果。用枚举表达"成不成功、失败原因是什么"，
// 类只返回结果代码，具体的中文提示由界面层（main.cpp）负责，做到"业务"与"显示"分离。
enum class Result {
    Ok,           // 成功
    EmptyId,      // 编号为空
    DuplicateId,  // 编号重复
    EmptyName,    // 名称为空
    NotFound      // 找不到该编号的设备
};

// DeviceManager 负责"管理一组设备"：创建、按编号查找、开关控制、列表显示。
// 它持有 std::vector<Device>，是设备对象的容器；所有设备编号的唯一性由它保证。
class DeviceManager {
public:
    // 创建一个设备并放入列表：先校验编号与名称，校验失败则拒绝创建（列表不变）
    Result addDevice(const std::string& id, const std::string& name, const std::string& room);

    // 按编号控制开关：on 为 true 表示开启，false 表示关闭
    Result setPower(const std::string& id, bool on);

    // 按编号查找，找不到返回 nullptr（调用方必须先判断）
    Device* findById(const std::string& id);

    // 列表显示当前全部设备
    void printAll(std::ostream& os) const;

    // ---------- 只读访问（const，供界面层查询） ----------
    std::size_t size() const;
    bool empty() const;
    const std::vector<Device>& devices() const;

private:
    std::vector<Device> devices_;
};

#endif  // SMART_HOME_DEVICE_MANAGER_H
