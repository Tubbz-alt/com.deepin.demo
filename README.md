# Example for Store SDK demo

## 检查依赖
  集成付费SDK，需安装 libdtkpay 和 libdtkpay-dev 动态库，而libdtkpay依赖动态库libdtkcore-dev。

检测安装命令分别为：

```bash
sudo dpkg -s libdtkcore-dev
sudo dpkg -s libdtkpay
sudo dpkg -s libdtkpay-dev
```

如果没有安装，使用如下命令分别进行安装

```bash
sudo apt install libdtkcore-dev
sudo apt install libdtkpay
sudo apt install libdtkpay-dev
```


## 获取应用公钥
  登录开发者后台，创建一个付费应用，获取应用公钥 和 应用ID （例：com.deepin.demo）


## 构造应用项目集成SDK

### 查找集成需要用到的头文件和链接库路径；

```bash
sudo dpkg -L libdtkpay-dev
```

或者使用pkg-config集成付费SDK的相关依赖；

