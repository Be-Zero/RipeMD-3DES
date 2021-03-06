# Ripemd-3DES

## 一、概述

该系统为本人的毕业设计，简单来讲就是实现了对任意大小、类型文件利用 3DES 算法进行加解密操作的算法系统，开发环境为Windows，采用C++语言编写，开发工具为 CLion ，图形界面设计的部分使用了 Qt Creator 。

系统的头文件在 Header 文件夹中，源文件在 Source 文件夹中，交互界面的部分文件在 SystemUI 文件夹中。

### 1. 该系统的完整功能流程如下：

* 接收待加解密文件的**路径**以及用户**密钥**；
* 使用 Ripemd-256 算法对用户密钥进行杂凑，得出 128 位应用密钥；
* 按文件路径读取文件并填充至8字节的倍数（ 3DES 算法要求）；
* 选定工作模式，将文件分组进行处理；
* 使用 3DES 算法对得到的每个分组进行处理；
* 将加工后的数据写入新生成的文件。

### 2. 系统展示：

* 初始界面：

  ![初始界面](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E5%88%9D%E5%A7%8B%E7%95%8C%E9%9D%A2.png)

* 选定文件路径：

  ![选定文件路径](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E9%80%89%E5%AE%9A%E6%96%87%E4%BB%B6%E8%B7%AF%E5%BE%84.png)

* 输入用户密钥并单击 Save ：

  ![输入用户密钥并单击Save](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E8%BE%93%E5%85%A5%E7%94%A8%E6%88%B7%E5%AF%86%E9%92%A5%E5%B9%B6%E5%8D%95%E5%87%BBSave.png)

* 选择工作模式：

  ![选择工作模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E9%80%89%E6%8B%A9%E5%B7%A5%E4%BD%9C%E6%A8%A1%E5%BC%8F.png)

* 加密：

  ![加密](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E5%8A%A0%E5%AF%86.png)

* 解密：

  ![解密](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E8%A7%A3%E5%AF%86.png)

* 打开文件：单击 Open 按钮即可打开文件目录。

* 无效文件路径测试：

  ![无效文件路径](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E6%97%A0%E6%95%88%E6%96%87%E4%BB%B6%E8%B7%AF%E5%BE%84.png)

* 空密钥测试：

  ![空密钥Save](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E7%A9%BA%E5%AF%86%E9%92%A5Save.png)

### 3. 系统使用方法：

* 使用 Qt Creator 编译该项目并运行即可；
* 或将 main.cpp 文件内容注释，Run.cpp 文件内容反注释，运行 Run.cpp 文件可对代码性能进行测试。

## 二、模块设计

### 1. Key 模块：

### ![Key模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/Key%E6%A8%A1%E5%9D%97.png)

Key 模块是专门用来处理密钥的模块，获取用户密钥时使用 string 类型进行传值，然后对其应用 Ripemd-256 算法进行杂凑，得到 128 位的新密钥，然后依据 3DES 算法的规则，将新密钥处理为 2 组 16 × 48 的子密钥，算法流程图部分如下：

