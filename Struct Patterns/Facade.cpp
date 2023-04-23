#include <iostream>
#include <stdlib.h>
#include <string>

// 语法分析子系统
class CSyntaxParser {
public:
    void SyntaxParser(std::string defaultSignal) {
        std::cout << defaultSignal << " Syntax Parser" << std::endl;
    }
};

// 生成中间代码子系统
class CGenMidCode {
public:
    void GenMidCode(std::string defaultSignal) {
        std::cout << defaultSignal << " Generate middle code" << std::endl;
    }
};

// 生成汇编代码子系统
class CGenAssemblyCode {
public:
    void GenAssemblyCode(std::string defaultSignal) {
        std::cout << defaultSignal << " Generate assembly code" << std::endl;
    }
};

// 链接生成可执行应用程序或库子系统
class CLinkSystem {
public:
    void LinkSystem(std::string defaultSignal) {
        std::cout << defaultSignal << " Link System" << std::endl;
    }
};

class Facade {
public:
    void Compile(std::string defaultSignal = "action") {
        CSyntaxParser    syntaxParser;
        CGenMidCode      genMidCode;
        CGenAssemblyCode genAssemblyCode;
        CLinkSystem      linkSystem;

        syntaxParser.SyntaxParser(defaultSignal);
        genMidCode.GenMidCode(defaultSignal);
        genAssemblyCode.GenAssemblyCode(defaultSignal);
        linkSystem.LinkSystem(defaultSignal);
    }
};

// 客户端
int main() {
    Facade facade;
    facade.Compile();

    return EXIT_SUCCESS;
}
