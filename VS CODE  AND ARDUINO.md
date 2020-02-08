# VS CODE  AND ARDUINO

https://docs.microsoft.com/zh-cn/azure/iot-hub/iot-hub-arduino-iot-devkit-az3166-get-started

1. 安装 [Arduino IDE](https://www.arduino.cc/en/Main/Software)。 此 IDE 提供必要的工具链用于编译和上传 Arduino 代码。

   - **Windows**：使用 Windows Installer 版本。 不要从应用商店安装。
   - **macOS**：将解压缩的 **Arduino.app** 拖放到 `/Applications` 文件夹中。
   - **Ubuntu**：解压缩到某个文件夹中，例如 `$HOME/Downloads/arduino-1.8.8`

2. 安装[Visual Studio Code](https://code.visualstudio.com/)是一个跨平台源代码编辑器，其中包含功能强大的 intellisense、代码完成和调试支持以及可从 marketplace 安装丰富的扩展。

3. 启动 VS Code，在扩展市场中找到 **Arduino** 并安装它。 此扩展提供在 Arduino 平台上进行开发的增强体验。

   ![安装 Arduino](https://docs.microsoft.com/zh-cn/azure/iot-hub/media/iot-hub-arduino-devkit-az3166-get-started/getting-started/install-arduino.png)

4. 在扩展市场中找到 [Azure IoT Tools](https://aka.ms/azure-iot-tools) 并安装它。

   ![安装 Azure IoT Tools](https://docs.microsoft.com/zh-cn/azure/iot-hub/media/iot-hub-arduino-devkit-az3166-get-started/getting-started/install-azure-iot-tools.png)

   或使用此直接链接：

   [安装 Azure IoT 工具扩展包](vscode:extension/vsciot-vscode.azure-iot-tools)

    备注

   Azure IoT 工具扩展包包含用于在各种 IoT devkit 设备上进行开发和调试的[Azure Iot 设备工作台](https://aka.ms/iot-workbench)。 Azure iot[中心扩展](https://aka.ms/iot-toolkit)（随附于 Azure iot 工具扩展包）用于管理 Azure iot 中心并与之进行交互。

5. 为 VS Code 配置 Arduino 设置。

   在 Visual Studio Code 中，单击 "**文件" > 首选项 > 设置**（在 macOS 上，**代码 > 首选项 > 设置**）。 然后单击 "*设置*" 页右上角的 "**打开设置（JSON）** " 图标。

   ![安装 Azure IoT Tools](https://docs.microsoft.com/zh-cn/azure/iot-hub/media/iot-hub-arduino-devkit-az3166-get-started/getting-started/user-settings-arduino.png)

   根据你的平台添加以下行来配置 Arduino：

   - Windows：

     JSON复制

     ```json
     "arduino.path": "C:\\Program Files (x86)\\Arduino",
     "arduino.additionalUrls": "https://raw.githubusercontent.com/VSChina/azureiotdevkit_tools/master/package_azureboard_index.json"
     ```

   - **macOS**：

     JSON

     ```json
     "arduino.path": "/Applications",
     "arduino.additionalUrls": "https://raw.githubusercontent.com/VSChina/azureiotdevkit_tools/master/package_azureboard_index.json"
     ```

   - **Ubuntu**：

     将下面的 **{username}** 占位符替换为你的用户名。

     JSON复制

     ```json
     "arduino.path": "/home/{username}/Downloads/arduino-1.8.8",
     "arduino.additionalUrls": "https://raw.githubusercontent.com/VSChina/azureiotdevkit_tools/master/package_azureboard_index.json"
     ```

6. 