![3DES算法流程图](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/3DES%E7%AE%97%E6%B3%95%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

### 2. TripleDes 模块：

### ![TripleDes模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/TripleDes%E6%A8%A1%E5%9D%97.png)

TripleDes 模块是用来对一个分组（64bit）进行加密解密操作的函数，由 OPMode 模块负责调用，算法流程图部分如下：

![3DES算法流程图](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/3DES%E7%AE%97%E6%B3%95%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

### 3. RIPEMD-256 模块：

![RIPEMD-256模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/RIPEMD-256%E6%A8%A1%E5%9D%97.png)

RIPEMD-256 模块是用来对用户密钥进行杂凑的函数，由 Key 模块调用，最终生成 256 位杂凑值，本系统选取其前 128 位作为 3DES 算法的实际密钥，算法流程图如下：

![RIPEMD-256算法流程图](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/RIPEMD-256%E7%AE%97%E6%B3%95%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

### 4. OPMode 模块：

![OPMode模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/OPMode%E6%A8%A1%E5%9D%97.png)

OPMode 模块用来完成不同的工作模式，由 System_UI 模块直接调用，不同的工作模式特点如下：

* ECB 模式：

  ECB 模式（电子密码本模式），是最简单的分组密码工作模式，其原理是将原始信息进行分组后，对每一个分组进行相同的加解密操作，因此各分组之间没有联系。ECB 工作模式的原理如图所示：

  ![ECB模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/ECB%E6%A8%A1%E5%BC%8F.png)

  由于 ECB 模式各分组之间没有联系，不能隐藏数据的工作模式，难以保证系统的安全性，因此在实际应用情境中，ECB 模式通常不被使用。但也正因为这样的特性，ECB 模式支持并行工作。

* CBC 模式：

  CBC 模式（密码分组链接模式），需要设定一个初始向量 IV，将初始向量与第一个原始信息分组进行异或操作后再进行加密操作，得到第一个分组的密文。然后使用该密文作为后续组的初始向量 IV，依次进行相同操作即可完成加密。解密操作与加密操作刚好相反，首先对第一个分组解密后再与初始向量 IV 进行异或操作，得到第一个分组的明文。然后使用得出的明文作为后续组的初始向量 IV，依次进行相同的操作即可完成解密。CBC 工作模式的原理如图所示：

  ![CBC模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/CBC%E6%A8%A1%E5%BC%8F.png)

  从图中可以发现，CBC 模式的加密过程中每个分组会用到前一个分组加密处理后的结果，因此不支持并行工作。而解密过程由于使用的是前一个分组的密文，因此支持并行工作。

* CFB 模式：

  CFB 模式（密文反馈模式），与 CBC 模式的逆过程十分相似，主要区别在于CFB模式是对初始向量进行加密处理后再与明文块做异或操作。值得注意的是由于该模式加解密处理的是初始向量，因此再解密操作中需要对初始向量进行加密而不是解密。该模式的特点是能够将块密码转换为自同步的流密码。CFB 工作模式的原理如图所示：

  ![CFB模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/CFB%E6%A8%A1%E5%BC%8F.png)

  从图中可以发现，与 CBC 模式相似，CFB 模式的加密过程中每个分组会用到前一个分组加密处理后的结果，因此不支持并行工作。而解密过程由于使用的是前一个分组的密文，因此支持并行工作。

* OFB 模式：

  OFB 模式（输出反馈模式），与 CFB 模式相似，主要区别在于 OFB 模式中每个分组使用的是前一个分组进行加密操作后的块，而不是进行异或操作后的块。该模式的解密操作也是如此，并不是使用前一分组的密文进行处理。OFB 工作模式的原理如图所示：

  ![OFB模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/OFB%E6%A8%A1%E5%BC%8F.png)

  从图中可以发现，由于 OFB 模式在加解密过程中均需要使用到前一分组处理后的块，因此加解密操作均不支持并行工作。

* CTR 模式：

  CTR 模式（计数器模式），与 ECB 模式类似，主要区别在于 CTR 模式为每个分组设定了计数器，首先对计数器进行加解密处理，然后再与明（密）文进行异或操作。CTR 工作模式的原理如图所示：

  ![CTR模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/CTR%E6%A8%A1%E5%BC%8F.png)

  从图中可以发现，由于 CTR 模式每个分组都是独立的，因此可以进行并行工作。

* PCBC 模式：

  PCBC 模式（填充密码块链接模式），是 CBC 模式的加强版，主要区别在于PCBC 模式每一分组并未直接使用前一分组加密处理后的密文，而是将其与明文先进行异或操作后再使用。解密操作同理，也是先将前一分组的密文与解密处理后的明文进行异或操作后再使用。PCBC 工作模式的原理如图所示：

  ![PCBC模式](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/PCBC%E6%A8%A1%E5%BC%8F.png)

  从图中可以发现，PCBC 模式优化了 CBC 模式中解密操作各分组联系薄弱的问题，使得相邻密文块不会对后续块的解密造成影响，因此不支持并行工作。

### 5. File_IO 模块

![File_IO模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/File_IO%E6%A8%A1%E5%9D%97.png)

File_IO 模块主要实现了对任意大小、类型的文件进行读写操作的功能，由 OPMode 模块负责调用，提供了读取文件大小的接口。

### 6. System_UI 模块：

![SystemUI模块](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/SystemUI%E6%A8%A1%E5%9D%97.png)

System_UI 模块主要是构造交互界面的类，还负责将前面六个类的功能进行整合，使得系统完整可靠，整个系统的工作流程如下：

![系统执行流程图](https://github.com/Be-Zero/RipeMD-3DES/blob/main/README/%E7%B3%BB%E7%BB%9F%E6%89%A7%E8%A1%8C%E6%B5%81%E7%A8%8B%E5%9B%BE.png)

## 三、问题与改进

本系统虽然较为完整，但在开发过程中还是因为没有做好模块及接口的设计导致出现了许多问题，而在后续文档的编写过程中同样遇到了一些困难，本小节对此进行记录：

### 1. 系统设计的问题

系统在最开始的开发阶段为了实现方便，将二进制串用 string 类型进行记录，各模块之间数据的传递竟然没有用地址传递，结果导致第一个版本执行效率巨慢，为提高效率浪费了大把时间进行系统优化，最终还是采用了二进制处理的方式。

对于各模块的接口设计也不够好，特别是在实现文件读写操作的过程中，没有将其按分组进行读写处理，而是先将文件全部进行读写后再进行分组，导致系统实际上能够加解密的文件大小无法超过内存限制，还导致 QT 界面的进度条没能实现。

该系统还可以对 CTR 、ECB 等工作模式采用多线程并行工作的方式进行优化，QT 交互界面也可以采用多线程的方式来解决系统加解密时卡死的问题。

### 2. C++ 不同版本的问题

若将 3DES 算法中的置换表写在头文件中，需要借助 C++ 17 中的 constexpr 来进行定义，或是在 cpp 文件中对数据进行初始化，否则会报错。

### 3. QT 生成可执行文件

**方法一**：配置系统的环境变量路径（path），例如我的是：`D:\QT\5.5\msvc2013_64\bin`

**方法二**：发布程序

* 在 QT 中选择 release 进行构建，得到 exe 文件；
* 把该 exe 文件单独拷贝到一个空文件夹；
* 打开（搜索找到） QT 的桌面（Desktop）版，进入 exe 程序所在目录；
* 输入命令：`windeployqt`；
* 运行 exe 文件即可。

### 4. gitignore 文件失效的问题

使用 `git rm --cached 文件路径`命令来 Untrack 文件。

