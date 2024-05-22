要使用GDB调试compilerlab3，你需要确保你的程序是以调试模式编译的。这通常意味着在编译命令中包含-g选项，例如g++ -g -o compilerlab3 compilerlab3.cpp。

然后，你可以使用以下步骤来调试你的程序：

1. 启动GDB：在命令行中输入gdb ./compilerlab3来启动GDB并加载你的程序。

2. 设置断点：如果你知道你想在哪里暂停你的程序，你可以设置一个断点。例如，如果你想在compilerlab3.cpp的第655行设置断点，你可以输入break compilerlab3.cpp:655。

3. 运行程序：输入run ./test_input_2.txt来运行你的程序。当程序到达断点时，它将会暂停。

4. 单步运行和查看变量：现在你可以使用next、step、print等命令来单步运行你的程序和查看变量的值。

5. 继续运行：当你想继续运行你的程序时，输入continue。

6. 退出GDB：当你完成调试并想退出GDB时，输入quit。

以上就是使用GDB调试compilerlab3的基本步骤。如果你需要更详细的信息，你可以查看GDB的官方文档。

在GDB中，print命令默认只显示字符串的前200个字符。如果你想查看更长的字符串，你可以使用set print elements命令来增加这个限制。例如，set print elements 0将会移除这个限制，允许你打印整个字符串。

在你的GDB会话中，你可以输入以下命令来移除这个限制：

```cmd
set print elements 0
```

然后，你可以再次使用print命令来打印assemblyCode的值：

```cmd
print assemblyCode
```

这应该会显示assemblyCode的完整值