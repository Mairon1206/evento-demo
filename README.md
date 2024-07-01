<div align=center>
    <img width=64 src="app_icon.svg">
</div>

<h1 align=center>Evento Demo</h1>

<p align="center">
    <img src="https://img.shields.io/badge/license-MIT-blue.svg">
    <img src="https://img.shields.io/badge/gui-slint-blueviolet">
    <img src="https://img.shields.io/badge/lang-C%2B%2B20-yellow.svg">
    <img src="https://img.shields.io/badge/platform-windows%20%7C%20macos%20%7C%20linux-lightgreen.svg">
</p>

## 简介

Evento Demo是为重构[SAST Evento Desktop](https://github.com/NJUPT-SAST/SAST-Evento-Desktop)所准备的一个最小开发环境，包括项目大纲。

GUI框架选用[Slint](https://slint.dev/), 网络部分选用Boost库，核心为[Boost.Beast](https://www.boost.org/doc/libs/1_85_0/libs/beast/doc/html/index.html)。

与[SAST LINK](https://github.com/NJUPT-SAST/sast-link-backend)交互的逻辑由[sast-link-cxx-sdk](https://github.com/Serein207/sast-link-cxx-sdk)完成。

> [!WARNING]
>
> 这仍然是一个早期版本，并非最终版，项目结构可能会变动

克隆仓库请使用以下命令：
```shell
git clone --recursive https://github.com/Mairon1206/evento-demo.git
```

## 环境与依赖
要想构建该项目，请确保你已配置好以下环境:

- 支持C++20或更高版本的编译器
- CMake 3.21 或更高版本
- Rust 工具链
- Vcpkg

项目使用Vcpkg进行跨平台包管理，主要依赖项:

- [Boost.Beast](https://github.com/boostorg/beast)
- [Boost.Url](https://github.com/boostorg/url)
- [Boost.System](https://github.com/boostorg/system)
- [OpenSSL](https://github.com/openssl/openssl)
- [Spdlog](https://github.com/gabime/spdlog)
- [Nlohmann-Json](https://github.com/nlohmann/json)
- [GoogleTest](https://github.com/google/googletest)

GUI框架:

- [Slint](https://github.com/slint-ui/slint)