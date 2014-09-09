快速开始
====

## 下载
####选择要下载的版本
- 核心包版本
核心包只有20M左右。它包含了功能强大的quick player，支持从创建工程、开发调试到打包发布的整个过程所需要的主要功能。使用player还能够管理、演示你的工程，以及运行quick丰富的示例等。
如果你不需要在C/C++层面对引擎进行修改或者添加功能模块，核心包完全能够满足开发需求。下载轻巧的核心包，可以让你立刻体会到用quick开发的快捷与方便。
- 源代码版本
如果需要在C/C++层面添加和定制新的功能模块，需要下载完整的源代码版本。它包含平台所有的源码，因此可以进行更深度的开发。你可以从quick的GitHub仓库下载压缩包，也可以直接克隆quick的仓库到本地(推荐)。
源代码版本的体积较大。同时，使用它也需要更多的开发知识，比如，你需要自己打开player的工程进行编译，才能够使用quick player。

####下载地址
请在 https://github.com/dualface/v3quick 上获取最新版本的相关信息。

## 安装与基本配置
####安装
如果下载的是zip压缩包，那么直接将它解压就可以了。唯一要注意的是，不要把平台的主目录直接放在根目录下。(例如，C:\quick-x-v3是错误的，C:\mysdk\quick-x-v3是正确的)
如果是克隆源码仓库，那就没有任何安装过程。不过也要注意仓库不要直接放在根目录下。
####基本配置
需要做一个简单的基本配置来保证后面的正常使用。
Mac: 运行平台目录下的setup_mac.sh
Windows: 运行平台目录下的setup_win.bat
如果是源代码版本，Mac下运行setup_mac.sh时，最后会询问是否需要安装luajit，如果你没有安装过，输入“y”并回车继续吧。
整个配置过程非常快捷。现在，祝贺你，可以开始工作了！

## 启动player
使用player可以让你的工作变得更简单。
player的运行文件在平台目录下。Mac下是player3.app；Windows下是player3.exe。双击运行，就能够看到以下的player主界面：

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/player.png)

如果是源代码版本，需要自己编译player的运行文件。在Mac下使用xcode打开quick/player/proj.mac下的工程；在Windows下使用VS2013打开quick/player/proj.win32下的工程。将工程完整编译一次，平台目录下就会生成player了。当然，你也可以在xode和vs里直接运行和调试player。

## 运行示例
quick提供了丰富的示例，你可以通过player来运行它们。
在player主界面上点击“示例”页，上下滚动查看示例列表，选择需要的示例来运行吧。

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/player_sample.png)

## 创建项目
在player界面上点选“新建项目”：

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/new_proj_create.png)

选择项目存放目录，输入项目的包名，选择屏幕方向，点击“Create Project”创建一个新项目。
![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/new_proj_open.png)

创建完成后，右下角按钮变成“Open ...”，点击可以打开自己的项目了！

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/new_proj_run.png)

## 导入和运行项目
你可以用player来运行自己新建的项目。选择“导入项目”：

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/open_project.png)

选“Open Project”就可以运行自己的项目了。
下一次你进入player时，“我的项目”里会列出你运行过的项目，因此你不需要再重新导入，只需要选中项目，点击“打开”即可运行。

![Alt text](https://raw.githubusercontent.com/dualface/v3quick/v3quick/docs/howto/get-started/res/my_projects.png)

